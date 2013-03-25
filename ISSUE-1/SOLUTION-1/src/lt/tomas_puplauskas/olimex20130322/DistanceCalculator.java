package lt.tomas_puplauskas.olimex20130322;

public class DistanceCalculator {
    public static double distanceBetweenPoints(Point p1, Point p2){
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;
        return Math.sqrt(dx*dx + dy*dy);
    }
    public static double distanceBetweenLineAndPoints(Point a, Point b, Point c){
        //lets find are of triangle
        double ab = distanceBetweenPoints(a, b);
        double bc = distanceBetweenPoints(b, c);
        double ca = distanceBetweenPoints(c, a);
        double p = (ab + bc + ca)/2;

        double area = Math.sqrt(p*(p-ab)*(p-bc)*(p-ca));

        return (area*2)/ab;
    }
}
