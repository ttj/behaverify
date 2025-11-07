#!/usr/bin/env python3
"""
Custom visualization for DoorKey gridworld behavior tree simulation.
Generates animated GIF showing agent navigating to collect key, open door, and reach goal.
"""

from PIL import Image, ImageDraw, ImageFont
import re
import os

# Grid configuration
GRID_SIZE = 5
KEY_POS = (1, 1)
DOOR_POS = (2, 2)
GOAL_POS = (4, 4)

# Visual settings
TILE_SIZE = 80
LINE_WIDTH = 2
FONT_SIZE = 36

# Colors
COLORS = {
    'empty': '#F0F0F0',      # Light gray
    'agent': '#FF6B6B',      # Red
    'key': '#FFD93D',        # Yellow/Gold
    'door_locked': '#8B4513', # Brown
    'door_open': '#90EE90',   # Light green
    'goal': '#4ECDC4',       # Turquoise
    'grid_line': '#333333',  # Dark gray
    'text': '#FFFFFF'        # White
}

def parse_trace(trace_file):
    """Parse the behavior tree simulation trace to extract states."""
    states = []

    with open(trace_file, 'r') as f:
        content = f.read()

    # Split by state markers
    state_blocks = re.split(r'------------------------\nState after tick: \d+', content)

    # Parse initial state
    initial_match = re.search(r'Initial State.*?environment\s+agent_x: (\d+)\s+agent_y: (\d+)\s+has_key: (\w+)\s+door_open: (\w+)\s+action: (\w+)\s+at_goal: (\w+)',
                             content, re.DOTALL)
    if initial_match:
        states.append({
            'agent_x': int(initial_match.group(1)),
            'agent_y': int(initial_match.group(2)),
            'has_key': initial_match.group(3) == 'True',
            'door_open': initial_match.group(4) == 'True',
            'action': initial_match.group(5),
            'at_goal': initial_match.group(6) == 'True',
            'tick': 0
        })

    # Parse subsequent states
    for idx, block in enumerate(state_blocks[1:], 1):
        env_match = re.search(r'environment\s+agent_x: (\d+)\s+agent_y: (\d+)\s+has_key: (\w+)\s+door_open: (\w+)\s+action: (\w+)\s+at_goal: (\w+)',
                            block)
        if env_match:
            states.append({
                'agent_x': int(env_match.group(1)),
                'agent_y': int(env_match.group(2)),
                'has_key': env_match.group(3) == 'True',
                'door_open': env_match.group(4) == 'True',
                'action': env_match.group(5),
                'at_goal': env_match.group(6) == 'True',
                'tick': idx
            })

    return states

def draw_grid_state(state, frame_num, output_dir):
    """Draw a single grid state as a PNG image."""
    img_size = GRID_SIZE * TILE_SIZE + LINE_WIDTH
    img = Image.new('RGB', (img_size, img_size), COLORS['grid_line'])
    draw = ImageDraw.Draw(img)

    # Draw grid cells
    for x in range(GRID_SIZE):
        for y in range(GRID_SIZE):
            left = x * TILE_SIZE + LINE_WIDTH
            top = y * TILE_SIZE + LINE_WIDTH
            right = left + TILE_SIZE - LINE_WIDTH
            bottom = top + TILE_SIZE - LINE_WIDTH

            # Determine cell color
            pos = (x, y)

            if pos == (state['agent_x'], state['agent_y']):
                color = COLORS['agent']
            elif pos == KEY_POS and not state['has_key']:
                color = COLORS['key']
            elif pos == DOOR_POS:
                color = COLORS['door_open'] if state['door_open'] else COLORS['door_locked']
            elif pos == GOAL_POS:
                color = COLORS['goal']
            else:
                color = COLORS['empty']

            draw.rectangle([left, top, right, bottom], fill=color)

    # Add labels
    try:
        # Try to use a default font
        font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", FONT_SIZE)
    except:
        # Fallback to default
        font = ImageFont.load_default()

    # Draw agent symbol
    agent_x, agent_y = state['agent_x'], state['agent_y']
    agent_center_x = agent_x * TILE_SIZE + TILE_SIZE // 2
    agent_center_y = agent_y * TILE_SIZE + TILE_SIZE // 2
    draw.text((agent_center_x, agent_center_y), 'A', fill=COLORS['text'],
              font=font, anchor='mm')

    # Draw key if not acquired
    if not state['has_key']:
        key_center_x = KEY_POS[0] * TILE_SIZE + TILE_SIZE // 2
        key_center_y = KEY_POS[1] * TILE_SIZE + TILE_SIZE // 2
        if (state['agent_x'], state['agent_y']) != KEY_POS:
            draw.text((key_center_x, key_center_y), 'K', fill='#000000',
                     font=font, anchor='mm')

    # Draw door symbol
    door_center_x = DOOR_POS[0] * TILE_SIZE + TILE_SIZE // 2
    door_center_y = DOOR_POS[1] * TILE_SIZE + TILE_SIZE // 2
    door_symbol = 'O' if state['door_open'] else 'X'
    if (state['agent_x'], state['agent_y']) != DOOR_POS:
        draw.text((door_center_x, door_center_y), door_symbol, fill=COLORS['text'],
                 font=font, anchor='mm')

    # Draw goal symbol
    goal_center_x = GOAL_POS[0] * TILE_SIZE + TILE_SIZE // 2
    goal_center_y = GOAL_POS[1] * TILE_SIZE + TILE_SIZE // 2
    if (state['agent_x'], state['agent_y']) != GOAL_POS:
        draw.text((goal_center_x, goal_center_y), 'G', fill='#000000',
                 font=font, anchor='mm')

    # Add status text at bottom
    status_img = Image.new('RGB', (img_size, 120), '#FFFFFF')
    status_draw = ImageDraw.Draw(status_img)

    try:
        status_font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16)
    except:
        status_font = ImageFont.load_default()

    status_text = f"Tick: {state['tick']}  |  Has Key: {state['has_key']}  |  Door: {'Open' if state['door_open'] else 'Locked'}  |  At Goal: {state['at_goal']}"
    status_draw.text((10, 20), status_text, fill='#000000', font=status_font)
    status_draw.text((10, 50), f"Action: {state['action']}", fill='#000000', font=status_font)
    status_draw.text((10, 80), f"Agent: ({state['agent_x']}, {state['agent_y']})", fill='#000000', font=status_font)

    # Combine grid and status
    final_img = Image.new('RGB', (img_size, img_size + 120), '#FFFFFF')
    final_img.paste(img, (0, 0))
    final_img.paste(status_img, (0, img_size))

    # Save frame
    output_path = os.path.join(output_dir, f'frame_{frame_num:04d}.png')
    final_img.save(output_path)
    print(f"Generated frame {frame_num}: Agent at ({state['agent_x']}, {state['agent_y']}), Key: {state['has_key']}, Door: {state['door_open']}")

    return output_path

def create_gif(frame_paths, output_path, duration=500):
    """Create animated GIF from frame images."""
    frames = [Image.open(path) for path in frame_paths]

    if frames:
        # Save as GIF with loop
        frames[0].save(
            output_path,
            format='GIF',
            append_images=frames[1:],
            save_all=True,
            duration=duration,  # milliseconds per frame
            loop=0  # infinite loop
        )
        print(f"\n✓ Created animated GIF: {output_path}")
        print(f"  Total frames: {len(frames)}")
        print(f"  Duration per frame: {duration}ms")
    else:
        print("No frames to create GIF!")

def main():
    trace_file = '/tmp/doorkey_gif/trace.txt'
    output_dir = '/tmp/doorkey_gif/frames'
    gif_output = '/tmp/doorkey_gif/doorkey_animation.gif'

    # Create output directory
    os.makedirs(output_dir, exist_ok=True)

    print("=" * 80)
    print("DoorKey Gridworld Visualization")
    print("=" * 80)
    print(f"\nGrid Size: {GRID_SIZE}x{GRID_SIZE}")
    print(f"Key Position: {KEY_POS}")
    print(f"Door Position: {DOOR_POS}")
    print(f"Goal Position: {GOAL_POS}")
    print("\nLegend:")
    print("  A = Agent (Red)")
    print("  K = Key (Yellow, disappears when acquired)")
    print("  X = Locked Door (Brown)")
    print("  O = Open Door (Green)")
    print("  G = Goal (Turquoise)")
    print("\n" + "=" * 80)

    # Parse trace
    print("\nParsing simulation trace...")
    states = parse_trace(trace_file)
    print(f"Found {len(states)} states")

    # Generate frames
    print("\nGenerating frames...")
    frame_paths = []
    for idx, state in enumerate(states):
        path = draw_grid_state(state, idx, output_dir)
        frame_paths.append(path)

        # Stop when goal is reached
        if state['at_goal']:
            print(f"\n✓ Goal reached at tick {state['tick']}!")
            # Add a few more frames of the final state
            for i in range(3):
                path = draw_grid_state(state, idx + i + 1, output_dir)
                frame_paths.append(path)
            break

    # Create GIF
    print("\nCreating animated GIF...")
    create_gif(frame_paths, gif_output, duration=500)

    print("\n" + "=" * 80)
    print("Visualization complete!")
    print(f"GIF saved to: {gif_output}")
    print("=" * 80)

if __name__ == '__main__':
    main()
