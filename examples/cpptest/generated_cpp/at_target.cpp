#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "at_target.h"

at_target::at_target(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode(name, config) {

}

BT::PortsList at_target::providedPorts() {
    return {BT::InputPort<int>("agent_x"), BT::InputPort<int>("agent_y")};
}
BT::NodeStatus at_target::tick() {
    int agent_x;
    if(!getInput("agent_x", agent_x)) { throw BT::RuntimeError("Missing Input: agent_x"); }
    int agent_y;
    if(!getInput("agent_y", agent_y)) { throw BT::RuntimeError("Missing Input: agent_y"); }
    BT::NodeStatus return_status = ((agent_x == 4) && (agent_y == 4)) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    return return_status;
}
