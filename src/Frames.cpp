#include "Frames.h"
#include "assets.h"

int Frames::frames = 0;

int Frames::framecounter() {
	frames++;
	frames %= 3601;
	return(frames);
}