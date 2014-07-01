using System;

namespace WPC59_Big_Little_Endian
{
    class Program
    {
        static void Main(string[] args)
        {
            // Method 1 using unmanaged .NET code
            Console.WriteLine("Method 1 using .Net C# code");
            Console.WriteLine("----------------------------");

            Int32 testValue = 0x0201;
            Console.WriteLine("Writing hex value 0x{0:X} to memory", testValue);

            unsafe
            {
                Int32* myInt32Pointer = &testValue;
                Console.WriteLine("Address pointed to by myInt32Pointer = 0x{0:X}", (Int64)myInt32Pointer);

                byte* myBytePointer = (byte*)myInt32Pointer;
                byte byteValue = *myBytePointer;
                Console.WriteLine("First  byte in memory = 0x{0:X}", *myBytePointer);
                Console.WriteLine("Second byte in memory = 0x{0:X}", *(myBytePointer+1));

                if (byteValue == 1)
                {
                    Console.WriteLine("System is therefore Little Endian");
                }
                else
                {
                    Console.WriteLine("System is therefore Big Endian");
                }

                Console.WriteLine();
            }

            // Method 2 using a .NET method
            Console.WriteLine("Method 2 using .Net method");
            Console.WriteLine("----------------------------");
            Console.WriteLine("System is {0} Endian", BitConverter.IsLittleEndian ? "Little" : "Big");

            Console.Read();
        }
    }
}
