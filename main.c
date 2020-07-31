#include "tic_tac_toe.h"

#define TAG "main"

static struct {
    char* player1; 
    char* player2; 
} _main; 

static void main_init(void) {
    // clear screen
    system("cls"); 

    // initialize
    tic_tac_toe_init(); 

    // dialog
    printf("Welcome to the best version of tic-tac-toe you will ever play\n"); 
    printf("Player1, %s, you are %s's\n", _main.player1, TIC_TAC_TOE_PLAYER_1_SYMBOL); 
    printf("Player2, %s, you are %s's\n", _main.player2, TIC_TAC_TOE_PLAYER_2_SYMBOL);
}

static status_t main_prompt_turn(tic_tac_toe_player_t player) {
    char* player_str = player == TIC_TAC_TOE_PLAYER_1 ? _main.player1 : _main.player2; 
    int x; 
    int y; 
    printf("%s: Please enter the index you would like to place your token\n\t(x y): ", player_str); 
    scanf("%d %d", &x, &y); 

    // error check input
    if (x < 0 || x > TIC_TAC_TOE_BOARD_WIDTH || y < 0 || y > TIC_TAC_TOE_BOARD_WIDTH) {
        printf("Error: Please enter valid input\n"); 
        return STATUS_FAIL;
    }

    return tic_tac_toe_play_turn(player, x, y); 
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("%s: invalid arguments provided. Example usage: main \"Blake\" \"Sydney\"\n", TAG); 
        return -1; 
    }

    _main.player1 = argv[1]; 
    _main.player2 = argv[2];     

    // initialize
    main_init(); 

    // play game
    status_t status; 
    int turn;
    int turn_count;  
    while (1) {
        turn = (turn_count++) % 2; 
        tic_tac_toe_print_board(); 
        status = main_prompt_turn(turn); 
        char* player_str = turn == TIC_TAC_TOE_PLAYER_1 ? "Player1" : "Player2"; 
        switch (status) {
            case STATUS_SUCCESS: {
                break;
            } case STATUS_PLACEMENT_UNAVAILABLE: {
                printf("Spot is unavailable, enter a valid placement\n"); 
                main_prompt_turn(turn); 
            } case STATUS_GAME_OVER: {
                printf("Game over. Thank you for playing!\n");
                return 0;
            } case STATUS_PLAYER_WON: {
                printf("%s won! Thank you for playing. Please play again (pretty please)\n", player_str);
                return 0; 
            } case STATUS_FAIL: {
                main_prompt_turn(turn); 
                break; 
            } default: {
                printf("Something went very wrong, I don't know how we got here.. returning"); 
                return -1;
            }
        }
    }

    return 0; 
}