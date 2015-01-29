#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "CubeMapTexture.h"
#include "Camera.h"

class Skybox {
	public:
		// Constructor
		Skybox(const CubeMapTexture* texture);

		// Render skybox.
		void render(const Camera* camera);

	private:
		const CubeMapTexture* texture;
};

#endif