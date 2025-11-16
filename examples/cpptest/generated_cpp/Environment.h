#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <functional>

class Environment {
private:

public:
    Environment();
    void initialize();
    void pre_tick_update();
    void post_tick_update();
    bool check_tick_condition();
};

#endif
