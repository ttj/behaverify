#ifndef pick_up_key_header
#define pick_up_key_header

#include <behaviortree_cpp/bt_factory.h>

class pick_up_key : public BT::SyncActionNode {
    private:

    public:
        pick_up_key(const std::string& name, const BT::NodeConfiguration& config);
        static BT::PortsList providedPorts();
        BT::NodeStatus tick() override;
};

#endif
