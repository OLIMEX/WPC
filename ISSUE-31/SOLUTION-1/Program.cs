using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace $safeprojectname$
    {
    class Program
        {
        static void Main(string[] args)
            {
            Console.WriteLine("Enter $safeprojectname$ String (i.e. WWWWBBBWWW)");
            string sInput = Console.ReadLine();
            char[] cInput = sInput.ToCharArray();

         
            if (sInput=="")  {
                return;

                }


            int cur_count=0;
            char cur_Char = cInput[0];
            foreach (char iChar in cInput)
                {
                if (iChar == cur_Char)
                    {
                    cur_count++;
                    }
                else
                    {
                    Console.Write(cur_count.ToString() + cur_Char);
                    cur_count = 1;
                    cur_Char = iChar;
                    }
                }
            Console.Write(cur_count.ToString() + cur_Char);

            Console.ReadLine();






            }
        }
    }
