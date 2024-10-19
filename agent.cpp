// agent.cpp
#include "agent.h"
#include <cstdlib> // For rand()

agent::agent(int player_number, int reward, int punish, xo_env rl_env, int training_ep)
        : player(player_number), reward(reward), punish(punish), rl_bord(rl_env), training_loop(training_ep) {}

void agent::setReward(int r) { reward = r; }
int agent::getReward() const { return reward; }

void agent::setPunish(int p) { punish = p; }
int agent::getPunish() const { return punish; }

void agent::setTrainingLoop(int training_ep) { training_loop = training_ep; }
int agent::getTrainingLoop() const { return training_loop; }

void agent::setRl_bord(xo_env bord) { rl_bord = bord; }
xo_env agent::getRl_bord() const { return rl_bord; }

void agent::random_move(xo_env& env) {
    int a, b;
    do {
        a = rand() % 3;
        b = rand() % 3;
    } while (env.check_the_move(a, b, player) == -1);
    env.move(a, b, player);
}

int agent::smart_last_move(xo_env& env) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (env.check_the_move(i, j, player) == 0) {
                xo_env env_copy = env;
                env_copy.move(i, j, player);
                if (env_copy.check_winner() == player) {
                    env.move(i, j, player);
                    return 0;
                }
            }
        }
    }
    random_move(env);
    return 0;
}

void agent::make_move(xo_env& env, bool use_smart_move) {
    if (use_smart_move) {
        smart_last_move(env);
    } else {
        random_move(env);
    }
}

int agent::getID() const { return player; }
