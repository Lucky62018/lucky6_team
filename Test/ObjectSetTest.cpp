#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <gtest\gtest.h>

using namespace std;

//tested class
//ClassName:ObjectSet
//TestNum:004
#include "Object.h"

class ObjectSet : public Object {
public:
	int size;
	Object **set;

	ObjectSet() {}
	ObjectSet(Object **s, int n) { set = s; size = n; }
	virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const;
};

bool ObjectSet::Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
	IntersectInfo tempInfo;
	bool result = false;
	float closestT = maxT;
	for (int i = 0; i < size; i++) {
		if (set[i]->Intersect(r, minT, closestT, tempInfo)) {
			result = true;
			closestT = tempInfo.t;
			info = tempInfo;
		}
	}
	return result;
}

//TestFunction 004
TEST(Intersect, vector3Dtest)
{

	EXPECT_TRUE(Intersect(2,0,10,info));
	EXPECT_TRUE(Intersect(2,10,0,info));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	system("pause");
}