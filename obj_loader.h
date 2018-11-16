#pragma once
#include <stdio.h>
#include <string.h>


#define Debug(x){MessageBox(NULL, x, "Debug:", MB_OK);}


// Define targa header.
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)



////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the fil
	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	BYTE_SWAP(tgaHeader.colorMapStart);
	BYTE_SWAP(tgaHeader.colorMapLength);
	BYTE_SWAP(tgaHeader.xstart);
	BYTE_SWAP(tgaHeader.ystart);
	BYTE_SWAP(tgaHeader.width);
	BYTE_SWAP(tgaHeader.height);
#endif


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:     // Most likely case
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

struct vertex
{
	float x, y, z;
	unsigned int index;
};
typedef vertex normal;
struct texcoord
{
	float u, v;
	unsigned int index;
};

struct face
{
	float x[3], y[3], z[3];		//vertices
	float u[3], v[3];			//text coords
	float a[3], b[3], c[3];		//normals
};

struct material
{
	char name[32];
	int illum;
	char map_Kd[32];
	float Ni;
	float Kd[3];
	float Ka[3];
	float Tf[3];
	unsigned int texture;
};

class model
{
private:
	int faces;
	int coords;
	int normals;
	bool loaded;
	char mtllib[256];
	char filename[256];
	char directory[256];
	unsigned int vindex;
	unsigned int tindex;
	unsigned int nindex;
	struct vnode
	{
		vertex data;
		vnode * next;
	};
	struct tnode
	{
		texcoord data;
		tnode * next;
	};

	struct mnode
	{
		material data;
		mnode * next;
	};
	struct fnode
	{
		face data;
		mnode * mat;
		fnode * next;
	};

	vnode * vfirst;
	vnode * vcurrent;
	tnode * tfirst;
	tnode * tcurrent;
	vnode * nfirst;
	vnode * ncurrent;
	fnode * ffirst;
	fnode * fcurrent;
	mnode * mfirst;
	mnode * mcurrent;
	void skipComment(FILE *);

	bool loadVertex(FILE *);
	bool loadTexCoord(FILE *);
	bool loadNormal(FILE *);
	bool loadFace(FILE *);
	bool loadMaterialLib(FILE *);
	void loadMaterials(FILE *);
	void loadBmpTexture(char* fileName, GLuint* texture);
	void loadTGAtexture(char* fileName, GLuint* texture);
	void useMaterial(FILE *);

	AUX_RGBImageRec *LoadBMPFile(char *filename)
	{
		FILE *hFile = NULL;

		if (!filename) return NULL;

		hFile = fopen(filename, "r");

		if (hFile) {
			fclose(hFile);
			return auxDIBImageLoad(filename);
		}

		return NULL;
	}

public:
	bool Load(char * objfile, char * mtlname);
	model()
	{
		vfirst = vcurrent = NULL;
		tfirst = tcurrent = NULL;
		nfirst = ncurrent = NULL;
		ffirst = fcurrent = NULL;
		mfirst = mcurrent = NULL;
		vindex = tindex = nindex = 1;
	}
	void draw();
	float Y(float, float) { return 0.0; }
	bool Collide(float, float, float, float, float, float) { return false; }
};

void model::loadTGAtexture(char* fileName, GLuint* texture)
{
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	GLbyte *pBytes = NULL;

	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, *texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	pBytes = gltLoadTGA(fileName, &iWidth, &iHeight, &iComponents, &eFormat);
	gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void model::loadBmpTexture(char* fileName, GLuint* texture)
{
	AUX_RGBImageRec* texRec;

	if ((texRec = LoadBMPFile(fileName))) {
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			3,
			texRec->sizeX,
			texRec->sizeY,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			texRec->data);
	}

	if (texRec)
	{
		if (texRec->data) free(texRec->data);
		free(texRec);
	}
}

bool model::Load(char * objfile, char * mtlname)
{
	char buffer[256];
	strcpy(filename, objfile);
	FILE * file = fopen(filename, "r");

	strcpy(mtllib, mtlname);

	if (file == NULL)
	{
		MessageBox(NULL, objfile, "Model file not found:", MB_OK);
		return false;
	}
	while (fscanf(file, "%s", buffer) != EOF)
	{
		if (!strcmp("#", buffer))skipComment(file);
		if (!strcmp("mtllib", buffer))loadMaterialLib(file);
		if (!strcmp("v", buffer))loadVertex(file);
		if (!strcmp("vt", buffer))loadTexCoord(file);
		if (!strcmp("vn", buffer))loadNormal(file);
		if (!strcmp("f", buffer))loadFace(file);
		if (!strcmp("s", buffer))fscanf(file, "%s", buffer);
		if (!strcmp("usemtl", buffer))useMaterial(file);
	}
	fclose(file);
	loaded = true;
	return true;
}

void model::useMaterial(FILE * file)
{
	char buffer[256];
	mnode * cursor = mfirst;
	fscanf(file, "%s", buffer);
	while (strcmp(buffer, cursor->data.name))
		cursor = cursor->next;
	mcurrent = cursor;
}

void model::skipComment(FILE * file)
{
	char buffer[256];
	fgets(buffer, 256, file);
}

bool model::loadMaterialLib(FILE * file)
{
	/*
	char * wd = strtok(filename, "/");
	char buffer[256];
	fscanf(file, "%s", buffer);
	sprintf(mtllib, "%s/%s", wd, buffer);
	strcpy(directory, wd);
	*/
	FILE * lib = fopen(mtllib, "r");
	if (lib == NULL)
	{
		MessageBox(NULL, mtllib, "Material library not found:", MB_OK);
		return false;
	}
	else loadMaterials(lib);
	fclose(lib);
	return true;
}

void model::loadMaterials(FILE * file)
{

	char parameter[32];
	mnode * temp;
	while (fscanf(file, "%s", parameter) != EOF)
	{

		if (!strcmp("newmtl", parameter))
		{
			temp = new mnode();
			fscanf(file, "%s", temp->data.name);
		}
		if (!strcmp("illum", parameter))
			fscanf(file, "%i", &temp->data.illum);
		if (!strcmp("map_Kd", parameter))
		{
			fscanf(file, "%s", temp->data.map_Kd);

			if (strstr(temp->data.map_Kd, ".bmp") != NULL)
				loadBmpTexture(temp->data.map_Kd, &(temp->data.texture));
			else if (strstr(temp->data.map_Kd, ".tga") != NULL)
				loadTGAtexture(temp->data.map_Kd, &(temp->data.texture));
		}
		if (!strcmp("Ni", parameter))
			fscanf(file, "%f", &temp->data.Ni);
		if (!strcmp("Kd", parameter))
			fscanf(file, "%f %f %f", &temp->data.Kd[0], &temp->data.Kd[1], &temp->data.Kd[2]);
		if (!strcmp("Ka", parameter))
			fscanf(file, "%f %f %f", &temp->data.Ka[0], &temp->data.Ka[1], &temp->data.Ka[2]);
		if (!strcmp("Tf", parameter))
		{
			fscanf(file, "%f %f %f", &temp->data.Tf[0], &temp->data.Tf[1], &temp->data.Tf[2]);
			if (mfirst == NULL)
			{
				mfirst = temp;
				mcurrent = temp;
				mfirst->next = NULL;
			}
			else
			{
				mcurrent->next = temp;
				mcurrent = mcurrent->next;
				mcurrent->next = NULL;
			}

		}
	}

}

bool model::loadVertex(FILE * file)
{
	vnode * temp = new vnode();
	fscanf(file, "%f %f %f", &temp->data.x, &temp->data.y, &temp->data.z);
	temp->data.index = vindex;
	if (vfirst == NULL)
	{
		vfirst = temp;
		vcurrent = temp;
		vfirst->next = NULL;
	}
	else
	{
		vcurrent->next = temp;
		vcurrent = vcurrent->next;
		vcurrent->next = NULL;
	}
	vindex++;
	return true;
}

bool model::loadTexCoord(FILE * file)
{
	tnode * temp = new tnode();
	fscanf(file, "%f %f", &temp->data.u, &temp->data.v);
	temp->data.index = tindex;
	temp->next = NULL;
	if (tfirst == NULL)
	{
		tfirst = temp;
		tcurrent = temp;
	}
	else
	{
		tcurrent->next = temp;
		tcurrent = tcurrent->next;
	}
	tindex++;
	return true;
}

bool model::loadNormal(FILE * file)
{
	vnode * temp = new vnode();
	fscanf(file, "%f %f %f", &temp->data.x, &temp->data.y, &temp->data.z);
	temp->data.index = nindex;
	temp->next = NULL;
	if (nfirst == NULL)
	{
		nfirst = temp;
		ncurrent = temp;
	}
	else
	{
		ncurrent->next = temp;
		ncurrent = ncurrent->next;
	}
	nindex++;
	return true;
}

bool model::loadFace(FILE * file)
{
	fnode * temp = new fnode();
	temp->mat = mcurrent;
	vnode * vcursor = vfirst;
	tnode * tcursor = tfirst;
	vnode * ncursor = nfirst;
	unsigned int v_index[3], t_index[3], n_index[3];
	for (int i = 0; i < 3; i++)
	{
		vcursor = vfirst;
		tcursor = tfirst;
		ncursor = nfirst;
		fscanf(file, "%i/%i/%i", &v_index[i], &t_index[i], &n_index[i]);

		for (int v = 1; v != v_index[i]; v++)
			vcursor = vcursor->next;
		temp->data.x[i] = vcursor->data.x;
		temp->data.y[i] = vcursor->data.y;
		temp->data.z[i] = vcursor->data.z;

		for (int k = 1; k != t_index[i]; k++)
			tcursor = tcursor->next;
		temp->data.u[i] = tcursor->data.u;
		temp->data.v[i] = tcursor->data.v;

		for (int j = 1; j != n_index[i]; j++)
			ncursor = ncursor->next;
		temp->data.a[i] = ncursor->data.x;
		temp->data.b[i] = ncursor->data.y;
		temp->data.c[i] = ncursor->data.z;
	}

	temp->next = NULL;
	if (ffirst == NULL)
	{
		ffirst = temp;
		fcurrent = temp;
		ffirst->next = NULL;
	}
	else
	{
		fcurrent->next = temp;
		fcurrent = fcurrent->next;
		fcurrent->next = NULL;
	}
	faces++;
	return true;
}

void model::draw()
{
#ifdef __GL_H__
	if (loaded)
	{
		fnode * fcursor = ffirst;
		//if( *ffirst->mat->data.texture != NULL)
		//glBindTexture(GL_TEXTURE_2D, ffirst->mat->data.texture);
		int nCnt = 0;
		glBegin(GL_TRIANGLES);
		while (fcursor != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, fcursor->mat->data.texture);
			nCnt++;
			glColor3f(1.0f, 1.0f, 1.0f);

			glTexCoord2f(fcursor->data.u[0], fcursor->data.v[0]);
			glNormal3f(fcursor->data.a[0], fcursor->data.b[0], fcursor->data.c[0]);
			glVertex3f(fcursor->data.x[0], fcursor->data.y[0], fcursor->data.z[0]);

			glTexCoord2f(fcursor->data.u[1], fcursor->data.v[1]);
			glNormal3f(fcursor->data.a[1], fcursor->data.b[1], fcursor->data.c[1]);
			glVertex3f(fcursor->data.x[1], fcursor->data.y[1], fcursor->data.z[1]);

			glTexCoord2f(fcursor->data.u[2], fcursor->data.v[2]);
			glNormal3f(fcursor->data.a[2], fcursor->data.b[2], fcursor->data.c[2]);
			glVertex3f(fcursor->data.x[2], fcursor->data.y[2], fcursor->data.z[2]);
			fcursor = fcursor->next;
		}

		glEnd();
	}
#endif
}
