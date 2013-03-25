package lt.tomas_puplauskas.olimex20130322;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import static org.junit.Assert.assertEquals;


@RunWith(JUnit4.class)
public class DistanceCalculatorTest {
    @Test
    public void testDistanceBetweenPoints(){
        assertEquals(5d, DistanceCalculator.distanceBetweenPoints(new Point( -2, 1), new Point(1, 5)), 0);
        assertEquals(5d, DistanceCalculator.distanceBetweenPoints(new Point(1, 5), new Point( -2, 1)), 0);
    }

    @Test
    public void testDistanceBetweenLineAndPoints1(){
        Point a = new Point(-1,0);
        Point b = new Point(3,0);
        Point c = new Point(1,2);
        assertEquals(2d, DistanceCalculator.distanceBetweenLineAndPoints(a, b, c), 0.01);
    }
    @Test
    public void testDistanceBetweenLineAndPoints2(){
        Point a = new Point(-1,0);
        Point b = new Point(3,0);
        Point c = new Point(-1,2);
        assertEquals(2d, DistanceCalculator.distanceBetweenLineAndPoints(a, b, c), 0.01);
    }

    @Test
    public void testDistanceBetweenLineAndPoints3(){
        Point a = new Point(-1,0);
        Point b = new Point(3,0);
        Point c = new Point(7,-2);
        assertEquals(2d, DistanceCalculator.distanceBetweenLineAndPoints(a, b, c), 0.01);
    }
}
