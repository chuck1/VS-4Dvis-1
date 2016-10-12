#include "stdafx.h"

#include <nmath/geometry/Polytope.h>

#include <nspace/actor/RigidBody.h>
#include <nspace/app/App.h>
#include <nspace/util/Task.h>

void nspace::app::AppBase::render_init()
{
	unsigned int pixels_size = _M_viewport->_M_w * _M_viewport->_M_h;
	unsigned int lights_size = _M_lights->size();

	unsigned int rays_size = pixels_size + pixels_size * lights_size;

	/*unsigned int faces_size = 0;
	for (int k = 0; k < _M_polytopes->size(); ++k)
	{
		std::shared_ptr<nmath::geometry::PolytopeBase> p = _M_polytopes->operator[](k);
		faces_size += p->faces_len();
	}*/

	_M_rays = std::make_shared<ARRAY_RAY>();
	for (unsigned int i = 0; i < rays_size; ++i) _M_rays->push_back(make_ray());

	std::vector<nspace::util::task::RayFaceIntersect> _M_tasks;

	unsigned int h = _M_viewport->_M_h;
	unsigned int w = _M_viewport->_M_w;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			unsigned int r = i * h + j;

			for (int k = 0; k < _M_polytopes->size(); ++k)
			{
				std::shared_ptr<nmath::geometry::PolytopeBase> p = _M_polytopes->operator[](k);

				for (int l = 0; l < p->faces_len(); ++l)
				{
					nspace::util::task::RayFaceIntersect task;
					task.polytope_i = k;
					task.face_i = l;
					task.ray_i = r;
					task.intersect = false;
				}
			}
		}
	}

	// for each pixel
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			// for each light
			for (int k = 0; k < lights_size; ++k)
			{
				unsigned int r = i * h * lights_size + j * lights_size + k;

				// for each polytope
				for (int l = 0; l < _M_polytopes->size(); ++l)
				{
					std::shared_ptr<nmath::geometry::PolytopeBase> p = _M_polytopes->operator[](l);

					// for each face
					for (int m = 0; m < p->faces_len(); ++m)
					{
						nspace::util::task::RayFaceIntersect task;
						task.polytope_i = l;
						task.face_i = m;
						task.ray_i = r;
						task.intersect = false;
					}
				}
			}
		}
	}
}
void nspace::app::AppBase::render()
{
	// cast rays
	
	for (int i = 0; i < _M_viewport->_M_w; ++i)
	{
		for (int j = 0; j < _M_viewport->_M_h; ++j)
		{
			for (std::shared_ptr<nspace::actor::Base> actor : _M_actors)
			{
				auto actorRigidBody = std::dynamic_pointer_cast<nspace::actor::RigidBodyBase>(actor);
				if (actorRigidBody)
				{
					
				}
			}
		}
	}

	// copy color data from rays to GL buffer

	// render the GL buffer
}


