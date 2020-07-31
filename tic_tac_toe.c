#include "tic_tac_toe.h"

#define TAG "tic_tac_toe"
#define MAX_NUM_TURNS (TIC_TAC_TOE_BOARD_WIDTH * TIC_TAC_TOE_BOARD_HEIGHT)

static enum {
    DEFAULT_INT,
    PLAYER_1_INT = 1,
    PLAYER_2_INT = 5,
} player_int_t; 

static struct {
    int num_turns; 
    tic_tac_toe_player_t winner; 
    int board[TIC_TAC_TOE_BOARD_WIDTH][TIC_TAC_TOE_BOARD_HEIGHT]; 
} _data;

/**
 * Static helpers
 **/
static char* player_to_token(tic_tac_toe_player_t player) { 
    if (TIC_TAC_TOE_PLAYER_1 == player) { 
        return TIC_TAC_TOE_PLAYER_1_SYMBOL; 
    } else if (TIC_TAC_TOE_PLAYER_2 == player) { 
        return TIC_TAC_TOE_PLAYER_2_SYMBOL; 
    } else { 
        return " "; 
    } 
}

static char* int_to_token(int num) { 
    if (PLAYER_1_INT == num) { 
        return TIC_TAC_TOE_PLAYER_1_SYMBOL; 
    } else if (PLAYER_2_INT == num) { 
        return TIC_TAC_TOE_PLAYER_2_SYMBOL; 
    } else { 
        return " "; 
    } 
} 

static int player_to_int(tic_tac_toe_player_t player) { \
    if (TIC_TAC_TOE_PLAYER_1 == player) { 
        return PLAYER_1_INT; 
    } else if (TIC_TAC_TOE_PLAYER_2 == player) { 
        return PLAYER_2_INT; 
    } else { 
        return DEFAULT_INT; 
    } 
} 

static bool placement_available(int x, int y) {
    if (tic_tac_toe_game_is_over()) {
        return false; 
    }

    return _data.board[x][y] == DEFAULT_INT;
}

static bool player_did_win(tic_tac_toe_player_t player) {
    int winning_num = player == TIC_TAC_TOE_PLAYER_1 ? PLAYER_1_INT * 3 : PLAYER_2_INT * 3; 
    bool did_win = false; 

    if (_data.board[0][0] + _data.board[1][0] + _data.board[2][0] == winning_num) {
        // top row directly across
        did_win = true;  
    } else if (_data.board[0][0] + _data.board[1][1] + _data.board[2][2] == winning_num) {
        // diagnol left-top to bottom-right
        did_win = true; 
    } else if (_data.board[0][0] + _data.board[0][1] + _data.board[0][2] == winning_num) {
        // left column
        did_win = true; 
    } else if (_data.board[1][0] + _data.board[1][1] + _data.board[1][2] == winning_num) {
        // middle row across
        did_win = true; 
    } else if (_data.board[2][0] + _data.board[2][1] + _data.board[2][2] == winning_num) {
        // bottom row across
        did_win = true; 
    } else if (_data.board[0][2] + _data.board[1][1] + _data.board[2][0] == winning_num) {
        // diagnol bottom-left to top-right
        did_win = true; 
    } else if (_data.board[1][0] + _data.board[1][1] + _data.board[1][2] == winning_num) {
        // middle column
        did_win = true; 
    } else if (_data.board[2][0] + _data.board[2][1] + _data.board[2][2] == winning_num) {
        // right column
        did_win = true; 
    }

    if (did_win) {
        _data.winner = player; 
    }

    return did_win; 
}

/**
 * API definitions
 */
tic_tac_toe_player_t tic_tac_toe_get_winner(void) {
    return _data.winner; 
}

bool tic_tac_toe_game_is_over(void) {
    if (_data.num_turns >= MAX_NUM_TURNS) {
        return true; 
    }

    return player_did_win(TIC_TAC_TOE_PLAYER_1) || player_did_win(TIC_TAC_TOE_PLAYER_2);
}

status_t tic_tac_toe_play_turn(tic_tac_toe_player_t player, int x, int y) {
    // check if specified placement is empty
    if (!placement_available(x, y)) {
        return STATUS_PLACEMENT_UNAVAILABLE;
    }

    // if we make it here, token can be placed
    _data.board[x][y] = player_to_int(player); 

    // if game is over, that means the player won
    if (tic_tac_toe_game_is_over()) {
        return STATUS_PLAYER_WON; 
    }

    // if player didn't win, throw a success status
    return STATUS_SUCCESS; 
}

void tic_tac_toe_print_board(void) {
    printf("\n\t  %s  |  %s  |  %s\n", int_to_token(_data.board[0][0]), int_to_token(_data.board[1][0]), int_to_token(_data.board[2][0])); 
    printf("\t-----------------\n"); 
    printf("\t  %s  |  %s  |  %s\n", int_to_token(_data.board[0][1]), int_to_token(_data.board[1][1]), int_to_token(_data.board[2][1])); 
    printf("\t-----------------\n"); 
    printf("\t  %s  |  %s  |  %s\n\n", int_to_token(_data.board[0][2]), int_to_token(_data.board[1][2]), int_to_token(_data.board[2][2])); 
}

void tic_tac_toe_init() {
    for (int i = 0; i < TIC_TAC_TOE_BOARD_WIDTH; i++) {
        for (int j = 0; j < TIC_TAC_TOE_BOARD_HEIGHT; j++) {
            _data.board[i][j] = DEFAULT_INT; 
        }
    } 
}