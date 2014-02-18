using System.IO;
using System.Linq;
using System.Reflection;
using System.Xml.Linq;

namespace WPC43_Bank_Card_Validation
{
    public enum IINResult 
    { 
        ValidIIN, 
        ValidIINButInactive, 
        InvalidIIN, 
        ValidIINButNoLuhnValidation, 
        ValidIINButIncorrectCardNumberLength 
    };

    /// <summary>
    /// Checks if the IIN prefix of the card number (the PAN) is valid or not.
    /// </summary>
    public class IIN
    {
        private XDocument iinDoc;

        public IIN()
        {
            Assembly ourAssembly = Assembly.GetExecutingAssembly();
            string resource = "WPC43_Bank_Card_Validation.IINLookup.xml";

            using (Stream stream = ourAssembly.GetManifestResourceStream(resource))
            {
                iinDoc = XDocument.Load(stream);
            }
        }

        public string GetIINIssuer(string cardNumber, out IINResult result)
        {
            // Get the list of range elements and sort them into "from" value descending
            // order.  This ensures we pick up values that start with 5020 before those that
            // start with 500 and before those that start with 50.
            var ranges = from e in iinDoc.Descendants("range")
                         orderby e.Attribute("from").Value descending
                         select e;
            
            // Scan through each range looking for a "from" value that matches the initial
            // digits of card number.  If we find a match, it's a possible IIN candidate.
            foreach (XElement range in ranges)
            {
                // Read the validation data from the range element.
                string from = range.Attribute("from").Value;
                string to = range.Attribute("to").Value;
                bool isActive = bool.Parse(range.Attribute("active").Value);
                bool useLuhnValidation = bool.Parse(range.Attribute("luhn").Value);
                string validCardLength = range.Attribute("length").Value;
                string issuer = range.Attribute("issuer").Value;

                // There can be several valid lengths of card number so parse the
                // comma seperator list into an array so we can check against it.
                // Note - the valid lengths may not be a contiguous set of values so we
                // can't just check the card length to see if it's within min and max limits.
                string[] validLengths = validCardLength.Split(new char[] { ',' });
                int[] validNoOfDigits = new int[validLengths.Length];
                for (int i = 0; i < validLengths.Length; i++)
                {
                    validNoOfDigits[i] = int.Parse(validLengths[i]);
                }

                // Do we have a "to" value?
                if (to.Trim().Length == 0)
                {
                    // No, so check against just the "from" value.
                    int lengthOfFrom = from.Length;
                    if (cardNumber.Substring(0, lengthOfFrom) == from)
                    {
                        // This range is potentially valid for the card number.
                        // Check that the card number length matches the list of valid lengths.
                        bool isValidLength = IsCardNumberlengthValid(cardNumber, validNoOfDigits);
                        if (isValidLength)
                        {
                            if (isActive)
                            {
                                if (useLuhnValidation)
                                    result = IINResult.ValidIIN;
                                else
                                    result = IINResult.ValidIINButNoLuhnValidation;
                                return issuer;
                            }
                            else
                            {
                                result = IINResult.ValidIINButInactive;
                                return string.Empty;
                            }
                        }
                        else
                        {
                            result = IINResult.ValidIINButIncorrectCardNumberLength;
                            return string.Empty;
                        }
                    }
                }
                else
                {
                    // Yes we have a "to" value, so We have a range of IINs to test against.
                    int lengthOfFrom = from.Length;
                    int fromNumber = int.Parse(from);
                    int toNumber = int.Parse(to);
                    int cardNumberIIN = int.Parse(cardNumber.Substring(0, lengthOfFrom));
                    if (cardNumberIIN >= fromNumber && cardNumberIIN <= toNumber)
                    {
                        // This range is potentially value for the card number.
                        bool isValidLength = IsCardNumberlengthValid(cardNumber, validNoOfDigits);
                        if (isValidLength)
                        {
                            if (isActive)
                            {
                                if (useLuhnValidation)
                                    result = IINResult.ValidIIN;
                                else
                                    result = IINResult.ValidIINButNoLuhnValidation;
                                return issuer;
                            }
                            else
                            {
                                result = IINResult.ValidIINButInactive;
                                return string.Empty;
                            }
                        }
                        else
                        {
                            result = IINResult.ValidIINButIncorrectCardNumberLength;
                            return string.Empty;
                        }
                    }
                }
            }

            // The card number doesn't start with a valid value so return no issuer.
            result = IINResult.InvalidIIN;
            return string.Empty;
        }

        private bool IsCardNumberlengthValid(string cardNumber, int[] validLengths)
        {
            // It is if the length of the card number is present in the array of valid lengths.
            int cardLength = cardNumber.Length;
            return validLengths.Contains(cardLength);
        }
    }
}
