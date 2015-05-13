
#ifndef COLOR
#define COLOR

/** \brief represents a color of 4 float components(r, g, b, a)
 */
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
