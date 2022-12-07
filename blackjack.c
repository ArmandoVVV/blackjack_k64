/*
 * blackjack.c
 *
 *  Created on: Dec 3, 2022
 *      Author: armando
 */
#include "blackjack.h"

void setup_player_cards(player_t* player){
	player->cards[0] = get_card();
	player->cards[1] = get_card();

	player->total_cards = 2;
	player->card_position = PLAYER1_CARD_ORIGIN;
	set_player_cards_value(player);
}

void set_next_card_position(player_t* player){
	if( 0 == (player->total_cards % 5) ){
		player->card_position.x = 6;
	}
	else{
		player->card_position.x += 47;
	}
}

void setup_dealer_cards(player_t* dealer){
	dealer->cards[0] = get_card();
	dealer->cards[1] = get_card();

	dealer->total_cards = 2;
	dealer->card_position = DEALER_CARD_ORIGIN;
	set_player_cards_value(dealer);
}

void set_player_cards_value(player_t* player){
	uint8_t cards_value = 0;
	static uint8_t index;

	for(index = 0; index < player->total_cards; index++){
		cards_value += player->cards[index].blackjack_value;
	}

	player->cards_value = cards_value;

	if( player_lost(player) ){
		for(index = 0; index < player->total_cards; index++){
			if( AS == player->cards[index].number &&  11 == player->cards[index].blackjack_value){
				player->cards[index].blackjack_value = 1;
				cards_value -= 10;

				player->cards_value = cards_value;
				break;
			}
		}
	}
}

void player_add_card(player_t* player, card_t card){
	player->cards[player->total_cards] = card;
	player->total_cards++;

	set_player_cards_value(player);
}

boolean_t player_lost(player_t* player){
	if( 21 < player->cards_value ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

boolean_t dealer_complete(player_t* dealer){
	if( 17 <= dealer->cards_value ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

boolean_t dealer_lost(player_t* dealer, player_t* player){
	boolean_t result;

	if( 21 < dealer->cards_value ){
		result = TRUE;
	}
	else if( dealer->cards_value < player->cards_value){
		result = TRUE;
	}
	else{
		result = FALSE;
	}

	return result;
}

boolean_t game_tied(player_t* dealer, player_t* player){
	if(dealer->cards_value == player->cards_value){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
