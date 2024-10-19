// agent.h
#ifndef AGENT_H
#define AGENT_H

#include "xo_env.h"

class agent {
private:
    int player;
    int reward;
    int punish;
    xo_env rl_bord;
    int training_loop;

public:
    agent(int player_number, int reward, int punish, xo_env rl_env, int training_ep);

    void setReward(int r);
    int getReward() const;

    void setPunish(int p);
    int getPunish() const;

    void setTrainingLoop(int training_ep);
    int getTrainingLoop() const;

    void setRl_bord(xo_env bord);
    xo_env getRl_bord() const;

    void random_move(xo_env& env);
    int smart_last_move(xo_env& env);
    void make_move(xo_env& env, bool use_smart_move = true);
    int getID() const;
};

#endif // AGENT_H
