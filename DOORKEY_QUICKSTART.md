# DoorKey Gridworld - Quick Start Guide

A minimal guide to get started with the BehaVerify DoorKey gridworld example.

## Prerequisites

```bash
# Install BehaVerify
pip install -e .

# Optional: Download nuXmv for verification
wget https://nuxmv.fbk.eu/theme/download.php?file=nuXmv-2.1.0-linux64.tar.xz -O nuXmv.tar.xz
tar -xf nuXmv.tar.xz
mv nuXmv-2.1.0-linux64/bin/nuXmv ./nuXmv
chmod +x nuXmv
```

## Quick Commands

### 1. Visualize the Behavior Tree

```bash
# Generate LaTeX
python3 -m behaverify latex ./examples/simple_doorkey_demo.tree ./output/tree.tex

# Compile to PDF
pdflatex ./output/tree.tex
```

### 2. Generate nuXmv Model

```bash
python3 -m behaverify nuxmv ./examples/simple_doorkey_demo.tree ./output/ --generate
```

### 3. Verify Goal Reachability

```bash
python3 -m behaverify nuxmv ./examples/simple_doorkey_demo.tree ./output/ \
    --generate --ltl --nuxmv_path ./nuXmv
```

## Scaling the Grid

Edit `examples/simple_doorkey_demo.tree`, constants section:

```
constants {
    grid_size := 10,    # Change from 5 to 10
    goal_x := 9,        # Update goal position
    goal_y := 9,
    door_x := 5,        # Update door position
    door_y := 5,
    key_x := 2,         # Update key position
    key_y := 2
}
```

Then regenerate and re-verify.

## File Structure

```
examples/simple_doorkey_demo.tree  # Main model file
├── configuration {}               # Global settings
├── enumerations {...}            # Action types
├── constants {...}               # Grid size and positions ← EDIT HERE TO SCALE
├── variables {...}               # State variables
├── environment_update {...}      # Gridworld dynamics
├── environment_checks {...}      # Condition checks
├── actions {...}                 # Behavior tree actions
├── tree {...}                    # Behavior tree structure
└── specifications {...}          # LTL property: F at_goal ← GOAL REACHABILITY
```

## The Behavior Tree

```
root_node (sequence)
├── get_key (sequence)
│   ├── move_to_key
│   ├── check NOT have_key (inverter)
│   └── pick_up_key
├── unlock_door (sequence)
│   ├── move_to_door
│   ├── check NOT door_open (inverter)
│   └── open_door
└── reach_goal (sequence)
    ├── move_to_goal
    └── reached_goal
```

## The LTL Property

```
LTLSPEC {(finally, at_goal)}
```

Meaning: "**Eventually, the goal is always reached**" (◊ at_goal)

This verifies that no matter what actions are taken, the agent will eventually reach the goal.

## Expected Verification Result

✓ **Property is TRUE**: The behavior tree guarantees goal reachability.

The agent will:
1. Move towards and acquire the key
2. Move towards and open the door
3. Move towards and reach the goal

## Modifying the Example

### Add Obstacles

1. Add obstacle position constants
2. Update movement logic to avoid obstacles

### Change Grid Layout

1. Modify `grid_size` constant
2. Update location constants (key, door, goal)
3. Ensure path from start to goal exists

### Add New Properties

```
specifications {
    # Original property
    LTLSPEC {(finally, at_goal)}

    # New: Key must be acquired before door opens
    LTLSPEC {(until, (not, door_open), has_key)}

    # New: Goal requires passing through door
    LTLSPEC {(implies, at_goal, (once, door_open))}
}
```

## Next Steps

- Read the full tutorial: `DOORKEY_VISUALIZATION_TUTORIAL.md`
- Explore other examples: `examples/` directory
- Learn DSL syntax: `tutorial_examples/README.md`

## Help

- Issues: https://github.com/verivital/behaverify/issues
- Main README: `README.md`
- Tutorial: `tutorial_examples/README.md`
