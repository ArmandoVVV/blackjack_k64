/*
 * drawing.c
 *
 *  Created on: Dec 4, 2022
 *      Author: armando
 */

#include "drawing.h"
#include "images.h"
#include "st7789.h"
#include "records.h"

void draw_background_image(void){
	st7789_draw_image((vector_t){0, 0}, (vector_t){240, 240}, get_background_image());
}

void draw_menu_image(void){
	st7789_draw_image((vector_t){0, 0}, (vector_t){240, 240}, get_menu_image());
}

void draw_blackjack_player(void){
	vector_t origin = {6, 160};

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_P());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_L());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_Y());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_R());
}

void draw_play_again(vector_t origin){
	st7789_draw_rectangle(origin, (vector_t){90, 30}, ST7789_COLOR_BLUE);

	origin.y += 8;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_P());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_L());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_Y());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_G());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_I());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_N());
}

// RECORDS
void draw_games_played(vector_t origin){
	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_G());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_M());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_S());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_P());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_L());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_Y());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_D());
}

void draw_records(void){
	draw_background_image();

	draw_games_played( (vector_t){20, 20} );
	draw_number( get_games_played() / 100, (vector_t){200, 20}); // third digit
	draw_number( (get_games_played() / 10) % 10, (vector_t){210, 20}); // second digit
	draw_number( get_games_played() % 10, (vector_t){220, 20}); // first digit

	draw_games_won( (vector_t){20, 40} );
	draw_number( get_games_won() / 100, (vector_t){200, 40}); // third digit
	draw_number( (get_games_won() / 10) % 10, (vector_t){210, 40}); // second digit
	draw_number( get_games_won() % 10, (vector_t){220, 40}); // first digit
}

void draw_games_won(vector_t origin){
	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_G());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_M());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_S());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_W());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_O());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_N());
}

void draw_exit(vector_t origin){
	st7789_draw_rectangle(origin, (vector_t){90, 30}, ST7789_COLOR_RED);

	origin.x += 25;
	origin.y += 8;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_X());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_I());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_T());
}

void draw_number(uint8_t number, vector_t origin){
	const uint8_t* number_to_draw;

	switch(number){
		case 0:
			number_to_draw = get_letter_O();
			break;

		case 1:
			number_to_draw = get_number_one();
			break;

		case 2:
			number_to_draw = get_number_two();
			break;

		case 3:
			number_to_draw = get_number_three();
			break;

		case 4:
			number_to_draw = get_number_four();
			break;

		case 5:
			number_to_draw = get_number_five();
			break;

		case 6:
			number_to_draw = get_number_six();
			break;

		case 7:
			number_to_draw = get_number_seven();
			break;

		case 8:
			number_to_draw = get_number_eight();
			break;

		case 9:
			number_to_draw = get_number_nine();
			break;
	}

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, number_to_draw);
}



void draw_you_won(vector_t origin){
	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_Y());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_O());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_U());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_W());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_O());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_N());
}

void draw_you_lost(vector_t origin){
	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_Y());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_O());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_U());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_L());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_O());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_S());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_T());
	origin.x += VALUE_SIZE.x;
}

void draw_game_tied(vector_t origin){
	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_T());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_I());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;
}

void draw_blackjack_dealer(void){
	vector_t origin = {126, 160};

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_D());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_A());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_L());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_E());
	origin.x += VALUE_SIZE.x;

	st7789_draw_image(origin, (vector_t){VALUE_SIZE.x + origin.x, VALUE_SIZE.y + origin.y}, get_letter_R());
	origin.x += VALUE_SIZE.x;
	origin.x += VALUE_SIZE.x;
}

void draw_flipped_card(vector_t origin){
	st7789_draw_image(origin, (vector_t){origin.x + 39, origin.y + 52}, get_flipped_card_image());
}

void draw_card(card_t card, vector_t card_origin){
	static const uint8_t* figure_image;
	static const uint8_t* value_image;

	vector_t figure_origin = {card_origin.x + 7, card_origin.y + 13};
	vector_t value_origin = {card_origin.x + 2, card_origin.y + 2};

	switch(card.figure){
		case DIAMOND:
			figure_image = get_diamond_image();
			break;
		case HEART:
			figure_image = get_heart_image();
			break;
		case SPADE:
			figure_image = get_spade_image();
			break;
		case CLOVER:
			figure_image = get_clover_image();
			break;
	}

	switch(card.number){
		case AS:
			value_image = get_letter_A();
			break;

		case TWO:
			value_image = get_number_two();
			break;

		case THREE:
			value_image = get_number_three();
			break;

		case FOUR:
			value_image = get_number_four();
			break;

		case FIVE:
			value_image = get_number_five();
			break;

		case SIX:
			value_image = get_number_six();
			break;

		case SEVEN:
			value_image = get_number_seven();
			break;

		case EIGHT:
			value_image = get_number_eight();
			break;

		case NINE:
			value_image = get_number_nine();
			break;

		case TEN:
			value_image = get_number_ten();
			break;

		case JACK:
			value_image = get_letter_J();
			break;

		case QUEEN:
			value_image = get_letter_Q();
			break;

		case KING:
			value_image = get_letter_K();
			break;

	}

	st7789_draw_rectangle(card_origin, CARDS_SIZE, ST7789_COLOR_WHITE);
	st7789_draw_image(figure_origin, (vector_t){figure_origin.x + FIGURE_SIZE.x, figure_origin.y + FIGURE_SIZE.y}, figure_image);
	st7789_draw_image(value_origin, (vector_t){value_origin.x + VALUE_SIZE.x, value_origin.y + VALUE_SIZE.y}, value_image);
}
