#include "ransac.h"

/**
 * initialize ransac 
 * @param self pointer tRansac object
 */
void tRansac_init(tRansac *self)
{
	
}

/**
 * main loop of ransac calculation
 * @param self pointer tRansac object
 */
void tRansac_run(tRansac *self)
{
	
}

/**
 * estimate least square line equation of selected points
 * @param self pointer tRansac object
 * @param depth_data pointer to depth data
 * @param depth_data_sample_indexes pointer to data containing indexes 
 * 		of sample to be taken from depth_data. 
 * @param robot_orientation the current orientation state of robot
 * @return tLine type with {a, b} values
 */
tLine tRansac_least_squares_line_estimate(
			tRansac *self,
			uint16_t *depth_data,
			uint16_t *depth_data_sample_indexes,
			uint16_t depth_data_sample_size,
			tPoint robot_orientation
		)
{
	double x;
	double y;
	double sum_y;
	double sum_yy;
	double sum_x;
	double sum_xx;
	double sum_xy;
	tPoint *d = new_tPoint(d);
	uint16_t i;
	
	for (i=0; i<depth_data_sample_size; i+=1)
	{
		d->range = depth_data[*depth_data_sample_indexes];
		d->bearing = (
			robot_orientation.bearing + 
			get_bearing_within_sensor(*depth_data_sample_indexes)
		);
		//-- measure x,y from known bearing
		d->refresh_coordinate(d);
		depth_data_sample_indexes += 1;
	}
}

