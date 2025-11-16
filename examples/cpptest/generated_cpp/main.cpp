#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <time.h>
#include "Environment.h"
#include "at_key.h"
#include "at_door.h"
#include "at_target.h"
#include "has_key_check.h"
#include "door_unlocked_check.h"
#include "need_move_to_key.h"
#include "need_move_to_door.h"
#include "need_move_to_target.h"
#include "move_toward_key.h"
#include "pick_up_key.h"
#include "move_toward_door.h"
#include "unlock_door.h"
#include "move_toward_target.h"

int main(int argc, char** argv) {
    // Create behavior tree factory
    BT::BehaviorTreeFactory factory;

    // Create environment
    Environment environment;

    // Register all custom nodes
    factory.registerNodeType<at_key>("at_key");
    factory.registerNodeType<at_door>("at_door");
    factory.registerNodeType<at_target>("at_target");
    factory.registerNodeType<has_key_check>("has_key_check");
    factory.registerNodeType<door_unlocked_check>("door_unlocked_check");
    factory.registerNodeType<need_move_to_key>("need_move_to_key");
    factory.registerNodeType<need_move_to_door>("need_move_to_door");
    factory.registerNodeType<need_move_to_target>("need_move_to_target");
    factory.registerNodeType<move_toward_key>("move_toward_key");
    factory.registerNodeType<pick_up_key>("pick_up_key");
    factory.registerNodeType<move_toward_door>("move_toward_door");
    factory.registerNodeType<unlock_door>("unlock_door");
    factory.registerNodeType<move_toward_target>("move_toward_target");

    // Create tree from XML
    auto tree = factory.createTreeFromFile("/tmp/gridworld_output/build/tree.xml");

    // Get blackboard and initialize variables
    auto blackboard = tree.rootBlackboard();
    blackboard->set<int>("agent_x", 0);
    blackboard->set<int>("agent_y", 0);
    blackboard->set<int>("has_key", 0);
    blackboard->set<int>("door_unlocked", 0);
    blackboard->set<int>("step_count", 0);

    // Initialize environment
    environment.initialize();

    // Print initial state
    std::cout << "------------------------" << std::endl;
    std::cout << "Initial State" << std::endl;
    std::cout << "agent_x = " << blackboard->get<int>("agent_x") << std::endl;
    std::cout << "agent_y = " << blackboard->get<int>("agent_y") << std::endl;
    std::cout << "has_key = " << blackboard->get<int>("has_key") << std::endl;
    std::cout << "door_unlocked = " << blackboard->get<int>("door_unlocked") << std::endl;
    std::cout << "step_count = " << blackboard->get<int>("step_count") << std::endl;

    // Run tree for max iterations
    for (int count = 0; count < 50; count++) {
        std::cout << "------------------------" << std::endl;
        std::cout << "Tick: " << (count + 1) << std::endl;

        if (!environment.check_tick_condition()) {
            std::cout << "Tick condition no longer holds. Exiting." << std::endl;
            break;
        }

        // Pre-tick update
        environment.pre_tick_update();

        // Tick the tree
        BT::NodeStatus status = tree.tickOnce();

        // Post-tick update
        environment.post_tick_update();

        // Print state
        std::cout << "Status: " << BT::toStr(status) << std::endl;
        std::cout << "agent_x = " << blackboard->get<int>("agent_x") << std::endl;
        std::cout << "agent_y = " << blackboard->get<int>("agent_y") << std::endl;
        std::cout << "has_key = " << blackboard->get<int>("has_key") << std::endl;
        std::cout << "door_unlocked = " << blackboard->get<int>("door_unlocked") << std::endl;
        std::cout << "step_count = " << blackboard->get<int>("step_count") << std::endl;
    }

    return 0;
}
