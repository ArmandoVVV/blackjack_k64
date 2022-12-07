/*
 * state_machine.c
 *
 *  Created on: Dec 3, 2022
 *      Author: armando
 */
#include "state_machine.h"

#include "blackjack.h"
#include "images.h"
#include "drawing.h"
#include "pit.h"
#include "records.h"
#include "sounds.h"
#include "dma.h"

static volatile boolean_t g_white_button_pressed = FALSE;
static volatile boolean_t g_green_button_pressed = FALSE;
static volatile boolean_t g_red_button_pressed = FALSE;
static volatile boolean_t g_blue_button_pressed = FALSE;

static volatile boolean_t g_exit_flag = FALSE;

void button_pressed(uint32_t flags){
	if( FALSE == get_pit2_flag() ){
		set_pit2_flag(TRUE);
		PIT_start(kPIT_Chnl_2);

		g_white_button_pressed = (flags & WHITE_BUTTON_MASK) >> WHITE_BUTTON_PIN;
		g_green_button_pressed = (flags & GREEN_BUTTON_MASK) >> GREEN_BUTTON_PIN;
		g_red_button_pressed = (flags & RED_BUTTON_MASK) >> RED_BUTTON_PIN;
		g_blue_button_pressed = (flags & BLUE_BUTTON_MASK) >> BLUE_BUTTON_PIN;
	}
}

static void clean_flags(void){
	g_white_button_pressed = FALSE;
	g_green_button_pressed = FALSE;
	g_red_button_pressed = FALSE;
	g_blue_button_pressed = FALSE;
}

//************** BLACKJACK1 STATE MACHINE STATE FUNCTIONS ***************//

static inline void state_initial_state(bj1_state_t* current_state, player_t* player1, player_t* dealer){
	draw_background_image();

	shuffle_cards(100);
	setup_player_cards(player1);
	setup_dealer_cards(dealer);

	draw_card( player1->cards[0], player1->card_position );
	set_next_card_position(player1);

	draw_card( player1->cards[1], player1->card_position );
	set_next_card_position(player1);

	draw_flipped_card(dealer->card_position);
	set_next_card_position(dealer);

	draw_card( dealer->cards[1], dealer->card_position );
	set_next_card_position(dealer);

	draw_blackjack_player();
	draw_blackjack_dealer();

	draw_number(player1->cards_value / 10, PLAYER1_CARDS_VALUE_ORIGIN);
	draw_number(player1->cards_value % 10, (vector_t){ PLAYER1_CARDS_VALUE_ORIGIN.x + 10, 160});

	// player wins if he has blackjack on first hand
	if(21 == player1->cards_value){
		*current_state = PLAYER_WON;
	}
	else{
		*current_state = PLAYER_TURN;

		// play cards sound
		setup_dma_transfer_config(CARD_SOUND_BYTES, get_card_sound());
		PIT_start(kPIT_Chnl_0);
	}

	clean_flags();
}

static inline void state_player_turn(bj1_state_t* current_state, player_t* player1, player_t* dealer){
	if(g_white_button_pressed){
		player_add_card(player1, get_card());
		draw_card( player1->cards[player1->total_cards - 1], player1->card_position );
		set_next_card_position(player1);

		// play cards sound
		setup_dma_transfer_config(CARD_SOUND_BYTES, get_card_sound());
		PIT_start(kPIT_Chnl_0);

		draw_number(player1->cards_value / 10, PLAYER1_CARDS_VALUE_ORIGIN);
		draw_number(player1->cards_value % 10, (vector_t){ PLAYER1_CARDS_VALUE_ORIGIN.x + 10, 160});

		clean_flags();
	}

	if(g_green_button_pressed){
		*current_state = DEALER_TURN;
		//reveals hidden card
		draw_card( dealer->cards[0], DEALER_CARD_ORIGIN );

		// play cards sound
		setup_dma_transfer_config(CARD_SOUND_BYTES, get_card_sound());
		PIT_start(kPIT_Chnl_0);

		// delay
		set_pit1_flag(TRUE);
		PIT_start(kPIT_Chnl_1);

		clean_flags();
	}

	if( player_lost(player1) ){
		*current_state = PLAYER_LOST;
	}
}

static inline void state_dealer_turn(bj1_state_t* current_state, player_t* player1, player_t* dealer){
	if(dealer_complete(dealer)){
		if( dealer_lost(dealer, player1)) {
			*current_state = PLAYER_WON;
		}
		else if(game_tied(dealer, player1)){
			*current_state = GAME_TIED;
		}
		else{
			*current_state = PLAYER_LOST;
		}

	}
	else{
		if( FALSE == get_pit1_flag() ){
			set_pit1_flag(TRUE);
			PIT_start(kPIT_Chnl_1);

			// play cards sound
			setup_dma_transfer_config(CARD_SOUND_BYTES, get_card_sound());
			PIT_start(kPIT_Chnl_0);

			player_add_card(dealer, get_card());
			draw_card( dealer->cards[dealer->total_cards - 1], dealer->card_position );
			set_next_card_position(dealer);
		}
	}

	// draws dealer current cards value
	draw_number(dealer->cards_value / 10, DEALER_CARDS_VALUE_ORIGIN);
	draw_number(dealer->cards_value % 10, (vector_t){ DEALER_CARDS_VALUE_ORIGIN.x + 10, DEALER_CARDS_VALUE_ORIGIN.y});

	clean_flags();

}

static inline void state_player_lost(bj1_state_t* current_state){
	draw_you_lost((vector_t){ 70, 145});
	draw_play_again( PLAY_AGAIN_ORIGIN );
	draw_exit( EXIT_ORIGIN );

	setup_dma_transfer_config(LOST_SOUND_BYTES, get_error_sound());
	PIT_start(kPIT_Chnl_0);

	*current_state = END_SCREEN;
}

static inline void state_player_won(bj1_state_t* current_state){
	draw_you_won((vector_t){ 70, 145});
	draw_play_again( PLAY_AGAIN_ORIGIN );
	draw_exit( EXIT_ORIGIN );

	// writes on i2c memory
	add_one_game_won();

	setup_dma_transfer_config(WIN_SOUND_BYTES, get_good_sound());
	PIT_start(kPIT_Chnl_0);

	*current_state = END_SCREEN;
}

static inline void state_game_tied(bj1_state_t* current_state){
	draw_game_tied((vector_t){ 70, 145});
	draw_play_again( PLAY_AGAIN_ORIGIN );
	draw_exit( EXIT_ORIGIN );

	setup_dma_transfer_config(LOST_SOUND_BYTES, get_error_sound());
	PIT_start(kPIT_Chnl_0);

	*current_state = END_SCREEN;
}

static inline void state_end_screen(bj1_state_t* current_state){
	if(g_blue_button_pressed){
		*current_state = INITIAL_STATE;
		// writes on i2c memory
		add_one_game_played();

		clean_flags();
	}

	if(g_red_button_pressed){
		*current_state = INITIAL_STATE;
		// writes on i2c memory
		add_one_game_played();

		clean_flags();

		g_exit_flag = TRUE;
	}
}
//***************** ************************************ ****************//

//***************** SYSTEM STATE MACHINE STATE FUNCTIONS ****************//
static inline void state_menu(state_t* current_state){
	draw_menu_image();

	if(g_white_button_pressed){
		*current_state = BLACKJACK1;

		clean_flags();
	}
	else if(g_red_button_pressed){
		*current_state = RECORDS;
		draw_records();

		clean_flags();
	}
}

static inline void state_blackjack1(state_t* current_state){
	if(g_exit_flag){
		*current_state = MENU;
		g_exit_flag = FALSE;
	}
	else{
		blackjack1_state_machine();
	}
}

static inline void state_records(state_t* current_state){
	if(g_red_button_pressed){
		*current_state = MENU;

		clean_flags();
	}
	else if(g_green_button_pressed){
		clear_games_won();

		clean_flags();
	}
	else if(g_blue_button_pressed){
		clear_games_played();

		clean_flags();
	}
}
//***************** ************************************ ****************//

void state_machine(void){
	static state_t current_state = MENU;

	switch(current_state){
		case MENU:
			state_menu(&current_state);
			break;
		case BLACKJACK1:
			state_blackjack1(&current_state);
			break;
		case BLACKJACK2:
			break;
		case POKER:
			break;
		case RECORDS:
			state_records(&current_state);

			break;
	}
}

bj1_state_t blackjack1_state_machine(void){
	static player_t player1;
	static player_t dealer;
	static bj1_state_t current_state = INITIAL_STATE;


	switch(current_state){
		case INITIAL_STATE:
			state_initial_state(&current_state, &player1, &dealer);
			break;

		case PLAYER_TURN:
			state_player_turn(&current_state, &player1, &dealer);
			break;

		case DEALER_TURN:
			state_dealer_turn(&current_state, &player1, &dealer);
			break;

		case PLAYER_LOST:
			state_player_lost(&current_state);
			break;

		case PLAYER_WON:
			state_player_won(&current_state);
			break;

		case GAME_TIED:
			state_game_tied(&current_state);
			break;

		case END_SCREEN:
			state_end_screen(&current_state);
			break;
	}

	return current_state;
}
