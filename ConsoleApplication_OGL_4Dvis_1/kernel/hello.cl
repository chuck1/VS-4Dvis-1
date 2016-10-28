
#define M (N)

#include "kernel/kernel.h"



float	vec_dot_gg(__global float * a, __global float * b, unsigned int m)
{
	float ret = 0;
	for (unsigned int i = 0; i < m; ++i)
	{
		ret += (a[i] * b[i]);
	}
	return ret;
}
float	vec_dot_gp(__global float * a, float * b, unsigned int m)
{
	float ret = 0;
	for (unsigned int i = 0; i < m; ++i)
	{
		ret += (a[i] * b[i]);
	}
	return ret;
}

float		vec_dot(struct Vec a, struct Vec b)
{
	float ret = 0;
	for (unsigned int i = 0; i < M; ++i)
	{
		ret += (a.v[i] * b.v[i]);
	}
	return ret;
}
struct Vec	vec_sub(struct Vec a, struct Vec b)
{
	struct Vec ret;
	for (unsigned int i = 0; i < M; ++i)
	{
		ret.v[i] = a.v[i] - b.v[i];
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
void	vec_sub_pg(float * ret, struct Vec a, __global float * b)
{
	for (int i = 0; i < N; ++i)
	{
		ret[i] = a.v[i] - b[i];
	}
}
void	vec_sub_ggp(__global float * ret, __global float * a, float * b)
{
	for (int i = 0; i < N; ++i)
	{
		ret[i] = a[i] - b[i];
	}
}

void	vec_cpy_gp(__global float * dst, float * src, unsigned int m)
{
	for (unsigned int i = 0; i < m; ++i)
	{
		dst[i] = src[i];
	}
}
void	vec_cpy_gg(__global float * dst, __global float * src, unsigned int m)
{
	for (unsigned int i = 0; i < m; ++i)
	{
		dst[i] = src[i];
	}
}

void	vec_normalize_g(__global float * ret, unsigned int m)
{
	float l = 0;
	for (unsigned int i = 0; i < m; ++i)
	{
		l += ret[i] * ret[i];
	}
	l = sqrt(l);
	for (unsigned int i = 0; i < m; ++i)
	{
		ret[i] /= l;
	}
}

void	vec_normalize(__global struct Vec * ret)
{
	float l = 0;
	for (unsigned int i = 0; i < M; ++i)
	{
		l += ret->v[i] * ret->v[i];
	}
	l = sqrt(l);
	for (unsigned int i = 0; i < M; ++i)
	{
		ret->v[i] /= l;
	}
}


void	mat_mul_transpose_gp(float * ret, __global float * A, float * b)
{
	/*for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			ret(i) += A(i, j) * v(j);
		}
	}*/

	for (int i = 0; i < (N-1); ++i) // rows
	{
		ret[i] = 0;

		for (int j = 0; j < N; ++j) // columns
		{
			ret[i] += A[j*(N-1) + i] * b[j];
		}
	}
}



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

	unsigned int fail_code;

	// debugging
	float nv;
	struct Vec x;
	float s[M - 1];
	float A[M*(M - 1)];
};
struct RayInterceptInOut
{
	unsigned int pixel_i;
	unsigned int pixel_j;
	unsigned int ray_i;

	float k;
	bool intersect;

	unsigned int _M_task_i;
};
struct Color_1_1_1
{
	unsigned char c[3];
};

struct Color_1_1_1 color_convert(struct Colorf color)
{
	struct Color_1_1_1 ret;

	for (int i = 0; i < 3; ++i)
	{
		float c = color.c[i] * 255.f;

		//if (c > 255.f) c = 255.f;

		ret.c[i] = (unsigned int)c;
	}

	return ret;
}

struct KernelHeader
{
	unsigned int h;
	unsigned int w;
	unsigned int s;
	unsigned int counter;
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
void				subspace_s(__global char * subspace, float * s, struct Vec x)
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
	return vec_dot_gp(inequality_get_a(inequality), s, M-1);
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
void				face_s(__global char * face, float * s, struct Vec x)
{
	subspace_s(face_get_subspace(face), s, x);
}
bool				face_eval(__global char * face, float * s)
{
	__global char * inequalities = face_get_inequalities(face);

	unsigned int size = inequalities_size(inequalities);

	for (unsigned int j = 0; j < size; ++j)
	{
		//nmath::geometry::Inequality<M - 1> & ineq = _M_inequalities[j];
		__global char * ineq = inequalities_get(inequalities, j);

		if (!inequality_eval(ineq, s)) {
			return false;
		}
	}

	return true;
}


struct Vec			plane_get_n(__global char * plane)
{
	return *(__global struct Vec *)plane;
}
__global float *	plane_get_d(__global char * plane)
{
	plane += (sizeof(float) * N);

	return (__global float *)plane;
}

struct Vec			ray_x(struct Ray * ray, float k)
{
	struct Vec x;
	for (int i = 0; i < N; ++i)
	{
		x.v[i] = ray->p.v[i] + ray->v.v[i] * k;
	}
	return x;
}
struct Vec			ray_x_g(__global struct Ray * ray, float k)
{
	struct Vec x;
	for (int i = 0; i < N; ++i)
	{
		x.v[i] = ray->p.v[i] + ray->v.v[i] * k;
	}
	return x;
}


unsigned int		task_ray_in_tasks_ray_face_intercept_i_size(__global char * task_ray_in)
{
	task_ray_in += sizeof(unsigned int);

	return *((__global unsigned int*)task_ray_in);
}
unsigned int		task_ray_in_tasks_ray_face_intercept_i_get(__global char * task_ray_in, unsigned int i)
{
	task_ray_in += sizeof(unsigned int);
	task_ray_in += sizeof(unsigned int);

	return ((__global unsigned int*)task_ray_in)[i];
}


void ray_face_intercept(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * task)
{
	__global char * polytope = buffer_seek(polytopes, task->polytope_i) + sizeof(unsigned int);
	__global char * face = polytope_get_face(polytope, task->face_i);
	__global char * subspace = face_get_subspace(face);

	struct Ray ray = rays[task->ray_i];

	__global char * plane = face_get_plane(face);

	struct Vec n = plane_get_n(plane);

	float d = *plane_get_d(plane);
	
	// debugging
	vec_cpy_gg(task->A, subspace_get_A(subspace), M*(M-1));

	// calculate

	task->fail_code = 0;
	task->intersect = false;
	
	float nv = vec_dot(n, ray.v);
	
	// debugging
	task->nv = nv;
	
	if (nv > 0)
	{
		// no intersection
		return;
	}

	float k = (d - vec_dot(n, ray.p)) / nv;
	
	if (k < 0)
	{
		// no intersection
		return;
	}

	struct Vec x;
	float s[M-1];

	x = ray_x(&ray, k);
	
	// debugging
	task->x = x;
	//vec_cpy_gp(task->x, x, M);

	//nmath::linalg::Vec<M - 1> s = f.s(x);
	face_s(face, s, x);
	
	// debugging
	vec_cpy_gp(task->s, s, M-1);

	task->k = k;
	
	if (!face_eval(face, s))
	{
		task->fail_code = 3;
		return;
	}

	task->intersect = true;
}


void ray_view(
	__global char * task_ray_in,
	__global struct RayInterceptInOut * task_ray_inout,
	__global struct RayFaceInterceptTask * tasks_ray_face)
{
	task_ray_inout->k = FLT_MAX;
	task_ray_inout->intersect = false;

	//for (unsigned int i = 0; i < task_in->_M_tasks_ray_face_intercept_i.size(); ++i)

	//unsigned int size = task_ray_in_tasks_ray_face_intercept_i_size(task_ray_in);
	unsigned int size = 8;

	for (unsigned int i = 0; i < size; ++i)
	{
		unsigned int tasks_ray_face_intercept_i = task_ray_in_tasks_ray_face_intercept_i_get(task_ray_in, i);
		
		struct RayFaceInterceptTask task_ray_face = tasks_ray_face[tasks_ray_face_intercept_i];

		if (!task_ray_face.intersect) continue;

		if (task_ray_face.k > task_ray_inout->k) continue;

		task_ray_inout->k = task_ray_face.k;
		task_ray_inout->intersect = true;
		task_ray_inout->_M_task_i = i;
	}
}



__kernel void ray_cast(
	__global void * polytopes,
	//__global void * lights,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * tasks_ray_face,
	__global uint * tasks_ray_face_len,
	__global char * tasks_ray_in,
	__global struct RayInterceptInOut * tasks_ray_inout,
	__global uint * tasks_ray_inout_len,
	//__global float3 * pixel_color,
	volatile __global uint * counter)
{
	// ray view calculate all possible face intersections
	
	if (get_global_id(0) == 0) *counter = 0;
	barrier(CLK_GLOBAL_MEM_FENCE);

	while (true){
		int task_id = atomic_inc(counter);
		if (task_id > ((*tasks_ray_face_len) - 1)) break;

		__global struct RayFaceInterceptTask * task_ray_face = tasks_ray_face + task_id;

		ray_face_intercept(polytopes, rays, task_ray_face);
	}

	// ray view determine first face intersection
	

	barrier(CLK_GLOBAL_MEM_FENCE);
	if (get_global_id(0) == 0) *counter = 0;
	barrier(CLK_GLOBAL_MEM_FENCE);

	while (true){
		int task_id = atomic_inc(counter);
		if (task_id > ((*tasks_ray_inout_len) - 1)) break;

		// args
		__global char * task_ray_in = buffer_seek(tasks_ray_in, task_id) + sizeof(unsigned int);
		__global struct RayInterceptInOut * task_ray_inout = tasks_ray_inout + task_id;

		ray_view(task_ray_in, task_ray_inout, tasks_ray_face);
	}
}

__kernel void pointer_calc_test(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct RayFaceInterceptTask * tasks_ray_face,
	__global unsigned int * out_uint,
	__global float * out_float
	)
{
	struct RayFaceInterceptTask task = tasks_ray_face[0];

	__global char * polytope = buffer_seek(polytopes, task.polytope_i) + sizeof(unsigned int);

	__global char * face = polytope_get_face(polytope, task.face_i);

	struct Ray ray = rays[task.ray_i];


	__global char * subspacebounded = face_get_subspacebounded(face);
	__global char * subspace = face_get_subspace(face);
	__global char * inequalities = face_get_inequalities(face);
	__global char * inequality = inequalities_get(inequalities, 0);

	

	__global char * plane = face_get_plane(face);
	struct Vec n = plane_get_n(plane);
	float d = *plane_get_d(plane);
	
	
	out_uint[0] = task.ray_i;
	out_uint[1] = task.polytope_i;
	out_uint[2] = task.face_i;
	

	// calculate

	float nv = vec_dot(n, ray.v);

	if (nv > 0)
	{
		// no intersection
		return;
	}

	float k = (d - vec_dot(n, ray.p)) / nv;

	if (k < 0)
	{
		// no intersection
		return;
	}

	struct Vec x;
	float s[N - 1];

	x = ray_x(&ray, k);

	//nmath::linalg::Vec<M - 1> s = f.s(x);
	face_s(face, s, x);

	//task->k = k;

	if (!face_eval(face, s))
	{
		//task->fail_code = 3;
		return;
	}

	//task->intersect = true;

	return;

#if 0

	out_uint[0] = ((__global unsigned int *)polytopes)[0];
	out_uint[1] = ((__global unsigned int *)polytope)[0];
	out_uint[2] = ((__global unsigned int *)polytope)[1];
	out_uint[3] = ((__global unsigned int *)face)[0];
	out_uint[4] = ((__global unsigned int *)subspacebounded)[0];
	out_uint[5] = ((__global unsigned int *)subspace)[0];
	out_uint[6] = inequalities_size(inequalities);

	int size = inequalities_size(inequalities);
	for (int i = 0; i < size; ++i)
	{
		out_float[i] = inequality_get_d(inequalities_get(inequalities, i));
	}
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			out_float[j*N + i] = rays[j].p[i];
		}
	}

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

#endif
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


struct Vec vec_zero()
{
	struct Vec x;
	for (int i = 0; i < M; ++i) x.v[i] = 0;
	return x;
}


void calc_ray(__global struct Ray * ray, __global struct KernelHeader * header, unsigned int i, unsigned int j)
{
	float fov = 4.f / 6.f * M_PI;

	float offsetz = 4.0;

	struct Vec eye = vec_zero();
	ray->p = vec_zero();

	float hf = (float)header->h;
	float wf = (float)header->w;

	eye.v[2] = 1.0f * wf / hf / tan(fov / 2.0f);
	eye.v[2] += offsetz;

	// debug
	//eye.v[2] = 0.5 + offsetz;


	float i0 = (wf - 1.0f) / 2.0f;
	float j0 = (hf - 1.0f) / 2.0f;
	float dy = 2.0f / hf;

	ray->p.v[0] = ((float)i - i0) * dy;
	ray->p.v[1] = ((float)j - j0) * dy;
	ray->p.v[2] = offsetz;

	ray->v = vec_sub(ray->p, eye);

	vec_normalize(&ray->v);

	ray->color.c[0] = 0;
	ray->color.c[1] = 0;
	ray->color.c[2] = 0;
}



struct Colorf color_add(struct Colorf a, struct Colorf b)
{
	struct Colorf ret;
	for (int i = 0; i < 3; ++i) ret.c[i] = a.c[i] + b.c[i];
	return ret;
}
struct Colorf color_mul(struct Colorf a, struct Colorf b)
{
	struct Colorf ret;
	for (int i = 0; i < 3; ++i) ret.c[i] = a.c[i] * b.c[i];
	return ret;
}
struct Colorf color_mul_f(struct Colorf a, float b)
{
	struct Colorf ret;
	for (int i = 0; i < 3; ++i) ret.c[i] = a.c[i] * b;
	return ret;
}

struct Colorf color_ctor(float r, float g, float b)
{
	struct Colorf ret;
	ret.c[0] = r;
	ret.c[1] = g;
	ret.c[2] = b;
	return ret;
}

void strcpy(__private char * dst, constant char * src)
{
	while (*src != 0)
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = *src;
}

struct RayCastResult cast_sub(
	__global char * polytope,
	__global char * face,
	__global struct Ray * ray)
{
	struct RayCastResult ret;

	__global char * subspace = face_get_subspace(face);

	__global char * plane = face_get_plane(face);

	struct Vec n = plane_get_n(plane);

	float d = *plane_get_d(plane);

	// calc

	ret.hit = false;

	float nv = vec_dot(n, ray->v);

	if (nv > 0)
	{
		return ret;
	}

	float k = (d - vec_dot(n, ray->p)) / nv;

	if (isnan(k))
	{
		constant char * msg = "isnan(k)";
		strcpy(ret.message, msg);
		//ret.message = 
		return ret;
	}

	if (k < 0)
	{
		return ret;
	}

	struct Vec x;
	float s[M - 1];

	x = ray_x_g(ray, k);

	// debugging
	//vec_cpy_gp(task->x, x, M);

	//nmath::linalg::Vec<M - 1> s = f.s(x);
	face_s(face, s, x);

	// debugging
	//vec_cpy_gp(task->s, s, M - 1);

	ret.k = k;

	if (!face_eval(face, s))
	{
		//task->fail_code = 3;
		return ret;
	}

	ret.hit = true;

	// debug
	ret.mat.emittance = color_ctor(0, 1, 1);
	ret.mat.reflectance = color_ctor(1, 1, 1);
	ret.x = x;
	ret.n = n;

	return ret;
}

struct RayCastResult cast(
	__global char * polytopes,
	__global struct Ray * ray,
	struct RayCastResult * prev_result)
{
	struct RayCastResult ret;
	ret.hit = false;
	ret.k = FLT_MAX;

	unsigned int polytopes_size = 1;
	for (int i = 0; i < polytopes_size; ++i)
	{
		__global char * polytope = buffer_seek(polytopes, i) + sizeof(unsigned int);

		unsigned int faces_size = 8;
		for (int j = 0; j < faces_size; ++j)
		{
			if (prev_result != 0){
				if ((i == prev_result->polytope_i)&&(j == prev_result->face_i)) continue;
			}

			__global char * face = polytope_get_face(polytope, j);

			struct RayCastResult res = cast_sub(polytope, face, ray);

			if (res.hit == false) continue;
			if (res.k > ret.k) continue;
			
			res.polytope_i = i;
			res.face_i = j;

			ret = res;
		}
	}

	ray->res = ret;

	return ret;
}


struct Vec RandomUnitVectorInHemisphereOf(struct Vec n)
{
	return n;
}

struct Colorf path_trace_sub(
	__global char * polytopes,
	__global struct Ray * ray,
	int depth,
	struct RayCastResult * prev_result
	)
{
	struct Colorf color;
	color.c[0] = 0;
	color.c[1] = 0;
	color.c[2] = 0;

	if (depth == 2) return color;

	struct RayCastResult res = cast(polytopes, ray, prev_result);
	if (res.hit == false) return color;


	// debug
	//color.c[0] = 1.0;
	//color.c[1] = 1.0;
	//color.c[2] = 1.0;
	//return color;


	struct Colorf emittance = res.mat.emittance;

	return emittance;

	// redefine ray to be recast
	ray->p = res.x;
	ray->v = RandomUnitVectorInHemisphereOf(res.n);

	// Compute the BRDF for this ray (assuming Lambertian reflection)
	float cos_theta = vec_dot(ray->v, res.n);
	struct Colorf BRDF = color_mul_f(res.mat.reflectance, 2.0 * cos_theta);
	struct Colorf reflected = path_trace_sub(polytopes, ray, depth + 1, &res);

	// Apply the Rendering Equation here.
	return color_add(emittance, color_mul(BRDF, reflected));
}


__kernel void path_trace1(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct Color_1_1_1 * pixels,
	__global struct KernelHeader * header,
	volatile __global unsigned int * counter
	)
{
	unsigned int h = header->h;
	unsigned int w = header->w;
	unsigned int s = header->s;

	unsigned int len;

	len = w * h;

	// pixel index = j * w + i;
	// sample index = j * w * s + i * s + k;

	while (true)
	{
		unsigned int ind = atomic_inc(counter);
		if (ind > (len - 1)) break;

		unsigned int i = ind % w;
		unsigned int j = (ind - i) / w;

		unsigned int ray_i = j * w * s + i * s + 0;

		calc_ray(rays + ray_i, header, i, j);

		// copy
		for (unsigned int k = 1; k < s; ++k)
		{
			unsigned int ray_i2 = j * w * s + i * s + k;

			rays[ray_i2] = rays[ray_i];
		}
	}
}
__kernel void path_trace2(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct Color_1_1_1 * pixels,
	__global struct KernelHeader * header,
	volatile __global unsigned int * counter
	)
{
	unsigned int h = header->h;
	unsigned int w = header->w;
	unsigned int s = header->s;

	int len;

	len = w * h * s;

	while (true)
	{
		int ray_i = atomic_inc(counter);
		if (ray_i > (len - 1)) break;

		// j * w + i;
		// j * w * s + i * s + k;

		int k = ray_i % s;
		int i = ((ray_i - k) / s) % w;
		int j = (((ray_i - k) / s) - i) / h;

		__global struct Ray * ray = rays + ray_i;

		ray->color = path_trace_sub(polytopes, ray, 0, 0);
	}
}
__kernel void path_trace3(
	__global char * polytopes,
	__global struct Ray * rays,
	__global struct Color_1_1_1 * pixels,
	__global struct KernelHeader * header,
	volatile __global unsigned int * counter
	)
{
	unsigned int h = header->h;
	unsigned int w = header->w;
	unsigned int s = header->s;

	int len;

	len = w * h;

	while (true)
	{
		int pixel_i = atomic_inc(counter);
		if (pixel_i > (len - 1)) break;

		int i = pixel_i % w;
		int j = (pixel_i - i) / w;

		struct Colorf color;
		color.c[0] = 0;
		color.c[1] = 0;
		color.c[2] = 0;

		for (int k = 0; k < s; ++k)
		{
			int ray_i = j * w * s + i * s + k;

			color = color_add(color, rays[ray_i].color);
		}
		for (int k = 0; k < 3; ++k) color.c[k] /= (float)s;

		int ray_i = j * w * s + i * s + 0;

		//debug
		//color = rays[ray_i].color;
		//color.c[0] = fabs(rays[ray_i].v.v[0])*10.0;
		//color.c[1] = fabs(rays[ray_i].v.v[1])*10.0;


		pixels[pixel_i] = color_convert(color);

		//debug
		//pixels[pixel_i].c[0] = i;
		//pixels[pixel_i].c[1] = j;
	}
}
