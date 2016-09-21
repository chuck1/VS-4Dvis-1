// ConsoleApplication_OGL_4Dvis_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

int		cubeVertexIndex(int i, int j, int k, int l)
{
	return i * 8 + j * 4 + k * 2 + l;
}
void	construct2Plane4(int d, int dims, int d0, int v0, int d1, int v1, GLint* indexArray, int& indexArrayIndex, int* I)
{
	if (d < dims)
	{
		if (d == d0)
		{
			I[d] = v0;
			construct2Plane4(d + 1, dims, d0, v0, d1, v1, indexArray, indexArrayIndex, I);
		}
		else if (d == d1)
		{
			I[d] = v1;
			construct2Plane4(d + 1, dims, d0, v0, d1, v1, indexArray, indexArrayIndex, I);
		}
		else
		{
			for (int i = 0; i < 2; ++i)
			{
				I[d] = i;
				construct3Cube4(d + 1, dims, d0, v0, indexArray, indexArrayIndex, I);
			}
		}
	}
	else
	{
		indexArray[indexArrayIndex] = cubeVertexIndex(I[0], I[1], I[2], I[3]);
		++indexArrayIndex;
	}
}
void	construct3Cube4(int d, int dims, int d0, int v0, GLint* indexArray, int& indexArrayIndex, int* I)
{
	if (d < dims)
	{
		if (d == d0)
		{
			I[d] = v0;
			construct3Cube4(d + 1, dims, d0, v0, indexArray, indexArrayIndex, I);
		}
		else
		{
			for (int i = 0; i < 2; ++i)
			{
				I[d] = i;
				construct3Cube4(d + 1, dims, d0, v0, indexArray, indexArrayIndex, I);
			}
		}
	}
	else
	{
		indexArray[indexArrayIndex] = cubeVertexIndex(I[0], I[1], I[2], I[3]);
		++indexArrayIndex;
	}
}
void	construct2Plane4(int d0, int v0, int d1, int v1, GLint* indexArray, int& indexArrayIndex)
{

}
void	construct3Cube4(int dim, int val, GLint* indexArray, int& indexArrayIndex)
{
	int I[4];
	int D[3];

	D[0] = 0;
	D[1] = 1;
	D[2] = 2;

	for (int i = dim; i < 3; ++i)
	{
		++D[i];
	}
	
	construct3Cube4(0, 4, dim, val, indexArray, indexArrayIndex, I);




	for (int d = 0; d < 4; ++d)
	{
		if (d == dim) continue;

		for (int v = 0; v < 2; ++v)
		{
			construct2Plane4(dim, val, d, v, indexArray, indexArrayIndex);
		}
	}








	// or

	/*for (int i = 0; i < 2; ++i)
	{
		I[D[0]] = i;

		for (int j = 0; j < 2; ++j)
		{
			I[D[1]] = j;

			for (int k = 0; k < 2; ++k)
			{
				I[D[2]] = k;

				indexArray[indexArrayIndex] = cubeVertexIndex(I[0], I[1], I[2], I[3]);
				++indexArrayIndex;
			}
		}
	}*/
}
void	construct4Cube4()
{
	GLfloat* p = new GLfloat[16];

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				for (int l = 0; l < 2; ++l)
				{
					int m = cubeVertexIndex(i, j, k, l);
				}
			}
		}
	}

	GLint* indexArray = new GLint[8*8];
	int indexArrayIndex = 0;
	
	for (int dim = 0; dim < 4; ++dim)
	{
		for (int v = 0; v < 2; ++v)
		{
			construct3Cube4(dim, v, indexArray, indexArrayIndex);
		}
	}

	for (int i = 0; i < (8 * 8); ++i)
	{
		printf("%i\n", indexArray[i]);
	}
}




//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int _tmain(int argc, _TCHAR* argv[])
{
	construct4Cube4();


	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Declare a window object
	GLFWwindow* window;

	//Create a window and create its OpenGL context
	window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);

	//If the window couldn't be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(window);

	//Sets the key callback
	glfwSetKeyCallback(window, key_callback);

	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}

	//Set a background color
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	//Main Loop
	do
	{
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//Swap buffers
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();

	} //Check if the ESC key had been pressed or if the window had been closed
	while (!glfwWindowShouldClose(window));

	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}



