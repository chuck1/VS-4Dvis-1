


struct Vec
{
	float v[M];
};
struct Colorf
{
	float c[3];
};
struct Material
{
	struct Colorf emittance;
	struct Colorf reflectance;
};
struct RayCastResult
{
	bool hit;
	float k;
	struct Material mat;
	struct Vec x;
	struct Vec n;

	unsigned int polytope_i;
	unsigned int face_i;

	char message[128];
};
struct Ray
{
	struct Vec p;
	struct Vec v;

	struct Colorf color;

	// debugging
	struct RayCastResult res;
};



