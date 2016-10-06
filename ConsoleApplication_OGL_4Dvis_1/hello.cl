
__kernel void math_dot(__global const float * x, __global const float * y, const uint m, __global float * res)
{
	*res = 0;
	for (int i = 0; i < m; ++i)
	{
		*res += x[i] * y[i];
	}
}

__kernel void hello(__global char* string)
{
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
}





