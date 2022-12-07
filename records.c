/*
 * records.c
 *
 *  Created on: Dec 5, 2022
 *      Author: armando
 */

#include "records.h"
#include "AT24C32D.h"

uint8_t get_games_played(void){
	return get_value_at_address(GAMES_PLAYED_ADDRESS);
}

uint8_t get_games_won(void){
	return get_value_at_address(GAMES_WON_ADDRESS);
}

void add_one_game_played(void){
	 write_value_at_address(get_value_at_address(GAMES_PLAYED_ADDRESS) + 1, GAMES_PLAYED_ADDRESS);
}

void add_one_game_won(void){
	 write_value_at_address( get_value_at_address(GAMES_WON_ADDRESS) + 1, GAMES_WON_ADDRESS );
}

void clear_games_won(void){
	// TODO VERY CLOSE LINES OF CODE THAT MANIPULATES MEMORY DONT WORK
	//		IT ONLY WORKS THE FIRST INSTRUCTION
	write_value_at_address(0, GAMES_WON_ADDRESS);
	write_value_at_address(0, GAMES_PLAYED_ADDRESS);

}

void clear_games_played(void){
	write_value_at_address(0, GAMES_PLAYED_ADDRESS);
	write_value_at_address(0, GAMES_WON_ADDRESS);

}
