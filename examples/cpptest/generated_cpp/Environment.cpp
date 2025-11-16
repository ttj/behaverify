#include "Environment.h"

Environment::Environment() {
}

void Environment::initialize() {
}

void Environment::pre_tick_update() {
    // No pre-tick updates
}

void Environment::post_tick_update() {
    // No post-tick updates
}

bool Environment::check_tick_condition() {
    return true;  // Iteration limit handled in main loop
}
