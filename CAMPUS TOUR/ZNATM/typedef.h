#pragma once

#include <string>


/**
*	\brief this typedef is for storing object data in an easy formate 

*	\bug one thing to note is that the vt3 stores the texture coordinate but textures are 2d so it is not needed, in this case however it stores the 0.0 info
*
*/
typedef struct {
	float x,y,z;

} points;

typedef struct {
	float vn[3];	// store the ve3rtex normals
} normal;						


typedef struct {
	float vt[3];	// store the texture coordinates
} coordinate;


typedef struct {
	int shaders;
	std::string name;
	points p[3];
	normal norm[3];
	coordinate coord[3];
} face;

