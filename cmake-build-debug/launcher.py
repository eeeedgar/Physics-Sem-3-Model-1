import os
from matplotlib import pyplot as plt

xtFileName = "x_t.txt"
trajectoryFileName = "trajectory.txt"

os.system("sem_2_model_1.exe")

def draw(filename, title, label1, label2, pic_path):
    file = open(filename, 'r')
    xs = []
    ys = []
    lines = file.readlines()
    for line in lines:
        x, y = map(float, line.split())
        xs.append(x)
        ys.append(y)
    fig, ax = plt.subplots()

    ax.plot(xs, ys)
    plt.title(title)
    plt.xlabel(label1)
    plt.ylabel(label2)
    plt.grid(True)
    plt.savefig(pic_path)
    file.close()

draw(xtFileName, "x(t)", "t", "x", "pictures/x_t.png")
draw(trajectoryFileName, "trajectory", "x", "y", "pictures/trajectory")
