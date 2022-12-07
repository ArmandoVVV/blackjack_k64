/*
 * blackjack.h
 *
 *  Created on: Dec 3, 2022
 *      Author: armando
 */

#ifndef BLACKJACK_H_
#define BLACKJACK_H_

#include "stdint.h"
#include "cards.h"
#include "config.h"

typedef struct{
	uint8_t total_cards;
	uint8_t cards_value;

	vector_t card_position;

	card_t cards[10];
}player_t;

void setup_player_cards(player_t* player);
void setup_dealer_cards(player_t* dealer);

void set_player_cards_value(player_t* player);

void player_add_card(player_t* player, card_t card);
boolean_t player_lost(player_t* player);
boolean_t dealer_complete(player_t* dealer);
boolean_t dealer_lost(player_t* dealer, player_t* player);
boolean_t game_tied(player_t* dealer, player_t* player);

void set_next_card_position(player_t* player);

#endif /* BLACKJACK_H_ */
