/*
 * sounds.h
 *
 *  Created on: Dec 5, 2022
 *      Author: armando
 */

#ifndef SOUNDS_H_
#define SOUNDS_H_

#include "stdint.h"

#define WIN_SOUND_BYTES		7000
#define LOST_SOUND_BYTES	14000
#define CARD_SOUND_BYTES	3949

const uint16_t* get_error_sound(void);
const uint16_t* get_good_sound(void);
const uint16_t* get_card_sound(void);



#endif /* SOUNDS_H_ */
