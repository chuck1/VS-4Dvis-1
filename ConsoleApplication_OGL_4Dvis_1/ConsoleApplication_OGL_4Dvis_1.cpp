// ConsoleApplication_OGL_4Dvis_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include <nmath/linalg/NMath.h>

#include <nspace\actor\RigidBody.h>
#include <nspace/tests.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "OCL.h"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

class Geometry
{
public:
	void drawTriangles()
	{
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			4,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glDrawElements(
			GL_TRIANGLES,      // mode
			indexArrayIndex,    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
			);

		glDisableVertexAttribArray(0);
	}
	void drawLines()
	{
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			4,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glDrawElements(
			GL_LINES,      // mode
			indexArrayIndex,    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
			);

		glDisableVertexAttribArray(0);
	}
	void setup()
	{
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &indexBuffer);

		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, pArrayIndex * sizeof(GLfloat), p, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArrayIndex * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}

	GLuint vertexBuffer;
	GLuint indexBuffer;

	GLuint VertexArrayID;

	GLfloat* p;
	int pArrayIndex;

	GLuint* indexArray;
	int indexArrayIndex;
};
class Cube4: public Geometry
{
public:
	int		cubeVertexIndex(int i, int j, int k, int l)
	{
		return i * 8 + j * 4 + k * 2 + l;
	}
	void	construct2Plane4(int d, int dims, int d0, int v0, int d1, int v1, GLuint* indexArray, int& indexArrayIndex, int* I)
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
					construct2Plane4(d + 1, dims, d0, v0, d1, v1, indexArray, indexArrayIndex, I);
				}
			}
		}
		else
		{
			indexArray[indexArrayIndex] = cubeVertexIndex(I[0], I[1], I[2], I[3]);
			++indexArrayIndex;
		}
	}
	void	construct1Line4(int d, int dims, int d0, int v0, int d1, int v1, int d2, int v2, GLuint* indexArray, int& indexArrayIndex, int* I)
	{
		if (d < dims)
		{
			if (d == d0)
			{
				I[d] = v0;
				construct1Line4(d + 1, dims, d0, v0, d1, v1, d2, v2, indexArray, indexArrayIndex, I);
			}
			else if (d == d1)
			{
				I[d] = v1;
				construct1Line4(d + 1, dims, d0, v0, d1, v1, d2, v2, indexArray, indexArrayIndex, I);
			}
			else if (d == d2)
			{
				I[d] = v2;
				construct1Line4(d + 1, dims, d0, v0, d1, v1, d2, v2, indexArray, indexArrayIndex, I);
			}
			else
			{
				for (int i = 0; i < 2; ++i)
				{
					I[d] = i;
					construct1Line4(d + 1, dims, d0, v0, d1, v1, d2, v2, indexArray, indexArrayIndex, I);
				}
			}
		}
		else
		{
			indexArray[indexArrayIndex] = cubeVertexIndex(I[0], I[1], I[2], I[3]);
			++indexArrayIndex;
		}
	}
	void	construct2Plane4(int d0, int v0, int d1, int v1, GLuint* indexArray, int& indexArrayIndex)
	{
		int I[4];

		//construct2Plane4(0, 4, d0, v0, d1, v1, indexArray, indexArrayIndex, I);




		for (int d = 0; d < 4; ++d)
		{
			if (d == d0) continue;
			if (d == d1) continue;

			for (int v = 0; v < 2; ++v)
			{
				construct1Line4(0, 4, d0, v0, d1, v1, d, v, indexArray, indexArrayIndex, I);
			}
		}

	}
	void	construct3Cube4(int dim, int val, GLuint* indexArray, int& indexArrayIndex)
	{
		for (int d = 0; d < 4; ++d)
		{
			if (d == dim) continue;

			for (int v = 0; v < 2; ++v)
			{
				construct2Plane4(dim, val, d, v, indexArray, indexArrayIndex);
			}
		}
	}
	void	construct4Cube4Pos(int d, int dims, GLfloat* p, int& pArrayIndex, float* pTemp)
	{
		if (d < dims)
		{
			for (int i = 0; i < 2; ++i)
			{
				pTemp[d] = i * 2 - 1;
				construct4Cube4Pos(d + 1, dims, p, pArrayIndex, pTemp);
			}
		}
		else
		{
			memcpy(p + pArrayIndex, pTemp, dims*sizeof(GLfloat));
			pArrayIndex += dims;
		}
	}
	void	construct4Cube4()
	{
		pArrayIndex = 0;
		p = new GLfloat[16 * 4];

		GLfloat pTemp[4];

		construct4Cube4Pos(0, 4, p, pArrayIndex, pTemp);

		// index array

		int N = 2 * (2 * 2) * (3 * 2)*(4 * 2);

		indexArrayIndex = 0;
		indexArray = new GLuint[N];
		



		for (int dim = 0; dim < 4; ++dim)
		{
			for (int v = 0; v < 2; ++v)
			{
				construct3Cube4(dim, v, indexArray, indexArrayIndex);
			}
		}
		


		printf("pArrayIndex = %i\n", pArrayIndex);
		printf("indexArrayIndex = %i\n", indexArrayIndex);
		printf("N = %i\n", N);

		for (int i = 0; i < indexArrayIndex; ++i)
		{
			int j = indexArray[i];
			printf("%3i %4f %4f %4f %4f\n", j, p[4 * j], p[4 * j+1], p[4 * j+2], p[4 * j+3]);
		}
	}
	
	
};
class Triangle: public Geometry
{
public:
	void construct()
	{
		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
		};

		p = new GLfloat[12];

		memcpy(p, g_vertex_buffer_data, 12 * sizeof(GLfloat));

		pArrayIndex = 12;


		indexArray = new GLuint[3];
		indexArray[0] = 0;
		indexArray[1] = 1;
		indexArray[2] = 2;
		indexArrayIndex = 3;
	}
};



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



Cube4 cube;
Triangle tri;

OCL ocl;


void OCLtest2()
{
	try{
		OCLtest(ocl);
	}
	catch (std::exception & e)
	{
		printf(e.what());
		getchar();
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	NMath::test();
	nspace::tests::test_array();
	ocl.init();

	OCLtest2();



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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



	// initialize rendering data
	cube.construct4Cube4();
	cube.setup();

	tri.construct();
	tri.setup();

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	

	//Main Loop
	do
	{
		
		OCLtest2();
		
		
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);



		//cube.drawTriangles();
		cube.drawLines();
		//tri.drawTriangles();
		//tri.drawLines();

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


	// OpenCL cleanup
	ocl.flush();
	ocl.shutdown();

	exit(EXIT_SUCCESS);
}



