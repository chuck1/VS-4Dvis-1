
struct Ray
{
	float p[N];
	float v[N];

	// intersection data
	double k;
	int face_index;
	float color[3];
};

struct Face
{

};

void math_dot(__global const float * x, __global const float * y, const uint m, __global float * res)
{
	*res = 0;
	for (int i = 0; i < m; ++i)
	{
		*res += x[i] * y[i];
	}
}

//void ray_face_intersect(__global struct Ray * ray, __global struct Face * face)


struct RayFaceInterceptTask
{
	unsigned int shape;
	unsigned int face;
	unsigned int ray;
	float k;
};


__kernel void ray_cast(
		__global struct RayFaceInterceptTask * tasks,
		unsigned int tasks_len,
		__global float3 * pixel_color,
		volatile __global uint * counter)
{
	while (true){
		int task_id = atomic_inc(counter);
		if (task_id > (tasks_len - 1)) return;
	}
}

__kernel void hello(
	__global char* string,
	volatile __global uint * counter)
{
	constant char * s = "Hello, World!";

	while (true)
	{
		int task_id = atomic_inc(counter);

		if (task_id > 13) return;

		string[task_id] = s[task_id];
	}
	/*
	string[0] = 'H';
	string[1] = 'e';
	string[2] = 'l';
	string[3] = 'l';
	string[4] = 'o';
	string[5] = ',';
	string[6] = ' ';
	string[7] = 'W';
	string[8] = 'o';
	string[9] = 'r';
	string[10] = 'l';
	string[11] = 'd';
	string[12] = '!';
	string[13] = '\0';
	*/
}






