// xo_env.cpp
#include "xo_env.h"

xo_env::xo_env() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

int xo_env::getElement(int a, int b) {
    return board[a][b];
}

void xo_env::print_bord() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0)
                cout << ".";
            else if (board[i][j] == 1)
                cout << "X";
            else if (board[i][j] == 2)
                cout << "O";
            cout << " ";
        }
        cout << "\n";
    }
}

int xo_env::move(int a, int b, int c) {
    board[a][b] = c;
    return 1;
}

int xo_env::check_the_move(int a, int b, int c) {
    if (a < 0 || a >= 3 || b < 0 || b >= 3 || (c != 1 && c != 2)) {
        return -1;
    }
    if (board[a][b] != 0) {
        return -1;
    }
    return 0;
}

int xo_env::check_winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
            return board[i][0];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != 0) {
            return board[0][j];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
        return board[0][2];
    }

    return 0;
}
