#ifndef __OBJMODEL_H__
#define __OBJMODEL_H__

#include <Model.h>

/** @ingroup editor
 * @{
 */

/// A model loaded from an OBJ file.
class OBJModel : public Model {
	public:
		/// Create new model from OBJ file.
		/**
		* @param filename Filename (relative or absolute) to the OBJ model file.
		*/
		OBJModel(const char* filename);

	private:
		struct Face {
			struct Vertex {
				unsigned int positionIndex;
				unsigned int normalIndex;
				unsigned int textureIndex;
			};

			Vertex vertices[3];
		};

		static glm::vec3 readVec3(std::ifstream& modelFile);
		static glm::vec2 readVec2(std::ifstream& modelFile);
		static Face readFace(std::ifstream& modelFile);
		static Face::Vertex readVertex(std::ifstream& modelFile);
		static void calculateTangents(std::vector<Face>& faces, std::vector<glm::vec3>& positions, std::vector<glm::vec2>& textureCoordinates, std::vector<glm::vec3>& tangents);
};

/** @} */

#endif