//
// Created by Cybaster on 2022/9/4.
//

#include <iostream>
#include <cstdio>
#include <Eigen/Core>
#include "Trajectory.h"
#include "Path.h"
#include "Python.h"

using namespace std;
using namespace Eigen;

int main() {
    list<VectorXd> waypoints;
    VectorXd waypoint(3);
    waypoint << 0.0, 0.0, 0.0;
    waypoints.push_back(waypoint);
    waypoint << 0.0, 0.2, 1.0;
    waypoints.push_back(waypoint);
    waypoint << 0.0, 3.0, 0.5;
    waypoints.push_back(waypoint);
    waypoint << 1.1, 2.0, 0.0;
    waypoints.push_back(waypoint);
    waypoint << 1.0, 0.0, 0.0;
    waypoints.push_back(waypoint);
    waypoint << 0.0, 1.0, 0.0;
    waypoints.push_back(waypoint);
    waypoint << 0.0, 0.0, 1.0;
    waypoints.push_back(waypoint);

    VectorXd maxAcceleration(3);
    maxAcceleration << 1.0, 1.0, 1.0;
    VectorXd maxVelocity(3);
    maxVelocity << 1.0, 1.0, 1.0;

    Trajectory trajectory(Path(waypoints, 0.1), maxVelocity, maxAcceleration);
    trajectory.outputPhasePlaneTrajectory();
    int k = 0;
    double tt[1000], positionX[1000], positionY[1000], positionZ[1000];
    const int num2 = 10001;
    int _length;
    double _s[num2], _maxVelocity[num2], _velocityMaxPathVelocity[num2], _pathPos[num2], _pathVel[num2];

    if(trajectory.isValid()) {
        double duration = trajectory.getDuration();
//        cout << "Trajectory duration: " << duration << " s" << endl << endl;
//        cout << "Time      Position                  Velocity" << endl;
        for(double t = 0.0; t < duration; t += 0.1) {
//            printf("%6.4f   %7.4f %7.4f %7.4f   %7.4f %7.4f %7.4f\n", t, trajectory.getPosition(t)[0], trajectory.getPosition(t)[1], trajectory.getPosition(t)[2],
//                   trajectory.getVelocity(t)[0], trajectory.getVelocity(t)[1], trajectory.getVelocity(t)[2]);
            tt[k] = t;
            positionX[k] = trajectory.getPosition(t)[0];
            positionY[k] = trajectory.getPosition(t)[1];
            positionZ[k++] = trajectory.getPosition(t)[2];
        }
//        printf("%6.4f   %7.4f %7.4f %7.4f   %7.4f %7.4f %7.4f\n", duration, trajectory.getPosition(duration)[0], trajectory.getPosition(duration)[1], trajectory.getPosition(duration)[2],
//               trajectory.getVelocity(duration)[0], trajectory.getVelocity(duration)[1], trajectory.getVelocity(duration)[2]);
        tt[k] = duration;
        positionX[k] = trajectory.getPosition(duration)[0];
        positionY[k] = trajectory.getPosition(duration)[1];
        positionZ[k++] = trajectory.getPosition(duration)[2];
    }
    else {
        cout << "Trajectory generation failed." << endl;
    }

    trajectory.outputPhasePlaneTrajectory(_s, _maxVelocity, _velocityMaxPathVelocity, _pathPos, _pathVel, _length);


    Py_SetPythonHome(L"D:/ProgramData/Anaconda3");
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../utils/python/')");

//     Plot3
    PyObject *pModuleObject = PyImport_ImportModule("PyPlot");
    PyObject *pFuncPlot3 = PyObject_GetAttrString(pModuleObject, "plot3");

    PyObject *PyList31 = PyList_New(k);
    PyObject *PyList32 = PyList_New(k);
    PyObject *PyList33 = PyList_New(k);
    PyObject *ArgList3 = PyTuple_New(4);

    for(int i = 0; i< PyList_Size(PyList31); i++) {
        PyList_SetItem(PyList31, i, PyFloat_FromDouble(positionX[i]));
        PyList_SetItem(PyList32, i, PyFloat_FromDouble(positionY[i]));
        PyList_SetItem(PyList33, i, PyFloat_FromDouble(positionZ[i]));
    }

    PyTuple_SetItem(ArgList3, 0, PyFloat_FromDouble(1));
    PyTuple_SetItem(ArgList3, 1, PyList31);
    PyTuple_SetItem(ArgList3, 2, PyList32);
    PyTuple_SetItem(ArgList3, 3, PyList33);
    PyObject_CallObject(pFuncPlot3, ArgList3);

    // Plot
    PyObject *pFuncPlot = PyObject_GetAttrString(pModuleObject, "plot");
    PyObject *PyList1 = PyList_New(num2);
    PyObject *PyList2 = PyList_New(num2);
    PyObject *PyList3 = PyList_New(num2);
    PyObject *PyList4 = PyList_New(_length);
    PyObject *PyList5 = PyList_New(_length);

    PyObject *ArgList = PyTuple_New(4);
    PyObject *ArgList2 = PyTuple_New(3);

    for(int i = 0; i< PyList_Size(PyList1); i++) {
        PyList_SetItem(PyList1, i, PyFloat_FromDouble(_s[i]));
        PyList_SetItem(PyList2, i, PyFloat_FromDouble(_maxVelocity[i]));
        PyList_SetItem(PyList3, i, PyFloat_FromDouble(_velocityMaxPathVelocity[i]));
    }

    PyTuple_SetItem(ArgList, 0, PyFloat_FromDouble(2));
    PyTuple_SetItem(ArgList, 1, PyList1);
    PyTuple_SetItem(ArgList, 2, PyList2);
    PyTuple_SetItem(ArgList, 3, PyList3);
    PyObject_CallObject(pFuncPlot, ArgList);


    for(int i = 0; i< PyList_Size(PyList4); i++) {
        PyList_SetItem(PyList4, i, PyFloat_FromDouble(_pathPos[i]));
        PyList_SetItem(PyList5, i, PyFloat_FromDouble(_pathVel[i]));
    }
    PyTuple_SetItem(ArgList2, 0, PyFloat_FromDouble(2));
    PyTuple_SetItem(ArgList2, 1, PyList4);
    PyTuple_SetItem(ArgList2, 2, PyList5);
    PyObject_CallObject(pFuncPlot, ArgList2);
}
