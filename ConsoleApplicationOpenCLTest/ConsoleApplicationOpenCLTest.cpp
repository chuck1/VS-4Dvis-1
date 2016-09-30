// ConsoleApplicationOpenCLTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <cstdio>
#include <stdlib.h>

#include <CL/cl.h>

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

class OCL
{
public:
	void init()
	{
		cl_int ret;
		cl_uint ret_num_devices;
		cl_uint ret_num_platforms;

		/* Get Platform and Device Info */
		ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
		ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

		/* Create OpenCL context */
		context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

		/* Create Command Queue */
		command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	}
	cl_program createProgram(cl_context context, char * fileName)
	{
		FILE *fp;
		char *source_str;
		size_t source_size;

		/* Load the source code containing the kernel*/

		fopen_s(&fp, fileName, "r");
		if (!fp) {
			printf("Failed to load kernel.\n");
			exit(1);
		}
		source_str = (char*)malloc(MAX_SOURCE_SIZE);
		source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
		fclose(fp);

		cl_int ret;

		cl_program program;

		program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
			(const size_t *)&source_size, &ret);

		free(source_str);

		/* Build Kernel Program */
		ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

		return program;
	}
	void flush()
	{
		cl_int ret;
		ret = clFlush(command_queue);
		ret = clFinish(command_queue);
	}
	void shutdown()
	{
		cl_int ret;
		ret = clReleaseCommandQueue(command_queue);
		ret = clReleaseContext(context);
	}

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
};

void OCLtest()
{
	OCL ocl;

	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;


	cl_int ret;

	char string[MEM_SIZE];

	ocl.init();

	/* Create Memory Buffer */
	memobj = clCreateBuffer(ocl.context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);

	/* Create Kernel Program from the source */
	program = ocl.createProgram(ocl.context, "hello.cl");



	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "hello", &ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

	/* Execute OpenCL Kernel */
	ret = clEnqueueTask(ocl.command_queue, kernel, 0, NULL, NULL);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(ocl.command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

	/* Display Result */
	puts(string);

	ocl.flush();

	/* Finalization */

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);


	ocl.shutdown();

	//printf("");
	getchar();
}


int _tmain(int argc, _TCHAR* argv[])
{
	OCLtest();

	return 0;
}