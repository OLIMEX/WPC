import java.io.*;

public class Resistor {

	private double[] temperatures;
	private double[] resistances;
	private double minResistance;
	private double maxResistance;
	private double[] error;

	public Resistor ( double[] temperatures, double[] resistances, double[] error, double minResistance, double maxResistance ) {
		this.temperatures = temperatures;
		this.resistances = resistances;
		this.error = error;
		if ( temperatures.length != resistances.length || temperatures.length != error.length ) {
			throw new IllegalArgumentException( "The Arrays have to be of the same length!" );
		}
		this.minResistance = minResistance;
		this.maxResistance = maxResistance;
	}

	public double[] getTemp  ( double resistance ) {
		double[] ret = new double[2];
		if ( resistance < minResistance || resistance > maxResistance ) {
			throw new IllegalArgumentException ( "Resistance is out of Range." );
		}
		if ( resistance <= resistances[0] ) {
			ret[0] = temperatures[0];
			ret[1] = error[0];
			return ret;
		}
		int pointerLow = 0;
		int pointerHigh = error.length - 1;
		if ( resistance >= resistances[pointerHigh] ) {
			ret[0] = temperatures[pointerHigh];
			ret[1] = error[pointerHigh];
			return ret;
		}
		int current = ( pointerLow + pointerHigh ) / 2;
		while ( pointerHigh - pointerLow > 1 ) {
			if ( resistance == resistances[current] ) {
				ret[0] = temperatures[current];
				ret[1] = error[current];
				return ret;
			}
			if ( resistance > resistances[current] ) {
				pointerLow = current;
			}
			else {
				pointerHigh = current;
			}
			current = ( pointerLow + pointerHigh ) / 2;
		}
		//linear Interpolation (better than nothing)
		ret[0] = temperatures[pointerLow] + ( temperatures[pointerHigh] - temperatures[pointerLow] ) 
			* ( resistance - resistances[pointerLow] ) 
			/ (resistances[pointerHigh] - resistances[pointerLow] );
		//returning the bigger error
		if ( error[ pointerLow ] > error[ pointerHigh ] ) {
			ret[1] = error[ pointerLow ];
		}
		else {
			ret[1] = error[ pointerHigh ];
		}
		return ret;
	}

	public static void main ( String[] args ) throws IOException {
		//values from the datasheet
		double[] resistances = { (double)490, (double)515, (double)567, 
			(double)624, (double)684, (double)747, (double)815, (double)886, 
			(double)961, (double)1000, (double)1040, (double)1122, 
			(double)1209, (double)1299, (double)1392, (double)1490, 
			(double)1591, (double)1696, (double)1805, (double)1915, 
			(double)1970, (double)2023, (double)2124, (double)2211 };
		double[] temperatures = { (double)-55, (double)-50, (double)-40, 
			(double)-30, (double)-20, (double)-10, (double)0, (double)10, 
			(double)20, (double)25, (double)30, (double)40, (double)50, 
			(double)60, (double)70, (double)80, (double)90, (double)100, 
			(double)110, (double)120, (double)125, (double)130, (double)140, 
			(double)150 };
		double[] error = { (double)3.02, (double)2.92, (double)2.74, 
			(double)2.55, (double)2.35, (double)2.14, (double)1.91, 
			(double)1.67, (double)1.41, (double)1.27, (double)1.39, 
			(double)1.64, (double)1.91, (double)2.19, (double)2.49, 
			(double)2.8, (double)3.12, (double)3.46, (double)3.83, 
			(double)4.33, (double)4.66, (double)5.07, (double)6.28, 
			(double)8.55 };
		Resistor resistor = new Resistor( temperatures, resistances, error, 
			(double)475, (double)2277 );
		double[] values;
		String in = "";
		BufferedReader read = new BufferedReader( new InputStreamReader( System.in ) );
		while ( !in.equalsIgnoreCase( "exit" ) ) {
			while( ! read.ready() ) {
			}
			in = read.readLine().trim();
			try {
				values = resistor.getTemp( Double.parseDouble( in ) );
				System.out.println( "Temperature is " + values[0] + 
					" because of the possible error it is between " 
					+ ( values[0] - values[1] ) + " and " + 
					( values[0] + values[1] ) + "." );
			}
			catch ( NumberFormatException e ) {
			}
		}
	}

}
