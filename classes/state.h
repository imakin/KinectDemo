/**
 * @file state.h
 */
#ifndef __STATE_H__
#define __STATE_H__

#include <math.h>
#include "libfreenect.h"
#include "../util.h"

/**
 * instantiate a new tPoint object.
 * usages: tPoint *object_name = new_tPoint(object_name);
 * @param name the object name
 */
#define new_tPoint(name) \
	malloc(sizeof(tPoint)); \
	name->init = &tPoint_init; \
	name->init(name);
typedef struct stPoint tPoint;
struct stPoint{
	double range; 		//!< range of this point measured from this.observer
	double bearing; 	//!< bearing of this point measured from this.observer
	double x;			//!< x position of this point on the map
	double y;			//!< y position of this point on the map
	double yaw;			//!< yaw orientation of this point
	double tilt;		//!< tilt orientation of this point
	double pan;			//!< pan orientation of this point
	tPoint *observer;	//!< range & bearing of this point is measured from this observer point	

	/**
	 * refresh self.x, self.y based on current self.range and self.bearing
	 * @param self pointer object
	 */
	void (*refresh_coordinate)(tPoint *self);

	/**
	 * initialize tPoint object
	 * @param self the self pointer object
	 */
	void (*init)(tPoint *self);

	/**
	 * destroy tPoint object
	 * @param self pointer object
	 */
	 void (*close)(tPoint *self);
};

void tPoint_refresh_coordinate(tPoint *self);
void tPoint_init(tPoint *self);
void tPoint_close(tPoint *self);



/**
 * instantiate a new tLine object.
 * usages: tLine *object_name = new_tLine(object_name);
 * @param name the object name
 */
#define new_tLine(name) \
	malloc(sizeof(tLine)); \
	name->init = &tLine_init; \
	name->init(name);
typedef struct stLine tLine;
struct stLine{
	double a; //!< equation constant for ax+by=c @see stLine.load_points
	double b; //!< equation constant for ax+by=c @see stLine.load_points
	double c; //!< equation constant for ax+by=c @see stLine.load_points

	/**
	 * initialize tLine object
	 */
	void (*init)(tLine *self);

	/**
	 * load a points data, and estimate least squares line from these and save it to a,b,c
	 * @param self object pointer
	 * @param depth_data pointer to depth image data
	 * @param depth_data_sample_indexes pointer to a list of sample 
	 * 			indexes of depth_data that needs to be loaded
	 * @param depth_data_sample_size size of depth_data_sample_indexes
	 */
	void (*load_points)(
			tLine *self,
			uint16_t *depth_data,
			uint16_t *depth_data_sample_indexes,
			uint16_t depth_data_sample_size
		);
};

void tLine_init(tLine *self);
void tLine_load_points(
		tLine *self,
		uint16_t *depth_data,
		uint16_t *depth_data_sample_indexes,
		uint16_t depth_data_sample_size
	); 

#endif
