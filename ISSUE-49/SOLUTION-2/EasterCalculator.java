import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Scanner;


public class EasterCalculator {

	public static void main(String[] args) 
	{
		String input = "";
		Scanner scanner = new Scanner(System.in);
		
		while (!input.equals("no"))
		{
			System.out.println("Enter an year : ");
			input = scanner.nextLine();
			
			SimpleDateFormat formatter = new SimpleDateFormat("MMMMM d, yyyy");
			
			GregorianCalendar westernCalendar = computeWesternEaster(Integer.parseInt(input));
			System.out.println("Western Easter : " + formatter.format(westernCalendar.getTime()));
			
			GregorianCalendar orthodoxCalendar = computeOrthodoxEaster(Integer.parseInt(input));
			System.out.println("Orthodox Easter : " + formatter.format(orthodoxCalendar.getTime()));
			
			System.out.println("Do you want to check another year ? (yes/no) ");
			input = scanner.nextLine();
		}
			
		scanner.close();
	}
	
	private static GregorianCalendar computeOrthodoxEaster(int year)
	{
		double a = year % 4;
		double b = year % 7;
		double c = year % 19;
		double d = ((19 * c) + 15) % 30;
		double e = ((2 * a) + (4 * b) - d + 34) % 7;
		double month = Math.floor((d + e + 114) / 31);
		double day = (((d + e + 114) % 31) + 1);
		
		GregorianCalendar orthodoxCalendar = new GregorianCalendar(year, ((int)month - 1), (int)day);
		orthodoxCalendar.add(Calendar.DATE, 13);
		
		return orthodoxCalendar;
	}

	private static GregorianCalendar computeWesternEaster(int year)
	{
		double a = year % 19;
		double b = Math.floor(year / 100);
		double c = year % 100;
		double d = Math.floor(b / 4);
		double e = b % 4;
		double f = Math.floor((b + 8) / 25);
		double g = Math.floor((b - f + 1) / 3);
		double h = ((19 * a) + b - d - g + 15) % 30;
		double i = Math.floor(c / 4);
		double k = c % 4;
		double l = (32 + (2 * e) + (2 * i) - h - k) % 7;
		double m = Math.floor((a + (11 * h) + (22 * l)) / 451);
		double month = Math.floor((h + l - (7 * m) + 114) / 31);
		double day = ((h + l - (7 * m) + 114) % 31) + 1;
		
		GregorianCalendar westernCalendar = new GregorianCalendar(year, (int)(month - 1), (int)day);
		
		return westernCalendar;
	}
}