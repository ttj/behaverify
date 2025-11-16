#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "move_toward_door.h"

move_toward_door::move_toward_door(const std::string& name, const BT::NodeConfiguration& config) : BT::SyncActionNode(name, config) {

}

BT::PortsList move_toward_door::providedPorts() {
    return {BT::InputPort<int>("agent_x"), BT::InputPort<int>("agent_y"), BT::InputPort<int>("step_count"), BT::BidirectionalPort<int>("agent_x"), BT::BidirectionalPort<int>("agent_y"), BT::BidirectionalPort<int>("step_count")};
}

BT::NodeStatus move_toward_door::tick() {
    BT::NodeStatus return_status;
    int agent_x;
    if(!getInput("agent_x", agent_x)) { throw BT::RuntimeError("Missing Input: agent_x"); }
    int agent_y;
    if(!getInput("agent_y", agent_y)) { throw BT::RuntimeError("Missing Input: agent_y"); }
    int step_count;
    if(!getInput("step_count", step_count)) { throw BT::RuntimeError("Missing Input: step_count"); }
    agent_x = ((agent_x < 2) ? (agent_x + 1) : ((agent_x > 2) ? (agent_x - 1) : (agent_x)));
    agent_y = (((agent_x == 2) && (agent_y < 2)) ? (agent_y + 1) : (((agent_x == 2) && (agent_y > 2)) ? (agent_y - 1) : (agent_y)));
    step_count = (step_count + 1);
    return_status = BT::NodeStatus::SUCCESS;
    setOutput("agent_x", agent_x);

    setOutput("agent_y", agent_y);

    setOutput("step_count", step_count);
    return return_status;
}

