#ifndef __util_h_included__
#define __util_h_included__
#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

/**
 * Allocate an image buffer and write it to the screen,
 * prompting for a key before closing.
 */
int drawToScreen(void drawFunc(CvArr*, int, int), const int WIDTH, const int HEIGHT);

#endif
