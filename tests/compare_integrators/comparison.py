import numpy as np
import matplotlib.pyplot as plt


def main():
    steps = [0.5, 0.1, 0.05, 0.01, 0.005, 0.001]

    data = np.empty((4, 6, 4, 10_000), dtype=np.float64)
    for i in range(4, 8):
        for j in range(6):
            with open(f"outRK{i}_{j}.txt", "r") as f:
                lines = f.readlines()
                for k, line in enumerate(lines):
                    values = [float(elem) for elem in line.split()]
                    data[i - 4, j, :, k] = values

    variables = (r"$\dot\theta$", r"$\dot\phi$", r"$\dot p_\theta$", r"$\dot p_\phi$")
    integrator_names = [f"RK{i}" for i in range(4, 8)]

    # Set up the subplots
    fig, axs = plt.subplots(4, 4, figsize=(9, 9))
    fig.suptitle("Comparison of Runge-Kutta Integrators and Step Sizes", fontsize=16)

    for rk_idx in range(4):  # 4 integrators
        for var_idx in range(4):  # 4 variables
            ax = axs[rk_idx, var_idx]
            for step_idx, step_size in enumerate(steps):  # 6 step sizes
                time = np.arange(0, 10, step_size)
                values = data[rk_idx, step_idx, var_idx, : len(time)]

                # Use a log-log plot
                ax.semilogy(time, values, label=f"h={step_size}", lw=1)

            if rk_idx == 0:
                ax.set_title(variables[var_idx], fontsize=12)

            if var_idx == 0:
                ax.set_ylabel(f"{integrator_names[rk_idx]}", fontsize=12)

            if rk_idx == 3:
                ax.set_xlabel("Time", fontsize=12)

            ax.legend(loc="upper right", fontsize=8)

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.show()


if __name__ == "__main__":
    main()
