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
    truchetInit( time(NULL) );

    CvRNG rng = truchetGetRNG();

    // White background
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    truchetGenericState state1 = {
        // Color
        cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256)
    };
    fillTiles(img, (void *) &state1, 1, width, height, 0, 0, TILE_WIDTH, TILE_HEIGHT, &truchetPoint);
}

int main( int argc, char** argv ) {
    drawToScreen(draw, WIDTH, HEIGHT);
}
