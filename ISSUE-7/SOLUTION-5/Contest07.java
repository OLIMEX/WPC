package de.hendriklipka.contest.olimex.contest07;

public class Contest07
{
    public static void main(String[] args)
    {
        System.out.println(steps(Integer.parseInt(args[0]))+" steps");
    }

    private static long steps(final int i)
    {
        switch (i)
        {
            case 0: return 0;
            case 1: return 1;
            case 2: return 2;
            default: return steps(i - 1)+ steps(i - 2);
        }
    }
}
