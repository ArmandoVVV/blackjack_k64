/*
 * drawing.h
 *
 *  Created on: Dec 4, 2022
 *      Author: armando
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include "cards.h"

void draw_background_image(void);
void draw_menu_image(void);
void draw_flipped_card(vector_t origin);
void draw_card(card_t card, vector_t card_origin);
void draw_blackjack_player(void);
void draw_blackjack_dealer(void);
void draw_you_won(vector_t origin);
void draw_you_lost(vector_t origin);
void draw_game_tied(vector_t origin);
void draw_exit(vector_t origin);
void draw_play_again(vector_t origin);
void draw_number(uint8_t number, vector_t origin);

// RECORDS
void draw_games_won(vector_t origin);
void draw_games_played(vector_t origin);
void draw_records(void);

static const vector_t PLAYER1_CARDS_VALUE_ORIGIN = {70, 160};
static const vector_t DEALER_CARDS_VALUE_ORIGIN = {200, 160};

static const vector_t PLAY_AGAIN_ORIGIN = {20, 70};
static const vector_t EXIT_ORIGIN = {130, 70};


#endif /* DRAWING_H_ */
