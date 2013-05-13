package zarev.hangman.data;

import java.util.HashSet;


public class FilterFactory {
	private FilterFactory(){
		//do nothing
	}
	public static String matchesRgEx(String[] guessed){
		HashSet<String> unique = new HashSet<String>();
		for(String s : guessed){
			if(null != s){
				unique.add(s);
			}
		}
		
		
		StringBuilder builder = new StringBuilder();
		builder.append("[^");
		for(String s : unique){
			builder.append(s);
		}
		builder.append("]");
		
		String except = builder.toString();
		except = except.equals("[^]") ? "." : except;
		builder.setLength(0);
		
		builder.append("^");
		for(String s : guessed){
			if(null == s){
				builder.append(except);
			}else{
				builder.append(s);
			}
		}
		builder.append("$");
		
		return builder.toString();
	}
		
	public static Filter matchingFilter(String[] guessed){
		String regex = matchesRgEx(guessed);
		 
		return new FilterMatches(regex);
	}	
}
