# GridWorld Lock/Key Example - BehaviorTree.CPP Output

This directory contains a complete example of C++ code generated from the BehaVerify DSL for use with the BehaviorTree.CPP framework.

## Example Scenario

The example demonstrates a lock/key gridworld scenario where:
- Agent starts at position (0, 0)
- Key is at position (1, 1)
- Locked door is at position (3, 2)
- Target is at position (4, 4)
- Agent must: navigate to key → pick up key → navigate to door → unlock door → reach target

## Files

### Input
- `gridworld_lockkey.tree` - DSL specification defining the behavior tree

### Generated C++ Files
- `main.cpp` - BehaviorTree.CPP integration with blackboard and main loop
- `tree.xml` - Behavior tree structure in BTCPP_format="4"
- `CMakeLists.txt` - Build configuration
- `Environment.h/cpp` - Environment simulation class

### Generated Node Files (13 nodes)
Each node has corresponding `.h` and `.cpp` files:

**Check Nodes:**
- `at_key` - Check if agent is at key location
- `at_door` - Check if agent is at door location
- `at_target` - Check if agent is at target location
- `has_key_check` - Check if agent has picked up the key
- `door_unlocked_check` - Check if door is unlocked
- `need_move_to_key` - Check if agent needs to move toward key
- `need_move_to_door` - Check if agent needs to move toward door
- `need_move_to_target` - Check if agent needs to move toward target

**Action Nodes:**
- `move_toward_key` - Move agent toward key location
- `pick_up_key` - Pick up the key
- `move_toward_door` - Move agent toward door location
- `unlock_door` - Unlock the door
- `move_toward_target` - Move agent toward target location

## Building

Requires BehaviorTree.CPP v3.8 or later installed.

```bash
cd build
cmake ..
make
```

## Running

```bash
./GridWorld
```

The executable will run 50 ticks of the behavior tree simulation.

## Tree Structure

The behavior tree follows this structure:
```
Sequence (main_sequence)
├── Sequence (get_key_sequence)
│   ├── RetryUntilSuccessful (repeat_move_to_key)
│   │   └── move_toward_key
│   ├── at_key
│   └── pick_up_key
├── Sequence (unlock_door_sequence)
│   ├── RetryUntilSuccessful (repeat_move_to_door)
│   │   └── move_toward_door
│   ├── at_door
│   └── unlock_door
└── Sequence (reach_target_sequence)
    ├── RetryUntilSuccessful (repeat_move_to_target)
    │   └── move_toward_target
    └── at_target
```

## Implementation Details

- All check nodes inherit from `BT::ConditionNode`
- All action nodes inherit from `BT::SyncActionNode`
- Blackboard is used for sharing state variables between nodes
- Variables: `agent_x`, `agent_y`, `has_key`, `door_unlocked`, `step_count`
- C++17 standard required
