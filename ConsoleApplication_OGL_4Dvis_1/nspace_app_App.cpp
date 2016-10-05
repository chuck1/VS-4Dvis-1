#include "stdafx.h"

#include <nspace/actor/RigidBody.h>
#include <nspace/app/App.h>

void nspace::app::App::render()
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


