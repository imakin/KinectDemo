#include "util.h"

/**
 * calculate bearing from given pixel point of sensor bitmap data
 * @param pixel is the index of bitmap data where the point is, data is in 1D array
 * @return bearing value
 */
double get_bearing_within_sensor(uint16_t pixel)
{
	return (
		((pixel % RES_W) - (RES_W/2)) /
		SENSOR_PIXEL_TO_DEGREE
	);
}

