#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "has_key_check.h"

has_key_check::has_key_check(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode(name, config) {

}

BT::PortsList has_key_check::providedPorts() {
    return {BT::InputPort<int>("has_key")};
}
BT::NodeStatus has_key_check::tick() {
    int has_key;
    if(!getInput("has_key", has_key)) { throw BT::RuntimeError("Missing Input: has_key"); }
    BT::NodeStatus return_status = (has_key == 1) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    return return_status;
}
