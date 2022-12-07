/*
 * cards.c
 *
 *  Created on: Nov 28, 2022
 *      Author: Laura García
 */

#include "cards.h"
#include "fsl_rnga.h"
#include "random.h"
#include "images.h"

#define TOTAL_CARDS			52
#define TOTAL_FIGURE   		4
#define TOTAL_CARD_VALUES	13

static card_t cards_deck [TOTAL_CARDS];
static uint8_t deck_index = 0;


void setup_deck(void){
	static uint8_t i;
	static uint8_t j;
	static card_t card;
	static uint8_t count = 0;

	for( i = 0; i < TOTAL_FIGURE; i++){
		for( j = 0; j < TOTAL_CARD_VALUES; j++){
			card.figure = i;
			card.number = j;

			switch(card.number){
				case AS:
					card.blackjack_value = 11;
					break;

				case JACK:
				case QUEEN:
				case KING:
					card.blackjack_value = 10;
					break;
				default:
					card.blackjack_value = card.number + 2;

			}

			cards_deck[count] = card;
			count++;
		}
	}
}

void shuffle_cards(uint16_t swap_times){
	static uint16_t i;
	static uint32_t random_number1;
	static uint32_t random_number2;

	for(i = 0; i < swap_times; i++){
		random_number1 = get_random_number();
		random_number2 = get_random_number();

		random_number1 %= TOTAL_CARDS;
		random_number2 %= TOTAL_CARDS;

		swap_cards(random_number1, random_number2);
	}
	deck_index = 0;
}

void swap_cards (uint8_t index1, uint8_t index2){
	static card_t temp;

	temp = cards_deck[index1];
	cards_deck[index1] = cards_deck[index2];
	cards_deck[index2] = temp;
}

card_t get_card(void){
	static card_t card;

	card = cards_deck[deck_index];
	deck_index++;

	return card;
}

