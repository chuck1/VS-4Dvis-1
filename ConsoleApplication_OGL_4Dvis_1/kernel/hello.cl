

struct RayFaceInterceptResult
{
	unsigned int shape;
	unsigned int face;
	unsigned int ray;
	float k;
}
struct Color
{
	float v[3];
}


__kernel void function0(
		__global RayFaceInterceptResult * results
		__global Color * pixels)
{

}


__kernel void hello(__global char* string)
{
	string[0] = '\0';
}


