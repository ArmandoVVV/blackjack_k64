/*
 * records.h
 *
 *  Created on: Dec 5, 2022
 *      Author: armando
 */

#ifndef RECORDS_H_
#define RECORDS_H_

#include "stdint.h"

#define GAMES_PLAYED_ADDRESS 0x01
#define GAMES_WON_ADDRESS	 0x00

uint8_t get_games_played(void);
uint8_t get_games_won(void);

void add_one_game_played(void);
void add_one_game_won(void);

void clear_games_won(void);
void clear_games_played(void);

#endif /* RECORDS_H_ */
