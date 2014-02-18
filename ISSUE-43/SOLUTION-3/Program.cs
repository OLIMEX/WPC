using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC43_Bank_Card_Validation
{
    /// <summary>
    /// Problem:
    /// Bank card numbers are not random, they carry information for the card processor 
    /// (Visa/Mastercard etc), bank which issued the card, the account and checksum.
    /// 
    /// More on the subject is available at http://en.wikipedia.org/wiki/Bank_card_number
    /// 
    /// Make code which enters card number and validate it i.e. writes VALID or INVALID 
    /// number has been entered.
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            IIN iins = new IIN();

            while (true)
            {
                // Get the card number from the user.
                Console.Write("Enter a card number (press Q to quit) : ");
                string cardNumber = Console.ReadLine();

                // Do we want to quit?
                if (cardNumber.ToLower() == "q") break;

                // Skip if no card number was entered.
                if (cardNumber.Trim().Length == 0) continue;

                bool isLuhnValid = false;

                // Check the IIN against the valid list.
                IINResult result;
                string issuer = iins.GetIINIssuer(cardNumber, out result);
                if (issuer.Length > 0)
                {
                    // If it's appropriate to do the Luhn validation, 
                    // do it.  Otherwise just say that it's valid.
                    if (result != IINResult.ValidIINButNoLuhnValidation)
                        isLuhnValid = Luhn.Modulus10Check(cardNumber);
                    else
                        isLuhnValid = true;
                }

                // Display the result.
                if (issuer.Length > 0 && isLuhnValid)
                {
                    Console.WriteLine("VALID   Card number {0} is a valid card number.  Issuer = {1}.", cardNumber, issuer);
                }
                else
                {
                    if (issuer.Length == 0)
                    {
                        if (result == IINResult.InvalidIIN)
                            Console.WriteLine("INVALID Card number {0} - IIN check failed.", cardNumber);
                        else if (result == IINResult.ValidIINButInactive)
                            Console.WriteLine("INVALID Card number {0} - Valid IIN but inactive.", cardNumber);
                        else
                            Console.WriteLine("INVALID Card number {0} - Valid IIN but card number wrong length.", cardNumber);
                    }
                    else
                        Console.WriteLine("INVALID Card number {0} - Luhn check failed.", cardNumber);
                }
                string dash = string.Empty.PadLeft(99, '-');
                Console.WriteLine(dash);
            }
        }
    }
}
