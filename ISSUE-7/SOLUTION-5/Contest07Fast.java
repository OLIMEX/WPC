package de.hendriklipka.contest.olimex.contest07;

import java.util.Arrays;

public class Contest07Fast
{
    private static long _cache[];
    public static void main(String[] args)
    {
        final int stairs = Integer.parseInt(args[0]);
        _cache =new long[stairs+1];
        Arrays.fill(_cache, -1);
        System.out.println(steps(stairs)+" steps");
    }

    private static long steps(final int i)
    {
        if (-1!=_cache[i])
            return _cache[i];
        switch (i)
        {
            case 0: _cache[i]=0; break;
            case 1: _cache[i]=1; break;
            case 2: _cache[i]=2; break;
            default: _cache[i]=steps(i - 1)+ steps(i - 2);
        }
        return _cache[i];
    }
}
