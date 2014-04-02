# http://www.gamedev.net/topic/187478-q-howto-determine-whether-a-triangle-is-cw-or-ccw/#6
# http://en.wikipedia.org/wiki/Curve_orientation
# or find determinant of matrix
# |x1, y1, 1, ... 1|
# |x2, y2, 1, ... 1|
# |..  ..  1, ... 1|
# |..  ..  1, ... 1|
# |xn, yn, 1, ... 1|
# (SIMD instruction ?:)
# result < 0 means cc and result > 0 means ccw

def find3points(x, y):
    #return x[0]*y[1] + x[1]*y[2] + x[2]*y[0] - x[1]*y[0] - x[2]*y[1] - x[0]*y[2]
    # more optimized code, only two mul instructions
    return (x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]) 
        
if __name__ == "__main__": 
    testcases = [[(1, 1), (2, 2), (3, 2)],\
            [(1, 1), (2, 2), (3, 3)],\
            [(-1, -1), (-2, -2), (-3, -3)],\
            [(0, 0), (100, 0), (100, 100)],\
            [(10, 12), (80, 70), (60, 50)],\
            [(80, 70), (60, 50), (10, 12)],\
            [(80, 70), (10, 12), (60, 50)],\
            [(1, 1), (2, 2), (3, 4)]]
    for testcase in testcases:
        a = testcase[0]
        b = testcase[1]
        c = testcase[2]
        ccwcw = find3points([a[0], b[0], c[0]], [a[1], b[1], c[1]])
        if ccwcw > 0:
            print a, b, c, "ccw"
        elif ccwcw < 0:
            print a, b, c, "cc"
        else:
            print a, b, c, "in line"