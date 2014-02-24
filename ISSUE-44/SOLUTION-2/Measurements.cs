using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC44_ECG_Heartbeat_Detection
{
    public class Measurements
    {
        /// <summary>
        /// The number of channels of data produced by the EEG-SMT device.
        /// </summary>
        public const int ChannelsOfData = 6;

        /// <summary>
        /// Data values sampled from the EEG-SMT device for all channels.<para/>
        /// The first element is the reading index; the second element is the channel index.
        /// </summary>
        public UInt16[,] Readings { get; private set; }

        /// <summary>
        /// Populates the Readings array with the data readings held in the packets list.
        /// </summary>
        /// <param name="packets"></param>
        public Measurements(List<ModeECGPacket> packets)
        {
            Readings = new UInt16[packets.Count, ChannelsOfData];

            // Fill the Readings array with the data from each channel.
            for (int i = 0; i < packets.Count; i++)
            {
                for (int channel = 0; channel < ChannelsOfData; channel++)
                {
                    Readings[i, channel] = packets[i].Data[channel];
                }
            }
        }
    }
}
