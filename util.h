#ifndef __UTIL_H__
#define __UTIL_H__
#include "libfreenect.h"
#include <stdlib.h>

#define RES 					FREENECT_RESOLUTION_MEDIUM
#define RES_W 					640
#define RES_H 					480
#define SENSOR_FIELD_OF_VIEW 	62
#define SENSOR_PIXEL_TO_DEGREE	RES_W/SENSOR_FIELD_OF_VIEW

extern double get_bearing_within_sensor(uint16_t pixel);
//~ extern void* malloc(size_t);

#endif
