// ConsoleApplication_OGL_4Dvis_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cmath>

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include <nmath/linalg/NMath.h>

#include <nmath/test.h>
#include <nmath/linalg/Mat.h>

#include <nspace\actor\RigidBody.h>
#include <nspace/app/AppTemplate.h>
#include <nspace/tests.h>



//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <nspace/graphics/ocl.h>


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
				pTemp[d] = (float)(i * 2 - 1);
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


class Rectangle : public Geometry
{
public:
	void construct()
	{
		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 0.0f,
		};

		p = new GLfloat[16];

		memcpy(p, g_vertex_buffer_data, 16 * sizeof(GLfloat));

		pArrayIndex = 16;

		indexArray = new GLuint[6];
		indexArray[0] = 0;
		indexArray[1] = 1;
		indexArray[2] = 3;
		indexArray[3] = 1;
		indexArray[4] = 2;
		indexArray[5] = 3;
		indexArrayIndex = 6;
	}
};

template<unsigned int M>
nmath::SMat<M> simple_rotation_matrix(unsigned int i, unsigned int j, float angle)
{
	nmath::SMat<M> ret = nmath::SMat<M>::Identity();

	float c = cos(angle);
	float s = sin(angle);

	ret(i, i) = c;
	ret(j, j) = c;
	ret(i, j) = s;
	ret(j, i) = -s;

	return ret;
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



Cube4 cube;
Triangle tri;
Rectangle rect;

//std::shared_ptr<OCL::Manager> ocl;

#define M (4)

void construct_cube(std::shared_ptr<nmath::geometry::Polytope<M>> p, nmath::SMat<M> const & rot)
{
	// an n-cube centered at the origin

	for (int j = 0; j < M; ++j)
	{
		{
			nmath::geometry::Face<M> f;
			f._M_plane.n = nmath::linalg::Vec<M>::baseVec(j);
			f._M_plane.d = 1;
			p->_M_faces.push_back(f);
		}

		{
			nmath::geometry::Face<M> f;
			f._M_plane.n = -nmath::linalg::Vec<M>::baseVec(j);
			f._M_plane.d = 1;
			p->_M_faces.push_back(f);
		}
	}

	for (int i = 0; i < p->_M_faces.size(); ++i)
	{
		nmath::geometry::Face<M> & f = p->_M_faces[i];

		f._M_plane.n = rot * f._M_plane.n;

		f.calc_basis();
		f._M_p = f._M_plane.n;
	}

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (i == j) continue;

			p->_M_faces[2 * i + 0].AddHyperplaneIntersection(p->_M_faces[2 * j + 0]._M_plane);
			p->_M_faces[2 * i + 0].AddHyperplaneIntersection(p->_M_faces[2 * j + 1]._M_plane);

			p->_M_faces[2 * i + 1].AddHyperplaneIntersection(p->_M_faces[2 * j + 0]._M_plane);
			p->_M_faces[2 * i + 1].AddHyperplaneIntersection(p->_M_faces[2 * j + 1]._M_plane);
		}
	}

	NMATH_DEBUG(10){
		for (int i = 0; i < p->_M_faces.size(); ++i)
		{
			nmath::geometry::Face<M> & f = p->_M_faces[i];

			std::cout << "face " << i << std::endl;
			std::cout << "A" << std::endl;
			std::cout << f._M_A << std::endl;
			std::cout << "n " << f._M_plane.n.length() << std::endl;
			std::cout << f._M_plane.n << std::endl;

			for (unsigned int j = 0; j < f._M_inequalities.size(); ++j)
			{
				nmath::geometry::Inequality<M - 1> & ineq = f._M_inequalities[j];

				printf("  ineq %i\n", j);
				std::cout << "    a " << ineq._M_a << std::endl;
				std::cout << "    d " << ineq._M_d << std::endl;
			}
		}
	}

	//getchar();exit(0);
}

void contruct_app(std::shared_ptr<nspace::app::App<M>> app)
{
	//auto rot = simple_rotation_matrix<M>(0, 2, CL_M_PI/8.f);
	
	app->_M_polytopes = std::make_shared<nspace::app::App<M>::ARRAY_POLYTOPE>();
	app->_M_lights = std::make_shared<nspace::app::App<M>::ARRAY_LIGHT>();

	//auto p0 = std::make_shared<nmath::geometry::Polytope<M>>();
	//construct_cube(p0, rot);
	
	//app->_M_polytopes->push_back(p0);

	auto l0 = std::make_shared<nspace::light::Point<M>>();
	l0->_M_color(0) = 1;
	l0->_M_color(1) = 1;
	l0->_M_color(2) = 1;
	l0->_M_atten[0] = 1;
	l0->_M_atten[1] = 1;
	l0->_M_atten[2] = 0;
	l0->_M_p(0) = 0.f;
	l0->_M_p(2) = 5.f;
	//l0->_M_p(3) = -5.f;

	app->_M_lights->push_back(l0);
}

void remake_cube(std::shared_ptr<nspace::app::App<M>> app, float angle, float angle2)
{
	auto rot1 = simple_rotation_matrix<M>(0, 3, angle);
	auto rot2 = simple_rotation_matrix<M>(0, 2, angle2); //CL_M_PI / 4.f);
	auto rot = rot2*rot1;
	//auto rot = rot1;

	app->_M_polytopes->clear();
	
	auto p0 = std::make_shared<nmath::geometry::Polytope<M>>();
	construct_cube(p0, rot);

	app->_M_polytopes->push_back(p0);
}

void OCLtest2(std::shared_ptr<OCL::Manager> ocl)
{
	try{
		OCLtest(*ocl);
	}
	catch (std::exception & e)
	{
		printf(e.what());
		getchar();
		return;
	}
}

float rotAngle = 2.42;// CL_M_PI / 4.f;

int _tmain(int argc, _TCHAR* argv[])
{
	int w = 4;
	int h = 3;

	int textureScale = 4;
	
	//int w = 160;//  640;
	//int h = 120;// 480;
	//int w = 320;//  640;
	//int h = 240;// 480;

	//nmath::test();
	//nspace::tests::test_array();

	//if (false)
	//{
	//	ocl = std::make_shared<OCL::Manager>();
	//	ocl->init();


	//	/* Create Kernel Program from the source */
	//	auto program = ocl->create_program("kernel/hello.cl");

	//	/* Create OpenCL Kernel */
	//	auto kernel = program->create_kernel("hello");
	//	//auto kernel = clCreateKernel(program, "hello", &ret);

	//	cl_int ret;

	//	auto memobj1 = ocl->create_buffer(CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char));
	//	auto memobj2 = ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(unsigned int));

	//	/* Set OpenCL Kernel Parameters */
	//	ret = clSetKernelArg(kernel->id, 0, sizeof(cl_mem), (void *)&(memobj1->id));
	//	OCL::errorcheck("clSetKernelArg 0", ret);
	//	ret = clSetKernelArg(kernel->id, 1, sizeof(cl_mem), (void *)&(memobj2->id));
	//	OCL::errorcheck("clSetKernelArg 1", ret);


	//	OCLtest2();
	//	getchar(); exit(0);
	//}

	unsigned int windowScale = 160;

	auto app = std::make_shared<nspace::app::App<M>>();
	app->_M_viewport = std::make_shared<nspace::graphics::raycast::Viewport<M>>();
	app->_M_viewport->_M_w = w*textureScale;
	app->_M_viewport->_M_h = h*textureScale;
	contruct_app(app);
	//app->render();

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
	window = glfwCreateWindow(w*windowScale, h*windowScale, "Test Window", NULL, NULL);

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

	rect.construct();
	rect.setup();

	remake_cube(app, 0, 0);
	//remake_cube(app, CL_M_PI / 4.f, 0);
	app->render_init();

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("kernel/SimpleVertexShader.vertexshader", "kernel/SimpleFragmentShader.fragmentshader");
	
	double t = glfwGetTime();
	double dt = 0;
	//Main Loop
	do
	{
		

		double ttemp = glfwGetTime();
		dt = ttemp - t;
		t = ttemp;

		printf("dt=%f\n", dt);

		//OCLtest2();
		
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		remake_cube(app, rotAngle, CL_M_PI / 4.f);
		rotAngle += dt * CL_M_PI / 32.f;
		
		app->reload_buffer();

		app->render();
		//getchar();

		rect.drawTriangles();

		//cube.drawTriangles();
		//cube.drawLines();
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
	app->_M_ocl->flush();
	app->_M_ocl->shutdown();

	exit(EXIT_SUCCESS);
}



