public class ClockArrows {

   public static void main(String[] args) throws Exception {
    double mi = 60.0/11.0;
       for (int h=0; h<11; h++) {
       double m = h * mi;
       System.out.println(String.format("%02d:%02d:%f", h, (int)m, 60.0*(m-(int)m)));
       }
   }
}


