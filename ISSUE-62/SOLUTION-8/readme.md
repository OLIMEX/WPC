

Programmed in Java. Here's a Pastebin of it incase the email screws up
formatting: http://pastebin.com/Hi227Uvg

Here is the entire class needed:

public class Main {

    public static void main(String[] args)
    {
        long startTime = System.nanoTime();
        long endTime;

        getNonZeroMultipliers(1000000);

        endTime = System.nanoTime();
        System.out.println(endTime-startTime);
    }

    public static void getNonZeroMultipliers(double number)
    {
        double quotient;
        int quotientl;

        short digitCount;

        boolean valid;
        for(int i = 1; i < number/2; i++)
        {
            valid = true;

            digitCount = getDigitCount(i);

            for(int d = 1; d < digitCount; d++)
            {
                if(getDigit(i, d) == 0)
                    valid = false;
            }

            if(!valid)
                continue;

            if((quotient = number/i) % 2 == 0)
            {
                quotientl = (int)quotient;
                digitCount = getDigitCount(quotientl);

                for(int d = 1; d < digitCount; d++)
                {
                    if(getDigit(quotientl, d) == 0)
                        valid = false;
                }

                if(!valid)
                    continue;

                System.out.println(quotientl + " * " + i);
            }
        }
    }

    public static short getDigitCount(int num)
    {
        short i = 1;
        while(num > Math.pow(10, i)) i++;

        return i;
    }

    public static int getDigit(int num, int digit)
    {
        int m = (int)Math.pow(10, digit);
        return num % m/(m/10);
    }

}

Happy coding,

Tyler Hackett


