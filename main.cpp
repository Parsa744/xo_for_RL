// main.cpp
#include "utilities.h"  // For save_multiple_vectors_to_file and calculate_average
#include "xo_env.h"     // For the xo_env class
#include "agent.h"      // For the agent class
#include <ctime>        // For time() to seed random number generator
#include <cstdlib>      // For rand() and srand()
#include <vector>
#include <iostream>

int main() {
    std::vector<int> x_win_list;
    std::vector<int> o_win_list;
    std::vector<int> draw_list;


    int games = 10;
    srand(static_cast<unsigned int>(time(0)));

    for (int j = 0; j < games; j++) {
        int x_win = 0;
        int o_win = 0;
        int draw = 0;

        // Play 'j' games for the current round
        for (int i = 0; i < j; i++) {
            xo_env xo_board;
            xo_env rl_board;
            agent computer(1, 1, -1, rl_board, 2);
            agent human(2, 1, -1, rl_board, 2);

            int won = 0;
            int turn = 0;

            while (won == 0) {
                computer.smart_last_move(xo_board);
                turn++;
                xo_board.print_bord();  // Print the board after the move

                if (turn == 9) {  // All moves made (9 turns), game must be a draw or win
                    won = xo_board.check_winner();  // Check for winner
                    break;
                }

                human.make_move(xo_board, false);  // Use random moves for human
                won = xo_board.check_winner();     // Check if the game is won by human
                turn++;
            }

            if (won == 1) {
                x_win++;
            } else if (won == 2) {
                o_win++;
            } else {
                draw++;
            }
        }

        x_win_list.push_back(x_win);
        o_win_list.push_back(o_win);
        draw_list.push_back(draw);
    }

    std::cout << "X wins on average: " << calculate_average(x_win_list) << std::endl;
    std::cout << "O wins on average: " << calculate_average(o_win_list) << std::endl;
    std::cout << "Draws on average: " << calculate_average(draw_list) << std::endl;

    std::vector<std::vector<int>> all_vectors = {x_win_list, o_win_list, draw_list};
    save_multiple_vectors_to_file(all_vectors, "vectors_data_10.txt");

    return 0;
}
