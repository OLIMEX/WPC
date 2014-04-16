#!/usr/bin/env ruby
# h_bot.rb

=begin
(C) 2014 C. Prelz <fluido@fluido.as>
This file is in the public domain

handles a virtual x-y cnc table where, by rotating two motors,
the center head can move anywhere on a 2-d plane

see

http://olimex.wordpress.com/2014/05/09/weekend-programming-challenge-week-52-h-bot/

Pass the pulley diameter and the size of the playground, like this:

ruby h_bot.rb 15 1000 1500

Pass pairs of X-Y coordinates, and you will be returned the angles
that the two motors will have to rotate in order to reach the new
position.

=end

class Hbot

  def initialize(pulley_diameter,size_x,size_y)
    @pulley_diameter,@size_x,@size_y=pulley_diameter,size_x,size_y
    @halfsize_x=@size_x/2.0
    @halfsize_y=@size_y/2.0
    
    @cur_x=0.0
    @cur_y=0.0
    circ=@pulley_diameter*Math::PI
    @rot_per_dist_unit=360.0/circ
  end

  def runme
    loop do
      printf("Currently at %.2f, %.2f. Go to? (x, y): ",@cur_x,@cur_y)
      r=STDIN.gets.chomp     
      break if(r=='')
      a=r.split(',').map do |el|
        el.to_f
      end
      if(a.length!=2)
        puts("Eh?")
        next
      end
      if(a[0]<-@halfsize_x || a[0]>@halfsize_x)
        printf("Bad X coordinate (%.2f). Must be between %.2f and %.2f\n",a[0],-@halfsize_x,@halfsize_x)
        next
      end
      if(a[1]<-@halfsize_y || a[1]>@halfsize_y)
        printf("Bad Y coordinate (%.2f). Must be between %.2f and %.2f\n",a[1],-@halfsize_y,@halfsize_y)
        next
      end

      xdif=a[0]-@cur_x
      ydif=a[1]-@cur_y

      leftrot=@rot_per_dist_unit*xdif-@rot_per_dist_unit*ydif
      rightrot=@rot_per_dist_unit*xdif+@rot_per_dist_unit*ydif

      printf("Left motor rotates %.2f degrees.\nRight motor rotates %.2f degrees.\n",leftrot,rightrot)
      @cur_x=a[0]
      @cur_y=a[1]
    end
  end
end

raise "Usage: #{$0} pulley_diameter playground_x playground_y" unless(ARGV.length==3)

a=ARGV.map do |v|
  v.to_f
end

raise "Bad parameters! #{a}" if(a[0]<=0.0 || a[1]<=0.0 || a[2]<=0.0)
  
Hbot::new(*a).runme
