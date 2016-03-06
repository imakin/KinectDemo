/*
 */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "libfreenect.h"

#define RES FREENECT_RESOLUTION_MEDIUM
#define RES_W 640
#define RES_H 320


void depth_cb(freenect_device* dev, void* data, uint32_t timestamp)
{
	uint16_t *depth = (uint16_t*)data;
	uint32_t x,y;
	x = 0;
	y = RES_H/2;
	printf("\rvalue mid hahaaha is %d\n", depth[640*160-160]);
}
