#ifndef TRIANGLE
#define TRIANGLE

#include <iostream>
#include <string>

#include "shape.h"
#include "../core/eqsolver.h"
#include <vector>

class Triangle : public Shape
{
public:
	Triangle() = delete;
	Triangle(const Vector3D a, const Vector3D b, const Vector3D c, Material *material_);

	Vector3D getNormalWorld(const Vector3D &pt_world) const;

	virtual bool rayIntersect(const Ray &ray, Intersection &its) const;
	virtual bool rayIntersectP(const Ray &ray) const;
	std::vector<Vector3D*> * getVertex();
	std::string toString() const;

	

private:
	Vector3D aWorld;
	Vector3D bWorld;
	Vector3D cWorld;
	Vector3D nWorld;
	Vector3D vab, vac, vca, vbc;
	std::vector<Vector3D*> *vertex;
};

std::ostream& operator<<(std::ostream &out, const Triangle &s);

#endif // TRIANGLE
