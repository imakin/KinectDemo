/*
 */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "libfreenect.h"
#include "util.h"

/**
 * this callback called for each depth image captured
 * 
 * @param dev device id pointer
 * @param data depth data pointer cast it to unsigned int
 * @param timestap timestap of the image capturation
 * @return void
 */
void depth_cb(freenect_device* dev, void* data, uint32_t timestamp)
{
	uint16_t *depth = (uint16_t*)data;
	uint16_t x,y,p;
	x = 0;
	y = RES_H/2;
	
	for (x=0;x<(RES_W);x+=1)
	{
		p = RES_W*(y-1) + x;
		printf("%d ", depth[p]);
	}
}

