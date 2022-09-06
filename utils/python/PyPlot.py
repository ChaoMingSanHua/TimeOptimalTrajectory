import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

font1={'family' : 'Times New Roman', 'size': 8}
font2={'family' : 'Times New Roman', 'size': 16}
# def plot(num, x, y, z=None):
#     plt.figure(num)
#     plt.plot(x, y)
#     if z:
#         plt.plot(x, z)
#     # plt.show()


# def plot3(num, x, y, z):
#     plt.figure(num)
#     ax1 = plt.axes(projection='3d')
#     ax1.plot3D(x, y, z, 'gray')
#     # ax1.scatter(x[0], y[0], z[0])
#     # plt.show()


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


def anima(num, x, y, z):
    def updata(i):
        plt.cla()
        ax1.plot3D(x, y, z, 'gray')
        ax1.plot3D(x[i], y[i], z[i], 'r', marker='o')
    fig = plt.figure(num)
    ax1 = plt.axes(projection='3d')
    ax1.plot3D(x, y, z, 'gray')
    ax1.plot3D(x[0], y[0], z[0], 'r', marker='o')
    ani = animation.FuncAnimation(fig=fig, func=updata, frames=np.arange(0, len(x)), interval=100)
    ani.save('trajectory.gif')

    plt.show()

def show():
    plt.show()


if __name__ == '__main__':
    x = np.arange(0, 100)
    y = np.arange(0, 100)
    z = np.arange(0, 100)
    # plot(1, x, y, z)
    # plot(1, x, y, z)

    # plot3(2, x, y, z)
    anima(2, x, y, z)
    # show()