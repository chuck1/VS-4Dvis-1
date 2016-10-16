
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
{
}

struct Ray
{
	float p[N];
	float v[N];
};

//void ray_face_intersect(__global struct Ray * ray, __global struct Face * face)

struct RayFaceInterceptTask
{
	unsigned int task_ray_intercept_i;

	unsigned int polytope_i;
	unsigned int face_i;

	float k;
	bool intersect;

	// redundent
	unsigned int ray_i;
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
__global char *		buffer_seek(__global char * c, unsigned int i)
{
	for (int j = 0; j < i; ++j)
	{
		unsigned int l = *((__global unsigned int *)c);

		c += l;
	}

	return c;
}

// subspace
__global float *	subspace_get_A(__global char * subspace)
{
	subspace += sizeof(unsigned int);
	return (__global float *)subspace;
}
__global float *	subspace_get_p(__global char * subspace)
{
	subspace += sizeof(unsigned int);
	subspace += N*(N-1)*sizeof(float);
	return (__global float *)subspace;
}
////unsigned int		subspace_get_M(__global char * subspace)
//{
//	return 0;
//}
//unsigned int		subspace_get_K(__global char * subspace)
//{
//	return 0;
//}
void				subspace_s(__global char * subspace, float * s, float * x)
{
	float a[N];

	vec_sub_pg(a, x, subspace_get_p(subspace));

	mat_mul_transpose_gp(s, subspace_get_A(subspace), a);
}


__global char *		polytope_get_face(__global char * polytope, unsigned int i)
{
	polytope += sizeof(unsigned int); // vector block size
	polytope += sizeof(unsigned int); // vector size

	polytope = buffer_seek(polytope, i); // vector elements blocks

	polytope += sizeof(unsigned int); // vector element block size

	return polytope;
}

unsigned int		inequalities_size(__global char * inequalities)
{
	inequalities += sizeof(unsigned int);
	return *((__global unsigned int*)inequalities);
}
__global char *		inequalities_get(__global char * inequalities, unsigned int ind)
{
	inequalities += sizeof(unsigned int);
	inequalities += sizeof(unsigned int);

	inequalities = buffer_seek(inequalities, ind);
	
	inequalities += sizeof(unsigned int);

	return inequalities;
}

__global float *	inequality_get_a(__global char * inequality)
{
	return (__global float *)inequality;
}
float				inequality_get_d(__global char * inequality)
{
	inequality += sizeof(float)* (N - 1);
	return *((__global float *)inequality);
}
float				inequality_d(__global char * inequality, float * s)
{
	return vec_dot_gp(inequality_get_a(inequality), s);
}
bool				inequality_eval(__global char * inequality, float * s)
{
	return (inequality_d(inequality, s) < inequality_get_d(inequality));
}

__global char *		face_get_subspace(__global char * face)
{
	face += sizeof(unsigned int);
	face += sizeof(unsigned int);
	return face;
}
__global char *		face_get_subspacebounded(__global char * face)
{
	face += sizeof(unsigned int);
	return face;
}
__global char *		face_get_inequalities(__global char * face)
{
	face += sizeof(unsigned int);
	face += sizeof(unsigned int);
	face = buffer_seek(face, 1);
	return face;
}
__global char *		face_get_plane(__global char * face)
{
	face += sizeof(unsigned int); // face block size int
	return buffer_seek(face, 1); // subspacebounded block
}
void				face_s(__global char * face, float * s, float * x)
{
	subspace_s(face_get_subspace(face), s, x);
}
bool				face_eval(__global char * face, float * s)
{
	__global char * inequalities = face_get_inequalities(face);

	for (unsigned int j = 0; j < inequalities_size(inequalities); ++j)
	{
		//nmath::geometry::Inequality<M - 1> & ineq = _M_inequalities[j];
		__global char * ineq = inequalities_get(inequalities, j);

		if (!inequality_eval(ineq, s)) {
			return false;
		}
	}

	return true;
}


__global float *	plane_get_n(__global char * plane)
{
	return (__global float *)plane;
}
__global float *	plane_get_d(__global char * plane)
{
	plane += (sizeof(float) * N);

	return (__global float *)plane;
}

void				ray_x(struct Ray * ray, float * x, float k)
{
	for (int i = 0; i < N; ++i)
	{
		x[i] = ray->p[i] + ray->v[i] * k;
	}
}



void ray_face_intercept(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * task)
{
	__global char * polytope = buffer_seek(polytopes, task->polytope_i);

	__global char * face = polytope_get_face(polytope, task->face_i);

	struct Ray ray = rays[task->ray_i];

	__global char * plane = face_get_plane(face);

	__global float * n = plane_get_n(plane);

	float d = *plane_get_d(plane);
	
	// calculate

	task->intersect = false;
	
	float nv = vec_dot_gp(n, ray.v);
	
	if (nv > 0)
	{
		// no intersection
		return;
	}

	float k = (d - vec_dot_gp(n, ray.p)) / nv;
	
	if (k < 0)
	{
		// no intersection
		return;
	}

	float x[N];
	float s[N-1];

	ray_x(&ray, x, k);
	
	//nmath::linalg::Vec<M - 1> s = f.s(x);
	face_s(face, s, x);
	
	return; // debugging=================
	// problem occurs after this point. but the error could have started earlier. the face pointer here could be wrong.

	if (!face_eval(face, s))
	{
		return;
	}

	task->intersect = true;
	task->k = k;
}

__kernel void ray_cast(
	__global void * polytopes,
	//__global void * lights,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * tasks_ray_face,
	__global uint * tasks_len,
	//__global float3 * pixel_color,
	volatile __global uint * counter)
{
	while (true){
		int task_id = atomic_inc(counter);
		if (task_id > ((*tasks_len) - 1)) return;

		__global struct RayFaceInterceptTask * task_ray_face = tasks_ray_face + task_id;

		// ERROR SOMEWHERE IN HERE
		ray_face_intercept(polytopes, rays, task_ray_face);
	}

}

__kernel void pointer_calc_test(
	__global char * polytopes,
	__global unsigned int * out_uint,
	__global float * out_float
	)
{
	__global char * polytope = polytopes + sizeof(unsigned int);

	__global char * face = polytope_get_face(polytope, 0);

	__global char * subspacebounded = face_get_subspacebounded(face);
	__global char * subspace = face_get_subspace(face);
	__global char * inequalities = face_get_inequalities(face);
	__global char * inequality = inequalities_get(inequalities, 0);

	out_uint[0] = ((__global unsigned int *)polytopes)[0];
	out_uint[1] = ((__global unsigned int *)polytope)[0];
	out_uint[2] = ((__global unsigned int *)polytope)[1];
	out_uint[3] = ((__global unsigned int *)face)[0];
	out_uint[4] = ((__global unsigned int *)subspacebounded)[0];
	out_uint[5] = ((__global unsigned int *)subspace)[0];

	//__global char * subspace = face_get_subspace(face);
	//__global char * inequalities = face_get_inequalities(face);
	__global char * plane = face_get_plane(face);
	__global float * plane_n = plane_get_n(plane);



	for (int i = 0; i < N; ++i)
	{
		out_float[i] = plane_n[i];
	}

	for (int j = 0; j < 4; ++j)
	{
		int stride = (j + 1) * 4;
		for (int i = 0; i < (N - 1); ++i)
		{
			out_float[i + stride] = inequality_get_a(inequalities_get(inequalities, j))[i];
		}
		out_float[3 + stride] = 0;
	}
	
	//__global float * plane_d = plane_get_d(plane);


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






