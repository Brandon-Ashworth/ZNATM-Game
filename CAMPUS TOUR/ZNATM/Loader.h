#pragma once
#include "typedef.h"
#include <string>
#include <vector>
#include <fstream>

#include "MTL.h"
#include "../freeglut.h"

#include <iostream> // this is just for testing, you can remove this with all the cout's



/**
 *  \brief This is a basic 3D Object Loader
 *  
 *  This does basic object loading it requires each face to be a triangle.
 *  It also requires and export of faces (f) vertex normals (vn) texture coordinates (vt), and the vertices themselves (v).
 *  In order for it to unction properly all of these must be included in the obj file. if there are any extra parts that have been exported 
 *  it will be ignored 
 *  
 *  \bug Does not clean up the vectors that used for temporary storage
 *  \bug Does not do Textures (yet)
 *  
 *  
 *  \author Umar Badat
 *  
 *  \example Loader object(path\name.obj)
 *  \example object.draw(); 
 *  
 *  \ possible feature a locking system that stops movement to an object if it has been written to the se position function
 */

class Loader
{
public:
	/**
	 *  \brief this is the default constructor for the loader
	 *  
	 *  The class has been shifted to a form that is easy to create a loader without the need to give it data for the first time
	 *  
	 *  \author Welsley Gai-Yeen Lui 31612382
	 */
	Loader();
	/**
	 *  \brief string location of the obj file
	 *  
	 *  In Order for you to Load the 3D object you need to specify its location 
	 *  in a string. 
	 *  
	 *  \param string fileLocation, vector<string> &ImageLocation, vector<GLuint> &ImageTextureID
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  
	 */
	Loader(std::string input, std::vector<std::string>* imgLoIN, std::vector<GLuint>* imgTexIN);

	~Loader(void);

	/**
	 *  \brief draws the object
	 *  
	 *  This function draws the object that was loaded into it via the constructor.
	 *  \note {\note the draw() disables textures before drawing \note draw() uses a bad rand feature to assign the random colours to the faces \note all faces are triangle }
	 *  \bug at the moment textures don't load
	 *  \bug faces don't all have the triangles
	 *  \param N/A
	 *  \return N/A
	 *  
	 *  \author Umar Badat
	 *  \date 
	 */
	void draw(); // this function takes the obj file and draws it

	/**
	 *  \brief Moves the object slightly
	 *  
	 *  This function moves the object slightly (given by user) and keeps track of how much 
	 *  it has moved. This is so that the user of the objLoader can specify where 
	 *  he wants the object at run time. 
	 *
	 *  \note { \note Keeps track of movement \note used for editing position during run time}
	 *  \param Takes in 3 float numbers (representing how much to move it by)
	 *  \return N/A
	 *  
	 *  \author Umar Badat, some assistance from stack overflow (look for Chaves MainMan, thats me)
	 *  \date 
	 */
	void move(float x, float y, float z);

	/**
	 *  \brief Gets the movement made
	 *  
	 *  This function gets the movement applied to it during run time and returns it.
	 *  This allows us to set it when the map is loaded again immediately set it.
	 *  The movement must have been done through move(float x, float y, float z) in order for it to have been recorded.
	 *  
	 *  \bug doesn't actually return anything 
	 *  \bug doesn't take in the variables needed to reference the results 	
	 *  
	 *  \param takes in 3 reference variables that it can write to.
	 *  \return returns via	 3 variables how much movement has been applied to it.
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void getPos();
	 /**  \brief sets the position of the object
	 *  
	 *  This Function takes in positions then adds it to the object (moving it) this function does not keep track of the movement applied.
	 *  This function does not allow any more movement after this function has been called.
	 *  
	 *  \bug does not actually disable movement after this function is called
	 *  
	 *  \param takes in 3 float numbers (x, y, z) and adds them to the object.
	 *  \return void
	 *  \author Umar Badat
	 *  \date
	 */
	void setPos(float x, float y, float z); // set position
	/**
	 *  \brief finds the min and max the x, y, z axis
	 *  
	 *  This function goes through all verticies and locates the 
	 *  minimum and maximum for all axis (x,y,z)
	 *  
	 *  \bug the order should have been min before max not the other way around
	 *  
	 *  \author Umar Badat - function writer
	 *  \author Welsley Gai-Yeen Lui - function implementer
	 *  
	 *  \param float &maxX,float &minX,float &maxY, float &minY, float &maxZ,float &minZ
	 *  \return void
	 *  \date
	 */
	void find_box(float &maxX,float &minX,float &maxY, float &minY, float &maxZ,float &minZ);
		/**
	 *  \brief with the class change, a new method to load the obj into this class
	 *  
	 *  Due to the need for change in implementation a the change to the default constructor
	 *  needed to remove forced process from its group. so this is the replacement function 
	 *  to allow for the read from obj
	 *  
	 *  \bug this whole class should be rewritten to reflect the things we have learnt
	 *  
	 *  author Welsley Gai-Yeen Lui
	 *  \date
	 *  
	 *  \param string fileLocation, vector<string> &ImageLocation, vector<GLuint> &ImageTextureID
	 *  \return void
	 */
	void process(std::string input, std::vector<std::string>* imgLoIN, std::vector<GLuint>* imgTexIN);

private:
	
	//this keeps track of the movement we added to the object so we can apply it later
	float m_x;
	float m_y;
	float m_z;

	//stupid additions to help define edges
	float R[3];
	float G[3];
	float B[3];

	// the list of vectors that i will be using
	std::vector<points> m_points;
	std::vector<normal> m_normals;
	std::vector<coordinate> m_coords;
	//********************* add this bit as well
	std::vector<MTL> m_mtl;
	//***************************
	std::vector<face> m_faces;

	void processMTL(std::string input);
	void process(std::string input);
	void inputPoints(points temp);
	void inputNormals(normal temp);
	void inputCoordinates(coordinate temp);
	void createFaces(face temp);

	//stupid ones
	
	//these are the mtl files in a vector
	std::vector<std::string> *imgLoc;
	std::vector<GLuint> *imgTex;
};

