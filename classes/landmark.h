#ifndef __LANDMARK_H__
#define __LANDMARK_H__
#include "libfreenect.h"
#include "../util.h"


#define LANDMARK_MIN_CONSENSUS 30
#define LANDMARK_MAX_TRIALS 1000

extern uint16_t num_of_landmarks;
/**
 * landmark object
 */
typedef struct stLandmark tLandmark;
struct stLandmark{
	double pos_x, pos_y;
	double range, bearing;
	uint16_t id;
	uint16_t life;
	uint16_t times_observed; 	// store how many times observed
	
	uint16_t min_consensus; 		// minimum number of points it shall have to be considered landmark
	uint16_t max_trials;			// maximum reading occured
	double a,b;
	double error_range, error_bearing;
	
	//-- mimic OOP
	void (*init)(tLandmark *self);
	tLandmark *previous_object;
};

extern tLandmark *last_object_landmark;
void tLandmark_init(tLandmark *self);

/**
 * creates landmark object macro
 * @param x name of the object to be created
 * @result x becomes tLandmark pointer pointing to the new landmark object created
 */
#define create_landmark(x) \
	tLandmark *x;\
	x = malloc(sizeof(tLandmark));\
	x->init = &tLandmark_init;\
	x->init(x);

#endif
