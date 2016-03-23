/**
 * @file ransac.h
 */

#ifndef __RANSAC_H__
#define __RANSAC_H__
#include "libfreenect.h"
#include "../util.h"
#include "landmark.h"
#include "state.h"



typedef struct stRansac tRansac;
struct stRansac{
	void (*init)(tRansac *self);
	tLandmark *(*add_landmark)(
			tRansac *self,
			double range,
			double bearing
		);
	void (*run)(tRansac *self);
	void (*least_squares_line_estimate)(
			tRansac *self,
			uint16_t *depth_data,
			uint16_t *depth_data_sample_indexes,
			uint16_t depth_data_sample_size,
			tPoint robot_orientation
		);
};

#endif


/*
 * while
 * 	> there are still unassociated depth readings
 * 	> the number of readings is larger than the consensus
 * 	> and have done less than N trials
 * do
 * 	> select random depth data reading
 * 	> randomly choose S sample data readings that lies within D degrees
 * 		of this selected laser data reading from previous point
 * 	> Using these S samples	and the original reading calculate 
 * 		least squares best fit line
 * 	> if the number of laser data readings on the line is above some 
 * 		consensus C, then 
 * 		- Calculate new least squares best fit line based on all the 
 * 			laser readings determined to lie on the old best fit line
 * 		- Add this best fit line to the lines we have extracted
 * 		- remove the number of readings lying on the line from the
 * 			total set of unassociated readings
 */
