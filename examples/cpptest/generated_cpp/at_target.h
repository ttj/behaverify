#ifndef at_target_header
#define at_target_header

#include <behaviortree_cpp/bt_factory.h>

class at_target : public BT::ConditionNode {
    private:

    public:
        at_target(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
