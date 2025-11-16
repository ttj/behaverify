#ifndef door_unlocked_check_header
#define door_unlocked_check_header

#include <behaviortree_cpp/bt_factory.h>

class door_unlocked_check : public BT::ConditionNode {
    private:

    public:
        door_unlocked_check(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
