#include "wavefrontLoader.h"

WFObject::WFObject()
{
	materialIndex = -1;		// Material index starts from zero
}

WFObject::~WFObject()
{

}

int WFObject::load(char *filename)
{
	fstream objFile;
	objFile.open(filename);

	if(objFile.is_open())
	{
		char line[255];

		// Parse object file line by line
		while(objFile.good())
		{
			objFile.getline(line, 255);
			parseLine(line);
		}

		objFile.close();
	}
	else
	{
		cout << "Could not open WFObject file '" << filename << "'\n";
		return false;
	}

	return true;
}

void WFObject::parseLine(char *line)
{
	//char *lineType;

	// Copy type string to type char[] for strtok()

	//lineType = strtok(lineStr, " ");
	if(!strlen(line))
	{
		return;
	}

	char *lineType;
	lineType = strtok(strdup(line), " ");

	// Decide what to do
	if(!strcmp(lineType, "v"))		// Vertex
	{
		parseVertex(line);
	}
	else if(!strcmp(lineType, "vn"))	// Normal
	{
		parseNormal(line);
	}
	else if(!strcmp(lineType, "f"))	// Face
	{
		parseFace(line);
	}
	else if(!strcmp(lineType, "mtllib"))		// Material library (file)
	{
		char fileName[255];

		sscanf(line, "mtllib %s", &fileName);

		if(strlen(fileName))
		{
			loadMaterials(fileName);
		}
		else
		{
			cout << "Parse error" << endl;
		}
	}
	else if(!strcmp(lineType, "usemtl"))		// Use a material from the materials library
	{
		string mtlName;

		materialIndex++;

		sscanf(line, "usemtl %s", mtlName.c_str());

		parseMaterial(mtlName.c_str());

		faces.push_back(vector<Face>());
	}

	return;
}

// Draw object
void WFObject::draw()
{
	for(int g = 0; g < faces.size(); g++)
	{
		// Apply material for this material group
		glMaterialfv(GL_FRONT, GL_SPECULAR, materials[g].Ks);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[g].Kd);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materials[g].Ka);
		glMaterialf(GL_FRONT, GL_SHININESS, materials[g].Ns);

		glBegin(GL_TRIANGLES);

		for(int f = 0; f < faces[g].size(); f++)
		{
			glNormal3f(normals[faces[g][f].vn1 - 1].x, normals[faces[g][f].vn1 - 1].y, normals[faces[g][f].vn1 - 1].z);
			glVertex3f(vertices[faces[g][f].v1 - 1].x, vertices[faces[g][f].v1 - 1].y, vertices[faces[g][f].v1 - 1].z);

			glNormal3f(normals[faces[g][f].vn2 - 1].x, normals[faces[g][f].vn2 - 1].y, normals[faces[g][f].vn2 - 1].z);
			glVertex3f(vertices[faces[g][f].v2 - 1].x, vertices[faces[g][f].v2 - 1].y, vertices[faces[g][f].v2 - 1].z);

			glNormal3f(normals[faces[g][f].vn3 - 1].x, normals[faces[g][f].vn3 - 1].y, normals[faces[g][f].vn3 - 1].z);
			glVertex3f(vertices[faces[g][f].v3 - 1].x, vertices[faces[g][f].v3 - 1].y, vertices[faces[g][f].v3 - 1].z);
		}

		glEnd();
	}
}

void WFObject::parseVertex(char *line)
{
	vertices.push_back(Vector());		// Add a new element to the vertices array

	sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);

	return;
}

// Parse a "vn" normal line of the file into the normals array
void WFObject::parseNormal(char *line)
{
	normals.push_back(Vector());

	sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);

	return;
}


// Parse a "f" face line into the faces array. This gets complex due to there being different line formats.
void WFObject::parseFace(char *line)
{
	//Face tmp;	// Temporary storage for our face
	faces[materialIndex].push_back(Face());

	// Read face line. If texture indicies aren't present, don't read them.
	if(sscanf(line, "f %d//%d %d//%d %d//%d", &faces[materialIndex].back().v1,
											  &faces[materialIndex].back().vn1,
											  &faces[materialIndex].back().v2,
											  &faces[materialIndex].back().vn2,
											  &faces[materialIndex].back().v3,
											  &faces[materialIndex].back().vn3) <= 1)
	{
		sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces[materialIndex].back().v1,
													 &faces[materialIndex].back().vt1,
													 &faces[materialIndex].back().vn1,
													 &faces[materialIndex].back().v2,
													 &faces[materialIndex].back().vt2,
													 &faces[materialIndex].back().vn2,
													 &faces[materialIndex].back().v3,
													 &faces[materialIndex].back().vt3,
													 &faces[materialIndex].back().vn3);
	}

	return;
}

// Open .mtl file and save into memory
int WFObject::loadMaterials(char *filename)
{
	char filePath[255];
	fstream file;

	file.open(filename);

	if(file.is_open())
	{
		char line[255];

		// Parse material file
		while(file.good())
		{
			file.getline(line, 255);

			mtlFile.push_back(line);
		}
	}
	else
	{
		cout << "Could not open mtl file '" << filename << "'\n";
		return false;
	}

	file.close();

	return true;
}

// Search .mtl file in memory for the material we want. Load that materials properties into the materials
// array.
void WFObject::parseMaterial(string mtlName)
{
	string materialName;
	char *line = new char[255];
	bool mtlFound = false;

	for(int i = 0; i < mtlFile.size(); i++)
	{
		strncpy(line, mtlFile[i].c_str(), 255);

		if(strlen(line))
		{
			if(sscanf(line, "newmtl %s", materialName.c_str()))
			{
				if(mtlFound)
				{
					return;
				}

				if(!strcmp(mtlName.c_str(), materialName.c_str()))
				{
					mtlFound = true;	// Set the "found material" flag to true
					materials.push_back(Material());
				}
			}

			if(mtlFound)
			{
				// Parse this line into a material
				if(line[0] == 'N' && line[1] == 's')
				{
					sscanf(line, "Ns %f", &materials.back().Ns);
				}
				else if(line[0] == 'K' && line[1] == 'a')
				{
					sscanf(line, "Ka %f %f %f", &materials.back().Ka[0], &materials.back().Ka[1], &materials.back().Ka[2]);
				}
				else if(line[0] == 'K' && line[1] == 'd')
				{
					sscanf(line, "Kd %f %f %f", &materials.back().Kd[0], &materials.back().Kd[1], &materials.back().Kd[2]);
				}
				else if(line[0] == 'K' && line[1] == 's')
				{
					sscanf(line, "Ks %f %f %f", &materials.back().Ks[0], &materials.back().Ks[1], &materials.back().Ks[2]);
				}
			}
		}
		else
		{
			return;
		}
	}

	return;
}
