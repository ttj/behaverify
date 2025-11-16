#ifndef need_move_to_target_header
#define need_move_to_target_header

#include <behaviortree_cpp/bt_factory.h>

class need_move_to_target : public BT::ConditionNode {
    private:

    public:
        need_move_to_target(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
