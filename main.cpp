#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For rand() and srand()
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = WINDOW_WIDTH / 3;

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
    int getElement(int a,int b){
        return board[a][b];
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
        srand(static_cast<unsigned int>(time(0)));
        int a;
        int b;
        do {
            a = rand() % 3;  // Random row index
            b = rand() % 3;  // Random column index
        } while (env.check_the_move(a, b, player) == -1);
        env.move(a, b, player);
    }
    int getID() const{
        return player;
    }
};
void renderBoard(SDL_Renderer* renderer, xo_env& env) {
    // Set background to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw grid lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < 3; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
    }

    // Draw X's and O's
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int cell = env.getElement(i, j);
            if (cell == 1) {
                // Draw X
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
                SDL_RenderDrawLine(renderer, (j + 1) * CELL_SIZE, i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE);
            } else if (cell == 2) {
                // Draw O
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_Rect rect = { j * CELL_SIZE + CELL_SIZE / 4, i * CELL_SIZE + CELL_SIZE / 4, CELL_SIZE / 2, CELL_SIZE / 2 };
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
class smart_agent : public agent {
private:
    int reward;
    int punish;
    xo_env rl_bord;
    int training_loop;

public:
    smart_agent(int player, int reward, int punish,xo_env rl_env,int training_ep)
            : agent(player), reward(reward), punish(punish),rl_bord(rl_env),training_loop(training_ep) {}
    void setReward(int r) {
        reward = r;
    }

    int getReward() const {
        return reward;
    }
    void setPunish(int p) {
        punish = p;
    }
    int getPunish() const {
        return punish;
    }
    void setTrainingLop(int trinaing_ep){
        training_loop = trinaing_ep;
    }
    int getTraningLoop() const{
        return training_loop;
    }
    void setRl_bord(xo_env bord){
        rl_bord = bord;
    }
    xo_env getRl_bord() const{
        return rl_bord;
    }
    int smart_move(xo_env& env){
        for(int i;i<3;i++){
            for(int j;j<3;j++){
                if(env.check_the_move(i,j, getID())){
                    xo_env env_copy = env;
                    env_copy.move(i,j,getID());
                    if(env_copy.check_winner()==getID()) {
                        int prives_reward = rl_bord.getElement(i, j);
                        prives_reward += reward;
                        rl_bord.move(i, j, prives_reward);
                    }
                    else if(env_copy.check_winner()==0){
                    } else{
                        int prives_reward = rl_bord.getElement(i, j);
                        prives_reward += punish;
                        rl_bord.move(i, j, prives_reward);
                    }

                }
            }
        }
        for(int i;i<3;i++){
            for(int j;j<3;j++){
            if(env.check_the_move(i,j, getID())&& rl_bord.getElement(i,j) > 0){
                    env.move(i,j,getID());
                    return 0;
                }
            }
        }
        make_move(env);
        return 0;

    }

};

int main(){
    xo_env xo_bord;
    xo_env rl;
    smart_agent computer(1,1,-1,rl,2); // x
    agent you = 2;
    int won = 0;
    int turn = 0;
    // Initialize SDL for UI
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    while(won == 0){

        cout << '\n';
        computer.smart_move(xo_bord);
        turn++;
        //xo_bord.print_bord();
        renderBoard(renderer, xo_bord);
        SDL_Delay(900);
        if(turn==9){
            won = xo_bord.check_winner();
            break;
        }
        cout << '\n';

        you.make_move(xo_bord);
        won = xo_bord.check_winner();
        turn++;
        //xo_bord.print_bord();
        renderBoard(renderer, xo_bord);

    }
    if (won == 1) {
        cout << "Player 1 (X) wins!\n";
    } else if (won == 2) {
        cout << "Player 2 (O) wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
}