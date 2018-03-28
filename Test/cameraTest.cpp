#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <gtest\gtest.h>
#include "RayTest.cpp"

using namespace std;

//tested class
//ClassName:Canmera
//TestNumber 003
class Camera {
public:
	Vector3D origin;
	Vector3D leftLowerCorner;
	Vector3D horizontal;
	Vector3D vertical;

	Camera(Vector3D from, Vector3D at, Vector3D vup, float vfov, float aspect) { // vfov is top to bottom in degrees
		Vector3D u, v, w;
		float theta = vfov * M_PI / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = from;
		w = GetUnitizedCopy(from - at);
		u = GetUnitizedCopy(CrossProduct(vup, w));
		v = CrossProduct(w, u);
		leftLowerCorner = origin - halfWidth * u - halfHeight * v - w;
		horizontal = 2 * halfWidth * u;
		vertical = 2 * halfHeight * v;
	}

	// Camera() {
	//   leftLowerCorner = Vector3D(-2, -1, -1);
	//   horizontal = Vector3D(4, 0, 0);
	//   vertical = Vector3D(0, 2, 0);
	//   origin = Vector3D(0,0,0);
	// }


	Ray getRay(float a, float b) {
		return Ray(origin, leftLowerCorner + a * horizontal + b * vertical - origin);
	}

};


//TestFunction 002-1
TEST(LengthTest, vector3Dtest)
{
	Vector3D a(1, 1, 1);
	Vector3D b(-1, -1, -1);
	Vector3D c(1, 1, -1);

	//test 
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 0, 2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 45, 2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, -45, 2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 0, -2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 45, -2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, -45, -2););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 0, 0););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 45, 0););
	EXPECT_ANY_THROW(Camera first_camera(a, b, c, 90, 0););

}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	system("pause");
}