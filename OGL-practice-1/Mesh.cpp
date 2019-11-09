#include "Mesh.h"

using namespace std;
using namespace glm;

Mesh::Mesh()
{
}

void Mesh::load(const char* filename)
{
	// Open a file and check if there are some troubles with it
	ifstream f(filename);
	if (!f.is_open())
	{
		cerr << "ERROR: file " << filename <<" was not loaded\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	GLuint buffer = 0;
	
	// Read info from the file
	vector<vec3> vCoords;
	vector<vec3> vNormals;
	vector<vec3> vTexCoords;
	vector<ivec3> vFaces;
	string sWordBuf;
	char sTemp[512];
	while (!f.eof())
	{
		f >> sWordBuf;
		if (sWordBuf == "v")
		{
			vec3 vCoordTemp;
			f >> vCoordTemp.x;
			f >> vCoordTemp.y;
			f >> vCoordTemp.z;
			vCoords.push_back(vCoordTemp);
		}
		if (sWordBuf == "vn")
		{
			vec3 vNormalTemp;
			f >> vNormalTemp.x;
			f >> vNormalTemp.y;
			f >> vNormalTemp.z;
			vNormals.push_back(vNormalTemp);
		}
		if (sWordBuf == "vt")
		{
			vec3 vTexTemp;
			f >> vTexTemp.x;
			f >> vTexTemp.y;
			f >> vTexTemp.z;
			vTexCoords.push_back(vTexTemp);
		}
		if (sWordBuf == "f")
		{
			for (int i = 0; i < 3; i++) // read one triple int/int/int
			{
				ivec3 vTempInd;
				char delim;
				f >> vTempInd.x;
				f >> delim;
				f >> vTempInd.y;
				f >> delim;
				f >> vTempInd.z;
				vFaces.push_back(vTempInd);
			}
		}
			f.getline(sTemp, 512);
	}

	// Close the file
	f.close();

	// Build array of vertices
	map<string, int> m;
	int i = 0;
	vertices.clear();
	for (auto it = vFaces.begin(); it != vFaces.end(); it++)
	{
		vec3 tempCoord    = vCoords[(*it).x - 1];
		vec3 tempTexCoord = vTexCoords[(*it).y - 1];
		vec3 tempNormal   = vNormals[(*it).z - 1];
		Vertex tmp =
		{
			{tempCoord.x, tempCoord.y, tempCoord.z},
			{tempNormal.z, tempNormal.y, tempNormal.z},
			{tempTexCoord.x, tempTexCoord.y}
		};

		string tmp_str = to_string((*it).x) + '/' + to_string((*it).y) + '/' + to_string((*it).z);
		
		if (m.find(tmp_str) == m.end())
		{
			vertices.push_back(tmp);
			m.insert(make_pair(tmp_str, i++));
		}
		indices.push_back(m[tmp_str]);
	}

	// Load it to buffers
	if (!(buffers[0] && buffers[1]))
		glGenBuffers(2, buffers);
	// Load data 
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);    // set VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);	  // set EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

	// Enable vertex attribs
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Point to data
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(Vertex, coord)));		    // Coords
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));		    // Normal

	// Draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Disable vertex attribs
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


Mesh::~Mesh()
{
	glDeleteBuffers(2, buffers);
}