 #pragma once 


#include "../freeglut.h"

#include <string>
#include <fstream>
#include "typedef.h"
#include "../lib/IL/il.h"
#include <iostream>
#include <vector>
//#include <IL/il.h>





/**
 *  \brief This stores the mtl information and loads the texture.
 *  
 *  This class is linked to the loader for it stores the mtl data as well as the 
 *  the texture id after it has been loaded and given to openGL.
 *  
 *  \bug loads a texture for every face evrey object has multiple faces
 *  \note bug fixed by passing in a vector of textures that have already been processed and gives them the correct textureID.
 *  \bug you now have to pass in the vector, there is no option, you should have had an option to or not to pass in, this was bad coding on my part because i needed to do this quickly.
 *  
 *  \author Umar Badat
 *  
 *  
 */
class MTL
{
public:
	MTL();
	 /**
	 *  \brief takes the file location and current textures that have already been bound to openGL
	 *  
	 *  This constructor takes in a string representing the mtl location, a vector of already existing textures and the texture id.
	 *  using this information it can determine weather or not it needs to generate a texture ID
	 *  
	 *  \author Umar Badat
	 *  \bug you must give it a vector to check against, it will work if the vector is empty
	 *  
	 *  \param  vector<string> &ImageLocation, vector<GLuint> &ImageTextureID
	 */
	MTL(std::vector<std::string> *imgLoIN, std::vector<GLuint>* imgTexIN); //name of the file
	~MTL(void);
	/**
	 *  \brief function that is not needed.
	 *  
	 *  When I planned for this class in the beginning i did no know that 3DSMax handles 
	 *  The texure bind type (so tile/ stretch) so this function was never filled in
	 *  
	 *  \param string bindType
	 *  \return void
	 *  \author Umar Badat
	 *  \bug doesn't do anything
	 *  \date	 
	 */
	void bind(std::string bindType);// somehow set the bind type eg tile stretch ect
		/**
	 *  \brief sets all of the lighting information
	 *  
	 *  This function takes all the lighting information as one large function 
	 *  This is in case we ever wanted to add a way to give the mtl data manually
	 *  or if you wanted to include the mtl only.
	 *  
	 *  \param float ka0, float ka1, float ka2,float kd0, float kd1, float kd2, float ks0, float ks1, float ks2
	 *  \note if you don't understand this you probably don't need access to it
	 *  \return void
	 *  \author Umar Badat
	 *  \date
	 */
	void setVar(float ka0, float ka1, float ka2,float kd0, float kd1, float kd2, float ks0, float ks1, float ks2); // takes in all the inputs and sets them to the class
	/**
	 *  \brief sets the location of the texture file to read in.
	 *  \param string ImageLocation
	 *  
	 *  \return void
	 *  \author Umar Badat
	 *  \date
	 */
	void setLoc(std::string inLocation); // set the location
		/**
	 *  \brief sets the name of the material (newmtl)
	 *  
	 *  from inside the mtl file is given a meterial name to be applied
	 *  
	 *  \param string name - name of mtl given by 3dsMax
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void setName(std::string inName);

		/**
	 *  \brief sets the material ambiance 
	 *  
	 *  \param float ka0, float ka1, float ka2 - texture ambiance 
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void setKa(float ka0, float ka1, float ka2);
	/**
	 *  \brief sets the material diffusion
	 *  
	 *  \param float kd0, float kd1, float kd2 
	 *  \author Umar Badat
	 *  \date
	 */
	void setKd(float kd0, float kd1, float kd2);
	/**
	 *  \brief sets the specular
	 *  
	 *  \param float ks0, float ks1, float ks2
	 *  \author Umar Badat
	 *  \date
	 */
	void setKs(float ks0, float ks1, float ks2);
	/**
	 *  \brief sets the model shininess from 0-100 3DSMax sets this
	 *  
	 *  \param float Ns
	 *  \author Umar Badat
	 *  \date
	 */
	void setNs(float inNs);
	
	/**
	 *  \brief compares the string with this objects name if true return true
	 *  
	 *  \param string name
	 *  \return bool - if equal return true
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	bool compare(std::string inName); // compare the string with another
	/**
	 *  \brief applies the texture inside this mtl file
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void draw(); // change the binds
	/**
	 *  \brief return the location of the file that it read in
	 *  
	 *  This function was used before we passed in the mtl vector, the loader could take this information and 
	 *  using it say if a new mtl should be created
	 *  
	 *  \return string location
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	std::string getLoc() {return location;};
	/**
	 *  \brief returns the texture ID
	 *  
	 *  This Function returns the texture id given by openGL, see getLoc()
	 *  
	 *  \return textureID
	 *  \author Umar Badat
	 *  \date
	 */
	GLuint getGLID() { return texture;};

	//useless functions should never be called
	void noLight();
	void getLight();
	void ourLight();
	GLint findLight();

	//static std::vector<std::string> imgLoc;
	//static std::vector<int> imgTex;
	
private:
	
	std::string name;
	std::string location; // the location of the image
	
	float ka[3];
	float kd[3];
	float ks[3];
	float Ns;

	// must have freeglut in order to use this
	BYTE *pixmap; // contains the data (not yet set)
	GLuint texture;

	//two functions that you need to load and display
	void LoadThing();
	void createTex(int width, int height, int chan);

	//vectors to stop duplicare images

	std::vector<std::string> *imgLoc;
	std::vector<GLuint> *imgTex;

	//hahahaha
	GLint oldLight;

};