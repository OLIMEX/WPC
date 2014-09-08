package;

/* 
   Olimex WPC 63 - Braille converter
   Translates lowercase letters, digits and some punctuation letter by letter.    
   Haxe 3.1.3 with cpp target (gcc 4.7.3) 
*/
   

class Braille {
    
    static var map = [
        "a" => ["*.","..",".."],
        "b" => ["*.","*.",".."],
        "c" => ["**","..",".."],
        "d" => ["**",".*",".."],
        "e" => ["*.",".*",".."],
        "f" => ["**","*.",".."],
        "g" => ["**","**",".."],
        "h" => ["*.","**",".."],
        "i" => [".*","*.",".."],
        "j" => [".*","**",".."],
        "k" => ["*.","..","*."],
        "l" => ["*.","*.","*."],
        "m" => ["**","..","*."],
        "n" => ["**",".*","*."],
        "o" => ["*.",".*","*."],
        "p" => ["**","*.","*."],
        "q" => ["**","**","*."],
        "r" => ["*.","**","*."],
        "s" => [".*","*.","*."],
        "t" => [".*","**","*."],
        "u" => ["*.","..","**"],
        "v" => ["*.","*.","**"],
        "w" => [".*","**",".*"],
        "x" => ["**","..","**"],
        "y" => ["**",".*","**"],
        "z" => ["*.",".*","**"],
        "1" => ["*.","..",".."],
        "2" => ["*.","*.",".."],
        "3" => ["**","..",".."],
        "4" => ["**",".*",".."],
        "5" => ["*.",".*",".."],
        "6" => ["**","*.",".."],
        "7" => ["**","**",".."],
        "8" => ["*.","**",".."],
        "9" => [".*","*.",".."],
        "0" => [".*","**",".."],
        "," => ["..","*.",".."],
        ";" => ["..","*.","*."],
        ":" => ["..","**",".."],
        "." => ["..","**",".*"],
        "!" => ["..","**","*."],
        " " => ["..","..",".."],
        "\x00"  => [".*",".*","**"]
        ];
        
    /* Special handling of digits */    
    static function check_numeric(input: String): String {
        var in_number = false;
        var buf = new StringBuf();
         
        for (pos in 0...input.length)
        {
            var c = input.charAt(pos);
             
            if ((c >= "0") && (c <= "9")) 
            {
                if (!in_number)
                {
                    in_number = true;
                    buf.add("\x00");
                }
                buf.add(c);    
            }
            else
            {
                if (in_number)
                {
                    in_number = false;
                    if ((c >= "a") && ( c <= "j"))
                        buf.add(" "); 
                }
                buf.add(c);                    
            }
        }
        return buf.toString();
    }
    
    /* Convert string to braille */
    static function convert(input: String) {
        input = check_numeric(input);
         for (line in 0...3)
         {         
             for (pos in 0...input.length)
             {                          
                 if (map.exists(input.charAt(pos)))
                     Sys.print(map[input.charAt(pos)][line]);
                 else
                     Sys.print("...");
                 Sys.print(" ");
             }             
             Sys.println("");
         }
    }
    
    static function main () {        
        Sys.print("Enter text to translate: ");
        var input = Sys.stdin().readLine();    
        convert(input.toLowerCase());
    }

}
