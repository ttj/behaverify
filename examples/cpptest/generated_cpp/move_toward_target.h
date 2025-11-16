#ifndef move_toward_target_header
#define move_toward_target_header

#include <behaviortree_cpp/bt_factory.h>

class move_toward_target : public BT::SyncActionNode {
    private:

    public:
        move_toward_target(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
