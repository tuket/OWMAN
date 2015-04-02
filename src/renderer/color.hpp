
#ifndef COLOR
#define COLOR

class Color
{
	
public:
	
	float r, g, b, a;
	
	Color(float r, float g, float b)
	:r(r), g(g), b(b), a(1.0)
	{}
	
	Color(float r, float g, float b, float a)
	:r(r), g(g), b(b), a(a)
	{}
	
};

#endif
