/*
 * cards.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Laura García
 */

#ifndef CARDS_H_
#define CARDS_H_

#include "stdint.h"
#include "st7789.h"

typedef enum {
	AS_CLOVER,
	AS_SPADES,
	AS_DIAMONDS,
	AS_HEARTS,

	TWO_CLOVER,
	TWO_SPADES,
	TWO_DIAMONDS,
	TWO_HEARTS,

	THREE_CLOVER,
	THREE_SPADES,
	THREE_DIAMONDS,
	THREE_HEARTS,

	FOUR_CLOVER,
	FOUR_SPADES,
	FOUR_DIAMONDS,
	FOUR_HEARTS,

	FIVE_CLOVER,
	FIVE_SPADES,
	FIVE_DIAMONDS,
	FIVE_HEARTS,

	SIX_CLOVER,
	SIX_SPADES,
	SIX_DIAMONDS,
	SIX_HEARTS,

	SEVEN_CLOVER,
	SEVEN_SPADES,
	SEVEN_DIAMONDS,
	SEVEN_HEARTS,

	EIGTH_CLOVER,
	EIGTH_SPADES,
	EIGTH_DIAMONDS,
	EIGTH_HEARTS,

	NINE_CLOVER,
	NINE_SPADES,
	NINE_DIAMONDS,
	NINE_HEARTS,

	TEN_CLOVER,
	TEN_SPADES,
	TEN_DIAMONDS,
	TEN_HEARTS,

	JACK_CLOVER,
	JACK_SPADES,
	JACK_DIAMONDS,
	JACK_HEARTS,

	QUEEN_CLOVER,
	QUEEN_SPADES,
	QUEEN_DIAMONDS,
	QUEEN_HEARTS,

	KING_CLOVER,
	KING_SPADES,
	KING_DIAMONDS,
	KING_HEARTS,
}cards_t;

typedef enum{
	CLOVER,
	SPADE,
	DIAMOND,
	HEART
}card_figure_t;

typedef enum{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	AS
}card_number_t;

typedef struct{
	card_figure_t figure;
	card_number_t number;
	uint8_t blackjack_value;
}card_t;



void setup_deck(void);
void shuffle_cards(uint16_t swap_times);
void swap_cards (uint8_t index1, uint8_t index2);
card_t get_card(void);

static const vector_t CARDS_SIZE = {40, 52};
static const vector_t FIGURE_SIZE = {25, 26};
static const vector_t VALUE_SIZE = {9, 11};
static const vector_t PLAYER1_CARD_ORIGIN = {6, 180};
static const vector_t DEALER_CARD_ORIGIN = {6, 6};


#endif /* CARDS_H_ */
