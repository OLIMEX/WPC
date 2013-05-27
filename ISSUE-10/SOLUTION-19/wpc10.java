import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *
 * @author delpart
 */
public class Issue10 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int a, b;

try{
            System.out.append("a = ");
    BufferedReader br = new BufferedReader(new
InputStreamReader(System.in));
    String s = br.readLine();
            a = Integer.parseInt(s);
            System.out.append("\nb = ");
            s = br.readLine();
            b = Integer.parseInt(s);
            if(a < b){
                System.out.println(calculateNumbers(a,b));
            }else{
                System.out.println("Invalid input");
            }
}
catch(IOException e)
{
e.printStackTrace();
}
    }

    private static String calculateNumbers(int a, int b){
        String s = new String();
        if(b%a == 0){
            s += b/a;
        }else{
            int b2 = b;
            while(++b2%a != 0);
            int an = a*b2 - a*b;
            int bn = b2*b;
            int q = euclid(an, bn);
            an /= q;
            bn /= q;
            s += b2/a + ", " + calculateNumbers(an, bn);
        }
        return s;
    }

    private static int euclid(int a, int b){
        while (a != 0) {
            int temp = a;
            a = b % a;
            b = temp;
        }
        return b;
    }
}
