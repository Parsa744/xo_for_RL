// xo_env.h
#ifndef XO_ENV_H
#define XO_ENV_H

#include <iostream>
using namespace std;

class xo_env {
private:
    int board[3][3];  // 2D array for the 3x3 board
public:
    xo_env();  // Constructor to initialize the board
    int getElement(int a, int b);
    void print_bord();
    int move(int a, int b, int c);
    int check_the_move(int a, int b, int c);
    int check_winner();
};

#endif // XO_ENV_H
