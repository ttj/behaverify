# BehaVerify DoorKey Gridworld Tutorial: Visualization and Verification

This tutorial demonstrates how to visualize a behavior tree for a gridworld environment (DoorKey example) and verify goal reachability using BehaVerify's interface to nuXmv.

## Table of Contents
1. [Example Overview](#example-overview)
2. [Model File Structure](#model-file-structure)
3. [Visualizing the Behavior Tree](#visualizing-the-behavior-tree)
4. [Generating the nuXmv Model](#generating-the-nuxmv-model)
5. [Verifying Goal Reachability](#verifying-goal-reachability)
6. [Scaling the Grid](#scaling-the-grid)
7. [Understanding the Results](#understanding-the-results)

## Example Overview

The example (`examples/simple_doorkey_demo.tree`) implements a simple gridworld where an agent must:
1. Navigate to a key and pick it up
2. Navigate to a door and open it (requires having the key)
3. Navigate to the goal location

**Current Configuration:**
- Grid size: 5x5
- Agent starts at: (0, 0)
- Key location: (1, 1)
- Door location: (2, 2)
- Goal location: (4, 4)

## Model File Structure

The BehaVerify DSL file has the following main sections:

```
configuration {}              # Global settings
enumerations {...}           # Define enumeration types (actions, states, etc.)
constants {...}              # Define constants (grid size, locations)
variables {...}              # Declare state variables (env/blackboard/local)
environment_update {...}     # How environment variables change each tick
checks {}                    # Condition checks reading blackboard variables
environment_checks {...}     # Condition checks reading environment variables
actions {...}                # Action nodes in the behavior tree
sub_trees {}                 # Reusable subtree definitions
tree {...}                   # Main behavior tree structure
tick_prerequisite {...}      # Condition for tree execution
specifications {...}         # Formal verification properties (LTL/CTL/INVAR)
```

### Key Variables

**Environment Variables (updated by environment_update):**
- `agent_x`, `agent_y`: Agent position (0 to grid_size)
- `has_key`: Boolean indicating if agent has picked up the key
- `door_open`: Boolean indicating if the door is open
- `action`: Agent's current action (north, south, east, west, pickup, toggle, idle)
- `at_goal`: Boolean indicating if goal has been reached

## Visualizing the Behavior Tree

### Method 1: Generate LaTeX Visualization

```bash
# From the behaverify directory
python3 -m behaverify latex ./examples/simple_doorkey_demo.tree ./output/doorkey_tree.tex --overwrite
```

This generates a TikZ-based LaTeX file that you can compile to PDF:

```bash
pdflatex ./output/doorkey_tree.tex
```

**What you'll see:**
- A hierarchical tree diagram showing:
  - **Root sequence node** (root_node)
    - **get_key** sequence
      - move_to_key action
      - check_at_key inverter (checking NOT have_key)
      - pick_up_key action
    - **unlock_door** sequence
      - move_to_door action
      - check_door_open inverter (checking NOT is_door_open)
      - open_door action
    - **reach_goal** sequence
      - move_to_goal action
      - reached_goal check

### Method 2: Use the GUI (if tkinter is available)

```bash
python3 -m behaverify gui
```

Then load the tree file and use the visualization features.

## Generating the nuXmv Model

The nuXmv model file is a formal model suitable for model checking. Generate it with:

```bash
python3 -m behaverify nuxmv ./examples/simple_doorkey_demo.tree ./output/ --generate --overwrite
```

**Output:** `./output/nuxmv/simple_doorkey_demo.smv`

**What's in the .smv file:**
- State machine encoding of the behavior tree
- Variable declarations and transitions
- Specification properties for verification
- Environment dynamics (how the gridworld changes)

### Alternative: Using Python Script

If the CLI has issues, use the direct Python API:

```python
import sys
sys.path.insert(0, '/home/user/behaverify/src')
from behaverify.dsl_to_nuxmv import dsl_to_nuxmv
from importlib.resources import files
import os

metamodel_file = str(files('behaverify').joinpath('data/metamodel/behaverify.tx'))
os.chdir('/home/user/behaverify')

dsl_to_nuxmv(
    metamodel_file=metamodel_file,
    model_file='./examples/simple_doorkey_demo.tree',
    output_file='./output/simple_doorkey_demo',
    keep_stage_0=False,
    keep_last_stage=False,
    do_not_trim=False,
    behave_only=False,
    recursion_limit=5000,
    return_values=False,
    skip_grammar_check=False,
    record_times=None,
    variant='naive'
)
```

## Verifying Goal Reachability

### The LTL Property

In `simple_doorkey_demo.tree`, we have:

```
specifications {
    LTLSPEC {(finally, at_goal)}
}
```

This LTL (Linear Temporal Logic) specification means: **"Eventually, the goal will be reached"** (◊ at_goal).

### Running Verification

**Prerequisites:**
1. Install nuXmv 2.1.0 from https://nuxmv.fbk.eu/
2. Place the `nuXmv` executable in an accessible location

**Verification command:**

```bash
# Generate model and verify LTL property
python3 -m behaverify nuxmv ./examples/simple_doorkey_demo.tree ./output/ \
    --generate --ltl --nuxmv_path /path/to/nuXmv --overwrite
```

**What happens:**
1. BehaVerify generates the .smv file
2. Invokes nuXmv to check the LTL specification
3. nuXmv performs model checking:
   - If property is TRUE: Goal is always eventually reached
   - If property is FALSE: nuXmv provides a counterexample trace

### Verification Options

You can verify different types of properties:

```bash
# Verify INVAR (invariant) properties
python3 -m behaverify nuxmv ... --invar --nuxmv_path /path/to/nuXmv

# Verify CTL (Computation Tree Logic) properties
python3 -m behaverify nuxmv ... --ctl --nuxmv_path /path/to/nuXmv

# Verify LTL (Linear Temporal Logic) properties
python3 -m behaverify nuxmv ... --ltl --nuxmv_path /path/to/nuXmv

# Verify all property types
python3 -m behaverify nuxmv ... --invar --ctl --ltl --nuxmv_path /path/to/nuXmv

# Simulate for N steps
python3 -m behaverify nuxmv ... --simulate 50 --nuxmv_path /path/to/nuXmv
```

### Example Specifications

You can add different specifications to verify various properties:

```
specifications {
    # Liveness: Goal is eventually reached
    LTLSPEC {(finally, at_goal)}

    # Safety: Agent position stays within bounds
    LTLSPEC {(globally, (and, (gte, agent_x, 0), (lte, agent_x, grid_size)))}

    # Conditional: If key is acquired, eventually door is opened
    LTLSPEC {(implies, (finally, has_key), (finally, door_open))}

    # Invariant: Agent never has negative coordinates
    INVARSPEC {(and, (gte, agent_x, 0), (gte, agent_y, 0))}

    # CTL: There exists a path where goal is reached
    CTLSPEC {(exists_finally, at_goal)}
}
```

## Scaling the Grid

You can easily scale the grid size by modifying the constants section:

### Example: 10x10 Grid

Edit `examples/simple_doorkey_demo.tree`:

```
constants {
    grid_size := 10,    # Change from 5 to 10
    goal_x := 9,        # Adjust goal location
    goal_y := 9,
    door_x := 5,        # Adjust door location
    door_y := 5,
    key_x := 2,         # Adjust key location
    key_y := 2
}
```

### Example: 20x20 Grid with Different Layout

```
constants {
    grid_size := 20,
    key_x := 3,
    key_y := 3,
    door_x := 10,
    door_y := 10,
    goal_x := 18,
    goal_y := 18
}
```

### Example: Non-Square Grid

For a non-square grid, you need to modify the variable declarations:

```
constants {
    grid_width := 10,
    grid_height := 5,
    # ... locations ...
}
variables {
    variable { env agent_x VAR [0, grid_width] assign{result{0}}}
    variable { env agent_y VAR [0, grid_height] assign{result{0}}}
    # ... rest ...
}
environment_update {
    variable_statement { agent_x assign{
        case{(and, (eq, action, 'east'), (lt, agent_x, grid_width))} result{(min, grid_width, (add, agent_x, 1))}
        case{(and, (eq, action, 'west'), (gt, agent_x, 0))} result{(max, 0, (add, agent_x, -1))}
        result{agent_x}
    }}
    variable_statement { agent_y assign{
        case{(and, (eq, action, 'north'), (lt, agent_y, grid_height))} result{(min, grid_height, (add, agent_y, 1))}
        case{(and, (eq, action, 'south'), (gt, agent_y, 0))} result{(max, 0, (add, agent_y, -1))}
        result{agent_y}
    }}
    # ... rest ...
}
```

### Performance Considerations

**State Space Explosion:**
- Grid size directly affects state space size
- A 5x5 grid has 25 positions; a 10x10 grid has 100 positions
- Combined with other variables, this grows exponentially
- Larger grids may require more memory and time for verification

**Tips for Large Grids:**
1. Use the `fastfowarding` encoding (typo: use `--use_encoding fastfowarding`)
2. Enable optimization flags: don't use `--do_not_trim`
3. Break verification into smaller properties
4. Use bounded model checking for large state spaces
5. Consider abstracting the model (e.g., symbolic positions)

## Understanding the Results

### Successful Verification

If nuXmv verifies the property, you'll see output like:

```
-- specification  F at_goal  is true
```

This means: **For all possible executions, the goal is eventually reached.**

### Failed Verification (Counterexample)

If the property fails, nuXmv provides a counterexample trace:

```
-- specification  F at_goal  is false
-- as demonstrated by the following execution sequence
Trace Description: LTL Counterexample
Trace Type: Counterexample
  -> State: 1.1 <-
    agent_x = 0
    agent_y = 0
    ...
  -> State: 1.2 <-
    agent_x = 0
    agent_y = 1
    action = north
    ...
```

This trace shows a specific execution where the goal is NOT reached.

### Trace Visualization

You can visualize traces using the trace mode:

```bash
# First, generate and verify (to get a trace)
python3 -m behaverify nuxmv ./examples/simple_doorkey_demo.tree ./output/ \
    --generate --ltl --nuxmv_path /path/to/nuXmv --overwrite

# Then visualize the trace
python3 -m behaverify trace ./examples/simple_doorkey_demo.tree \
    ./output/nuxmv/simple_doorkey_demo_output.txt ./trace_viz/ --overwrite
```

This generates a series of images showing the behavior tree execution at each step.

## Complete Workflow Example

Here's a complete end-to-end workflow:

```bash
#!/bin/bash
# Complete BehaVerify workflow for DoorKey gridworld

TREE_FILE="./examples/simple_doorkey_demo.tree"
OUTPUT_DIR="./demo_output"
NUXMV_PATH="/path/to/nuXmv"

# 1. Generate LaTeX visualization
echo "Generating LaTeX visualization..."
python3 -m behaverify latex "$TREE_FILE" "$OUTPUT_DIR/doorkey_tree.tex" --overwrite
pdflatex -output-directory="$OUTPUT_DIR" "$OUTPUT_DIR/doorkey_tree.tex"

# 2. Generate nuXmv model
echo "Generating nuXmv model..."
python3 -m behaverify nuxmv "$TREE_FILE" "$OUTPUT_DIR/" --generate --overwrite

# 3. Verify LTL properties
echo "Verifying LTL specifications..."
python3 -m behaverify nuxmv "$TREE_FILE" "$OUTPUT_DIR/" \
    --generate --ltl --nuxmv_path "$NUXMV_PATH" --overwrite

# 4. Simulate execution
echo "Simulating for 50 steps..."
python3 -m behaverify nuxmv "$TREE_FILE" "$OUTPUT_DIR/" \
    --generate --simulate 50 --nuxmv_path "$NUXMV_PATH" --overwrite

# 5. Visualize trace
echo "Visualizing execution trace..."
python3 -m behaverify trace "$TREE_FILE" \
    "$OUTPUT_DIR/nuxmv/simple_doorkey_demo_output.txt" \
    "$OUTPUT_DIR/trace/" --overwrite

echo "Done! Check $OUTPUT_DIR for all outputs."
```

## Advanced Topics

### Multiple Agents

To model multiple agents, duplicate agent variables:

```
variables {
    variable { env agent1_x VAR [0, grid_size] assign{result{0}}}
    variable { env agent1_y VAR [0, grid_size] assign{result{0}}}
    variable { env agent2_x VAR [0, grid_size] assign{result{0}}}
    variable { env agent2_y VAR [0, grid_size] assign{result{0}}}
    # ...
}
```

### Obstacles

Add obstacle positions as constants and modify movement logic:

```
constants {
    # ... existing constants ...
    obstacle1_x := 2,
    obstacle1_y := 3
}

environment_update {
    variable_statement { agent_x assign{
        case{(and, (eq, action, 'east'), (lt, agent_x, grid_size),
             (not, (and, (eq, (add, agent_x, 1), obstacle1_x),
                         (eq, agent_y, obstacle1_y))))}
            result{(min, grid_size, (add, agent_x, 1))}
        # ... rest ...
    }}
}
```

### Stochastic Environments

Use non-deterministic choice in environment_update:

```
environment_update {
    # Random action selection
    variable_statement { action assign{result{
        'north', 'south', 'east', 'west', 'pickup', 'toggle', 'idle'
    }}}
    # ... rest ...
}
```

## Further Reading

- **BehaVerify README**: `/home/user/behaverify/README.md`
- **Tutorial Examples**: `/home/user/behaverify/tutorial_examples/README.md`
- **DSL Grammar**: `/home/user/behaverify/src/behaverify/data/metamodel/behaverify.tx`
- **Research Papers**: See references in main README
- **Examples Directory**: `/home/user/behaverify/examples/` (30+ examples)

## Troubleshooting

### Common Issues

1. **"Expected ',' or '}'"**: Missing commas in constants/enumerations
2. **"Expected blackboard variable but got environment"**: Using check instead of environment_check
3. **"Updating non-environment variable"**: Trying to update blackboard/local vars in environment_update
4. **State space too large**: Grid too big, consider abstractions or bounded checking
5. **tkinter not found**: GUI not available, use command-line modes instead

### Getting Help

- GitHub Issues: https://github.com/verivital/behaverify/issues
- Documentation: https://github.com/verivital/behaverify/tree/main/tutorial_examples

---

**Generated**: November 2025
**BehaVerify Version**: 0.0.1
**Example File**: `/home/user/behaverify/examples/simple_doorkey_demo.tree`
