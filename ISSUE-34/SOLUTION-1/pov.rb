#!/usr/bin/env ruby
# pov.rb

=begin

(C) 2013 C. Prelz <fluido@fluido.as>
This file is in the public domain

Receives from standard input IN_Y lines of IN_X characters,
representing a bitmap image (a space is off, anything else is on)
and sends to standard output 360 lines of ROTLEN characters
(a '0' is off, a '1' is on) representing the status of each led of a
rotating strip of leds at each angle of a complete rotation

The algorithm prefers precision to speed.

Usage: ruby pov.rb < input.txt > output.txt

=end

class Pov
  IN_X=140
  IN_X_HALF=IN_X>>1
  IN_Y=140
  IN_Y_HALF=IN_Y>>1
  ROTLEN=100
  HALFDIAG=Math::sqrt(IN_X_HALF*IN_X_HALF+IN_Y_HALF*IN_Y_HALF)
  SCALEFACT=HALFDIAG/ROTLEN.to_f
  RADF=Math::PI/180.0

  def initialize
    @input=[]
    IN_Y.times do 
      l=STDIN.gets.chomp
      raise "Input lines must be #{IN_X} characters long!" unless(l.length==IN_X)
      @input.push(l.unpack('c*').map do |c|
                    c!=32
                  end)
    end
  end

  def sincos(ang)
    rang=ang.to_f*RADF
    sv=Math::sin(rang)
    cv=Math::cos(rang)
    a=[]
    ROTLEN.times do |i|
      a.push([IN_X_HALF+i*cv*SCALEFACT,IN_Y_HALF-i*sv*SCALEFACT])
    end
    a
  end

  def value_at(xv,yv)
    v=0.0
    xd,xm=xv.divmod(1)
    yd,ym=yv.divmod(1)
    return false if(xd<0 || xd>=IN_X-1 || yd<0 || yd>=IN_Y-1)
    xm2=1.0-xm
    ym2=1.0-ym
    
    v+=Math::sqrt(xm2*xm2+ym2*ym2) if(@input[yd][xd])
    v+=Math::sqrt(xm*xm+ym2*ym2) if(@input[yd][xd+1])
    v+=Math::sqrt(xm*xm+ym*ym) if(@input[yd+1][xd+1])
    v+=Math::sqrt(xm2*xm2+ym*ym) if(@input[yd+1][xd])

    v>2.0
  end

  def runme
    360.times do |ang|
      sc=sincos(ang)
      puts(sc.map do |xv,yv|
             value_at(xv,yv) ? '1' : '0'
           end.join)
    end
  end
end

Pov::new.runme
