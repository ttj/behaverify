#ifndef move_toward_key_header
#define move_toward_key_header

#include <behaviortree_cpp/bt_factory.h>

class move_toward_key : public BT::SyncActionNode {
    private:

    public:
        move_toward_key(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
