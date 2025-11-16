#ifndef need_move_to_door_header
#define need_move_to_door_header

#include <behaviortree_cpp/bt_factory.h>

class need_move_to_door : public BT::ConditionNode {
    private:

    public:
        need_move_to_door(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
