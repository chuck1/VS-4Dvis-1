#include "stdafx.h"

#include <cstdio>
#include <stdlib.h>

#include"OCL.h"

void OCLtest(OCL& ocl)
{
	

	

	cl_int ret;

	char string[MEM_SIZE];

	
	

	/* Execute OpenCL Kernel */
	ret = clEnqueueTask(ocl.command_queue, ocl.kernel, 0, NULL, NULL);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(ocl.command_queue, ocl.memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

	/* Display Result */
	puts(string);

	

	//printf("");
	getchar();
}