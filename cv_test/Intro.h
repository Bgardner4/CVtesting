#pragma once
/*********************show image************************************
*******************************************************************/
int returnImage(char** argv);

/************************smoothed image******************************
********************************************************************/
int returnSmoothedImage(char** argv);

/************************downsample image****************************
********************************************************************/
int returnSmallImage(char** argv);

/************************canny image****************************
********************************************************************/
int returnCannyImage(char** argv);
/***********************show video***********************************
********************************************************************/

int returnVideo(char** argv);

/********************video camera***********************************
*******************************************************************/
int returnVideoInput(int argc, char** argv);

/*********************Video with slide bar*************************
******************************************************************/
int betterVideo(char** argv);