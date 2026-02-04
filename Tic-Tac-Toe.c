#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char board[9];
char player1[50] = "Player1";
char player2[50] = "Player2";
char mark1 = 'X';
char mark2 = 'O';
int wins1 = 0;
int wins2 = 0;
int draws = 0;

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void reset_board(void) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

void print_board(void) {
    printf("\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0], board[1], board[2]);
    printf("-----+-----+-----\n");
    printf("  %c  |  %c  |  %c  \n", board[3], board[4], board[5]);
    printf("-----+-----+-----\n");
    printf("  %c  |  %c  |  %c  \n", board[6], board[7], board[8]);
    printf("     |     |     \n\n");
}

int check_win(char mark) {
    if (board[0] == mark && board[1] == mark && board[2] == mark) return 1;
    if (board[3] == mark && board[4] == mark && board[5] == mark) return 1;
    if (board[6] == mark && board[7] == mark && board[8] == mark) return 1;

    if (board[0] == mark && board[3] == mark && board[6] == mark) return 1;
    if (board[1] == mark && board[4] == mark && board[7] == mark) return 1;
    if (board[2] == mark && board[5] == mark && board[8] == mark) return 1;

    if (board[0] == mark && board[4] == mark && board[8] == mark) return 1;
    if (board[2] == mark && board[4] == mark && board[6] == mark) return 1;

    return 0;
}

int board_full(void) {
    for (int i = 0; i < 9; i++) {
        if (board[i] >= '1' && board[i] <= '9') {
            return 0;
        }
    }
    return 1;
}

void load_scores(void) {
    FILE *f = fopen("scores.txt", "r");
    if (f == NULL) {
        wins1 = 0;
        wins2 = 0;
        draws = 0;
        return;
    }

    fscanf(f, "%d %d %d", &wins1, &wins2, &draws);
    fclose(f);
}

void save_scores(void) {
    FILE *f = fopen("scores.txt", "w");
    if (f == NULL) {
        printf("Warning: Could not save scores.\n");
        return;
    }

    fprintf(f, "%d %d %d\n", wins1, wins2, draws);
    fclose(f);
}

void log_result(int winner) {
    FILE *f = fopen("history.log", "a");
    if (f == NULL) {
        return;
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';

    if (winner == 1) {
        fprintf(f, "[%s] %s (%c) defeated %s (%c)\n",
                time_str, player1, mark1, player2, mark2);
    } else if (winner == 2) {
        fprintf(f, "[%s] %s (%c) defeated %s (%c)\n",
                time_str, player2, mark2, player1, mark1);
    } else {
        fprintf(f, "[%s] Draw between %s (%c) and %s (%c)\n",
                time_str, player1, mark1, player2, mark2);
    }

    fclose(f);
}

void view_stats(void) {
    int total = wins1 + wins2 + draws;
    printf("\nStatistics:\n");
    printf("%s (%c) Wins: %d\n", player1, mark1, wins1);
    printf("%s (%c) Wins: %d\n", player2, mark2, wins2);
    printf("Draws: %d\n", draws);
    printf("Total Games: %d\n\n", total);
}

void customize_players(void) {
    printf("\nEnter name for first player: ");
    scanf("%49s", player1);

    printf("Enter name for second player: ");
    scanf("%49s", player2);

    printf("\nChoose symbol for %s (any printable character): ", player1);
    scanf(" %c", &mark1);

    printf("Choose different symbol for %s: ", player2);
    scanf(" %c", &mark2);
    while (mark2 == mark1) {
        printf("Symbols must be different. Choose again: ");
        scanf(" %c", &mark2);
    }

    if (mark1 != 'X' && mark2 == 'X') {
        char temp_name[50];
        char temp_mark;

        strcpy(temp_name, player1);
        strcpy(player1, player2);
        strcpy(player2, temp_name);

        temp_mark = mark1;
        mark1 = mark2;
        mark2 = temp_mark;

        printf("Swapped players so 'X' goes first.\n");
    }

    clear_input();
    printf("Customization applied.\n\n");
}

int play_match(void) {
    int current_player;
    reset_board();

    current_player = (mark1 == 'X') ? 1 : 2;

    while (1) {
        int choice;
        int valid;
        int index;
        char mark;
        char *name;

        clear_screen();
        print_board();

        if (current_player == 1) {
            mark = mark1;
            name = player1;
        } else {
            mark = mark2;
            name = player2;
        }

        printf("%s (%c) turn > Position (1-9) or 0 to exit: ", name, mark);
        valid = scanf("%d", &choice);
        clear_input();

        if (valid != 1) {
            printf("Invalid input. Enter a number (0-9).\n\n");
            continue;
        }

        if (choice == 0) {
            printf("Match exited.\n\n");
            return -1;
        }

        if (choice < 1 || choice > 9) {
            printf("Invalid input. Use 1-9, or 0 to exit.\n\n");
            continue;
        }

        index = choice - 1;
        if (board[index] == mark1 || board[index] == mark2) {
            printf("Position taken.\n\n");
            continue;
        }

        board[index] = mark;

        if (check_win(mark)) {
            print_board();
            printf("%s (%c) wins the match.\n\n", name, mark);
            return current_player;
        }

        if (board_full()) {
            print_board();
            printf("Draw.\n\n");
            return 0;
        }

        current_player = 3 - current_player;
    }
}

int main(void) {
    char choice;

    load_scores();

    printf("\nTic-Tac-Toe\n\n");

    while (1) {
        printf("Main Menu:\n");
        printf("1. Play Match\n");
        printf("2. Customize Players & Symbols\n");
        printf("3. View Statistics\n");
        printf("4. Reset Scores\n");
        printf("5. Exit\n");
        printf("> Choose (1-5): ");

        scanf(" %c", &choice);
        clear_input();

        if (choice == '1') {
            int winner = play_match();
            if (winner == -1) {
                continue;
            }

            if (winner == 1) wins1++;
            else if (winner == 2) wins2++;
            else draws++;

            log_result(winner);
            save_scores();
        } else if (choice == '2') {
            customize_players();
        } else if (choice == '3') {
            view_stats();
        } else if (choice == '4') {
            wins1 = 0;
            wins2 = 0;
            draws = 0;
            save_scores();
            remove("history.log");
            printf("Scores and history reset.\n\n");
        } else if (choice == '5') {
            printf("Goodbye.\n\n");
            return 0;
        } else {
            printf("Invalid option. Choose 1-5.\n\n");
        }
    }

    return 0;
}
