
#include <math.h>

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------


typedef struct{
 int x;
 int y;
}T_COORD;  

typedef struct{
 float m;
 float a;
}T_LINE_EQ;


float distance(const T_COORD *a,const T_COORD *b,const T_COORD *c)
{  
 // equation of line is y=mx+a; 
 
 float dx,dy;
 T_LINE_EQ ab_eq;  
 T_LINE_EQ cd_eq; 
 
 if( (a->x==b->x) && (a->y==b->y) ) return (-1);  // if A and B are identical, line is not defined
 
 if( (a->x==b->x) && (a->y!=b->y) )  // AB line is vertical 
 {
   return ( fabs((float)(c->x-a->x)) );  // simply return x coord difference
 }  
 else if( (a->x!=b->x) && (a->y==b->y) )  // AB line is horizontal 
 {
   return ( fabs((float)(c->y-a->y)) );  // simply return y coord difference
 } 
 else if( (a->x!=b->x) && (a->y!=b->y) )  // AB line is not vertical, nor horizontal
 {
   ab_eq.m = (float)(a->y - b->y) / (float)(a->x - b->x);  // find m coeff of the AB line equation   
   ab_eq.a = (float)a->y - ((float)a->x * ab_eq.m);        // find a member of the AB line equation
 
   cd_eq.m = -1.0/ab_eq.m;                            // find the m coeff of the perpendicular line equation
   cd_eq.a = (float)c->y - ((float)c->x * cd_eq.m);   // find the a member of the perpendicular line equation
 
   dx = (cd_eq.a - ab_eq.a) / (ab_eq.m - cd_eq.m);  // find x coord of the project point D, adjacent to line AB
   dy = (dx * cd_eq.m) + cd_eq.a;                   // find y coord of the project point D, adjacent to line AB 
    
   return sqrt( ((c->x-dx) * (c->x-dx)) + ((c->y-dy) * (c->y-dy)) ); // find distance between project point D and C 
 }  
}

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------


typedef struct _Point { float x , y; } Point;
typedef struct _Vector { float x , y; } Vector; 

void vector_from_points( Vector * v , const Point * p1 , const Point * p2 )
{
  v->x = p2->x - p1->x;
  v->y = p2->y - p1->y;
}

void vector_add( Vector * v , const Vector * v1 , const Vector * v2 )
{
  v->x = v1->x + v2->x;
  v->y = v1->y + v2->y;
}

void vector_sub( Vector * v , const Vector * v1 , const Vector * v2 )
{
  v->x = v1->x - v2->x;
  v->y = v1->y - v2->y;
}

void vector_mul( Vector * result , const Vector * v , float s )
{
   result->x = v->x * s;
   result->y = v->y * s;
}

float vector_length( const Vector * v )
{
   return sqrt( v->x * v->x + v->y * v->y );   //return sqrtf( v->x * v->x + v->y * v->y );  
}

float vector_dot( const Vector * v1 , const Vector * v2 )
{
   return v1->x * v2->x + v1->y * v2->y;
}

float vector_norm( Vector * result , const Vector * src )
{
   float len = vector_length( src );
   if ( fabs( len ) < 0.0001f ) return 0.0f;   //if ( fasbf( len ) < 0.0001f ) return 0.0f; 
   result->x = src->x / len;
   result->y = src->y / len;
   return len;
}

float distance1( const Point * A , const Point * B , const Point * C )
{
   Vector v1 , v2 , v3 , v4;
   vector_from_points( &v1 , A , B );
   if ( 0.0f == vector_norm( &v1 , &v1 ) ) return -1.0f;
   vector_from_points( &v2 , A , C );
   
   vector_mul( &v3 , &v1 ,  vector_dot( &v1 , &v2 ) );
   vector_sub( &v4 , &v3 , &v2 );
   return vector_length( &v4 );
}
 

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------

T_COORD A,B,C;
float dist,dist1; 

Point AA;
Point BB;
Point CC;

void main(void)
{

 A.x=3;
 A.y=-5;
 
 B.x=17;
 B.y=49;
 
 C.x=-99;
 C.y=2;   


 
 AA.x=(float)A.x;
 AA.y=(float)A.y;
 
 BB.x=(float)B.x;
 BB.y=(float)B.y; 
 
 CC.x=(float)C.x;
 CC.y=(float)C.y; 
 
dist=distance( &A, &B, &C );
dist1=distance1( &AA , &BB , &CC ); 


 while(1);
}




