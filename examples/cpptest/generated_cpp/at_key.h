#ifndef at_key_header
#define at_key_header

#include <behaviortree_cpp/bt_factory.h>

class at_key : public BT::ConditionNode {
    private:

    public:
        at_key(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
