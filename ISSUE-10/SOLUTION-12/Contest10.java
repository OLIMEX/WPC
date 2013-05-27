package de.hendriklipka.contest.olimex.contest10;

import java.util.ArrayList;
import java.util.List;

public class Contest10
{
    public static void main(String[] args)
    {
        if (2!=args.length)
        {
            System.err.println("usage: java Contest10 num1 num2");
            System.exit(1);
        }
        try
        {
            long l1=Long.parseLong(args[0]);
            long l2=Long.parseLong(args[1]);
            List<Long> result=new Contest10().calculate(l1, l2);
            for (long l : result)
            {
                System.out.println(l + " ");
            }
        }
        catch (NumberFormatException nfe)
        {
            System.err.println("usage: java Contest10 num1 num2");
            System.exit(2);
        }
    }

    /*
        greedy algorithm - always try to find the next nominator
        depending on numerator / denominator, it might not terminate in the LONG value range (e.g. 5/121)
     */
    public List<Long> calculate(long l1, long l2)
    {
        long cl1=l1;
        long cl2=l2;
        List<Long> result=new ArrayList<>();

        long currentNum=1;

        while (true)
        {
            // cross multiplication of numerator (the other one is always currentNum)
            long nl1=currentNum*cl1;
            // is it smaller than the remainder we have?
            if (cl2<=nl1)
            {
                // yes -> we have a new result
                result.add(currentNum);
                // calculate new fraction
                cl1=nl1-cl2;
                cl2*=currentNum;
                // if nothing is left, we are finished
                if (0==cl1)
                    break;
                // if the remaining numerator is 1, we can finish too
                if (1==cl1)
                {
                    result.add(cl2);
                    break;
                }
                // and if the remaining denominator can be divided by the numerator, we can finish too
                if (0==(cl2%cl1))
                {
                    result.add(cl2/cl1);
                    break;
                }
            }
            currentNum++;
        }

        return result;
    }
}
