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
    const int num2 = 20001;
    int _length;
    double _s[num2], _maxVelocity[num2], _velocityMaxPathVelocity[num2], _pathPos[num2], _pathVel[num2];

    if(trajectory.isValid()) {
        double duration = trajectory.getDuration();
        for(double t = 0.0; t < duration; t += 0.1) {
            tt[k] = t;
            positionX[k] = trajectory.getPosition(t)[0];
            positionY[k] = trajectory.getPosition(t)[1];
            positionZ[k++] = trajectory.getPosition(t)[2];
        }
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


    PyObject *pModuleObject = PyImport_ImportModule("PyPlot");
    PyObject *pFuncAnima = PyObject_GetAttrString(pModuleObject, "anima");

    PyObject *PyListAnima1 = PyList_New(k);
    PyObject *PyListAnima2 = PyList_New(k);
    PyObject *PyListAnima3 = PyList_New(k);
    PyObject *ArgListAnima = PyTuple_New(4);

    for(int i = 0; i< PyList_Size(PyListAnima1); i++) {
        PyList_SetItem(PyListAnima1, i, PyFloat_FromDouble(positionX[i]));
        PyList_SetItem(PyListAnima2, i, PyFloat_FromDouble(positionY[i]));
        PyList_SetItem(PyListAnima3, i, PyFloat_FromDouble(positionZ[i]));
    }

    PyTuple_SetItem(ArgListAnima, 0, PyFloat_FromDouble(1));
    PyTuple_SetItem(ArgListAnima, 1, PyListAnima1);
    PyTuple_SetItem(ArgListAnima, 2, PyListAnima2);
    PyTuple_SetItem(ArgListAnima, 3, PyListAnima3);
    PyObject_CallObject(pFuncAnima, ArgListAnima);

    PyObject *pFuncPhasePlane = PyObject_GetAttrString(pModuleObject, "phasePlane");
    PyObject *PyListPhasePlane1 = PyList_New(num2);
    PyObject *PyListPhasePlane2 = PyList_New(num2);
    PyObject *PyListPhasePlane3 = PyList_New(num2);
    PyObject *PyListPhasePlane4 = PyList_New(_length);
    PyObject *PyListPhasePlane5 = PyList_New(_length);

    for(int i = 0; i< PyList_Size(PyListPhasePlane1); i++) {
        PyList_SetItem(PyListPhasePlane1, i, PyFloat_FromDouble(_s[i]));
        PyList_SetItem(PyListPhasePlane2, i, PyFloat_FromDouble(_maxVelocity[i]));
        PyList_SetItem(PyListPhasePlane3, i, PyFloat_FromDouble(_velocityMaxPathVelocity[i]));
    }

    for(int i = 0; i< PyList_Size(PyListPhasePlane4); i++) {
        PyList_SetItem(PyListPhasePlane4, i, PyFloat_FromDouble(_pathPos[i]));
        PyList_SetItem(PyListPhasePlane5, i, PyFloat_FromDouble(_pathVel[i]));
    }


    PyObject *ArgListPhasePlane = PyTuple_New(6);
    PyTuple_SetItem(ArgListPhasePlane, 0, PyFloat_FromDouble(2));
    PyTuple_SetItem(ArgListPhasePlane, 1, PyListPhasePlane1);
    PyTuple_SetItem(ArgListPhasePlane, 2, PyListPhasePlane2);
    PyTuple_SetItem(ArgListPhasePlane, 3, PyListPhasePlane3);
    PyTuple_SetItem(ArgListPhasePlane, 4, PyListPhasePlane4);
    PyTuple_SetItem(ArgListPhasePlane, 5, PyListPhasePlane5);
    PyObject_CallObject(pFuncPhasePlane, ArgListPhasePlane);


    PyObject *pFuncShow = PyObject_GetAttrString(pModuleObject, "show");
    PyObject_CallObject(pFuncShow, NULL);

}
