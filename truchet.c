/**
 * Justin Ethier, 2012
 */
#include "truchet.h"

CvRNG rng;

/**
 * This function must be called prior to using the module
 */
void truchetInit(){
    rng = cvRNG( time(NULL) );
}

CvRNG truchetGetRNG(){
    return rng;
}

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
      for(i=0;i<4;i++){
//        if (over.val[i] > 0){
            merged.val[i] = (S.val[i]*source.val[i]+D.val[i]*over.val[i]);
/*        } else {
            merged.val[i] = source.val[i];
        }
*/
      }
      cvSet2D(src, y+location.y, x+location.x, merged);
    }
  }
}

// Original Truchet based on 4 triangular patterns
// (http://mathworld.wolfram.com/TruchetTiling.html)
void truchetPoint(CvArr* img, void *state, int x, int y, int tileW, int tileH){
  truchetGenericState *astate = (truchetGenericState *)state;
  CvPoint ptt[3];
  CvScalar color = astate->fgColor;
  int len = tileW, // TODO: generalize this
      type = cvRandInt(&rng) % 4;

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
void truchetArc(CvArr* img, void *state, int x, int y, int tileW, int tileH){
  truchetGenericState *astate = (truchetGenericState *)state;
  int thickness = astate->thickness;
  CvScalar color = astate->fgColor;
  int len = tileW, // TODO: generalize this
      type = cvRandInt(&rng) % 4;

  if ((type % 2) == 0) {
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, color, thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, color, thickness, CV_AA, 0);
  } else {
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, color, thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, color, thickness, CV_AA, 0);
  }
}

truchetFilledArcState *truchetFilledArcChangeState(truchetFilledArcState *state, int x, int y){
  if (state != NULL) {
    truchetFilledArcState* astate = (truchetFilledArcState *)state;
    // First row
    if (x == 0 && astate->lastRow == -1){
        astate->lastRow = astate->piece = cvRandInt(&rng)%4;
    }
    // Started another row
    else if (x == 0){
        //astate->piece = (cvRandInt(&rng)%2 + ((astate->lastRow > 1) ? 0 : 2));
        if (astate->lastRow == 0 || astate->lastRow == 3){
            astate->lastRow = astate->piece = ((cvRandInt(&rng)%2)) + 1;
        } else {
            astate->lastRow = astate->piece = ((cvRandInt(&rng)%2)) ? 0 : 3;
        }
    }
    // Just another piece
    else {
        //astate->piece = (cvRandInt(&rng)%2 + ((astate->piece > 1) ? 0 : 2));
        if (astate->piece == 0 || astate->piece == 3){
            astate->piece = ((cvRandInt(&rng)%2)) + 1;
        } else {
            astate->piece = ((cvRandInt(&rng)%2)) ? 0 : 3;
        }
    }
  }
  return state;
}

/**
 *
 */
void truchetFilledArc(CvArr* img, void *state, int x, int y, int tileW, int tileH){
  truchetFilledArcState *astate = truchetFilledArcChangeState((truchetFilledArcState *)state, x, y);
  CvScalar color1 = astate->generic.fgColor, 
           color2 = astate->bgColor;
  int thickness = astate->generic.thickness, 
    len = tileW, // TODO: should generalize len to tileW/H
    type = astate->piece; 

  if (type == 0) {
    cvRectangle(img, cvPoint(x, y), cvPoint(x + len, y + len), color2, CV_FILLED, 8, 0);
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, color1, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, color1, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
  } else if (type == 1) {
    cvRectangle(img, cvPoint(x, y), cvPoint(x + len, y + len), color1, CV_FILLED, 8, 0);
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, color2, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, color2, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x, y + len), cvSize(len/2, len/2), 0.0, 0.0, 90.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y), cvSize(len/2, len/2), 0.0, 180.0, 270.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
  } else if (type == 2) {
    cvRectangle(img, cvPoint(x, y), cvPoint(x + len, y + len), color2, CV_FILLED, 8, 0);
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, color1, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, color1, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
  } else {
    cvRectangle(img, cvPoint(x, y), cvPoint(x + len, y + len), color1, CV_FILLED, 8, 0);
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, color2, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, color2, -1, CV_AA, 0);
    cvEllipse(img, cvPoint(x, y), cvSize(len/2, len/2), 0.0, 270.0, 360.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
    cvEllipse(img, cvPoint(x + len, y + len), cvSize(len/2, len/2), 0.0, 90.0, 180.0, cvScalar(255, 255, 255, 0), thickness, CV_AA, 0);
  }
}

// Fill an entire image using given function
void fillTiles(CvArr* img, void *state, int width, int height, int x, int y, int tileWidth, int tileHeight, void (funcPtr(CvArr*, void*, int, int, int, int))){
    int xinit = x, yinit = y;


    // TODO: don't want an overlay each time, need to make it an option or something
    IplImage *imgTmp = cvCreateImage(cvGetSize(img), 8, 1);
    for (y = yinit + tileHeight - tileHeight * 2; y < height + tileHeight; y += tileHeight){
        for (x = xinit + tileWidth - tileWidth * 2; x < width + tileWidth; x += tileWidth){
            (*funcPtr)(imgTmp, state, x, y, tileWidth, tileHeight);
        }
    }
    // OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(0.7, 0.7, 0.7, 0.7), cvScalar(0.3, 0.3, 0.3, 0.3));
    //OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(1, 1, 1, 1), cvScalar(1, 1, 1, 1));
    OverlayImage(img, imgTmp, width, height, cvPoint(0, 0), cvScalar(0.5, 0.5, 0.5, 0.5), cvScalar(0.5, 0.5, 0.5, 0.5));
    cvReleaseImage( &imgTmp );
}

