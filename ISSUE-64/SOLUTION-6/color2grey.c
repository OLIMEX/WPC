// Use  OpenCV 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char *argv[])
{
  IplImage* imgRGB = 0 , imgGREY = 0;   
  int i,j;

  if(argc<3){
    printf("Usage: main <input image file>  <output image file>\n");
    exit(0);
  }

  // load an image  
  imgRGB=cvLoadImage(argv[1]);
  if(!imgRGB){
    printf("Could not load image file: %s\n",argv[1]);
    exit(0);
  }

  *imgGREY = cvCreateImage(cvGetSize(imgRGB),IPL_DEPTH_8U,1);
  if(!imgGREY){
    printf("Can't creat grey image\n");
    exit(0);
  }
  // cvCvtColor(imgRGB,imgGREY,CV_RGB2GRAY);
  for(i=0;i<imgRGB->height;i++) for(j=0;j<imgRGB->width;j++) 
  imgGREY[i][j]= (uchar)(imgRGB[i][j].b*0.114 + 
                       imgRGB[i][j].g*0.587 + 
                       imgRGB[i][j].r*0.299);

   if ( !cvSaveImage(argv[2],imgGREY) ) 
    printf ( "Can't save file %s\n",argv[2]);

  // release the image
  cvReleaseImage(&imgRGB );
  cvReleaseImage(&imgGREY );	
  exit ( 0 ) ;
}























