/*
re add the !inFile return could not find file (ect)

from the loader handle reading from the mtl file and creating the vector of mtl class types thing
an if for usemmtl
*/



#include "MTL.h"





MTL::MTL()
{

}

MTL::MTL(std::vector<std::string>* imgLoIN, std::vector<GLuint>* imgTexIN) //name of the file
{
	//name = inName; // brah this shit not needed
	imgLoc = imgLoIN;
	imgTex = imgTexIN;
	
}
MTL::~MTL()
{

}

void MTL::setName(std::string inName)
{
	name = inName;
}

void MTL::setNs(float inNs)
{
	Ns = inNs;
	//do nothing isn't it great
}

void MTL::bind(std::string bindType)// somehow set the bind type eg tile stretch ect
{	
	if (bindType == "stretch" || bindType == "Stretch")
	{
	
	}
	/*else if()
	{
	
	}*/
	else
	{
	}
	
}

void MTL::setVar(float ka0, float ka1, float ka2,float kd0, float kd1, float kd2, float ks0, float ks1, float ks2 ) // takes in all the inputs and sets them to the class
{
	ka[0] = ka0;
	ka[1] = ka1;
	ka[2] = ka2;
	
	kd[0] = kd0;
	kd[1] = kd1;
	kd[2] = kd2;
	
	ks[0] = ks0;
	ks[1] = ks1;
	ks[2] = ks2;
}

void MTL::setLoc(std::string inLocation)
{
	location = inLocation;
	
	LoadThing();
	// add the ifstream for loading the bmp it should be in this scope only and the texture (in an array ) should be part of the class i think
}
bool MTL::compare(std::string inName) // compare the string with another
{
	//return true if they are the same
	if (name == inName)
		return true;
	else
		return false;
		
}
void MTL::draw() // change the binds
{
	// not sure how this is done but i need to 
	const GLfloat temp[] = {Ns};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR,ks);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, temp);
	
	glBindTexture(GL_TEXTURE_2D, texture); 

	
	GLint one;
	//glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,&one);
	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_);
	
}

void MTL::setKa(float ka0, float ka1, float ka2)
{
	ka[0] = ka0;
	ka[1] = ka1;
	ka[2] = ka2;
}

void MTL::setKd(float kd0, float kd1, float kd2)
{
	kd[0] = kd0;
	kd[1] = kd1;
	kd[2] = kd2;
}

void MTL::setKs(float ks0, float ks1, float ks2)
{
	ks[0] = ks0;
	ks[1] = ks1;
	ks[2] = ks2;
}

void MTL::LoadThing()
{
	int i;
	bool exists = false;
	std::string tempimgLoc;
	GLuint tempimgTex;

	for(i=0;i<imgLoc->size();i++)
	{
		 //tempimgLoc = *imgLoc[i];

		if (imgLoc->at(i) == location)
		{
			exists = true;
			texture = imgTex->at(i);
			break;
			
		}

	}

	if (exists == false)
	{
		ILuint devImg;
		ilGenImages(1,&devImg);
		ilBindImage(devImg);

		//added this line
		imgLoc->push_back(location);

		const char *input = location.c_str();
		//std::string temp(L(location));
		//const wchar_t* szName = location.c_str();

		std::wstring temp ;

		for( i = 0; i < location.length(); ++i)
			temp += wchar_t (location[i]);

		const wchar_t *result = temp.c_str(); // use result int eh ilLocadImage 

		int e = ilGetError();
		bool error = ilLoadImage(input);
		//int error = ilLoadImage("test/marble_floor2.png");
		//int error = ilLoadImage("marble_floor2.png");
		//int error = ilLoadImage("lol.jpg");

		/*std::ofstream findnowpls("findnow.pls");
		findnowpls << "pew" << std::endl;
		findnowpls.close();
		std::ifstream findplsnow("findnow.pls");
		std::string str = "ohgodplsno";
		findplsnow >> str;
		std::cout << str;
		findplsnow.close();*/

		e = ilGetError();

		pixmap = ilGetData();
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int chan = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);

		createTex(width,height,chan);
	}
	else
	{
		//can't remember
	}
}

void MTL::createTex(int width, int height, int chan)
{
	int error = glGetError();
	glEnable(GL_TEXTURE_2D);
	error = glGetError();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	error = glGetError();
	
	glGenTextures(1, &texture);
	error = glGetError();
	//glGenTextures(1, &texture); // this was put down twice

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);
	error = glGetError();

	//glTexImage2D(GL_TEXTURE_2D, 0, chan, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
	glTexImage2D(GL_TEXTURE_2D, 0, chan, width, height, 0, (chan == 4)?GL_RGBA: GL_RGB, GL_UNSIGNED_BYTE, pixmap);
	error = glGetError();
	//no clue
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	error = glGetError();

	//add this as well
	imgTex->push_back(texture);

}

void MTL::noLight()
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, oldLight);
}
void MTL::getLight()
{
	glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &oldLight);
}
void MTL::ourLight()
{
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}

GLint findLight()
{
	GLint lol;
	glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &lol);
	return(lol);
}