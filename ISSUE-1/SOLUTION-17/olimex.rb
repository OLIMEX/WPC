class Olimex
  attr_accessor :debug
  @debug = false

  def point_distance(p1, p2)
    Math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
  end

  def line_to_point_distance(line, c_point)
    a_point, b_point = line
    x, y = 0.0, 0.0
    distance = 0.0
    # check if they are equal
    if a_point[0] == b_point[0] and a_point[1] == b_point[1]
      # degenerated line
      x, y = a_point[0], a_point[1]
    else
      # line
      l1_slope = (a_point[1] - b_point[1]) / (a_point[0] - b_point[0])
      l1_intercept = (a_point[0]*b_point[1] - a_point[1]*b_point[0]) / (a_point[0] - b_point[0])
      # x axis parallel
      if l1_slope.zero?
        puts "X-Axis parallel" if debug
        x, y = c_point[0], a_point[1]
      # y axix parallel
      elsif l1_slope.infinite?
        puts "Y-Axis parallel" if debug
        x, y = a_point[0], c_point[1]
      # not parallel
      else
        puts "Line #{l1_intercept} + x * #{l1_slope}" if debug
        # perpendicular line
        lp_slope = -(1/l1_slope)
        lp_intercept = c_point[1] - lp_slope*c_point[0]
        # distance
        x = (lp_intercept - l1_intercept) / (l1_slope - lp_slope)
        y = l1_slope*x + l1_intercept
      end
      distance = point_distance([c_point[0], c_point[1]], [x, y])
      puts "Distance between line #{l1_intercept} + x * #{l1_slope} and (#{c_point[0]},#{c_point[1]}) is: #{distance}"
    end
    distance
  end
end
