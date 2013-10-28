import java.util.Scanner;
import java.util.*;
public class RomanNumber
{
	private static final String rLetters = "MDCLXVI";
	private static final int MAX_DIV = 1000;
	private static final int DIV = 10;
	
	public static void main(String[] argv)
	{
		Scanner input = new Scanner(System.in);
		String nromano="";	
		int ndecimal = -1, divider = MAX_DIV, digit = 0;
		
		System.out.println("Welcome to Decimal to Roman Number Converter");
		
		do{
			System.out.println("Please enter a Decimal Number between 1 and 1000");		
			if(!input.hasNextInt())
				input.nextLine();
			else
				ndecimal = input.nextInt();
		}while(ndecimal < 1 || ndecimal >1000);
		
		nromano = ndecimal + " In Roman is: ";
		
		if((ndecimal/divider)==1) nromano += "M";		
		ndecimal = ndecimal % divider;
		divider = divider/DIV;
		
		while(ndecimal>0)
		{						
			switch(ndecimal/divider)
			{
				case 9: nromano += rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit);
								   break;
				case 8: nromano += rLetters.charAt(digit+1)+""+
								   rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2);
								   break;
				case 7: nromano += rLetters.charAt(digit+1)+""+
								   rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2);
								   break;
				case 6: nromano += rLetters.charAt(digit+1)+""+
								   rLetters.charAt(digit);
								   break;
				case 5: nromano += rLetters.charAt(digit+1);
								   break;
				case 4: nromano += rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+1);
								   break;
				case 3: nromano += rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2);
								   break;
				case 2: nromano += rLetters.charAt(digit+2)+""+
								   rLetters.charAt(digit+2);
								   break;
				case 1: nromano += rLetters.charAt(digit+2);
								   break;
			}			
			ndecimal = ndecimal % divider;
			divider = divider/DIV;
			digit +=2;
		}	
		System.out.println(nromano);
	}
	
}