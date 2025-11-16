#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "door_unlocked_check.h"

door_unlocked_check::door_unlocked_check(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode(name, config) {

}

BT::PortsList door_unlocked_check::providedPorts() {
    return {BT::InputPort<int>("door_unlocked")};
}
BT::NodeStatus door_unlocked_check::tick() {
    int door_unlocked;
    if(!getInput("door_unlocked", door_unlocked)) { throw BT::RuntimeError("Missing Input: door_unlocked"); }
    BT::NodeStatus return_status = (door_unlocked == 1) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    return return_status;
}
