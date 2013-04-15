package de.hendriklipka.contest.olimex.contest04;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Arrays;

public class Contest04
{
    public static void main(String[] args)
    {
        Contest04 c=new Contest04();
        try
        {
            String result=c.calculate(System.in);
            if (result==null)
            {
                System.err.println("[NO RESULT FOUND");
                System.exit(1);
            }
            else
            {
                System.out.println(result);
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    private String calculate(final InputStream in) throws IOException
    {
        // remember current result and its length
        String currentResult=null;
        int currentLength=0;

        // these are the characters already used in the word currently processed
        boolean[] wordChars=new boolean[65536];

        // wrap the input to be Unicode-aware
        Reader inputReader=new InputStreamReader(in);

        // start reading
        int c=inputReader.read();

        // until we run EOF
        while (c!=-1)
        {
            // scan forr the first letter of a word
            if (!Character.isLetter(c))
            {
                c=inputReader.read();
                continue;
            }

            // we have a new word, so we reset the used-characters list
            Arrays.fill(wordChars,false);

            // and we start building a new word
            StringBuilder currentWord=new StringBuilder();

            // convert to lowercase (note that this is charset-aware!)
            c=Character.toLowerCase(c);
            // append to current word
            currentWord.append((char)c);
            // and mark character as used
            wordChars[c]=true;
            
            // read next char
            c=inputReader.read();
            boolean isogramFound=true;
            // and start scanning for the end of the word
            // we are finished when we either reach EOF or a non-letter has been reached
            // we are NOT finished when we find that the word is a non-isogram - we must still read it fully
            while (-1!=c &&  Character.isLetter(c))
            {
                // if we already know its not an isogram, just skip ahead to the end of the word
                if (!isogramFound)
                {
                    c=inputReader.read();
                    continue;
                }
                // convert to lower-case too
                c=Character.toLowerCase(c);
                // if this character hasn't been used before
                if (!wordChars[c])
                {
                    // mark as used, and append to current word
                    wordChars[c]=true;
                    currentWord.append((char)c);
                }
                else
                {
                    // otherwise we know its not an isogram
                    isogramFound=false;
                }
                c=inputReader.read();
            }
            // if we have a new isogram, we check whether its longer than the last one
            if (isogramFound)
            {
                if (currentWord.length()>currentLength)
                {
                    currentResult=currentWord.toString();
                    currentLength=currentWord.length();
                }
            }

        }
        return currentResult;
    }
}
