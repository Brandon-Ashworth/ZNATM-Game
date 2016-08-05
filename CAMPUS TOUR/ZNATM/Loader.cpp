#include "Loader.h"

Loader::Loader()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;

	//this needs to go
	R[0] = 1.0;
	R[1] = 0.0;
	R[2] = 0.0;

	G[0] = 0.0;
	G[1] = 1.0;
	G[2] = 0.0;

	B[0] = 0.0;
	B[1] = 0.0;
	B[2] = 1.0;
}

Loader::Loader(std::string input,std::vector<std::string>* imgLoIN, std::vector<GLuint>* imgTexIN )
{
	m_x = 0;
	m_y = 0;
	m_z = 0;

	imgLoc = imgLoIN;
	imgTex = imgTexIN;	

	process(input);

	//this needs to go
	R[0] = 1.0;
	R[1] = 0.0;
	R[2] = 0.0;

	G[0] = 0.0;
	G[1] = 1.0;
	G[2] = 0.0;

	B[0] = 0.0;
	B[1] = 0.0;
	B[2] = 1.0;
}


Loader::~Loader(void)
{

}

void Loader::process(std::string input)
{
	std::ifstream m_inFile;
	std::string identifier;	//used to identify where the input should go



	points temppoint;
	normal tempnormal;
	coordinate tempcoord;
	face tempface; 


	std::string read;		// used to read the curent line

	int readNum; // this is the number that has just been read in
	char skip; // a char to skip thr /
	int i;
	int count= 1;
	
	//other things to take into account
	//****************************************
	std::string l_name;
	//int l_image;
	bool firstRun = true;
	std::string parse;
	//**************************************


	m_inFile.open(input);
	/* // check to see if it read
	if(!m_inFile) 
		std::cout << "did not read";
	else
		std::cout << "file read";
	*/


	//creation of the reading loop
	//while(!m_inFile.eof())
	m_inFile >> identifier;

	do {
		 // check to see what the opening is

		if (identifier =="#")
		{
			getline(m_inFile,read); // use this to read the whole line
	
		}
		else if(identifier == "v")
		{
			m_inFile >> temppoint.x >> temppoint.y >> temppoint.z;
			inputPoints(temppoint);
		}
		else if(identifier == "vn")
		{
			m_inFile >> tempnormal.vn[0] >> tempnormal.vn[1] >> tempnormal.vn[2];
			inputNormals(tempnormal);
		}
		else if (identifier == "vt")
		{
			m_inFile >> tempcoord.vt[0] >> tempcoord.vt[1] >> tempcoord.vt[2];
			inputCoordinates(tempcoord);
		}
		else if(identifier == "f")
		{


			for( i =0; i < 3; i++)
			{
				//std::cout << "loops: " << count << std::endl;
				count++;
				//if(read == "Material.001")
				//	std::cout << std::endl;

				//std::cout << "Iteration: " << i << std::endl;
				m_inFile >> readNum;
				if(readNum == 0)
					break;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.p[i].x = m_points[readNum].x;
				//std::cout << "x: " << m_points[readNum].x << std::endl;
				tempface.p[i].y = m_points[readNum].y;
				//std::cout << "y: " << m_points[readNum].y << std::endl;
				tempface.p[i].z = m_points[readNum].z;
				//std::cout << "z: " << m_points[readNum].z << std::endl;

				
				m_inFile >> skip >> readNum;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.coord[i].vt[0] = m_coords[readNum].vt[0];
				//std::cout << "coord 1: " <<  m_coords[readNum].vt[0] << std::endl;
				tempface.coord[i].vt[1] = m_coords[readNum].vt[1];
				//std::cout << "coord 2: " <<  m_coords[readNum].vt[1] << std::endl;
				tempface.coord[i].vt[2] = m_coords[readNum].vt[2];
				//std::cout << "coord 3: " <<  m_coords[readNum].vt[2] << std::endl;


				m_inFile >> skip >> readNum;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.norm[i].vn[0] = m_normals[readNum].vn[0];
				//std::cout << "normal 1: " << m_normals[readNum].vn[0] << std::endl;
				tempface.norm[i].vn[1] = m_normals[readNum].vn[1];
				//std::cout << "normal 1: " << m_normals[readNum].vn[1] << std::endl;
				tempface.norm[i].vn[2] = m_normals[readNum].vn[2];
				//std::cout << "normal 1: " << m_normals[readNum].vn[2] << std::endl << std::endl;
				
				

			}
			
			tempface.name = l_name; // this gives the mtl name to the face so it can be compared and applied later
			
			createFaces(tempface);

		}
		else if(identifier =="mtllib")
		{
			m_inFile >> identifier;
			identifier = "test/" + identifier;
			processMTL(identifier);
		}
		
		else if(identifier == "usemtl")
		{
		// chnages the mtl that is being applied
			m_inFile >> read;
			
			l_name = read; // so the face can have 
		
		/*
			std::string l_location;
			//std::ifstream mtlFile;
			MTL temp;
		*/
			
			
			
			
		}
		else 
		{
			getline(m_inFile,read);
			//std::cout << "Not Processed From Loader" << identifier << " " << read <<std::endl;
		}

		m_inFile >> identifier;

	} while (!m_inFile.eof());
	m_inFile.close();
	//m_inFile.~basic_ifstream();
}

void Loader::process(std::string input, std::vector<std::string>* imgLoIN, std::vector<GLuint>* imgTexIN)
{
	std::ifstream m_inFile;
	std::string identifier;	//used to identify where the input should go

	imgLoc = imgLoIN;
	imgTex = imgTexIN;

	points temppoint;
	normal tempnormal;
	coordinate tempcoord;
	face tempface; 


	std::string read;		// used to read the curent line

	int readNum; // this is the number that has just been read in
	char skip; // a char to skip thr /
	int i;
	int count= 1;
	
	//other things to take into account
	//****************************************
	std::string l_name;
	//int l_image;
	bool firstRun = true;
	std::string parse;
	//**************************************


	m_inFile.open(input);
	/* // check to see if it read
	if(!m_inFile) 
		std::cout << "did not read";
	else
		std::cout << "file read";
	*/


	//creation of the reading loop
	//while(!m_inFile.eof())
	m_inFile >> identifier;

	do {
		 // check to see what the opening is

		if (identifier =="#")
		{
			getline(m_inFile,read); // use this to read the whole line
	
		}
		else if(identifier == "v")
		{
			m_inFile >> temppoint.x >> temppoint.y >> temppoint.z;
			inputPoints(temppoint);
		}
		else if(identifier == "vn")
		{
			m_inFile >> tempnormal.vn[0] >> tempnormal.vn[1] >> tempnormal.vn[2];
			inputNormals(tempnormal);
		}
		else if (identifier == "vt")
		{
			m_inFile >> tempcoord.vt[0] >> tempcoord.vt[1] >> tempcoord.vt[2];
			inputCoordinates(tempcoord);
		}
		else if(identifier == "f")
		{


			for( i =0; i < 3; i++)
			{
				//std::cout << "loops: " << count << std::endl;
				count++;
				//if(read == "Material.001")
				//	std::cout << std::endl;

				//std::cout << "Iteration: " << i << std::endl;
				m_inFile >> readNum;
				if(readNum == 0)
					break;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.p[i].x = m_points[readNum].x;
				//std::cout << "x: " << m_points[readNum].x << std::endl;
				tempface.p[i].y = m_points[readNum].y;
				//std::cout << "y: " << m_points[readNum].y << std::endl;
				tempface.p[i].z = m_points[readNum].z;
				//std::cout << "z: " << m_points[readNum].z << std::endl;

				
				m_inFile >> skip >> readNum;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.coord[i].vt[0] = m_coords[readNum].vt[0];
				//std::cout << "coord 1: " <<  m_coords[readNum].vt[0] << std::endl;
				tempface.coord[i].vt[1] = m_coords[readNum].vt[1];
				//std::cout << "coord 2: " <<  m_coords[readNum].vt[1] << std::endl;
				tempface.coord[i].vt[2] = m_coords[readNum].vt[2];
				//std::cout << "coord 3: " <<  m_coords[readNum].vt[2] << std::endl;


				m_inFile >> skip >> readNum;
				//std::cout << "ReadNum = " << readNum << std::endl;
				readNum--;
				//std::cout << "ReadNum = " << readNum << std::endl;
				tempface.norm[i].vn[0] = m_normals[readNum].vn[0];
				//std::cout << "normal 1: " << m_normals[readNum].vn[0] << std::endl;
				tempface.norm[i].vn[1] = m_normals[readNum].vn[1];
				//std::cout << "normal 1: " << m_normals[readNum].vn[1] << std::endl;
				tempface.norm[i].vn[2] = m_normals[readNum].vn[2];
				//std::cout << "normal 1: " << m_normals[readNum].vn[2] << std::endl << std::endl;
				
				

			}
			
			tempface.name = l_name; // this gives the mtl name to the face so it can be compared and applied later
			
			createFaces(tempface);

		}
		else if(identifier =="mtllib")
		{
			m_inFile >> identifier;
			identifier = "test/" + identifier;
			processMTL(identifier);
		}
		
		else if(identifier == "usemtl")
		{
		// chnages the mtl that is being applied
			m_inFile >> read;
			
			l_name = read; // so the face can have 
		
		/*
			std::string l_location;
			//std::ifstream mtlFile;
			MTL temp;
		*/
			
			
			
			
		}
		else 
		{
			getline(m_inFile,read);
			//std::cout << "Not Processed From Loader" << identifier << " " << read <<std::endl;
		}

		m_inFile >> identifier;

	} while (!m_inFile.eof());
	m_inFile.close();
	//m_inFile.~basic_ifstream();
}

void Loader::inputPoints(points temp)
{
	m_points.push_back(temp);

}

void Loader::inputNormals(normal temp)
{
	m_normals.push_back(temp);
}

void Loader::inputCoordinates(coordinate temp)
{
	m_coords.push_back(temp);
}

void Loader::createFaces(face temp)
{
	m_faces.push_back(temp);
}

void Loader::draw()
{
	int i;
	int j;
	int k;

	std::string currentTex;
	// ***********************
	//glEnable(GL_LIGHTING);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);
	//**************

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);
	//glBegin(GL_TRIANGLES);

	//srand(0);
	//glEnable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);
	for (i=0; i < m_faces.size();i++)
	{
		//bind a certain image 

		if(m_faces[i].name != currentTex)
		{
			for (k=0; k<m_mtl.size();k++)
			{
			
				if (m_mtl[k].compare(m_faces[i].name) == true)
				{
					glEnd();
					m_mtl[k].draw();
					currentTex = m_faces[i].name;
					glBegin(GL_TRIANGLES);
					//glBindTexture(GL_TEXTURE_2D,m_mtl[k].getGLID());
					//break; // break out of the loop
				}
				//if(m_face[i].name == m_mtl[k].compare ;
			}
		}
		
		//std::cout<<"glBegin" <<std::endl;
		
		//glColor3f((rand() % 256) / 256.0f,(rand() % 256) / 256.0f,(rand() % 256) / 256.0f);
		glColor3f(1.0f,1.0f,1.0f);
		

		for(j = 0 ; j < 3; j++)
		{
			//std::cout << "Vn1: "<< m_faces[i].norm[j].vn[0] << "Vn2: " << m_faces[i].norm[j].vn[1] <<"Vn3: "<< m_faces[i].norm[j].vn[2] << std::endl;
			//std::cout << "X: " << m_faces[i].p[j].x << "Y: " << m_faces[i].p[j].y << "Z: " << m_faces[i].p[j].z << std::endl;
			//glTexCoord2f(m_faces[i].coord[j].vt[0],m_faces[i].coord[j].vt[1]);
			glNormal3f(m_faces[i].norm[j].vn[0],m_faces[i].norm[j].vn[1],m_faces[i].norm[j].vn[2]);
			glTexCoord2f(m_faces[i].coord[j].vt[0],m_faces[i].coord[j].vt[1]);
			//glColor3f(R[j],G[j],B[j]);
			//glColor3f(R[i],G[i],B[i]); //broken
			//glColor3f(1.0,0.0,0.0);
			//glColor3f((rand() % 256) / 256.0f,(rand() % 256) / 256.0f,(rand() % 256) / 256.0f);
			glVertex3f(m_faces[i].p[j].x,m_faces[i].p[j].y,m_faces[i].p[j].z);
		}
		
		//std::cout << "glEnd()" << std::endl <<std::endl;
	}
	glEnd();
	//glDisable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);
}

void Loader::move(float x, float y, float z)
{
	int i;
	int j;

	m_x += x;
	m_y += y;
	m_z += z;

	for(i=0; i < m_faces.size(); i++)
	{
		for(j=0; j < 3; j++)
		{
			m_faces[i].p[j].x += x;
			m_faces[i].p[j].y += y;
			m_faces[i].p[j].z += z;
		}
	}
}

void Loader::getPos()
{
	std::cout << m_x;
}

//takes an input
void Loader::setPos(float x, float y, float z)
{
	int i;
	int j;

	for(i=0; i < m_faces.size(); i++)
	{
		for(j=0; j < 3; j++)
		{
			m_faces[i].p[j].x += x;
			m_faces[i].p[j].y += y;
			m_faces[i].p[j].z += z;
		}
	}

}

void Loader::processMTL(std::string input)
{

	std::string identifier;
	std::string read; //for reading whole lines
	
	MTL mtlTemp( imgLoc, imgTex);
	//std::string input; 
	std::ifstream l_inMtl;

	//for reading in numbers to give to the mtl
	float ka0, ka1, ka2;
	float kd0, kd1, kd2;
	float ks0, ks1, ks2;
	float Ns;

	//so that an empty mtl is not pushed back into the vector
	bool firstRun = true;

	l_inMtl.open(input);
	l_inMtl >> identifier;

	do{
		if(identifier == "#")
		{
			getline(l_inMtl,read);
		}
		else if(identifier == "newmtl")
		{
			//checks to see if it has run before if it has not run before don't push back the last read
			if (firstRun == false)
				m_mtl.push_back(mtlTemp);
			else 
				firstRun = false;


			l_inMtl >> identifier;
			mtlTemp.setName(identifier);
		}
		else if(identifier == "Ka")
		{
			l_inMtl >>ka0 >> ka1 >> ka2;
			mtlTemp.setKa(ka0,ka1,ka2);
		}
		else if(identifier == "Kd")
		{
			l_inMtl >> kd0 >>kd1 >> kd2;
			mtlTemp.setKd(kd0,kd1,kd2);
		}
		else if(identifier =="Ks")
		{
			l_inMtl >> ks0 >> ks1 >> ks2;
			mtlTemp.setKs(ks0, ks1, ks2);
		}
		else if(identifier == "map_Ka")
		{
			l_inMtl.get();
			getline(l_inMtl,identifier);
			//l_inMtl >> identifier;
			mtlTemp.setLoc(identifier);
		}
		else if(identifier == "Ns")
		{
			l_inMtl >> Ns;
			mtlTemp.setNs(Ns);
		}
		else
		{
			getline(l_inMtl,read);
			//std::cout << "Not Processed MTL" << identifier << " " << read << " " << input << std::endl;
		}
		l_inMtl >> identifier;
	}while(!l_inMtl.eof());

	l_inMtl.close();
	m_mtl.push_back(mtlTemp); // so the last one is pushed back

}

void Loader::find_box(float &maxX,float &minX,float &maxY, float &minY, float &maxZ,float &minZ)
{
	maxX = m_faces[0].p[0].x;
	minX = m_faces[0].p[0].x;
	maxY = m_faces[0].p[0].y;
	minY = m_faces[0].p[0].y;
	maxZ = m_faces[0].p[0].z;
	minZ = m_faces[0].p[0].z;
	
	int i, j;

	for(i=0; i < m_faces.size(); i++)
	{
		for(j=0; j < 3; j++)
		{
			// again check tomorrow if gfreater then max max = current else if less then min min = current
			if (maxX < m_faces[i].p[j].x)
				maxX = m_faces[i].p[j].x;
			else if (minX > m_faces[i].p[j].x)
				minX = m_faces[i].p[j].x;
			
			
			if (maxY < m_faces[i].p[j].y)
				maxY = m_faces[i].p[j].y;
			else if (minY > m_faces[i].p[j].y)
				minY = m_faces[i].p[j].y;
				
			if (maxZ < m_faces[i].p[j].z)
				maxZ = m_faces[i].p[j].z;
			else if (minZ > m_faces[i].p[j].z)
				minZ = m_faces[i].p[j].z;
	
		}
	}
}