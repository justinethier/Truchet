#include "util.h"

/**
 * Allocate an image buffer and write it to the screen,
 * prompting for a key before closing.
 */
int drawToScreen(void drawFunc(CvArr*, int, int), const int WIDTH, const int HEIGHT){

    /* data structure for the image */
    IplImage *img = 0;
    img = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);
   
    /* always check */
    if( img == 0 ) {
        fprintf( stderr, "Unable to allocate image!\n");
        return 1;
    }

    drawFunc(img, WIDTH, HEIGHT);

    /* create a window */
    cvNamedWindow( "image", CV_WINDOW_AUTOSIZE );
   
    /* display the image */
    cvShowImage( "image", img );

    /* Save image file */
#if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION < 2
    cvSaveImage( "out.png", img, NULL );
#else
    cvSaveImage( "out.png", img);
#endif
   
    /* wait until user press a key */
    cvWaitKey(0);
   
    /* free memory */
    cvDestroyWindow( "image" );
    cvReleaseImage( &img );
   
    return 0;
}

