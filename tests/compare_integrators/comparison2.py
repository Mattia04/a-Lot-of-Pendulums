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

    # Compute errors using the smallest step size (h=0.001) as the reference
    reference = data[:, -1, :, :]  # Last step size (h=0.001)
    errors = np.empty((4, 6, 4), dtype=np.float64)

    for rk_idx in range(4):  # 4 integrators
        for step_idx in range(6):  # 6 step sizes
            for var_idx in range(4):  # 4 variables
                # Compute mean absolute error for the variable
                values = data[rk_idx, step_idx, var_idx, : int(10 / steps[step_idx])]
                errors[rk_idx, step_idx, var_idx] = np.mean(np.abs(values))

    integrator_names = [f"RK{i}" for i in range(4, 8)]
    variables = (r"$\dot\theta$", r"$\dot\phi$", r"$\dot p_\theta$", r"$\dot p_\phi$")

    # Plot step size vs. average error for each variable
    fig, axs = plt.subplots(1, 4, figsize=(16, 8), sharex=True)
    fig.suptitle("Step Size vs. Average Error for Each Variable", fontsize=16)

    for var_idx in range(4):  # 4 variables
        ax = axs[var_idx]
        for rk_idx in range(4):  # 4 integrators
            ax.loglog(
                steps,
                errors[rk_idx, :, var_idx],
                label=integrator_names[rk_idx],
                marker="o",
                lw=1.5,
            )
        ax.set_ylabel(f"Error ({variables[var_idx]})", fontsize=12)
        ax.legend(fontsize=10, loc="upper right")
        ax.grid()

    axs[-1].set_xlabel("Step Size (h)", fontsize=12)
    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.show()


if __name__ == "__main__":
    main()
