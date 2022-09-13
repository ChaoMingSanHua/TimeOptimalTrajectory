#pragma once

#include <list>
#include <Eigen/Core>

class PathSegment
{
public:
	PathSegment(double length = 0.0) :
		length(length)
	{
	}
	
	virtual ~PathSegment() {}

	double getLength() const {
		return length;
	}
	virtual Eigen::VectorXd getConfig(double s) const = 0;
	virtual Eigen::VectorXd getTangent(double s) const = 0;
	virtual Eigen::VectorXd getCurvature(double s) const = 0;
	virtual std::list<double> getSwitchingPoints() const = 0;
	virtual PathSegment* clone() const = 0;

	double position;
protected:
	double length;
};



class Path
{
public:
	Path(const std::list<Eigen::VectorXd> &path, double maxDeviation = 0.0);
	Path(const Path &path);
	~Path();
	double getLength() const;
	Eigen::VectorXd getConfig(double s) const;
	Eigen::VectorXd getTangent(double s) const;
	Eigen::VectorXd getCurvature(double s) const;
	double getNextSwitchingPoint(double s, bool &discontinuity) const;
	std::list<std::pair<double, bool> > getSwitchingPoints() const;
private:
	PathSegment* getPathSegment(double &s) const;
	double length;
	std::list<std::pair<double, bool> > switchingPoints;
	std::list<PathSegment*> pathSegments;
};