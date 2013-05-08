package de.hendriklipka.contest.olimex.contest07;

import java.math.BigInteger;
import java.util.Arrays;

public class Contest07BigNum
{
    private static BigInteger _cache[];
    public static void main(String[] args)
    {
        final int stairs = Integer.parseInt(args[0]);
        _cache =new BigInteger[stairs+1];
        Arrays.fill(_cache, null);
        System.out.println(steps(stairs)+" steps");
    }

    private static BigInteger steps(final int i)
    {
        if (null!=_cache[i])
            return _cache[i];
        switch (i)
        {
            case 0: _cache[i]=BigInteger.ZERO; break;
            case 1: _cache[i]=BigInteger.ONE; break;
            case 2: _cache[i]=new BigInteger("2"); break;
            default: _cache[i]=steps(i - 1).add(steps(i - 2));
        }
        return _cache[i];
    }
}
