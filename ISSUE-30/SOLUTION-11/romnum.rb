#!/usr/bin/env ruby
# romnum.rb

=begin

(C) 2013 C. Prelz <fluido@fluido.as>
This file is in the public domain

Converts a number, passed as parameter, to its representation in
Roman numerals

=end

def romalgo(l_ten,l_five,l_one,val)
  retv=''
  if(val==9)
    retv+=l_one+l_ten
  else
    if(val>=5)
      retv+=l_five
      val-=5
    end
    if(val==4)
      retv+=l_one+l_five
    else
      retv+=l_one*val
    end
  end
  retv
end
  
raise "Usage: #{$0} number" unless(ARGV.length==1)

num=ARGV[0].to_i

thousands,num=num.divmod(1000)
hundreds,num=num.divmod(100)
tens,units=num.divmod(10)

puts('M'*thousands+romalgo('M','D','C',hundreds)+romalgo('C','L','X',tens)+romalgo('X','V','I',units))
