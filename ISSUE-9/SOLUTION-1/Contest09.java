package de.hendriklipka.contest.olimex.contest09;

import java.io.*;

/**
 * User: hli
 * Date: 17.05.13
 * Time: 20:55
 */
public class Contest09
{
    private static final double EPSILON = 0.00001;

    public static void main(String[] args)
    {
        Contest09 c09=new Contest09();
        c09.run(args[0]);
    }

    private void run(String fName)
    {
        try (
                FileReader fr=new FileReader(fName);
                BufferedReader br=new BufferedReader(fr);
        )
        {
            // first, read the number of points
            String line=br.readLine();
            int count=Integer.parseInt(line);

            // read the first 3 points
            double[] p1=readPoint(br.readLine());
            double[] p2=readPoint(br.readLine());
            double[] p3=readPoint(br.readLine());
            // do the form a circle? (can be only one)
            // if yes, we get x, y, radius
            double[] circle=createCircle(p1,p2,p3);
            int i=3;
            // and now for all remaining points we check whether they are on this circle or not
            while (i++<count)
            {
                double[] p=readPoint(br.readLine());
                if (!pointOnCircle(circle,p))
                {
                    System.err.println("no circle");
                    System.exit(1);
                }
            }
            System.out.println("points form a circle");

        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private double[] readPoint(final String line)
    {
        final double[] p = new double[2];
        String[] sa=line.split(",");
        p[0]=Double.parseDouble(sa[0]);
        p[1]=Double.parseDouble(sa[1]);
        return p;
    }

    /*
        calculates the circle values (x, y, radius) from 3 points
     */
    private double[] createCircle(final double[] p1, final double[] p2, final double[] p3)
    {
        // create system of linear equations from the given points
        final double[][] matrix=new double[3][4];
        matrix[0][0]=1;
        matrix[0][1]=-p1[0];
        matrix[0][2]=-p1[1];
        matrix[0][3]=-(p1[0]*p1[0]+p1[1]*p1[1]);

        matrix[1][0]=1;
        matrix[1][1]=-p2[0];
        matrix[1][2]=-p2[1];
        matrix[1][3]=-(p2[0]*p2[0]+p2[1]*p2[1]);

        matrix[2][0]=1;
        matrix[2][1]=-p3[0];
        matrix[2][2]=-p3[1];
        matrix[2][3]=-(p3[0]*p3[0]+p3[1]*p3[1]);

        try
        {
            // solve the equations
            double[] result=solve(matrix);
            // calculate the circle value from the resultst
            final double[] c = new double[3];
            c[0]=result[1]/2; // x
            c[1]=result[2]/2; // y
            c[2]=Math.sqrt(c[0]*c[0]+c[1]*c[1]-result[0]); // radius

            return c;  //To change body of created methods use File | Settings | File Templates.
        }
        // if we hit a calculation problem, we can assume the 3 points don#t form a circle
        catch (Exception e)
        {
            e.printStackTrace();
            System.err.println("no circle");
            System.exit(1);
        }
        return null;
    }

    /*
        solve linear equation sytem via guass algorithmus
        we know here that the matrix is 3 rows with 4 columns
     */
    private double[] solve(final double[][] matrix)
    {
        // first, reduce the rows
        double f1=matrix[1][0]/matrix[0][0];
        matrix[1][0]=0;
        matrix[1][1]-=f1*matrix[0][1];
        matrix[1][2]-=f1*matrix[0][2];
        matrix[1][3]-=f1*matrix[0][3];

        double f2=matrix[2][0]/matrix[0][0];
        matrix[2][0]=0;
        matrix[2][1]-=f2*matrix[0][1];
        matrix[2][2]-=f2*matrix[0][2];
        matrix[2][3]-=f2*matrix[0][3];

        double f3=matrix[2][1]/matrix[1][1];
        matrix[2][1]=0;
        matrix[2][2]-=f3*matrix[1][2];
        matrix[2][3]-=f3*matrix[1][3];

        // and now calculate the results
        double[] result=new double[3];
        result[2]=matrix[2][3]/matrix[2][2];

        matrix[1][2]*=result[2];
        matrix[1][3]-=matrix[1][2];
        result[1]=matrix[1][3]/matrix[1][1];

        matrix[0][2]*=result[2];
        matrix[0][1]*=result[1];
        matrix[0][3]-=matrix[0][2];
        matrix[0][3]-=matrix[0][1];
        result[0]=matrix[0][3]/matrix[0][0];

        return result;
    }

    /*
        is the point on the circle?
     */
    private boolean pointOnCircle(final double[] circle, final double[] p)
    {
        // first, calculate the distance of the
        double xd=p[0]-circle[0];
        double yd=p[1]-circle[1];
        double dist=Math.sqrt(xd*xd+yd*yd);
        return Math.abs(dist-circle[2])<EPSILON;
    }
}
