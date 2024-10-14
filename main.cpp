#include <iostream>

using namespace std;

class xo_env {
private:
    int board[3][3];  // 2D array for the 3x3 board
public:
    // Constructor to initialize the board with empty values (0)
    xo_env() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
    }
    void print_bord(){
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
    int move(int a, int b, int c) {
        board[a][b] = c;
        return 1;
    }
    int check_the_move(int a, int b, int c) {
        if(a < 0 || a >= 3 || b < 0 || b >= 3 || (c != 1 && c != 2)){
            return -1;
        }
        if (board[a][b] != 0) {
            return -1;
        }
        return 0;
    }
    int check_winner() {
        // Check rows for winner
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
                return board[i][0];
            }
        }

        // Check columns for winner
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != 0) {
                return board[0][j];
            }
        }

        // Check diagonals for winner
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
            return board[0][0];
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
            return board[0][2];
        }

        // No winner found, return 0
        return 0;
    }
};

class agent{
private:
    int player;
public:
    agent(int player_number){
        player = player_number;
    }
    void make_move(xo_env& env){
        int a;
        int b;
        do {
            a = rand() % 3;  // Random row index
            b = rand() % 3;  // Random column index
        } while (env.check_the_move(a, b, player) == -1);
        env.move(a, b, player);

    }
};



int main(){
    xo_env xo_bord;
    agent computer = 2;
    agent you=1;
    int won = 0;
    int turn = 0;
    while(won == 0){
        cout << '\n';
        computer.make_move(xo_bord);
        you.make_move(xo_bord);
        won = xo_bord.check_winner();
        turn++;
        xo_bord.print_bord();

    }
    if (won == 1) {
        cout << "Player 1 (X) wins!\n";
    } else if (won == 2) {
        cout << "Player 2 (O) wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
}