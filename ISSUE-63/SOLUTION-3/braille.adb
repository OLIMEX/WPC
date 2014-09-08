with Ada.Text_IO;
use Ada.Text_IO;


procedure Braille is
  type Sextet is new String(1..6); 
  type Letters is Array(Character range 'a'..'z') of Sextet;
  Data : constant Letters := (
      'a' => "x.....", 
      'b' => "x.x...", 
      'c' => "xx....", 
      'd' => "xx.x..", 
      'e' => "x..x..", 
      'f' => "xxx...", 
      'g' => "xxxx..", 
      'h' => "x.xx..", 
      'i' => ".x.x..", 
      'j' => ".xxx..", 
      'k' => "x...x.", 
      'l' => "x.x.x.", 
      'm' => "xx..x.", 
      'n' => "xx.xx.", 
      'o' => "x..xx.", 
      'p' => "xxx.x.", 
      'q' => "xxxxx.", 
      'r' => "x.xxx.", 
      's' => ".xx.x.", 
      't' => ".xxxx.", 
      'u' => "x...xx", 
      'v' => "x.x.xx", 
      'w' => ".xxx.x", 
      'x' => "xx..xx", 
      'y' => "xx.xxx", 
      'z' => "x..xxx");

  procedure printRow(Row : Integer; Text : String) is
  begin
    for index in Text'Range loop
      if Text(index) not in 'a'..'z'then
        Put("   ");     
      else 
        Put(String(Data(Text(index))(2 * Row - 1..Row * 2))); 
        Put(" ");
      end if;
    end loop;
    New_Line;
  end printRow;

  procedure printLine(Text : String) is 
  begin
    for row in 1..3 loop
      printRow(Row => row, Text => Text);
    end loop;
  end printLine;

  testtext : String := "hello world";

begin
  printLine(Text => testtext);
end Braille;
