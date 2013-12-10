#!/usr/bin/ruby

charset = {
	0 => ' ',
	1 => '',
	2 => %W{ a b c },
	3 => %W{ d e f },
	4 => %W{ g h i },
	5 => %W{ j k l },
	6 => %W{ m n o },
	7 => %W{ p q r s },
	8 => %W{ t u v },
	9 => %W{ w x y z }
}

input = gets.downcase.chomp;

decode = String.new;

input.each_char {
	|char|;
	res = nil;
	charset.each_pair {
		|k, v|;
		if v.include? char
			res = k.to_s * ((v.index char) + 1);
			break;
		end
	}
	decode += res.to_s + " ";
}

puts decode;
