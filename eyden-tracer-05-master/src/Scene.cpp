#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		std::shared_ptr<IShader> pShader = std::make_shared<CShaderPhong>(*this, RGB(1, 1, 1), 0.5f, 0.5f, 0, 0);
		std::vector<Vec3f> vVertexes;
		std::vector<Vec3f> vNormals;
		std::vector<Vec2f> vTextures;

		std::string line;

		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertexes.push_back(v);
			}
			else if (line == "vt") {
				Vec2f vt;
				for (int i = 0; i < 2; i++) ss >> vt.val[i];
				vTextures.push_back(vt);
			}
			else if (line == "vn") {
				Vec3f vn;
				for (int i = 0; i < 3; i++) ss >> vn.val[i];
				vNormals.push_back(vn);
			}
			else if (line == "f") {
				int v, n, t;
				Vec3i V, N, T;
				for (int i = 0; i < 3; i++) {
					getline(ss, line, ' ');
					sscanf(line.c_str(), "%d/%d/%d", &v, &t, &n);
					V.val[i] = v - 1;
					T.val[i] = t - 1;
					N.val[i] = n - 1;
				}
				// std::cout << "Face: " << V << std::endl;
				// std::cout << "Normal: " << N << std::endl;
				//Add(std::make_shared<CPrimTriangle>(vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]], pShader));
				//Add(std::make_shared<CPrimTriangleSmooth>(vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
				//										  vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]], pShader));
				Add(std::make_shared<CPrimTriangleSmoothTextured>(vVertexes[V.val[0]], vVertexes[V.val[1]], vVertexes[V.val[2]],
					vNormals[N.val[0]], vNormals[N.val[1]], vNormals[N.val[2]],
					vTextures[T.val[0]], vTextures[T.val[1]], vTextures[T.val[2]], pShader));
			}
			else if (line == "#") {}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	}
	else
		std::cout << "ERROR: Can't open OBJFile " << fileName << std::endl;
}
