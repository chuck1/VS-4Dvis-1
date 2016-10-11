
float	vec_dot_gg(__global float * a, __global float * b)
{
	float ret = 0;
	for (unsigned int i = 0; i < N; ++i)
	{
		ret += (a[i] * b[i]);
	}
	return ret;
}
float	vec_dot_gp(__global float * a, float * b)
{
	float ret = 0;
	for (unsigned int i = 0; i < N; ++i)
	{
		ret += (a[i] * b[i]);
	}
	return ret;
}
void	vec_sub_gg(float * ret, __global float * a, __global float * b)
{
	for (int i = 0; i < N; ++i)
	{
		ret[i] = a[i] - b[i];
	}
}
void	vec_sub_pg(float * ret, float * a, __global float * b)
{
	for (int i = 0; i < N; ++i)
	{
		ret[i] = a[i] - b[i];
	}
}

void	mat_mul_transpose_gp(float * ret, __global float * A, float * b)
{}

struct Ray
{
	float p[N];
	float v[N];
};

//void ray_face_intersect(__global struct Ray * ray, __global struct Face * face)


struct RayFaceInterceptTask
{
	unsigned int polytope_i;
	unsigned int face_i;
	unsigned int ray_i;
	float k;
	bool intersect;
};

//void * buffer_seek(void * c, unsigned int i)
//{
//	for (int j = 0; j < i; ++j)
//	{
//		unsigned int l = *((unsigned int *)c);
//
//		c += l;
//	}
//
//	return c;
//}
__global char * buffer_seek(__global char * c, unsigned int i)
{
	for (int j = 0; j < i; ++j)
	{
		unsigned int l = *((__global unsigned int *)c);

		c += l;
	}

	return c;
}

__global char * polytope_get_face(__global char * polytope, unsigned int i)
{
	polytope += sizeof(unsigned int) * 2;

	return buffer_seek(polytope, i);
}
__global char * face_get_subspace(__global char * face)
{
	return face;
}
__global char * face_get_plane(__global char * face)
{
	return buffer_seek(face, 1);
}

// subspace
__global float *	subspace_get_A(__global char * subspace)
{
	return 0;
}
__global float *	subspace_get_p(__global char * subspace)
{
	return 0;
}
unsigned int		subspace_get_M(__global char * subspace)
{
	return 0;
}
unsigned int		subspace_get_K(__global char * subspace)
{
	return 0;
}
void				subspace_s(__global char * subspace, float * s, float * x)
{
	// _M_A.transpose()*(x - _M_p);

	float a[N];

	vec_sub_pg(a, x, subspace_get_p(subspace));

	float b[N];

	mat_mul_transpose_gp(b, subspace_get_A(subspace), a);
}

__global float * plane_get_n(__global char * plane)
{
	return (__global float *)plane;
}
float plane_get_d(__global char * plane)
{
	plane += (sizeof(float) * N);

	return *(__global float *)plane;
}





void ray_face_intercept(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * tasks,
	unsigned int task_i)
{
	__global struct RayFaceInterceptTask * task = task + task_i;

	__global char * polytope = buffer_seek(polytopes, task->polytope_i);

	__global char * face = polytope_get_face(polytope, task->face_i);

	struct Ray ray = rays[task->ray_i];

	__global char * plane = face_get_plane(face);

	__global float * n = plane_get_n(plane);
	
	float d = plane_get_d(plane);

	// calculate

	float a = vec_dot(n, ray.v);

	if (a > 0)
	{
		// no intersection
		return;
	}

	float k = (d - vec_dot(n, ray.p)) / a;



}

__kernel void ray_cast(
	__global void * polytopes,
	__global void * lights,
	__global struct Ray * rays,
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






