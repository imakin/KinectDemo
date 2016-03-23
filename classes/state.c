#include "state.h"

/**
 * struct tPoint.refresh_coordinate pointed to this
 * @param stPoint.refresh_coordinate
 */
void tPoint_refresh_coordinate(tPoint *self)
{
	double X,Y;
	X = Y = 0;
	//-- range bearing shall be set to 0 if x,y is set manually
	//-- thus don't change any if range and bearing is 0
	if (self->range==0 && self->bearing==0)
		return;

	if (self->observer!=0)
	{
		X = self->observer->x;
		Y = self->observer->y;
	}
	self->x = X - (self->range * sin(self->bearing * 3.14 /180));
	self->y = Y + (self->range * cos(self->bearing * 3.14 /180));
}


/**
 * tPoint.init pointed to this
 * @see stPoint.init
 */
void tPoint_init(tPoint *self)
{
	self->refresh_coordinate = &tPoint_refresh_coordinate;
	self->close = &tPoint_close;
}

/**
 * tPoint.close pointed to this
 * @see stPoint.close
 */
void tPoint_close(tPoint *self)
{
	free(self);
}


/**
 * initialize tLine object
 */
void tLine_init(tLine *self)
{
	self->load_points = &tLine_load_points;
}

/**
 * load a points data, and estimate least squares line from these and save it to a,b,c
 * @param self object pointer
 * @param depth_data pointer to depth image data
 * @param depth_data_sample_indexes pointer to a list of sample 
 * 			indexes of depth_data that needs to be loaded
 * @param depth_data_sample_size size of depth_data_sample_indexes
 * @see stPoint.load_points
 */
void tLine_load_points(
		tLine *self,
		uint16_t *depth_data,
		uint16_t *depth_data_sample_indexes,
		uint16_t depth_data_sample_size
	)
{
	double ss_xx = 0;
	double ss_yy = 0;
	double ss_xy = 0;
	double mean_x = 0;
	double mean_y = 0;
	uint16_t *sample_index_pointer; // more variable for code readability
	uint16_t sample_index_value;
	uint16_t *sample_pointer;
	uint16_t sample_value;
	uint16_t i;
	double r2;
	double slope;
	double m, rm;
	double b, rb;
	tPoint *temp_point = new_tPoint(temp_point);
	

	for (i=0; i<depth_data_sample_size; i++)
	{
		sample_index_pointer = depth_data_sample_indexes + i;
		sample_index_value = *sample_index_pointer;

		sample_pointer = depth_data + sample_index_value;
		sample_value = *sample_pointer;

		temp_point->range = (double)sample_value;
		temp_point->bearing = get_bearing_within_sensor(sample_index);
		temp_point->refresh_coordinate(temp_point);

		ss_xx += (temp_point->x * temp_point->x);
		ss_yy += (temp_point->y * temp_point->y);
		ss_xy += (temp_point->x * temp_point->y);
		mean_x += (temp_point->x / depth_data_sample_size);
		mean_y += (temp_point->y / depth_data_sample_size);
	}
	//-- r2 = (ss_xy * ss_xy) / (ss_xx * ss_yy);
	r2 = ss_xy / ss_xx;
	r2 = r2 / ss_yy;
	r2 = r2 * ss_xy;
	slope = ss_xy / ss_xx;
	if (slope >= -1 && slope <= 1)
	{// horizontally line
		m = ss_xy / ss_xx;
		b = mean_y - m * mean_x;
		self->a = m;
		self->b = -1;
		self->c = b;
	}
	else
	{// vertically line
		rm = ss_xx / ss_xy;
		rb = mean_x - rm * mean_y;
		self->a = -1;
		self->b = rm;
		self->c = rb;
	}
	//-- r2???? TODO learn these calculation
}
