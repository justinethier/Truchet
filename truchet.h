/**
 * Justin Ethier, 2012
 */
#ifndef __truchet_h_included__
#define __truchet_h_included__
#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

/**
 * Generic state information for any algorithm
 */
typedef struct {
  CvScalar fgColor;
  int thickness;
} truchetGenericState;

/**
 * For filled arc's, need to alternate between 0/3 and 1/2
 * also need to keep track of first piece on prev row, because need to alternate
 * with that when the next row starts
 */
typedef struct {
  truchetGenericState generic;
  int lastRow;
  int piece;
  CvScalar bgColor;
} truchetFilledArcState;

/**
 * This function must be called prior to using the module
 */
void truchetInit();

/**
 * Return the RNG
 */
CvRNG truchetGetRNG();

// Transparent Overlay from http://www.aishack.in/2010/07/transparent-image-overlays-in-opencv/
void OverlayImage(IplImage* src, IplImage* overlay, int width, int height, CvPoint location, CvScalar S, CvScalar D);

// Original Truchet based on 4 triangular patterns
// (http://mathworld.wolfram.com/TruchetTiling.html)
void truchetPoint(CvArr* img, void *state, int x, int y, int, int );

// Modified Truchet based on 2 arc patterns
// (http://mathworld.wolfram.com/TruchetTiling.html)
void truchetArc(CvArr* img, void *state, int x, int y, int, int );

truchetFilledArcState *truchetFilledArcChangeState(truchetFilledArcState *state, int x, int y);

/**
 *
 */
void truchetFilledArc(CvArr* img, void *state, int x, int y, int tileW, int tileH);

// Fill an entire image using given function
void fillTiles(CvArr* img, void *state, int width, int height, int x, int y, int tileWidth, int tileHeight, void (funcPtr(CvArr*, void*, int, int, int, int)));

#endif
