# Creating Animated GIF Visualizations of DoorKey Gridworld

This guide shows how to create animated GIF visualizations of behavior tree execution in the DoorKey gridworld environment.

## Overview

BehaVerify includes capabilities to visualize behavior tree execution as animated GIFs. For the DoorKey gridworld example, we've created a custom visualization that shows:

- **Agent position** (Red square with 'A')
- **Key location** (Yellow square with 'K', disappears when acquired)
- **Door** (Brown 'X' when locked, Green 'O' when open)
- **Goal** (Turquoise square with 'G')
- **State information** (tick count, has_key, door status, at_goal)

## Quick Start

```bash
# 1. Generate Python executable
cd /home/user/behaverify
python3 scripts/generate_doorkey_python.py

# 2. Run simulation
cd /tmp/doorkey_gif
python3 doorkey_sim_runner.py > trace.txt

# 3. Generate GIF
python3 /home/user/behaverify/scripts/doorkey_visualizer.py
```

The animated GIF will be saved to `/tmp/doorkey_gif/doorkey_animation.gif`

## Generated Files

After running the visualization, you'll have:
- `doorkey_animation.gif` - The animated visualization
- `frames/frame_*.png` - Individual frame images
- `trace.txt` - The simulation trace output

## Understanding the Visualization

### Color Legend

| Color | Element | Description |
|-------|---------|-------------|
| 🟥 Red | Agent | Current position of the agent |
| 🟨 Yellow | Key | Location of the key (disappears when acquired) |
| 🟫 Brown | Locked Door | Door that requires the key to open |
| 🟩 Green | Open Door | Door that has been opened |
| 🟦 Turquoise | Goal | Target destination |
| ⬜ Light Gray | Empty Space | Traversable cells |

### Sample Frame Breakdown

Initial state (Tick 0):
```
┌─────┬─────┬─────┬─────┬─────┐
│  A  │     │     │     │     │  A = Agent at (0,0)
├─────┼─────┼─────┼─────┼─────┤
│     │  K  │     │     │     │  K = Key at (1,1)
├─────┼─────┼─────┼─────┼─────┤
│     │     │  X  │     │     │  X = Locked Door at (2,2)
├─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │  G  │  G = Goal at (4,4)
└─────┴─────┴─────┴─────┴─────┘

Status: Has Key: False | Door: Locked | At Goal: False
Action: south
```

## The Visualizer Script

The custom visualizer is located at `scripts/doorkey_visualizer.py` and includes:

```python
# Key functions:
- parse_trace()         # Extracts states from simulation output
- draw_grid_state()     # Renders a single frame as PNG
- create_gif()          # Combines frames into animated GIF
```

### Configuration

Edit these constants in `doorkey_visualizer.py` to match your grid:

```python
# Grid configuration (must match your .tree file)
GRID_SIZE = 5
KEY_POS = (1, 1)
DOOR_POS = (2, 2)
GOAL_POS = (4, 4)

# Visual settings
TILE_SIZE = 80        # Size of each grid cell in pixels
LINE_WIDTH = 2        # Grid line thickness
FONT_SIZE = 36        # Size of cell labels
```

### Customizing Colors

Modify the `COLORS` dictionary:

```python
COLORS = {
    'empty': '#F0F0F0',
    'agent': '#FF6B6B',
    'key': '#FFD93D',
    'door_locked': '#8B4513',
    'door_open': '#90EE90',
    'goal': '#4ECDC4',
    'grid_line': '#333333',
    'text': '#FFFFFF'
}
```

## Complete Workflow

Here's the complete process from model to GIF:

### Step 1: Create/Modify Your Model

Edit `examples/simple_doorkey_demo.tree` to adjust grid size or positions:

```
constants {
    grid_size := 5,
    goal_x := 4,
    goal_y := 4,
    door_x := 2,
    door_y := 2,
    key_x := 1,
    key_y := 1
}
```

### Step 2: Generate Python Simulation

Create a generation script:

```python
#!/usr/bin/env python3
import sys, os
sys.path.insert(0, '/home/user/behaverify/src')
from behaverify.dsl_to_python import dsl_to_python
from importlib.resources import files

metamodel_file = str(files('behaverify').joinpath('data/metamodel/behaverify.tx'))
os.chdir('/home/user/behaverify')

dsl_to_python(
    metamodel_file=metamodel_file,
    model_file='./examples/simple_doorkey_demo.tree',
    main_name='doorkey_sim',
    write_location='/tmp/doorkey_gif/',
    serene_print=True,
    max_iter=50,
    no_var_print=False,
    py_tree_print=False,
    recursion_limit=5000,
    safe_assignment=False,
    no_checks=False
)
```

Run it:
```bash
python3 generate_script.py
```

### Step 3: Run Simulation

```bash
cd /tmp/doorkey_gif
python3 doorkey_sim_runner.py > trace.txt
```

This generates a trace with states like:
```
State after tick: 1
environment
  agent_x: 0
  agent_y: 1
  has_key: False
  door_open: False
  action: north
  at_goal: False
```

### Step 4: Generate Visualization

```bash
python3 /home/user/behaverify/scripts/doorkey_visualizer.py
```

Output:
```
================================================================================
DoorKey Gridworld Visualization
================================================================================

Grid Size: 5x5
Key Position: (1, 1)
Door Position: (2, 2)
Goal Position: (4, 4)

Parsing simulation trace...
Found 51 states

Generating frames...
Generated frame 0: Agent at (0, 0), Key: False, Door: False
Generated frame 1: Agent at (0, 0), Key: False, Door: False
...

Creating animated GIF...

✓ Created animated GIF: /tmp/doorkey_gif/doorkey_animation.gif
  Total frames: 51
  Duration per frame: 500ms
================================================================================
```

### Step 5: View the GIF

```bash
# Copy to a permanent location
cp /tmp/doorkey_gif/doorkey_animation.gif ./my_simulation.gif

# View with image viewer
xdg-open my_simulation.gif
```

Or open directly in a web browser.

## Behavior Tree Execution Pattern

The visualization shows how the behavior tree executes:

1. **get_key sequence**:
   - move_to_key (always succeeds)
   - check NOT have_key (inverter)
   - pick_up_key (succeeds if at key location)

2. **unlock_door sequence**:
   - move_to_door (always succeeds)
   - check NOT door_open (inverter)
   - open_door (succeeds if at door with key)

3. **reach_goal sequence**:
   - move_to_goal (always succeeds)
   - reached_goal (succeeds if at goal)

**Note**: The current example uses non-deterministic actions (random movement), so the agent explores randomly. For deterministic behavior, you would need to implement actual pathfinding logic in the action nodes or use a more sophisticated environment model.

## Advanced: Customizing for Your Own Gridworld

To adapt this for a different gridworld:

### 1. Update Grid Configuration

Match your constants in the .tree file:

```python
GRID_SIZE = 10  # If your grid is 10x10
KEY_POS = (2, 3)
DOOR_POS = (5, 5)
GOAL_POS = (9, 9)
```

### 2. Add New Elements

To visualize obstacles or additional objects:

```python
OBSTACLE_POS = [(3, 3), (3, 4), (4, 3)]

# In draw_grid_state():
if pos in OBSTACLE_POS:
    color = '#000000'  # Black for obstacles
    draw.text((center_x, center_y), '█', ...)
```

### 3. Parse Additional State Variables

If you have extra variables in your trace:

```python
# In parse_trace():
env_match = re.search(
    r'environment\s+agent_x: (\d+).*has_item2: (\w+)',
    block, re.DOTALL
)
states.append({
    ...
    'has_item2': env_match.group(7) == 'True',
})
```

### 4. Adjust Animation Speed

Change the duration parameter:

```python
create_gif(frame_paths, gif_output, duration=300)  # 300ms = faster
create_gif(frame_paths, gif_output, duration=1000) # 1000ms = slower
```

## Integrating with BehaVerify's Built-in Grid Mode

BehaVerify has a built-in `grid` mode for drone examples. To use it:

```bash
# For examples that use x_d, y_d, x_g, y_g variables:
python3 -m behaverify python ./examples/DrunkenDrone/DrunkenDrone.tree ./output/
cd ./output
python3 DrunkenDrone.py > output.txt
python3 -m behaverify grid python ./output/output.txt ./grid_viz/ 10 10
```

The DoorKey custom visualizer extends this concept with domain-specific rendering (key, door, goal).

## Troubleshooting

### Issue: No frames generated

**Solution**: Check that trace.txt contains state information:
```bash
grep "agent_x:" /tmp/doorkey_gif/trace.txt
```

### Issue: Font errors

**Solution**: The script falls back to default fonts if TrueType fonts aren't available:
```python
try:
    font = ImageFont.truetype("/usr/share/fonts/...", FONT_SIZE)
except:
    font = ImageFont.load_default()  # Fallback
```

### Issue: GIF plays too fast/slow

**Solution**: Adjust `duration` parameter in `create_gif()`:
```python
# In doorkey_visualizer.py, line ~250:
create_gif(frame_paths, gif_output, duration=500)  # milliseconds
```

### Issue: Grid doesn't match visualization

**Solution**: Ensure constants in visualizer match your .tree file:
```python
# Must match:
# constants { grid_size := 5, key_x := 1, key_y := 1, ... }
GRID_SIZE = 5
KEY_POS = (1, 1)
```

## Example Output

The provided example generates a ~150KB GIF showing:
- 51 frames of simulation
- 500ms per frame (about 25 seconds total)
- Agent exploring the gridworld with non-deterministic movement
- State information displayed at the bottom of each frame

**Location**: `examples/doorkey_animation.gif`

## Tips for Better Visualizations

1. **Deterministic Behavior**: For clearer demonstrations, use a deterministic policy or guided actions

2. **Highlight Key Events**: Add extra frames when important events occur (key acquired, door opened)

3. **Annotations**: Add text overlays to explain what's happening

4. **Multiple Runs**: Generate several GIFs with different random seeds to show variety

5. **Resolution**: Increase `TILE_SIZE` for higher resolution (but larger files)

6. **Frame Selection**: Skip redundant frames where nothing changes:
   ```python
   if state != previous_state:
       draw_grid_state(state, frame_num, output_dir)
   ```

## Further Reading

- **BehaVerify README**: `README.md`
- **Grid Mode Documentation**: `README.md` (Grid Mode section)
- **Python Generation**: `DOORKEY_VISUALIZATION_TUTORIAL.md`
- **Existing Grid Examples**: `examples/DrunkenDrone/`, `examples/NetworkExample/`

## Scripts Location

- **Visualizer**: `scripts/doorkey_visualizer.py`
- **Example GIF**: `examples/doorkey_animation.gif`
- **Model File**: `examples/simple_doorkey_demo.tree`

---

**Author**: Generated with BehaVerify
**Date**: November 2025
**BehaVerify Version**: 0.0.1
