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

    // White background
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    truchetFilledArcState state = {
        {cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256), 3},
        -1, -1, cvScalar(cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256)};

    // Mixing these two gives a nice effect
    fillTiles(img, (void *) &state, width, height, TILE_WIDTH, TILE_HEIGHT, &truchetFilledArc);
    truchetGenericState state1 = {
        cvScalar( cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256),
        3};
    fillTiles(img, (void *) &state1, width, height, TILE_WIDTH, TILE_HEIGHT, &truchetArc);
}

int main( int argc, char** argv ) {
    drawToScreen(draw, WIDTH, HEIGHT);
}
