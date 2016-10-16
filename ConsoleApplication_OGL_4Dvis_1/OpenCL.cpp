#include "stdafx.h"

#include <cstdio>
#include <stdlib.h>
#include <iostream>

#include <nspace/graphics/ocl.h>

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

	auto kernel = ocl._M_programs[0]->_M_kernels[0];

	ret = clEnqueueNDRangeKernel(ocl._M_command_queue, kernel->id, 1, 0, &global_size, &local_size, 0, 0, 0);
	OCL::errorcheck("clEnqueueNDRangeKernel", ret);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(ocl._M_command_queue, ocl._M_memobj[0]->id, CL_TRUE, 0, MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

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
	printf("EnqueueWrite %16x %8i\n", src, size);

	auto mgr = _M_mgr.lock();
	int ret = clEnqueueWriteBuffer(mgr->_M_command_queue, id, CL_FALSE, 0, size, src, 0, 0, 0);
	OCL::errorcheck("clEnqueueWriteBuffer", ret);
}
void OCL::MemObj::EnqueueRead(void * dst, unsigned int size)
{
	printf("EnqueueRead  %16x %8i\n", dst, size);

	auto mgr = _M_mgr.lock();
	cl_int ret = clEnqueueReadBuffer(mgr->_M_command_queue, id, CL_TRUE, 0, size, dst, 0, NULL, NULL);
	OCL::errorcheck("clEnqueueReadBuffer", ret);
}



OCL::Kernel::~Kernel()
{
	cl_int ret;
	ret = clReleaseKernel(id);
}
void	OCL::Kernel::set_arg(std::shared_ptr<MemObj> memobj, int arg)
{
	cl_int ret;
	ret = clSetKernelArg(id, arg, sizeof(cl_mem), (void *)&(memobj->id));

	errorcheck("clSetKernelArg 0", ret);
}
void	OCL::Kernel::enqueue_ND_range_kernel(unsigned int global_size, unsigned int local_size)
{
	std::shared_ptr<Manager> mgr = _M_mgr.lock();
	cl_command_queue cq = mgr->_M_command_queue;
	cl_int ret = clEnqueueNDRangeKernel(cq, id, 1, 0, &global_size, &local_size, 0, 0, 0);
	OCL::errorcheck("clEnqueueNDRangeKernel", ret);
}
