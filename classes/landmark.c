#include "landmark.h"

uint16_t num_of_landmarks = 0;
tLandmark *last_object_landmark = 0;
/**
 * initalize a landmark object
 * @param self pointer to self object
 * @return void
 */
void tLandmark_init(tLandmark *self)
{
	self->id = num_of_landmarks;
	num_of_landmarks += 1;
	self->life = 0;
	self->times_observed = 0;
	self->min_consensus = LANDMARK_MIN_CONSENSUS;
	self->max_trials = LANDMARK_MAX_TRIALS;
	
	self->previous_object = last_object_landmark;
	last_object_landmark = self;
}
