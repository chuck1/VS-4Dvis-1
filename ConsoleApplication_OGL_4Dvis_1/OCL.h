

#include <exception>

#include <CL/cl.h>

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x10000)

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

		/* Create Memory Buffer */
		memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);

		/* Create Kernel Program from the source */
		program = createProgram(context, "kernel/hello.cl");

		/* Create OpenCL Kernel */
		kernel = clCreateKernel(program, "hello", &ret);

		/* Set OpenCL Kernel Parameters */
		ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	}
	cl_program createProgram(cl_context context, char * fileName)
	{
		FILE *fp;
		char *source_str;
		//char source_str[MAX_SOURCE_SIZE];
		size_t source_size;

		/* Load the source code containing the kernel*/

		fopen_s(&fp, fileName, "r");
		if (!fp) {
			throw std::exception("Failed to load kernel");
			abort();
		}
		
		source_str = (char*)malloc(MAX_SOURCE_SIZE);
		source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
		fclose(fp);

		cl_int ret;

		cl_program program;

		program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

		free(source_str);

		/* Build Kernel Program */
		ret = clBuildProgram(program, 1, &device_id, "-D N=(4)", NULL, NULL);

		if (ret != CL_SUCCESS) {
			char* programLog;
			cl_build_status status;
			size_t logSize;

			// check build error and build status first
			clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &status, NULL);

			// check build log
			clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
			programLog = (char*)calloc(logSize + 1, sizeof(char));
			clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, logSize + 1, programLog, NULL);
			printf("Build failed; error=%d, status=%d, programLog:nn%s", ret, status, programLog);
			free(programLog);
		}

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
		ret = clReleaseKernel(kernel);
		ret = clReleaseProgram(program);
		ret = clReleaseMemObject(memobj);
		ret = clReleaseCommandQueue(command_queue);
		ret = clReleaseContext(context);
	}

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;

	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
};

void OCLtest(OCL& ocl);