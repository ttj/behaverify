#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "pick_up_key.h"

pick_up_key::pick_up_key(const std::string& name, const BT::NodeConfiguration& config) : BT::SyncActionNode(name, config) {

}

BT::PortsList pick_up_key::providedPorts() {
    return {BT::InputPort<int>("has_key"), BT::InputPort<int>("step_count"), BT::BidirectionalPort<int>("has_key"), BT::BidirectionalPort<int>("step_count")};
}

BT::NodeStatus pick_up_key::tick() {
    BT::NodeStatus return_status;
    int has_key;
    if(!getInput("has_key", has_key)) { throw BT::RuntimeError("Missing Input: has_key"); }
    int step_count;
    if(!getInput("step_count", step_count)) { throw BT::RuntimeError("Missing Input: step_count"); }
    has_key = 1;
    step_count = (step_count + 1);
    return_status = BT::NodeStatus::SUCCESS;
    setOutput("has_key", has_key);
    setOutput("step_count", step_count);
    return return_status;
}

