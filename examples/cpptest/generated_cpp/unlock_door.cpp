#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "unlock_door.h"

unlock_door::unlock_door(const std::string& name, const BT::NodeConfiguration& config) : BT::SyncActionNode(name, config) {

}

BT::PortsList unlock_door::providedPorts() {
    return {BT::InputPort<int>("door_unlocked"), BT::InputPort<int>("step_count"), BT::BidirectionalPort<int>("door_unlocked"), BT::BidirectionalPort<int>("step_count")};
}

BT::NodeStatus unlock_door::tick() {
    BT::NodeStatus return_status;
    int door_unlocked;
    if(!getInput("door_unlocked", door_unlocked)) { throw BT::RuntimeError("Missing Input: door_unlocked"); }
    int step_count;
    if(!getInput("step_count", step_count)) { throw BT::RuntimeError("Missing Input: step_count"); }
    door_unlocked = 1;
    step_count = (step_count + 1);
    return_status = BT::NodeStatus::SUCCESS;
    setOutput("door_unlocked", door_unlocked);
    setOutput("step_count", step_count);
    return return_status;
}

