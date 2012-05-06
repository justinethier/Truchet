/**
 * Justin Ethier, 2012
 */
#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "truchet.h"
#include "util.h"

// All custom drawing goes here
void draw(CvArr* img, int width, int height) {
    // Initialize our library
    truchetInit();

    CvRNG rng = truchetGetRNG();

    // White background
    cvSet(img, cvScalar(255, 255, 255, 0), NULL);

    truchetFilledArcState state = {-1, -1, cvScalar(cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256, cvRandInt(&rng)%256)};

    // Mixing these two gives a nice effect
    fill(img, (void *) &state, width, height, &truchetFilledArc);
    //fill(img, NULL, width, height, &truchetArc);

//    fill(img, NULL, width, height, &truchetPoint);
}

int main( int argc, char** argv ) {
    const int WIDTH = 1200;
    const int HEIGHT= 1020;
    drawToScreen(draw, WIDTH, HEIGHT);
}
