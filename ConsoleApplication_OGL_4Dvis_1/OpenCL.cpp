#include "stdafx.h"

#include <cstdio>
#include <stdlib.h>
#include <iostream>

#include"OCL.h"

void OCL::OCLtest(OCL::Manager& ocl)
{
	std::cout << "OCLtest" << std::endl;

	

	cl_int ret;

	char string[MEM_SIZE];

	
	// initialize memobj2
	unsigned int i = 0;
	//clEnqueueWriteBuffer(ocl.command_queue, ocl.memobj2, CL_FALSE, 0, sizeof(unsigned int), &i, 0, 0, 0);

	ocl._M_memobj[1]->EnqueueWrite(&i, sizeof(unsigned int));

	unsigned int global_size = 5;
	unsigned int local_size = 5;

	/* Execute OpenCL Kernel */
	//ret = clEnqueueTask(ocl.command_queue, ocl.kernel, 0, NULL, NULL);

	ret = clEnqueueNDRangeKernel(ocl.command_queue, ocl.kernel, 1, 0, &global_size, &local_size, 0, 0, 0);
	ocl.errorcheck("clEnqueueNDRangeKernel", ret);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(ocl.command_queue, ocl._M_memobj[0]->id, CL_TRUE, 0, MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

	/* Display Result */
	puts(string);

	

	//printf("");
	getchar();
}



OCL::MemObj::~MemObj()
{
	int ret;
	ret = clReleaseMemObject(id);
}
void OCL::MemObj::EnqueueWrite(void * src, unsigned int size)
{
	auto mgr = _M_mgr.lock();
	int ret = clEnqueueWriteBuffer(mgr->command_queue, id, CL_FALSE, 0, size, src, 0, 0, 0);
	mgr->errorcheck("clEnqueueWriteBuffer", ret);
}

