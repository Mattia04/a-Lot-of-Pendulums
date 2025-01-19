import matplotlib.pyplot as plt
import numpy as np


def main():
    data = []
    for i in range(4, 7):
        temp = []
        with open(f"outputRK{i}.txt", "r") as f:
            for line in f.readlines():
                temp.append(line.split())
        data.append(temp)
    data = np.abs(np.array(data, dtype=float))

    data = np.sum(data, axis=1)

    variables = (r"$\dot\theta$", r"$\dot\phi$", r"$\dot p_\theta$", r"$\dot p_\phi$")
    methods = {f"RK{i+4}": data[i, :] for i in range(3)}

    x = np.arange(0, len(variables), 1)

    fig, ax = plt.subplots()

    width = 0.75 / len(methods)
    multiplier = 0

    for attribute, measurement in methods.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, measurement, width, label=attribute)
        ax.bar_label(rects, padding=3)
        multiplier += 1

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel("Total Absolute Error")
    ax.set_title("Error by methods")
    ax.set_xticks(x + width * (len(methods) // 2), variables)
    ax.legend(loc="upper left", ncols=3)

    plt.show()


if __name__ == "__main__":
    main()
