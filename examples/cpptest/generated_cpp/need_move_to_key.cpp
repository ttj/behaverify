#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "need_move_to_key.h"

need_move_to_key::need_move_to_key(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode(name, config) {

}

BT::PortsList need_move_to_key::providedPorts() {
    return {BT::InputPort<int>("agent_x"), BT::InputPort<int>("agent_y"), BT::InputPort<int>("has_key")};
}
BT::NodeStatus need_move_to_key::tick() {
    int agent_x;
    if(!getInput("agent_x", agent_x)) { throw BT::RuntimeError("Missing Input: agent_x"); }
    int agent_y;
    if(!getInput("agent_y", agent_y)) { throw BT::RuntimeError("Missing Input: agent_y"); }
    int has_key;
    if(!getInput("has_key", has_key)) { throw BT::RuntimeError("Missing Input: has_key"); }
    BT::NodeStatus return_status = ((has_key == 0) && ((agent_x != 1) || (agent_y != 1))) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    return return_status;
}
