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

// All custom drawing goes here
void draw(CvArr* img, int width, int height) {
    // Initialize our library
    truchetInit();

    CvRNG rng = truchetGetRNG();
    CvScalar fgColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256),
             bgColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256),
             strokeColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256);

    // White background
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    truchetFilledArcState state = {
        {fgColor, LINE_THICKNESS},
        -1, -1, // State machine
        bgColor,
        strokeColor
    };

    fillTiles(img, (void *) &state, width, height, 0, 0, TILE_WIDTH, TILE_HEIGHT, &truchetFilledArc);

// TODO: extract this out into another example file
    int i, offset = TILE_WIDTH/2;
    for (i = 0; i < 1; i++){

      truchetGenericState state1 = {
          cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256),
          LINE_THICKNESS};
      fillTiles(img, (void *) &state1, width, height, 0, 0, TILE_WIDTH * 2, TILE_HEIGHT * 2, &truchetArc);

      state.generic.fgColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256);
      state.bgColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256);
      state.strokeColor = cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256);
      fillTiles(img, (void *) &state, width, height, offset, offset, TILE_WIDTH, TILE_HEIGHT, &truchetFilledArc);

    }
}

int main( int argc, char** argv ) {
    drawToScreen(draw, WIDTH, HEIGHT);
}
