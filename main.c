/**
 * Justin Ethier, 2012
 */
#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

// Transparent Overlay from http://www.aishack.in/2010/07/transparent-image-overlays-in-opencv/
void OverlayImage(IplImage* src, IplImage* overlay, int width, int height, CvPoint location, CvScalar S, CvScalar D){
  int x, y, i;
  for(x=0;x < width;x++) {
    if(x+location.x>=src->width) continue;
    for(y=0;y < height;y++) {
      if(y+location.y>=src->height) continue;
      CvScalar source = cvGet2D(src, y+location.y, x+location.x);
      CvScalar over = cvGet2D(overlay, y, x);
      CvScalar merged;
      for(i=0;i<4;i++)
        merged.val[i] = (S.val[i]*source.val[i]+D.val[i]*over.val[i]);
      cvSet2D(src, y+location.y, x+location.x, merged);
    }
  }
}

// Original Truchet based on 4 triangular patterns
// (http://mathworld.wolfram.com/TruchetTiling.html)
void truchetPoint(CvArr* img, int x, int y, int len, int type, CvScalar color){
  CvPoint ptt[3];

  if (type == 0) {
    ptt[0] = cvPoint(x, y); // 1
    ptt[1] = cvPoint(x, y + len); // 2
    ptt[2] = cvPoint(x + len, y + len); // 3
  } else if (type == 1) {
    ptt[0] = cvPoint(x, y); // 1
    ptt[1] = cvPoint(x, y + len); // 2
    ptt[2] = cvPoint(x + len, y); // 4
  } else if (type == 2) {
    ptt[0] = cvPoint(x, y); // 1
    ptt[1] = cvPoint(x + len, y + len); // 3
    ptt[2] = cvPoint(x + len, y); // 4
  } else {
    ptt[0] = cvPoint(x, y + len); // 2
    ptt[1] = cvPoint(x + len, y + len); // 3
    ptt[2] = cvPoint(x + len, y); // 4
  }

  cvFillConvexPoly(img, ptt, 3, color, 8, 0); 
}

// Modified Truchet based on 2 arc patterns
// (http://mathworld.wolfram.com/TruchetTiling.html)
void truchetArc(CvArr* img, int x, int y, int len, int type, CvScalar color){
  CvPoint ptt[3];

  if ((type % 2) == 0) {
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, color, 1, 8, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, color, 1, 8, 0);
  } else {
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, color, 1, 8, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, color, 1, 8, 0);
  }
}

// Fill an entire image using given function
void fill(CvArr* img, int width, int height, void (funcPtr(CvArr*, int, int, int, int, CvScalar))){
    int x = 0, y = 0, len = 20;
    CvScalar color = cvScalar(rand()%256, rand()%256, rand()%256, rand()%256);

    IplImage *imgTmp = cvCreateImage(cvGetSize(img), 8, 1);
//    cvSet(imgTmp, cvScalar(255, 255, 255, 0), NULL);

    for (x = len - len*2; x < width + len; x += len){
        for (y = len - len*2; y < height + len; y += len){
            (*funcPtr)(img, x, y, len, rand()%4, color);
// TODO:            (*funcPtr)(imgTmp, x, y, len, rand()%4, color);
        }
    }

//    OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(0.7, 0.7, 0.7, 0.7), cvScalar(0.3, 0.3, 0.3, 0.3));
//    OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(0.5, 0.5, 0.5, 0.5), cvScalar(1, 1, 1, 1));
//    OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(0.5, 0.5, 0.5, 0.5), cvScalar(0.5, 0.5, 0.5, 0.5));
    cvReleaseImage( &imgTmp );
}

// All custom drawing goes here
void draw(CvArr* img, int width, int height) {
    // White background
    //cvRectangle(img, cvPoint(0, 0), cvPoint(width, height), cvScalar(255,255,255,0), CV_FILLED, 8, 0);
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    fill(img, width, height, &truchetArc);
    fill(img, width, height, &truchetArc);
    fill(img, width, height, &truchetArc);
    fill(img, width, height, &truchetArc);
}

int main( int argc, char** argv ) {
    const int WIDTH = 800;
    const int HEIGHT= 600;

    srand((unsigned)time(NULL));

    /* data structure for the image */
    IplImage *img = 0;
    img = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);
   
    /* always check */
    if( img == 0 ) {
        fprintf( stderr, "Unable to allocate image!\n");
        return 1;
    }

    draw(img, WIDTH, HEIGHT);

    /* create a window */
    cvNamedWindow( "image", CV_WINDOW_AUTOSIZE );
   
    /* display the image */
    cvShowImage( "image", img );
   
    /* wait until user press a key */
    cvWaitKey(0);
   
    /* free memory */
    cvDestroyWindow( "image" );
    cvReleaseImage( &img );
   
    return 0;
}
