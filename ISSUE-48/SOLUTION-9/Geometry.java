import java.util.Scanner;

public class Geometry {
	
	public static void main(String[] args)
	{
		Point a = null; 
		Point b = null; 
		Point c = null;
		double x, y, area;
		Scanner scanner = new Scanner(System.in);
		
		for (int i = 1; i <= 3; i++)
		{
			System.out.println("Enter the coordinates of the " + i + " point :");
			
			x = scanner.nextDouble();
			y = scanner.nextDouble();
			
			switch(i)
			{
				case 1 :
					a = new Point(x, y);
					break;
				case 2 :
					b = new Point(x, y);
					break;
				case 3 :
					c = new Point(x, y);
					break;
			}			
		}
		scanner.close();
		
		area = computeArea(a, b, c);
		
		if (area == 0)
		{
			System.out.println("The points are on a straight line");
		} 
		else if (area < 0)
		{
			System.out.println("The points are on a clockwise turn");
		}
		else 
		{
			System.out.println("The points are on a counter-clockwise turn");
		}
	}
	
	private static double computeArea(Point a, Point b, Point c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}
}
