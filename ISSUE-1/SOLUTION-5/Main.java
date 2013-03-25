package de.hendriklipka.contest.olimex.contest01;

import org.testng.annotations.BeforeClass;
import org.testng.annotations.DataProvider;
import org.testng.annotations.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.number.IsCloseTo.closeTo;

public class Main
{
    /*
        Explanation:
        The actual algorithm, without inlining, looks like this:
        <pre>
        {@code
        double ax=xa-xc;
        double ay=ya-yc;
        double bx=xb-xc;
        double by=yb-yc;

        double m=(by-ay)/(bx-ax);

        return (-1 * ay + m * ax)/StrictMath.sqrt(1+m*m);
        }
        </pre>
        The first 4 lines move the whole coordinate system so point C is on the origin. This simplifies the later calculation.
        The the slope of the line is calculated (as m).
        The last line is the condensation of the following steps:
        - take the line equation (in slope-intercetp-form: y = mx + b)
        - convert it to the 'hesse normal form'
        - solve this with the values for point C
        - take the absolute value of the result, which is the distance

        The actual code would be more readable if the method would take doubles as parameter, since the no type casts would be needed...
     */
    public double calculateDistanceLineToPoint(int xa, int ya, int xb, int yb, int xc, int yc)
    {
        double m=((double)yb-(double)yc - ((double)ya-(double)yc))/((double)xb-(double)xc - ((double)xa-(double)xc));
        return StrictMath.abs((-1d * ((double)ya-(double)yc) + m * ((double)xa-(double)xc))/StrictMath.sqrt(1d+m*m));
    }

    @DataProvider
    public Double[][] ValidDataProvider()
    {
        return new Double[][]
        {
            {-8d,-6d,12d,6d,-9d,7d,11.6619},
            {0d,0d,13d,12d,4d,9d,3.9},
            {0d,0d,13d,12d,-12d,-2d,6.67},
            {0d,0d,13d,12d,14d,-8d,15.37},
        };
    }

    @Test(dataProvider = "ValidDataProvider")
    public void doTest(double xa, double ya, double xb, double yb, double xc, double yc, double dist)
    {
        double result=_main.calculateDistanceLineToPoint((int)xa,(int)ya,(int)xb,(int)yb,(int)xc,(int)yc);
        assertThat(result, is (closeTo(dist,0.01d)));

    }

    private Main _main;

    @BeforeClass
    public void setup()
    {
        _main=new Main();
    }
}
