using System;
using System.Collections.Generic;
using System.IO;

namespace WPC44_ECG_Heartbeat_Detection
{
    /// <summary>
    /// Problem:
    /// We all have seen how ECG looks stylized, in real life there is usually lot of noise 
    /// add to this signal.
    /// 
    /// For today’s Challenge I asked one of our employee – Penko to connect himself to 
    /// EEG-SMT and to stay calm so his ECG signal is captured on file. This file is already 
    /// upload to GitHub and you can use as input data.
    /// 
    /// https://github.com/OLIMEX/WPC/tree/master/ISSUE-44
    ///
    /// Make code which detect the heart rate using this raw signal info.
    /// Description of the data packages is also upload on Github.
    /// </summary>
    /// 
    /// <remarks>
    /// Packet Format Version 2
    ///
    /// 17-byte packets are transmitted from the ModularEEG at 256Hz,
    /// using 1 start bit, 8 data bits, 1 stop bit, no parity, 57600 bits per second.
    ///
    /// struct modeeg_packet
    /// {
    ///     uint8_t sync0;      // = 0xA5
    ///     uint8_t sync1;      // = 0x5A
    ///     uint8_t version;    // = 2
    ///     uint8_t count;      // packet counter. Increases by 1 each packet.
    ///     uint16_t data[6];   // 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
    ///     uint8_t switches;   // State of PD5 to PD2, in bits 3 to 0.
    /// };
    /// 
    /// Or in other words:
    /// 
    /// ======== ======= ======= ========= ========= ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ==========
    /// Bytes   |  0xA5 |  0x5A |   0x02  |   0xXX  | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX | 0xXX |   0xXX   |
    /// ======== ======= ======= ========= ========= ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ==========
    /// Meaning | sync0 | sync1 | version | Counter |  Data Ch 0  |  Data Ch 1  |  Data Ch 2  |  Data Ch 3  |  Data Ch 4  |  Data Ch 5  | switches |
    /// ======== ======= ======= ========= ========= ============= ============= ============= ============= ============= ============= ==========
    /// 
    /// </remarks>
    class Program
    {
        /// <summary>
        /// The name of the input file containing the EEG-SMT data.
        /// </summary>
        const string ecgSampleFilename = "ecgsample.txt";

        /// <summary>
        /// The name of the output file where we'll write the data from each channel,
        /// 1 column for each channel.  This can easilly be pulled into Excel for charting.
        /// </summary>
        const string csvFilename = "ChannelData.csv";

        /// <summary>
        /// The ECG trace for a heartbeat has a sudden movement on each heartbeat.
        /// To detect a heartbeat, we detect when there's a sudden movement in the ECG trace
        /// and record that sample's index.  The heartbeat is the time interval between any 2 
        /// consecutive sudden movements.
        /// <para/>
        /// This value acts like a noise filter.
        /// - Lower values (e.g. 100) will give you false positive heartbeats.
        /// - High values (e.g 800) will give you no heartbeats at all.
        /// - For this data, any value between 200 and 500 will give you the same 
        ///   calculated heartbeats.
        /// </summary>
        const int differentialThreshold = 300;

        /// <summary>
        /// The maximum heart rate we can detect.  Anything over this will be rejected as
        /// a viable heartrate.
        /// </summary>
        const int maximumPossibleHeartRateBPM = 250;

        /// <summary>
        /// The rate at which readings were gathered in Hz, e.g. 256Hz.
        /// </summary>
        const int samplingRateHz = 256;

        /// <summary>
        /// Where all the action happens!
        /// </summary>
        /// <param name="args">None but the above constants could be parameterized.</param>
        static void Main(string[] args)
        {
            // Read the data from the input file.  We read the whole file here, which is OK on a PC,
            // but it would need refactoring to read blocks at a time on an embedded system.
            string ecgStream = OpenInputFile(ecgSampleFilename);

            // Convert the text stream into a list of ECG packet objects
            List<ModeECGPacket> packets = ParseECGStream(ecgStream);

            // Convert the ECG data values for each channel into an array.  This makes it easier
            // to analyse.
            Measurements channels = new Measurements(packets);

            // Output to csv file for analysis.  This isn't really necessary but it's quick to 
            // produce a chart in Excel.
            WriteToLogFile(channels, csvFilename);

            // Detect heartrates from the channel data.
            List<double> heartrates = GetHeartrates(channels);

            // Display our findings to the user.
            ReportFindings(heartrates);

            // Keep the console up so the user has a chance to read the heartbeats found.
            Console.ReadLine();
        }

        /// <summary>
        /// Display the heartbeats we've calculated from the data.
        /// </summary>
        /// <param name="heartrates">The list of heartbeats in beats/minute.</param>
        private static void ReportFindings(List<double> heartrates)
        {
            Console.WriteLine("Heartrates found (beats/minute)");
            Console.WriteLine("-------------------------------");
            if (heartrates != null && heartrates.Count > 0)
            {
                for (int i = 0; i < heartrates.Count; i++)
                {
                    Console.WriteLine("{0}", heartrates[i].ToString("0.00"));
                }
            }
            else
            {
                Console.WriteLine("No heartbeats calculated; try reducing the differential threshold.");
            }
            Console.WriteLine();
            Console.WriteLine("Press a key to quit...");
        }

        /// <summary>
        /// Work out what heartrates we can from the channel data.  At this point, we don't
        /// know which channel contains viable data.  Here we take a look at how the data fluctuates
        /// and if it's more than a differential threshold, we take it that this channel is the
        /// one containing the ECG data.  With the sample file of data, there's only one channel
        /// of data (channel 0 actually); all others are flat-liners so presumably the test 
        /// subjects on channels 1 to 5 are deceased!  Oh no, call the doc...  :-)
        /// </summary>
        /// <param name="channels">The data from all channels.</param>
        /// <returns>The list of heartrates that have been calculated.</returns>
        private static List<double> GetHeartrates(Measurements channels)
        {
            // We'll store the indices of readings in here.
            List<int> intervals = new List<int>();

            // Go through each of the channels to detect one that contains data.
            for (int channel = 0; channel < Measurements.ChannelsOfData; channel++)
            {
                UInt16 currentReading = 0;
                UInt16 previousReading = channels.Readings[0, channel];

                for (int reading = 1; reading < channels.Readings.GetUpperBound(0); reading++)
                {
                    currentReading = channels.Readings[reading, channel];
                    UInt16 differential = (UInt16)Math.Abs(currentReading - previousReading);
                    if (differential > differentialThreshold)
                    {
                        intervals.Add(reading);
                    }
                    previousReading = currentReading;
                }

                // If we have at least 2 values, we have an interval so we can calculate a
                // heartrate.  It may be that the interval between them is too small though.
                if (intervals.Count >= 2) break;
            }

            // If we haven't detected any suitable channel of data, we can't calculate the
            // heartrates.
            if (intervals.Count == 0) return null;

            // Calculate heartrates from the intervals we've recorded.
            List<double> heartrates = new List<double>();
            int interval1 = intervals[0];
            for (int i = 1; i < intervals.Count; i++)
            {
                int interval2 = intervals[i];
                double rate = 60 / (((double)(interval2 - interval1)) / samplingRateHz);
                if (rate < maximumPossibleHeartRateBPM)
                {
                    heartrates.Add(rate);
                }
                interval1 = interval2;
            }

            return heartrates;
        }

        /// <summary>
        /// Write the measurement data into a CSV file with 1 column for each channel of data.
        /// </summary>
        /// <param name="channels">The channels of data.</param>
        /// <param name="csvFilename">The name of the output file.</param>
        private static void WriteToLogFile(Measurements channels, string csvFilename)
        {
            string filepath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, csvFilename);
            StreamWriter csvOutput = new StreamWriter(filepath);

            for (int channel = 0; channel < Measurements.ChannelsOfData; channel++)
            {
                for (int reading = 0; reading < channels.Readings.GetUpperBound(0); reading++)
                {
                    csvOutput.WriteLine("{0},{1},{2},{3},{4},{5}",
                        channels.Readings[reading, 0],
                        channels.Readings[reading, 1],
                        channels.Readings[reading, 2],
                        channels.Readings[reading, 3],
                        channels.Readings[reading, 4],
                        channels.Readings[reading, 5]);
                }
            }
            csvOutput.Close();
        }

        /// <summary>
        /// Parses a string of ECG data into a list of ECG packet objects.
        /// </summary>
        /// <param name="ecgStream">The string of ECG data</param>
        /// <returns>A list containing the packets of ECG data.</returns>
        private static List<ModeECGPacket> ParseECGStream(string ecgStream)
        {
            List<ModeECGPacket> packets = new List<ModeECGPacket>();

            int byteIndex = 0;
            while (byteIndex < ecgStream.Length)
            {
                string packetValues = ecgStream.Substring(byteIndex, ModeECGPacket.ECGPacketHexTextLength);
                ModeECGPacket packet = new ModeECGPacket(packetValues);
                packets.Add(packet);
                byteIndex += ModeECGPacket.ECGPacketHexTextLength;
            }

            return packets;
        }

        /// <summary>
        /// Open a text file and read the entirety of its contents.
        /// </summary>
        /// <returns>The text as a string.</returns>
        private static string OpenInputFile(string filename)
        {
            string filepath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename);
            StreamReader input = new StreamReader(filepath);
            return input.ReadToEnd();
        }
    }
}
