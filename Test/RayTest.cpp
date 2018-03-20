#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <gtest\gtest.h>

#include "vector3Dtest.cpp"

using namespace std;

//tested class
//ClassName:Ray
//Test number 002
class Ray {
public:
	Vector3D origin;
	Vector3D direction;

	//constructors
	Ray() {}
	Ray(const Vector3D& a, const Vector3D& b) { origin = a; direction = b; }

	//test function 002-1
	Vector3D TerminalWithArgument(float k) const { return origin + k * direction; }

};

//TestFunction 002-1
TEST(LengthTest, vector3Dtest)
{
	Vector3D a(1, 1, 1);
	Vector3D b(-1, -1, -1);
	Vector3D c(1, 1, -1);
	Ray first_ray(a, b);
	Ray second_ray(a, c);
	Ray third_ray(b, c);
	//test k > 0
	EXPECT_ANY_THROW(first_ray.TerminalWithArgument(2.5));
	EXPECT_ANY_THROW(second_ray.TerminalWithArgument(2.5));
	EXPECT_ANY_THROW(third_ray.TerminalWithArgument(2.5));
	//test k = 0
	EXPECT_ANY_THROW(first_ray.TerminalWithArgument(0));
	EXPECT_ANY_THROW(second_ray.TerminalWithArgument(0));
	EXPECT_ANY_THROW(third_ray.TerminalWithArgument(0));
	//test k < 0
	EXPECT_ANY_THROW(first_ray.TerminalWithArgument(-2.5));
	EXPECT_ANY_THROW(second_ray.TerminalWithArgument(-2.5));
	EXPECT_ANY_THROW(third_ray.TerminalWithArgument(-2.5));

}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	system("pause");
}
