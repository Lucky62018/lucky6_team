#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <gtest\gtest.h>

using namespace std;

//tested class
//ClassName:Sphere
//TestNum:005
#include "Object.h"

class Sphere : public Object {
public:
	Vector3D center;
	float radius;
	Material* materialPointer;

	Sphere() {}
	Sphere(Vector3D c, float r, Material* m) {
		center = c;
		radius = r;
		materialPointer = m;
	}

	virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const;
};

bool Sphere::Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
	Vector3D oc = r.origin - center;
	float a = DotProduct(r.direction, r.direction);
	float b = 2 * DotProduct(oc, r.direction);
	float c = DotProduct(oc, oc) - radius * radius;
	float d = b * b - 4 * a * c;
	if (d > 0) {
		float temp = (-b - sqrt(d)) / (2 * a);
		if (temp < maxT && temp > minT) {
			info.t = temp;
			info.pointOfIntersection = r.TerminalWithArgument(temp);
			info.normal = (info.pointOfIntersection - center) / radius;
			info.materialPointer = materialPointer;
			return true;
		}
		temp = (-b + sqrt(d)) / (2 * a);
		if (temp < maxT && temp > minT) {
			info.t = temp;
			info.pointOfIntersection = r.TerminalWithArgument(temp);
			info.normal = (info.pointOfIntersection - center) / radius;
			info.materialPointer = materialPointer;
			return true;
		}
	}
	return false;
}

//TestFunction 002-1
TEST(LengthTest, vector3Dtest)
{
	Vector3D vector(1, 1, 1);
	Spheere sphere(vector, 20, 1);
	EXPECT_TRUE(sphere.Intersect(2,0,10,info));
	EXPECT_TRUE(sphereIntersect(2,10,0,info));
}
//TestFunction 001-2
TEST(UnitizeTest, vector3Dtest)
{

}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	system("pause");
}