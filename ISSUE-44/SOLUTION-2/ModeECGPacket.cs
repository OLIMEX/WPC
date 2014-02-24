using System;
namespace WPC44_ECG_Heartbeat_Detection
{
    public class ModeECGPacket
    {
        /// <summary>
        /// The number of hex characters in each packet of data (17 * 2 bytes).
        /// </summary>
        public const int ECGPacketHexTextLength = 34;

        /// <summary>
        /// Sync value.  Should always be 0xA55A (42330).
        /// </summary>
        public UInt16 Sync { get; set; }

        /// <summary>
        /// Version number.  Should always be 2.
        /// </summary>
        public byte Version { get; set; }

        /// <summary>
        /// Packet counter.  Increases by 1 for each packet.
        /// </summary>
        public byte Count { get; set; }

        /// <summary>
        /// 10-bit sample (= 0..1023) in big endian (Motorola) format.
        /// </summary>
        public UInt16[] Data { get; set; }

        /// <summary>
        /// State of PD5 to PD2, in bits 3 to 0.
        /// </summary>
        public byte Switches { get; set; }

        /// <summary>
        /// Has the object been fully populated with values?  This will be false if we're passed a
        /// partial packet of ECG data.
        /// </summary>
        public bool IsValid { get; private set; }

        /// <summary>
        /// Construct the packet object by parsing the values from the text.
        /// </summary>
        /// <param name="packetText"></param>
        public ModeECGPacket(string packetText)
        {
            // If we don't have sufficient text to populate a full object, don't bother trying.
            if (packetText.Length != ECGPacketHexTextLength) IsValid = false; ;

            // Parse the text parts into the object properties.
            int index = 0;
            Sync = Convert.ToUInt16(packetText.Substring(index, 4), 16);
            index += 4;
            Version = Convert.ToByte(packetText.Substring(index, 2), 16);
            index += 2;
            Count = Convert.ToByte(packetText.Substring(index, 2), 16);
            index += 2;
            
            Data = new UInt16[6];
            for (int i = 0; i < 6; i++)
            {
                Data[i] = Convert.ToUInt16(packetText.Substring(index, 4), 16);
                index += 4;
            }

            Switches = Convert.ToByte(packetText.Substring(index, 2), 16);

            // Indicate that the object is now fully populated.
            IsValid = true;
        }
    }
}
