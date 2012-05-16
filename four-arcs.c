/**
 * Justin Ethier, 2012
 */
#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "global-params.h"
#include "truchet.h"
#include "util.h"

void truchetFourArcs(CvArr* img, void *state, int x, int y, int tileW, int tileH){
  truchetGenericState *astate = (truchetGenericState *)state;
  int thickness = astate->thickness;
  CvScalar color = astate->fgColor;
//  int len = tileW, // TODO: generalize this
//      type = cvRandInt(&rng) % 4;
  int offset = 2; // Use 4 to look like an adobe logo

  cvEllipse(img, cvPoint((x + tileW/2), y), cvSize(tileW/2, tileH/offset), 0.0, 180.0, 360.0, color, thickness, CV_AA, 0);
  cvEllipse(img, cvPoint((x + tileW/2), y + tileH), cvSize(tileW/2, tileH/offset), 0.0, 0.0, 180.0, color, thickness, CV_AA, 0);

  cvEllipse(img, cvPoint(x, (y + tileH/2)), cvSize(tileW/offset, tileH/2), 0.0, 270.0, 450.0, color, thickness, CV_AA, 0);
  cvEllipse(img, cvPoint(x + tileW, (y + tileH/2)), cvSize(tileW/offset, tileH/2), 0.0, 90.0, 270.0, color, thickness, CV_AA, 0);

/*
  if ((type % 2) == 0) {
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, color, thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, color, thickness, CV_AA, 0);
  } else {
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, color, thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, color, thickness, CV_AA, 0);
  }*/
}

// All custom drawing goes here
void draw(CvArr* img, int width, int height) {
    // Initialize our library
    truchetInit( time(NULL) );

    CvRNG rng = truchetGetRNG();

    // White background
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    truchetGenericState state1 = {
        cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256),
        LINE_THICKNESS};
    fillTiles(img, (void *) &state1, 0, width, height, 0, 0, TILE_WIDTH, TILE_HEIGHT, &truchetFourArcs);
//    truchetFourArcs(img, (void *) &state1, 100, 100, TILE_WIDTH, TILE_HEIGHT);
//    cvRectangle(img, cvPoint(100,100), cvPoint(200, 200), state1.fgColor, 1, 8, 0);
}

int main( int argc, char** argv ) {
    drawToScreen(draw, WIDTH, HEIGHT);
}
