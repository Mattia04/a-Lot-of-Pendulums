import pandas as pd
import numpy as np
from PIL import Image


def time_to_rgb(value):
    # Blue (0, 0, 255) to Red (255, 0, 0) gradient
    if value < 0.25:
        return 4 * (0.25 - value) * 255, 0, 255
    if value < 0.5:
        return 0, 4 * (value - 0.25) * 255, 4 * (0.5 - value) * 255
    if value < 0.75:
        return 4 * (value - 0.5) * 255, 255, 0
    if value < 1:
        return 255, 4 * (1 - value) * 255, 0
    return 255, 255, 255


def main():
    data = pd.read_csv("output.csv", header=None, sep=",", dtype=float).dropna()
    data = data.to_numpy()
    data = np.concatenate((data, data[::-1, ::-1]), axis=0)

    data = np.log(data + 1)
    data = (data - np.min(data)) / (np.max(data) - np.min(data))

    colors = np.array([[time_to_rgb(d) for d in line] for line in data], dtype=np.uint8)

    image = Image.fromarray(colors, mode="RGB")
    image.save("output_image3.png")


if __name__ == "__main__":
    main()
