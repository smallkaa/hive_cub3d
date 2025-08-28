#!/usr/bin/env python3
# maze_gen.py
# Generate closed Cub3D-compatible maze maps.
# - Walls: '1'
# - Floor: '0'
# - Player start: one of N/S/E/W (here 'N')
#
# Usage:
#   python3 maze_gen.py --width 41 --height 21 --complexity 0.35 --seed 42 > map.cub

import argparse
import random
from collections import deque

def clamp(v, lo, hi):
    return max(lo, min(hi, v))

def ensure_odd(n, min_v=5):
    """Cub3D feels nicer with odd grid (walls/cells alternate)."""
    n = max(n, min_v)
    return n if n % 2 == 1 else n - 1

def neighbors_cells(x, y, w, h):
    """Return neighbor cell coordinates 2 steps away (for DFS carving)."""
    for dx, dy in ((0, -2), (2, 0), (0, 2), (-2, 0)):
        nx, ny = x + dx, y + dy
        if 1 <= nx < w - 1 and 1 <= ny < h - 1:
            yield nx, ny, dx, dy

def gen_perfect_maze(w, h, rng):
    """
    Generate a perfect maze on an odd-sized rectangular grid using randomized DFS.
    Returns a grid of '1' (wall) and '0' (space) with solid borders.
    """
    # Initialize all walls
    grid = [['1'] * w for _ in range(h)]
    # Carve starting cell
    start_x, start_y = 1, 1
    grid[start_y][start_x] = '0'
    stack = [(start_x, start_y)]

    while stack:
        x, y = stack[-1]
        nbrs = [(nx, ny, dx, dy) for nx, ny, dx, dy in neighbors_cells(x, y, w, h)
                if grid[ny][nx] == '1']
        if nbrs:
            nx, ny, dx, dy = rng.choice(nbrs)
            # Knock down wall between (x,y) and (nx,ny)
            grid[y + dy // 2][x + dx // 2] = '0'
            grid[ny][nx] = '0'
            stack.append((nx, ny))
        else:
            stack.pop()

    # Ensure border walls (closed map)
    for i in range(w):
        grid[0][i] = '1'
        grid[h - 1][i] = '1'
    for j in range(h):
        grid[j][0] = '1'
        grid[j][w - 1] = '1'
    return grid

def add_loops(grid, frac, rng):
    """
    Increase 'braid' (loops) by knocking down some walls between adjacent cells.
    frac in [0,1] — 0 keeps perfect maze, 1 knocks a lot of extra walls.
    """
    if frac <= 0:
        return
    h, w = len(grid), len(grid[0])
    # Candidate walls between two floor cells (vertical or horizontal)
    candidates = []
    for y in range(1, h - 1):
        for x in range(1, w - 1):
            if grid[y][x] != '1':
                continue
            # Horizontal wall between two cells
            if x - 1 >= 1 and x + 1 <= w - 2 and grid[y][x - 1] == '0' and grid[y][x + 1] == '0':
                candidates.append((x, y))
            # Vertical wall between two cells
            if y - 1 >= 1 and y + 1 <= h - 2 and grid[y - 1][x] == '0' and grid[y + 1][x] == '0':
                candidates.append((x, y))

    rng.shuffle(candidates)
    # Heuristic: number of extra knockdowns proportional to frac and area
    knocks = int(frac * len(candidates))
    for i in range(knocks):
        x, y = candidates[i]
        grid[y][x] = '0'

def farthest_cell_from(grid, sx, sy):
    """
    BFS to find a farthest reachable '0' cell from (sx, sy). Returns (x,y,dist).
    """
    h, w = len(grid), len(grid[0])
    q = deque()
    q.append((sx, sy, 0))
    seen = {(sx, sy)}
    best = (sx, sy, 0)
    while q:
        x, y, d = q.popleft()
        if d > best[2]:
            best = (x, y, d)
        for dx, dy in ((1,0),(-1,0),(0,1),(0,-1)):
            nx, ny = x + dx, y + dy
            if 0 <= nx < w and 0 <= ny < h and (nx, ny) not in seen and grid[ny][nx] == '0':
                seen.add((nx, ny))
                q.append((nx, ny, d + 1))
    return best

def place_player(grid, rng):
    """
    Place 'N' on a floor tile. We choose the farthest from (1,1) for nicer starts.
    """
    # If (1,1) is wall (it shouldn’t), scan for a '0'
    if grid[1][1] != '0':
        h, w = len(grid), len(grid[0])
        found = False
        for y in range(1, h - 1):
            for x in range(1, w - 1):
                if grid[y][x] == '0':
                    sx, sy = x, y
                    found = True
                    break
            if found:
                break
        if not found:
            return  # degenerate
    else:
        sx, sy = 1, 1

    fx, fy, _ = farthest_cell_from(grid, sx, sy)
    grid[fy][fx] = 'N'  # facing North by default

def generate_map(width, height, complexity, seed=None):
    rng = random.Random(seed)
    w = ensure_odd(width)
    h = ensure_odd(height)
    grid = gen_perfect_maze(w, h, rng)
    add_loops(grid, clamp(complexity, 0.0, 1.0), rng)
    place_player(grid, rng)
    # Convert to list of strings
    return ["".join(row) for row in grid]

def main():
    ap = argparse.ArgumentParser(description="Generate closed Cub3D maze maps.")
    ap.add_argument("--width", type=int, required=True, help="Map width (recommended odd, >= 5)")
    ap.add_argument("--height", type=int, required=True, help="Map height (recommended odd, >= 5)")
    ap.add_argument("--complexity", type=float, default=0.25,
                    help="Loopiness 0..1 (0 = perfect maze, 1 = many extra passages)")
    ap.add_argument("--seed", type=int, default=None, help="RNG seed for reproducibility")
    args = ap.parse_args()

    lines = generate_map(args.width, args.height, args.complexity, args.seed)
    # Print minimal .cub-like map block (only the map itself).
    # You can prepend texture/color settings if your parser expects them.
    for line in lines:
        print(line)

if __name__ == "__main__":
    main()
