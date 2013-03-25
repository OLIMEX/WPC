            

class Line(SageObject):
    def __init__(self,point_a,point_b):
        self.lambda_x = point_b[0]-point_a[0]
        self.lambda_y = point_b[1]-point_a[1]
        self.lambda_z = point_b[2]-point_a[2]
        self.u = vector([self.lambda_x,self.lambda_y,self.lambda_z])
        self.u = self.u/self.u.norm()
        self.point = point_a
    
def distance(line,point_c):
    ap = point_c - line.point
    return line.u.cross_product(ap).norm() / line.u.norm()

def resolve_challenge(a_x,a_y,b_x,b_y,c_x,c_y):
    z=0
    point_a = vector([a_x,a_y,z])
    point_b = vector([b_x,b_y,z])
    point_c = vector([c_x,c_y,z])
    return distance(Line(point_a,point_b),point_c)
