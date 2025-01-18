"""
This script creates an animated visualization of a two-point pendulum system using matplotlib.

Modules:
    - matplotlib.pyplot: Used for creating and customizing plots.
    - matplotlib.animation: Used for generating the animation.
    - numpy: Used for numerical computations and array manipulations.

Details:
    The script reads numerical data from the file 'tests/check if calculations are fine/outputFile.txt'.
    The data represents the positions of two points in a pendulum system. These positions are processed
    and visualized as a two-dimensional animation, where the motion of the points is simulated over time.

File Requirements:
    - 'tests/check if calculations are fine/outputFile.txt': Input file containing numerical data.

Usage:
    Run this script directly to display the animation.
"""

import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np


def main():
    # setup the data
    with open("tests/check if calculations are fine/outputFile.txt") as f:
        data = [line.strip("\n").split() for line in f.readlines()]

    data = np.array(data, dtype=float)

    data = data[:, :2]

    x = np.sin(data)
    x[:, 1] += x[:, 0]

    y = -np.cos(data)
    y[:, 1] += y[:, 0]

    fig, ax = plt.subplots()
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_aspect("equal")
    ax.grid()

    (line,) = ax.plot([], [], "o-", lw=2, markersize=8)

    # Initialization function
    def init():
        line.set_data([], [])
        return (line,)

    # Animation function
    def update(frame):
        # Update pendulum line positions
        line.set_data([0, x[frame, 0], x[frame, 1]], [0, y[frame, 0], y[frame, 1]])
        return (line,)

    # Create the animation
    ani = anim.FuncAnimation(
        fig,
        update,
        frames=len(data),
        init_func=init,
        blit=True,
        interval=1 / 60 * 1000,
    )

    # Show the animation
    plt.show()


if __name__ == "__main__":
    main()
