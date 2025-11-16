#ifndef at_door_header
#define at_door_header

#include <behaviortree_cpp/bt_factory.h>

class at_door : public BT::ConditionNode {
    private:

    public:
        at_door(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
