import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

font1={'family' : 'Times New Roman', 'size': 8}
font2={'family' : 'Times New Roman', 'size': 16}

def phasePlane(num, t, velLim, accLim, s, ds):
    plt.figure(num)
    plt.plot(t, velLim, label='acceleration limit curve')
    plt.plot(t, accLim, label='velocity limit curve')
    plt.plot(s, ds, label='time-optimal trajectory')
    plt.title('Phase-plane trajectory')
    plt.xlabel(r'$s$', fontdict=font2)
    plt.ylabel(r'$\dot{s}$', fontdict=font2)
    plt.grid()
    plt.legend()


def anima(num, x, y, z, px, py, pz):
    def updata(i):
        plt.cla()
        ax1.plot3D(x, y, z, 'gray')
        for j in range(len(px)):
            ax1.plot3D(px[j], py[j], pz[j], 'b', marker='o')
        ax1.plot3D(x[i], y[i], z[i], 'r', marker='o')
    fig = plt.figure(num)
    ax1 = plt.axes(projection='3d')
    ax1.plot3D(x, y, z, 'gray')
    for j in range(len(px)):
        ax1.plot3D(px[j], py[j], pz[j], 'b', marker='o')
    ax1.plot3D(x[0], y[0], z[0], 'r', marker='o')
    ani = animation.FuncAnimation(fig=fig, func=updata, frames=np.arange(0, len(x)), interval=100)
    ani.save('trajectory.gif')

    plt.show()

def show():
    plt.show()


if __name__ == '__main__':
    show()