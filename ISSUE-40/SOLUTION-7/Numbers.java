import java.util.*;
public class Numbers {
	
	public static void main ( String[] args) {
		System.out.println( encode ( Integer.parseInt( args[0] ) ) );	
	}
	
	public static String encode ( int number ) {
		return encode ( (long)number );
	}
	//creates the String with 1*3 ...
	public static String encode ( long number ) {
		if ( number == (long)1 ) {
			return "1";
		}
		//contains the *3 aund /2
		ArrayList<Boolean> list = new ArrayList<Boolean>();
		//contains the lists to test
		ArrayList<Boolean> tmpList = new ArrayList<Boolean>();
		list.add( true );
		ArrayList<ArrayList> all = new ArrayList<ArrayList>();
		all.add( list );
		long current;
		for (;;) {
			list = all.remove( 0 );
			current = evaluate( list );
			if ( current == number ) {
				//if we have found the Solution return the code of it
				return encode( list );
			}
			if ( current != (long)1 ) {
				//create all possible lists of *3 and /2 yes this can take a really really long (worst case infinite) time
				tmpList = (ArrayList<Boolean>)list.clone();
				tmpList.add( false );
				list.add( true );
				all.add( tmpList );
				all.add( list );
			}
		}
	}
	//calculates the nummeric value of a list of *3 and /2
	public static long evaluate ( ArrayList<Boolean> list ) {
		HashSet<Long> used = new HashSet<Long>();
		long ret = (long)1;
		for ( int i = 0; i < list.size(); i++ ) {
			if ( list.get( i ) ) {
				ret *= (long)3;
			}
			else {
				ret /= (long)2;
				//if the value is 1, we could have stzarted with 1 so calculating this list is pointless
				if ( ret < (long)2 ) {
					return (long)-1;
				}
			}
			//if there is a loop in the list calculating it is a waste of time
			if ( !used.add( ret ) ) {
				return (long)-1;
			}
		}
		return ret;
	}

	public static String encode ( ArrayList<Boolean> list ) {
		String ret = "1";
		for ( int i = 0; i < list.size(); i++ ) {
			if ( list.get(i) ) {
				ret = ret + "*3";
			}
			else {
				ret = ret + "/2";
			}
		}
		return ret;
	}

}
