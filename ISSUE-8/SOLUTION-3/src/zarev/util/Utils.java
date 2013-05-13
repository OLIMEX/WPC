package zarev.util;

public final class Utils {
	private Utils(){
		//do nothing
	}
	
	public static void checkNotNull(Object obj){
		checkNotNull(obj,"Argument is null");
	}
	
	public static void checkNotNull(Object obj, String msg){
		if(null == obj){
			throw new IllegalArgumentException(msg);
		}
	}
}
