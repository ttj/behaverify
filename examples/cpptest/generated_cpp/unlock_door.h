#ifndef unlock_door_header
#define unlock_door_header

#include <behaviortree_cpp/bt_factory.h>

class unlock_door : public BT::SyncActionNode {
    private:

    public:
        unlock_door(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
