#ifndef __OBJMODEL_H__
#define __OBJMODEL_H__

#include <Model.h>

/// A model loaded from an OBJ file.
class OBJModel : public Model {
	public:
		/// Create new model from OBJ file.
		/**
		* @param filename Filename (relative or absolute) to the OBJ model file.
		*/
		OBJModel(const char* filename);

	private:
		static glm::vec3 readVec3(std::ifstream &modelFile);
		static glm::vec2 readVec2(std::ifstream &modelFile);
		static Vertex readVertex(std::ifstream &modelFile, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textureCoordinates);
};

#endif