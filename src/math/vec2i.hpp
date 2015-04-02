
#ifndef VEC2I
#define VEC2I

class Vec2i
{

public:

	int x, y;
	
	Vec2i(){}
	Vec2i(int x, int y);
	
	Vec2i operator=(const Vec2i& vec);
	
	Vec2i operator+(const Vec2i& vec);
	Vec2i operator-(const Vec2i& vec);
	Vec2i operator-();
	
};

#endif
