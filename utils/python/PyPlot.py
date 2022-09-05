import matplotlib.pyplot as plt


def plot(num, x, y, z=None):
    plt.figure(num)
    plt.plot(x, y)
    if z:
        plt.plot(x, z)
    plt.show()


def plot3(num, x, y, z):
    plt.figure(num)
    ax1 = plt.axes(projection='3d')
    ax1.plot3D(x, y, z, 'gray')
    plt.show()


if __name__ == '__main__':
    x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    y = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    z = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    plot(1, x, y, z)
    plot(1, x, y, z)
    plt.show()
    # plot3(2, x, y, z)