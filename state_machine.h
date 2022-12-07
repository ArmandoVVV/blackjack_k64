/*
 * state_machine.h
 *
 *  Created on: Dec 3, 2022
 *      Author: armando
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "stdint.h"

typedef enum{
	INITIAL_STATE,
	PLAYER_TURN,
	DEALER_TURN,
	PLAYER_LOST,
	PLAYER_WON,
	GAME_TIED,
	END_SCREEN
}bj1_state_t;

typedef enum{
	MENU,
	BLACKJACK1,
	BLACKJACK2,
	POKER,
	RECORDS
}state_t;

bj1_state_t blackjack1_state_machine(void);
void state_machine(void);
void button_pressed(uint32_t flags);


#endif /* STATE_MACHINE_H_ */
