import java.util.*;

public class Main
{
int[] intlist = new int[100];//= {1,2,3,4,5,6,7,8,9};
int listCount;
int wanted = 100;

public static void main(String[] args)
{
Main m = new Main();
// testList list of numbers to use, wanted ressult.
m.testList("123456789",100);
}
public void testList(String stringList, int wantedInt){

System.out.println(stringList.length());
for(int i=0; i< stringList.length();i++){
intlist[i] = Integer.parseInt( stringList.substring(i,i+1));
}
listCount = stringList.length();
wanted = wantedInt;
t3(0,new String(), 0,0,true);
}
public void t3(int n, String str, int last, int counter, boolean pre)
{
int t = intlist[n];
int c2;

if(pre == true)//+
{
c2 = counter + last + t;
}else//-
{
c2 = counter - last - t;
}

if(n == listCount-1){//done, lets summ

if (c2==100)
{
    System.out.println(str + intlist[listCount-1] + "  = '" + c2 +"'");
}
return;
}
//''
t3(n+1, new String(str + intlist[n]),new Integer(last+t)*10, new
Integer(counter), pre);
//+
t3(n+1, new String(str + intlist[n] + " + "), 0, new Integer(c2),true);
//-
t3(n+1, new String(str + intlist[n] + " - "), 0, new Integer(c2), false);

return;

}

}


