#ifndef _WAVEFRONT_LOADER_H_
#define _WAVEFRONT_LOADER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#include <GL/gl.h>

typedef struct
{
	float x;
	float y;
	float z;
}
Vector;

typedef struct
{
	float r;
	float g;
	float b;
}
Colour;

typedef struct
{
	int v1, v2, v3;
	int vn1, vn2, vn3;
	int vt1, vt2, vt3;
}
Face;

typedef struct
{
	float u, v;
}
TexCoord;

typedef struct
{
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ns;				// Specular (coeff)
}
Material;

class WFObject
{
	private:
		// Dynamic variables to keep our object data in
		vector<Vector> vertices;
		vector<Vector> normals;
		vector< vector<Face> > faces;		// Vector of vectors because each material has a group of verticies
		vector<TexCoord> texCoords;
		vector<Material> materials;

		vector<string> mtlFile;		// Stores the material file. This is so the file doesn't have to be re-
									// read all the time for each material

		// Index of current material being used for the verticies _et al_ succeeding the `usemtl` line
		int materialIndex;

		void parseLine(char *line);

		void parseVertex(char *line);
		void parseNormal(char *line);
		void parseFace(char *line);

		int loadMaterials(char *filename);
		void parseMaterial(string line);

	public:
		WFObject();
		~WFObject();

		int load(char *filename);
		void draw();
};

#endif
