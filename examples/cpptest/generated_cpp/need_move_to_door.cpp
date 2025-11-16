#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "need_move_to_door.h"

need_move_to_door::need_move_to_door(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode(name, config) {

}

BT::PortsList need_move_to_door::providedPorts() {
    return {BT::InputPort<int>("agent_x"), BT::InputPort<int>("agent_y"), BT::InputPort<int>("has_key"), BT::InputPort<int>("door_unlocked")};
}
BT::NodeStatus need_move_to_door::tick() {
    int agent_x;
    if(!getInput("agent_x", agent_x)) { throw BT::RuntimeError("Missing Input: agent_x"); }
    int agent_y;
    if(!getInput("agent_y", agent_y)) { throw BT::RuntimeError("Missing Input: agent_y"); }
    int has_key;
    if(!getInput("has_key", has_key)) { throw BT::RuntimeError("Missing Input: has_key"); }
    int door_unlocked;
    if(!getInput("door_unlocked", door_unlocked)) { throw BT::RuntimeError("Missing Input: door_unlocked"); }
    BT::NodeStatus return_status = ((has_key == 1) && (door_unlocked == 0) && ((agent_x != 2) || (agent_y != 2))) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    return return_status;
}
