require 'test/unit'
require './olimex'

class TestAdd < Test::Unit::TestCase
    def test_random
    	olimex = Olimex.new
    	calculated = olimex.line_to_point_distance [[0.0, 0.0], [0.0, 0.0]], [0.0, 0.0]
        expected = 0
    	assert_equal expected, calculated
    end
end
