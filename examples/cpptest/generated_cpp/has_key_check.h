#ifndef has_key_check_header
#define has_key_check_header

#include <behaviortree_cpp/bt_factory.h>

class has_key_check : public BT::ConditionNode {
    private:

    public:
        has_key_check(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
