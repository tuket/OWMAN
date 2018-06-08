
#ifndef VEC2I
#define VEC2I

class Vec2f;

/**
 * Represents a vector of two integer components
 *
 */
class Vec2i
{

public:

	int x, y;

	Vec2i(){}
	Vec2i(int x, int y);
	Vec2i(const Vec2i& v);
	Vec2i(const Vec2f& v);

	Vec2i operator=(const Vec2i& vec);

	Vec2i operator+=(const Vec2i& vec);
	Vec2i operator-=(const Vec2i& vec);

	Vec2i operator+(const Vec2i& vec)const;
	Vec2i operator-(const Vec2i& vec)const;
	Vec2i operator-()const;

	bool operator<(const Vec2i& v)const;
	bool operator==(const Vec2i& v)const;
	bool operator!=(const Vec2i& v)const;

};

#endif
