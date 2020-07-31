#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TIC_TAC_TOE_BOARD_WIDTH 3
#define TIC_TAC_TOE_BOARD_HEIGHT 3
#define TIC_TAC_TOE_PLAYER_1_SYMBOL "X"
#define TIC_TAC_TOE_PLAYER_2_SYMBOL "O"

typedef enum {
    STATUS_SUCCESS,
    STATUS_FAIL,
    STATUS_PLAYER_WON,
    STATUS_PLACEMENT_UNAVAILABLE,
    STATUS_GAME_OVER,
} status_t; 

typedef enum {
    TIC_TAC_TOE_PLAYER_1,
    TIC_TAC_TOE_PLAYER_2,
} tic_tac_toe_player_t;

/// Check if the game is over
///
/// @return bool true if the game is over (i.e., a player has scored three in a
/// row or a cats game occurs (no one can possibly win)), false else wise
bool tic_tac_toe_game_is_over(void); 

/// Place marker at position if there is not already a token populating position
///
/// @param player the player who is making the move
/// @param x the x position for the disc to be placed
/// @param y the y position for the disc to be placed
///
/// @return status_t the status of the turn
status_t tic_tac_toe_play_turn(tic_tac_toe_player_t player, int x, int y); 

/// Print current board
void tic_tac_toe_print_board(void); 

/// Get the winner
///
/// @return tic tac toe winner, NULL if no one won the game
tic_tac_toe_player_t tic_tac_toe_get_winner(void);

/// Initilize board
void tic_tac_toe_init(); 