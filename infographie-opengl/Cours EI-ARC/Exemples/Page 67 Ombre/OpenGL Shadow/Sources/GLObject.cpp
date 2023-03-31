
#include "GLObject.H"

#ifdef	DEBUG_MATRIX_STACK

// �s��X�^�b�N�̃f�o�b�O���[�h
GLint DEBUG_modelViewMatrixStack = 0 ;
GLint DEBUG_projectionMatrixStack = 0 ;
GLint DEBUG_textureMatrixStack = 0 ;

void DEBUG_glPushMatrix()
{
	GLint mode ;
	glGetIntegerv(GL_MATRIX_MODE, &mode) ;

	switch (mode)
	{
	case GL_MODELVIEW:
		DEBUG_modelViewMatrixStack ++ ;
		break ;
	case GL_PROJECTION:
		DEBUG_projectionMatrixStack ++ ;
		break ;
	case GL_TEXTURE:
		DEBUG_textureMatrixStack ++ ;
		break ;
	}

#undef glPushMatrix
	glPushMatrix() ;
#define glPushMatrix	DEBUG_glPushMatrix
}

void DEBUG_glPopMatrix()
{
	GLint mode ;
	glGetIntegerv(GL_MATRIX_MODE, &mode) ;

	switch (mode)
	{
	case GL_MODELVIEW:
		DEBUG_modelViewMatrixStack -- ;
		if (DEBUG_modelViewMatrixStack < 0)
			MessageBox(NULL, "Modelview matrix underflow!", "glPopMatrix()", MB_OK | MB_ICONSTOP) ;
		break ;
	case GL_PROJECTION:
		DEBUG_projectionMatrixStack -- ;
		if (DEBUG_projectionMatrixStack < 0)
			MessageBox(NULL, "Projection matrix underflow!", "glPopMatrix()", MB_OK | MB_ICONSTOP) ;
		break ;
	case GL_TEXTURE:
		DEBUG_textureMatrixStack -- ;
		if (DEBUG_textureMatrixStack < 0)
			MessageBox(NULL, "Texture matrix underflow!", "glPopMatrix()", MB_OK | MB_ICONSTOP) ;
		break ;
	}

#undef glPopMatrix
	glPopMatrix() ;
#define glPopMatrix		DEBUG_glPopMatrix
}

#endif	// #ifdef DEBUG_MATRIX_STACK


// RGB BYTE �z���p �Ȉ� gluBuild2DMipmaps
//
// �~�b�v�}�b�v�쐬���Z�b�g
// image �͗\�ߍœK�ȃT�C�Y�ɃX�P�[������Ă���K�v����
// �܂��Aimage �̃t�H�[�}�b�g�� GL_ALPHA(1), GL_RGB(3), GL_RGBA(4) �� GL_UNSIGNED_BYTE
//int Build2DMipmaps(TRUEIMAGE *image, GLint format)
int Build2DMipmaps(TRUEIMAGE *image, GLint format, int arrayComponents)
{
	int width, height, maxLevel ;
	int err ;
	TRUEIMAGE *img[16] ;	// �ő� 16 ���x��

	maxLevel = 0 ;
	img[0] = CreateCopyImage(image, arrayComponents) ;

	// �e�N�X�`���̍ő�T�C�Y
	GLint	maxTextureSize ;
	int		scaleFlag = FALSE ;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize) ;

	if (img[0]->width > maxTextureSize)
	{
		scaleFlag = TRUE ;
		width  = maxTextureSize ;
	}
	if (img[0]->height > maxTextureSize)
	{
		scaleFlag = TRUE ;
		height = maxTextureSize ;
	}
	if (scaleFlag)
	{
		ScaleImage(&img[0], width, height, arrayComponents) ;
	}

	width  = img[0]->width ;
	height = img[0]->height ;

	GLenum arrayFormat ;
	if (arrayComponents <= 1)
	{
		arrayComponents = 1 ;
		arrayFormat = GL_ALPHA ;
	}
	else if (arrayComponents == 3)
		arrayFormat = GL_RGB ;
	else if (arrayComponents >= 4)
	{
		arrayComponents = 4 ;
		arrayFormat = GL_RGBA ;
	}

	err = 0 ;
	while (TRUE)
	{
		if (width ==1 && height == 1) break ;
		maxLevel ++ ;

		width  = (width  > 1 ? width  / 2 : 1) ;
		height = (height > 1 ? height / 2 : 1) ;

		img[maxLevel] = (TRUEIMAGE *)malloc(sizeof(TRUEIMAGE)) ;
		img[maxLevel]->dataptr = (unsigned char *)malloc(sizeof(unsigned char) * (width + 4) * height * arrayComponents) ;

		img[maxLevel]->width  = width ;
		img[maxLevel]->height = height ;

		if (err = gluScaleImage(arrayFormat, img[maxLevel - 1]->width, img[maxLevel - 1]->height,
								GL_UNSIGNED_BYTE, img[maxLevel - 1]->dataptr, width, height,
								GL_UNSIGNED_BYTE, img[maxLevel]->dataptr)
			)
		{
			break ;
		}
	}

	// �e���x���̃e�N�X�`���� OpenGL �ɃZ�b�g
	if (!err)
	{
		for (int level = 0 ; level <= maxLevel ; level ++)
		{
			glTexImage2D(GL_TEXTURE_2D, level, format, img[level]->width, img[level]->height,
						 0, arrayFormat, GL_UNSIGNED_BYTE, img[level]->dataptr) ;

/*
			glTexImage2D(GL_TEXTURE_2D, level, format, img[level]->width, img[level]->height,
						 0, GL_RGB, GL_UNSIGNED_BYTE, NULL) ;

			glTexSubImage2D(GL_TEXTURE_2D, level, 0,0, img[level]->width, img[level]->height,
							GL_RGB, GL_UNSIGNED_BYTE, img[level]->dataptr) ;
*/
		}
	}

	// �쐬�����摜���폜
	for (int level = 0 ; level <= maxLevel ; level ++)
		freeimage(img[level]) ;

	return err ;
}


TRUEIMAGE *LoadTextueImagePNM(String name)
{
	TRUEIMAGE *image = NULL ;

	FILE   *fp = fopen(name, "rb") ;
	if (fp)
	{
		image = finputpnm(fp) ;
		fclose(fp) ;
	}

	return image ;
}


// pnm �摜�̓ǂݍ���
TRUEIMAGE *LoadTextureImage(String name, int nPath, String *pathTable, String *effectivePath)
{
#ifdef WIN32
	char slash = '\\' ;
#else
	char slash = '/' ;
#endif

	String defaultPath[1] = { "" } ;
	String *path ;

	String imagePath ;
	String ext = Lower(Right(name, 4)) ;

	if (ext != ".ppm" && ext != ".pgm" && ext != ".pbm")
		ext = "" ;

	if (nPath <= 0 || !pathTable)
	{
		nPath = 1 ;
		path = defaultPath ;
	}
	else
		path = pathTable ;

	TRUEIMAGE *image = NULL ;
	for (int i = 0 ; i < nPath ; i ++)
	{
		if (path[i] == "" || Right(path[i], 1) == slash)
			imagePath = path[i] + name ;
		else
			imagePath = path[i] + slash + name ;

		String tmp = imagePath ;

		// ppm
		if (ext != ".pgm" && ext!= ".pbm")
		{
			if (ext != ".ppm")
				imagePath += ".ppm" ;
			image = LoadTextueImagePNM(imagePath) ;
		}
		if (image) break ;

		// pgm
		imagePath = tmp ;
		if (ext != ".ppm" && ext!= ".pbm")
		{
			if (ext != ".pgm")
				imagePath += ".pgm" ;
			image = LoadTextueImagePNM(imagePath) ;
		}
		if (image) break ;

		// pbm
		imagePath = tmp ;
		if (ext != ".ppm" && ext!= ".pgm")
		{
			if (ext != ".pbm")
				imagePath += ".pbm" ;
			image = LoadTextueImagePNM(imagePath) ;
		}

		if (image) break ;
	}

	if (effectivePath)
		*effectivePath = imagePath ;

	return image ;
}



// �C���[�W�t�H�[�}�b�g�� RGB ���� RGBA ��
// �A���t�@�l�̃f�t�H���g�� 1.0f
int RGBtoRGBA(TRUEIMAGE *image, GLfloat alpha)
{
	unsigned int x, y ;
	unsigned char *newImage ;

	if (!(newImage = (unsigned char *)malloc(image->width * image->height * 4))) return FAILURE ;

	if      (alpha < 0.0f) alpha = 0.0f ;
	else if (alpha > 0.0f) alpha = 1.0f ;

	for (y = 0 ; y < image->height ; y ++)
	{
		for (x = 0 ; x < image->width ; x ++)
		{
			unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3,	// ���C���[�W�|�C���^
						  *npt = newImage + y * image->width * 4 + x * 4 ;		// RGBA�C���[�W�|�C���^

			npt[0] = ptr[0] ; npt[1] = ptr[1] ; npt[2] = ptr[2] ;

			npt[3] = (unsigned char)(alpha * 255.0f) ;	// �A���t�@�l�� 1.0f
		}
	}

	free(image->dataptr) ;
	image->dataptr = newImage ;

	return SUCCESS ;
}

// �C���[�W�t�H�[�}�b�g�� RGB ���� RGBA ��
// �������A���l�͎Q�ƃC���[�W�̖��邳���g�p
int RGBtoRGBA(TRUEIMAGE *image, TRUEIMAGE *refimage)
{
	unsigned int x, y ;
	unsigned char *newImage ;

	if (!(newImage = (unsigned char *)malloc(image->width * image->height * 4))) return FAILURE ;

	for (y = 0 ; y < image->height ; y ++)
	{
		for (x = 0 ; x < image->width ; x ++)
		{
			unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3,	// ���C���[�W�|�C���^
						  *npt = newImage + y * image->width * 4 + x * 4 ;		// RGBA�C���[�W�|�C���^

			npt[0] = ptr[0] ; npt[1] = ptr[1] ; npt[2] = ptr[2] ;

			// �A���t�@�l�͎Q�ƃC���[�W�̖��邳
			ptr = refimage->dataptr + y * refimage->width * 3 + x * 3 ;	// �Q�ƃC���[�W�|�C���^
			unsigned char alpha = (unsigned char)((float)ptr[0] * GRAY_RATIO_R + (float)ptr[1] * GRAY_RATIO_G + (float)ptr[2] * GRAY_RATIO_B) ;
			npt[3] = (unsigned char)(alpha) ;
		}
	}

	free(image->dataptr) ;
	image->dataptr = newImage ;

	return SUCCESS ;
}


// �C���[�W�R�s�[
TRUEIMAGE *CreateCopyImage(TRUEIMAGE *src, int arrayCompponents)
{
	TRUEIMAGE *image ;
	image = (TRUEIMAGE *)malloc(sizeof(TRUEIMAGE)) ;
	if (!image) return NULL ;

	image->width  = src->width ;
	image->height = src->height ;

	image->dataptr = (unsigned char *)malloc((image->width + 4) * image->height * arrayCompponents) ;
	if (!image->dataptr)
	{
		free(image) ;
		return NULL ;
	}

	// �f�[�^���̃R�s�[
	memcpy(image->dataptr, src->dataptr, image->width * image->height * arrayCompponents) ;

	return image ;
}

// �w��T�C�Y�̐V���ȃC���[�W�����i�f�[�^�͕s���j
TRUEIMAGE *CreateNewImage(unsigned int w, unsigned int h)
{
	if (w == 0 && h == 0)
		return NULL ;

	TRUEIMAGE *image ;
	image = (TRUEIMAGE *)malloc(sizeof(TRUEIMAGE)) ;
	if (!image) return NULL ;

	image->width  = w ;
	image->height = h ;
	if (image->height == 0)
		image->height = w ;

	image->dataptr = (unsigned char *)malloc((image->width + 4) * image->height * 3) ;
	if (!image->dataptr)
	{
		free(image) ;
		return NULL ;
	}

	return image ;
}


// �C���[�W�N���A�i�f�t�H���g�͔��j
void ClearImage(TRUEIMAGE *image, float r, float g, float b, float radiusRatio,
				unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	unsigned int x, y ;

	if      (r < 0.0f) r = 0.0f ;
	else if (r > 1.0f) r = 1.0f ;

	if (g < 0.0f) g = r ;
	if (b < 0.0f) b = r ;

	if (r > 1.0f) r = 1.0f ;
	if (g > 1.0f) g = 1.0f ;
	if (b > 1.0f) b = 1.0f ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	if (radiusRatio == 0.0f)
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				ptr[0] = (unsigned char)(r * 255.0f) ;	// R
				ptr[1] = (unsigned char)(g * 255.0f) ;	// G
				ptr[2] = (unsigned char)(b * 255.0f) ;	// B
			}
		}
	}
	else
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				// ���S������̋���
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				float ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;

				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				float change = r * 255.0f - ptr[0] ;
				ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

				change = g * 255.0f - ptr[0] ;
				ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

				change = b * 255.0f - ptr[0] ;
				ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
}


// �C���[�W�K���}�␳
void GammaCollection(TRUEIMAGE *image, float gamma, float radiusRatio,
					 unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (gamma == 1.0f || gamma == 0.0f) return ;
	else if (gamma == 0.0f) return ;
	gamma = 1.0f / gamma ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	if (radiusRatio == 0.0f)
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				ptr[0] = (unsigned char)(Pow(ptr[0] / 255.0f, gamma) * 255.0f) ;	// R �␳
				ptr[1] = (unsigned char)(Pow(ptr[1] / 255.0f, gamma) * 255.0f) ;	// G �␳
				ptr[2] = (unsigned char)(Pow(ptr[2] / 255.0f, gamma) * 255.0f) ;	// B �␳
			}
		}
	}
	else
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				// ���S������̋���
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				float ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;

				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				float change = Pow(ptr[0] / 255.0f, gamma) * 255.0f - ptr[0] ;
				ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

				change = Pow(ptr[1] / 255.0f, gamma) * 255.0f - ptr[1] ;
				ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

				change = Pow(ptr[2] / 255.0f, gamma) * 255.0f - ptr[2] ;
				ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
}


// �C���[�W���邳�ω�
void ChangeBrightness(TRUEIMAGE *image, float bright, float radiusRatio,
					  unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (bright == 1.0f) return ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	if (radiusRatio == 0.0f)
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^	

				ptr[0] = (unsigned char)(Clump(ptr[0] * bright, 0.0f, 255.0f)) ;	// R �␳
				ptr[1] = (unsigned char)(Clump(ptr[1] * bright, 0.0f, 255.0f)) ;	// G �␳
				ptr[2] = (unsigned char)(Clump(ptr[2] * bright, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
	else
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				// ���S������̋���
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				float ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;

				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				float change = ptr[0] * bright - ptr[0] ;
				ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

				change = ptr[1] * bright - ptr[1] ;
				ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

				change = ptr[2] * bright - ptr[2] ;
				ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
}


// �C���[�W���邳�ω��i�������q�f�a�ʁX�Ɂj
void ModulateRGB(TRUEIMAGE *image, float r, float g, float b, float radiusRatio,
				 unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (r == 1.0f && g == 1.0f && b == 1.0f ) return ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	if (radiusRatio == 0.0f)
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				ptr[0] = (unsigned char)(Clump(ptr[0] * r, 0.0f, 255.0f)) ;	// R �␳
				ptr[1] = (unsigned char)(Clump(ptr[1] * g, 0.0f, 255.0f)) ;	// G �␳
				ptr[2] = (unsigned char)(Clump(ptr[2] * b, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
	else
	{
		for (y = iy ; y < height ; y ++)
		{
			for (x = ix ; x < width ; x ++)
			{
				// ���S������̋���
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				float ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;

				unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

				float change = ptr[0] * r - ptr[0] ;
				ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

				change = ptr[1] * g - ptr[1] ;
				ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

				change = ptr[2] * b - ptr[2] ;
				ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
			}
		}
	}
}


// �C���[�W�̍ʓx�ύX(�O�F�O���[�X�P�[���A�P�F�I���W�i���A�Q�F�Q�{�N�₩)
void ChangeSaturation(TRUEIMAGE *image, float vivid, float radiusRatio,
					  unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (vivid == 1.0f) return ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	for (y = iy ; y < height ; y ++)
	{
		for (x = ix ; x < width ; x ++)
		{
			float ratio ;

			// ���S������̋���
			if (radiusRatio)
			{
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;
			}
			else
				ratio = 1.0f ;

			unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

			// �ʓx�[���̏ꍇ�� RGB �P�x�i0�`255�j
			float bright = ptr[0] * GRAY_RATIO_R + ptr[1] * GRAY_RATIO_G +  ptr[2] * GRAY_RATIO_B ;

			float change = (bright - ptr[0]) * (1 - vivid) ;
			ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

			change = (bright - ptr[1]) * (1 - vivid) ;
			ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

			change = (bright - ptr[2]) * (1 - vivid) ;
			ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
		}
	}
}


// �C���[�W�̃R���g���X�g�ύX(�O�F�O���[)
void ChangeContrast(TRUEIMAGE *image, float cont, float radiusRatio,
					unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (cont == 1.0f) return ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	for (y = iy ; y < height ; y ++)
	{
		for (x = ix ; x < width ; x ++)
		{
			float ratio ;

			// ���S������̋���
			if (radiusRatio)
			{
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;
			}
			else
				ratio = 1.0f ;

			unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

			float change = (127 - (int)ptr[0]) * (1 - cont) ;
			ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

			change = (127 - (int)ptr[1]) * (1 - cont) ;
			ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

			change = (127 - (int)ptr[2]) * (1 - cont) ;
			ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
		}
	}
}


// �C���[�W�̖��邳�␳
// ��{�I�ɂ̓K���}�R���N�V���������A
// R,G,B �S�̂̋P�x���狤�ʂ̃K���}�ŕ␳���邽�߁A�ʓx���ω����Ȃ�
// �C���[�W�̖��邳�ύX
void ChangeGammaBrightness(TRUEIMAGE *image, float gamma, float radiusRatio,
						   unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (gamma == 1.0f || gamma == 0.0f) return ;
	else if (gamma == 0.0f) return ;
	gamma = 1.0f / gamma ;

	unsigned int x, y ;

	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

	for (y = iy ; y < height ; y ++)
	{
		for (x = ix ; x < width ; x ++)
		{
			float ratio ;

			// ���S������̋���
			if (radiusRatio)
			{
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;
			}
			else
				ratio = 1.0f ;

			unsigned char *ptr = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^

			// �S�̋P�x����̃K���}�␳�l
			float l = ((float)ptr[0] * GRAY_RATIO_R + (float)ptr[1] * GRAY_RATIO_G + (float)ptr[2] * GRAY_RATIO_B) / 255.0f ;
			if (l <= 0.0f || l >= 1.0f) continue ;
			float bright = Pow(l, gamma) ;

			// RGB �ɂ��d�ݕt���͕s�v�H
//			float bright = Pow(((float)ptr[0] + (float)ptr[1] + (float)ptr[2]) / (255.0f * 3), gamma) ;

			float change = (float)ptr[0] * bright - (float)ptr[0] ;
			ptr[0] = (unsigned char)(Clump((float)ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

			change = (float)ptr[1] * bright - (float)ptr[1] ;
			ptr[1] = (unsigned char)(Clump((float)ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

			change = (float)ptr[2] * bright - (float)ptr[2] ;
			ptr[2] = (unsigned char)(Clump((float)ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
		}
	}
}


int ScaleImage(TRUEIMAGE **image, int width, int height, int arrayComponents)
{
	TRUEIMAGE *image2 ;

	GLenum arrayFormat ;
	if (arrayComponents <= 1)
	{
		arrayComponents = 1 ;
		arrayFormat = GL_ALPHA ;
	}
	else if (arrayComponents == 3)
		arrayFormat = GL_RGB ;
	else if (arrayComponents >= 4)
	{
		arrayComponents = 4 ;
		arrayFormat = GL_RGBA ;
	}

	if (!(image2 = (TRUEIMAGE*)malloc(sizeof(TRUEIMAGE))))
	{
		return -1 ;	// �G���[�����i����`�j
	}

	image2->dataptr = (unsigned char *)malloc(sizeof(unsigned char) * (width + 4) * height * arrayComponents) ;
	if (!image2->dataptr)
	{
		return -1 ;	// �G���[�����i����`�j
	}

	int err =  gluScaleImage(arrayFormat, (*image)->width, (*image)->height,
							 GL_UNSIGNED_BYTE, (*image)->dataptr,
							 width, height,
							 GL_UNSIGNED_BYTE, image2->dataptr) ;
	if (err)
	{
		freeimage(image2) ;
		return err ;	// �G���[�����i����`�j
	}

	image2->width  = width ;
	image2->height = height ;

	freeimage(*image) ;
	*image = image2 ;

	return 0 ;
}


// image �� image2 �����Z�i���ꂼ��ɑ΂��d�ݕt�����\�j
// image �̂݁Awidth, height �w��\
void AddImage(TRUEIMAGE *image, TRUEIMAGE *image2, float weight, float weight2, float radiusRatio,
			  unsigned int ix, unsigned int iy, unsigned int width, unsigned int height)
{
	unsigned int x, y ;
	int allocFlag = FALSE ;
	width  += ix ;
	height += iy ;

	if (width  == ix || width  > image->width ) width  = image->width ;
	if (height == iy || height > image->height) height = image->height ;

//	if (width == 0 || height == 0)
//		return ;

	// image2 �̃T�C�Y�� image �̊Y�������ɍ��킹��
	TRUEIMAGE image3 ;
	image3.width  = width  - ix ;
	image3.height = height - iy ;

	if (image3.width == image2->width && image3.height == image2->height)
		image3.dataptr = image2->dataptr ;
	else
	{
		allocFlag =TRUE ;

		image3.dataptr = (unsigned char *)malloc(sizeof(unsigned char) * (image3.width + 4) * image3.height * 3) ;
		if (!image3.dataptr)
		{
			return ;	// �G���[�����i����`�j
		}

		int err =  gluScaleImage(GL_RGB, image2->width, image2->height,
								GL_UNSIGNED_BYTE, image2->dataptr,
								image3.width, image3.height,
								GL_UNSIGNED_BYTE, image3.dataptr) ;
		if (err)
		{
			freeimage(&image3) ;
			return ;	// �G���[�����i����`�j
		}
	}

	// image ���
	for (y = iy ; y < height ; y ++)
	{
		for (x = ix ; x < width ; x ++)
		{
			int x3 = x - ix, y3 = y - iy ;
			float ratio ;

			// ���S������̋���
			if (radiusRatio)
			{
				float rx = (x - ix) / (float)(width  - ix) * 2.0f - 1.0f ;
				float ry = (y - iy) / (float)(height - iy) * 2.0f - 1.0f ;
				ratio = sqrt(rx * rx + ry * ry) ;

				if (ratio > 1.0f) continue ;

				// �����ɂ��ύX���[�g
				ratio = 1.0 - Pow(ratio, radiusRatio) ;
			}
			else
				ratio = 1.0f ;

			unsigned char *ptr  = image->dataptr + y * image->width * 3 + x * 3 ;	// R �v�f�̃|�C���^
			unsigned char *ptr3 = image3.dataptr + y3 * image3.width * 3 + x3 * 3 ;	// R �v�f�̃|�C���^

			float change = (ptr[0] * weight + ptr3[0] * weight2) - ptr[0] ;
			ptr[0] = (unsigned char)(Clump(ptr[0] + change * ratio, 0.0f, 255.0f)) ;	// R �␳

			change = (ptr[1] * weight + ptr3[1] * weight2) - ptr[1] ;
			ptr[1] = (unsigned char)(Clump(ptr[1] + change * ratio, 0.0f, 255.0f)) ;	// G �␳

			change = (ptr[2] * weight + ptr3[2] * weight2) - ptr[2] ;
			ptr[2] = (unsigned char)(Clump(ptr[2] + change * ratio, 0.0f, 255.0f)) ;	// B �␳
		}
	}

	if (allocFlag)
		freeimage(&image3) ;
}


// �C���[�W�̏㉺���E���]
void ReverseCoordinates(TRUEIMAGE *image, int mirrorFlag, int flipFlag)
{
	// �ω��Ȃ��Ȃ瑦���^�[��
	if (!mirrorFlag && !flipFlag) return ;

	// ��Ɨp�ꎞ�o�b�t�@�쐬
	TRUEIMAGE *tmp ;
	tmp = (TRUEIMAGE *)malloc(sizeof(TRUEIMAGE)) ;
	if (!tmp) return ;
	tmp->dataptr = (unsigned char *)malloc(sizeof(unsigned char) * image->width * image->height * 3) ;
	if (!tmp->dataptr)
	{
		free(tmp) ;
		return ;
	}
	// �f�[�^���R�s�[
	memcpy(tmp->dataptr, image->dataptr, sizeof(unsigned char) * image->width * image->height * 3) ;

	// tmp ������ ���W���]���Ȃ���f�[�^���R�s�[
	for (int y = 0 ; y < image->height ; y ++)
	{
		int sy ;
		if (flipFlag) sy = image->height - y - 1 ;
		else		  sy = y ;

		for (int x = 0 ; x < image->width ; x ++)
		{
			int sx ;
			if (mirrorFlag) sx = image->width - x - 1 ;
			else			sx = x ;

			unsigned char *srcptr =   tmp->dataptr + sy * image->width * 3 + sx * 3 ;	// R �v�f�̃|�C���^
			unsigned char *dstptr = image->dataptr +  y * image->width * 3 +  x * 3 ;	// R �v�f�̃|�C���^

			dstptr[0] = srcptr[0] ;
			dstptr[1] = srcptr[1] ;
			dstptr[2] = srcptr[2] ;
		}
	}

	freeimage(tmp) ;
}


// ����s���~�b�h�쐬�i�W�b�^���܁j
void Perspective(GLfloat scr_w, GLfloat scr_h, GLfloat n_clip, GLfloat f_clip,
				 int win_w, int win_h, GLfloat px, GLfloat py)
{
	if (win_w < 0 || win_h < 0)
	{
		GLint vp[4] ;
		glGetIntegerv(GL_VIEWPORT, vp) ;
		win_w = vp[2] ;
		win_h = vp[3] ;
	}

	px *= scr_w / win_w ;
	py *= scr_h / win_h ;

	scr_w *= 0.5f ;
	scr_h *= 0.5f ;

	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glFrustum(-scr_w + px, scr_w + px, -scr_h + py, scr_h + py, n_clip, f_clip) ;
}


// �F�A�f�ރZ�b�g
//
// r, g, b, a	�f�ނ̊�{�J���[
// metal		�����W���i�������f�B�t���[�Y���Ⴍ�A�X�y�L�����[�� r, g, b �̉e�����󂯂�j
// specular		�X�y�L�����[���̖̂��邳
// shininess	�n�C���C�g�w��
// mirror		�~���[�t���O
// mirror_ratio	mirror == TRUE �̎��A���̒l�������������W���ɂ��f�B�t���[�Y�̕ω������Ȃ�
// amb			!= NONE �̏ꍇ�A�����ˌW�����f�B�t���[�Y�Ƃ͕ʂɗ^����ir, g, b �e�v�f * amb)
// color_switch	
void SetMaterial(GLenum surface, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat metal, GLfloat specular, GLfloat shininess, GLint mirror, GLfloat mirror_ratio, GLfloat amb)
{
	// �X�y�L�����[���[���̏ꍇ
	if (specular == 0.0f)
		shininess = 0.0f ;

	GLfloat param[3][4], diffuse = 1.0f - metal, d_r, d_g, d_b ;
	if (mirror) diffuse = 1.0f - metal * (1.0f - mirror_ratio) ;

	// �f�B�t���[�Y���A���r�G���g
	param[0][0] = param[2][0] = d_r = r * diffuse ;
	param[0][1] = param[2][1] = d_g = g * diffuse ;
	param[0][2] = param[2][2] = d_b = b * diffuse ;
	param[0][3] = a ;

	// �X�y�L�����[
	param[1][0] = (r + (1.0f - d_r) * (1.0f - metal)) * specular ;
	param[1][1] = (g + (1.0f - d_g) * (1.0f - metal)) * specular ;
	param[1][2] = (b + (1.0f - d_b) * (1.0f - metal)) * specular ;
	param[1][3] = 1.0f ;

//	if (shininess == 0.0f &&
//		(param[1][0] != 0.0f ||
//		 param[1][1] != 0.0f ||
//		 param[1][2] != 0.0f)
//		)
//		MessageBox(NULL, "AAAAAA", "GLU Error", MB_OK | MB_ICONSTOP) ;


	// amb ���Z�b�g����Ă���ꍇ�̃A���r�G���g
	if (amb != NONE)
	{
		param[2][0] = r * amb ;
		param[2][1] = g * amb ;
		param[2][2] = b * amb ;
	}

	if (amb == NONE)
		glMaterialfv(surface, GL_AMBIENT_AND_DIFFUSE, param[0]) ;
	else
	{
		glMaterialfv(surface, GL_DIFFUSE, param[0]) ;
		glMaterialfv(surface, GL_AMBIENT, param[2]) ;
	}

	glMaterialfv(surface, GL_SPECULAR,  param[1]) ;
	glMaterialf (surface, GL_SHININESS, shininess) ;
}



void SetLightColor(GLenum light, GLfloat colorRGBA[4], GLfloat amb,
				   GLfloat specularFlag, GLfloat bright, GLfloat *modulate)
{
	GLfloat color[4] = { colorRGBA[0], colorRGBA[1], colorRGBA[2], 1.0f } ;	// colorRGBA[3] } ;
	GLfloat	lamb[4] ;	// = { color[0] * 0.1, color[1] * 0.1, color[2] * 0.1, 1.0f } ;
	static GLfloat	spec[4] = { 0.0f, 0.0f, 0.0f, 1.0f } ;

	if (amb != 0.0f)
	{
		lamb[0] = colorRGBA[0] * amb ;
		lamb[1] = colorRGBA[1] * amb ;
		lamb[2] = colorRGBA[2] * amb ;
	}
	else
	{
		lamb[0] = 0.0f ;
		lamb[1] = 0.0f ;
		lamb[2] = 0.0f ;
	}

	// bright ���ݒ肳��Ă���ꍇ�A�f�B�t���[�Y�ƃX�y�L�����[�̖��邳�ύX�i�������ω��j
	if (modulate)
	{
		color[0] *= bright * modulate[0] ;
		color[1] *= bright * modulate[1] ;
		color[2] *= bright * modulate[2] ;

		lamb[0] *= bright * modulate[0] ;
		lamb[1] *= bright * modulate[1] ;
		lamb[2] *= bright * modulate[2] ;
	}
	else
	{
		color[0] *= bright ;
		color[1] *= bright ;
		color[2] *= bright ;

		lamb[0] *= bright ;
		lamb[1] *= bright ;
		lamb[2] *= bright ;
	}

	glLightfv(light, GL_AMBIENT,  lamb) ;
	glLightfv(light, GL_DIFFUSE,  color) ;

	if (specularFlag)
	{
		GLfloat	specular[4] = { color[0] * specularFlag, color[1] * specularFlag, color[2] * specularFlag, 1.0f } ;
		glLightfv(light, GL_SPECULAR, specular) ;
	}
	else
		glLightfv(light, GL_SPECULAR, spec) ;
}


void SetDirectionalLight(GLenum light, GLfloat pos[4], GLfloat colorRGBA[4],
						 GLfloat amb, GLfloat specularFlag, GLfloat bright, GLfloat *modulate)
{
	GLfloat color[4] = { colorRGBA[0], colorRGBA[1], colorRGBA[2], 1.0f } ;	// colorRGBA[3] } ;
	GLfloat	lamb[4] = { color[0] * 0.1, color[1] * 0.1, color[2] * 0.1, 1.0f } ;
	static GLfloat	u_pos[4] ;
	static GLfloat	spec[4] = { 0.0f, 0.0f, 0.0f, 1.0f } ;

	if (amb != 0.0f)
	{
//		color[0] = colorRGBA[0] * (1.0f - amb) ;
//		color[1] = colorRGBA[1] * (1.0f - amb) ;
//		color[2] = colorRGBA[2] * (1.0f - amb) ;

		lamb[0] = colorRGBA[0] * amb ;
		lamb[1] = colorRGBA[1] * amb ;
		lamb[2] = colorRGBA[2] * amb ;
	}

	Vector3d u(pos) ;
	u.Unit() ;

	u_pos[0] = u.X() ;
	u_pos[1] = u.Y() ;
	u_pos[2] = u.Z() ;
	u_pos[3] = 0.0f ;
//	u_pos[3] = pos[3] ;

	// bright ���ݒ肳��Ă���ꍇ�A�f�B�t���[�Y�ƃX�y�L�����[�̖��邳�ύX�i�������ω��j
	if (modulate)
	{
		color[0] *= bright * modulate[0] ;
		color[1] *= bright * modulate[1] ;
		color[2] *= bright * modulate[2] ;

		lamb[0] *= bright * modulate[0] ;
		lamb[1] *= bright * modulate[1] ;
		lamb[2] *= bright * modulate[2] ;
	}
	else
	{
		color[0] *= bright ;
		color[1] *= bright ;
		color[2] *= bright ;

		lamb[0] *= bright ;
		lamb[1] *= bright ;
		lamb[2] *= bright ;
	}

	glLightfv(light, GL_POSITION, u_pos) ;
	glLightfv(light, GL_AMBIENT,  lamb) ;
	glLightfv(light, GL_DIFFUSE,  color) ;

//	if (specularFlag) glLightfv(light, GL_SPECULAR, color) ;
//	else              glLightfv(light, GL_SPECULAR, spec) ;

	if (specularFlag)
	{
		GLfloat	specular[4] = { color[0] * specularFlag, color[1] * specularFlag, color[2] * specularFlag, 1.0f } ;
		glLightfv(light, GL_SPECULAR, specular) ;
	}
	else
		glLightfv(light, GL_SPECULAR, spec) ;


	// �ʒu�����֘A�̃p�����^�͋����I�ɃN���A

	// �ʒu����
	glLightf(light, GL_CONSTANT_ATTENUATION,  1.0f) ;
	glLightf(light, GL_LINEAR_ATTENUATION,    0.0f) ;
	glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0f) ;

	// �X�|�b�g�����p�����^
	glLightfv(light, GL_SPOT_DIRECTION, u_pos) ;	// �_�~�[
	glLightf(light, GL_SPOT_CUTOFF, 180.0f) ;
	glLightf(light, GL_SPOT_EXPONENT, 0.0f) ;
}


void SetPositionalLight(GLenum light, GLfloat pos[4], GLfloat colorRGBA[4], GLfloat amb, GLfloat specularFlag, GLfloat bright,
						GLfloat const_attn, GLfloat linear_attn, GLfloat quad_attn,
						GLfloat *dir, GLfloat spot_cutoff, GLfloat spot_exp, GLfloat *modulate)
{
	GLfloat color[4] = { colorRGBA[0], colorRGBA[1], colorRGBA[2], 1.0f } ;	// colorRGBA[3] } ;
	GLfloat	lamb[4] = { color[0] * amb, color[1] * amb, color[2] * amb, 1.0f } ;
	static GLfloat	u_dir[4] = { 0.0f, 0.0f, -1.0f, 0.0f } ;
	static GLfloat	spec[4] = { 0.0f, 0.0f, 0.0f, 1.0f } ;

	if (amb != 0.0f)
	{
//		color[0] = colorRGBA[0] * (1.0f - amb) ;
//		color[1] = colorRGBA[1] * (1.0f - amb) ;
//		color[2] = colorRGBA[2] * (1.0f - amb) ;

		lamb[0] = colorRGBA[0] * amb ;
		lamb[1] = colorRGBA[0] * amb ;
		lamb[2] = colorRGBA[0] * amb ;
	}

	// bright ���ݒ肳��Ă���ꍇ�A�f�B�t���[�Y�ƃX�y�L�����[�̖��邳�ύX�i�������ω��j
	if (modulate)
	{
		color[0] *= bright * modulate[0] ;
		color[1] *= bright * modulate[1] ;
		color[2] *= bright * modulate[2] ;

		lamb[0] *= bright * modulate[0] ;
		lamb[1] *= bright * modulate[1] ;
		lamb[2] *= bright * modulate[2] ;
	}
	else
	{
		color[0] *= bright ;
		color[1] *= bright ;
		color[2] *= bright ;

		lamb[0] *= bright ;
		lamb[1] *= bright ;
		lamb[2] *= bright ;
	}

	if (dir)
	{
		Vector3d u(dir) ;
		u.Unit() ;

		u_dir[0] = u.X() ;
		u_dir[1] = u.Y() ;
		u_dir[2] = u.Z() ;
		u_dir[3] = dir[3] ;
	}

	glLightfv(light, GL_POSITION, pos) ;
	glLightfv(light, GL_AMBIENT,  lamb) ;
	glLightfv(light, GL_DIFFUSE,  color) ;

//	if (specularFlag) glLightfv(light, GL_SPECULAR, color) ;
//	else              glLightfv(light, GL_SPECULAR, spec) ;

	if (specularFlag)
	{
		GLfloat	specular[4] = { color[0] * specularFlag, color[1] * specularFlag, color[2] * specularFlag, 1.0f } ;
		glLightfv(light, GL_SPECULAR, specular) ;
	}
	else
		glLightfv(light, GL_SPECULAR, spec) ;


	// �ʒu����
	glLightf(light, GL_CONSTANT_ATTENUATION,  const_attn) ;
	glLightf(light, GL_LINEAR_ATTENUATION,    linear_attn) ;
	glLightf(light, GL_QUADRATIC_ATTENUATION, quad_attn) ;

	// �X�|�b�g�����p�����^
	glLightfv(light, GL_SPOT_DIRECTION, u_dir) ;
	glLightf(light, GL_SPOT_CUTOFF, spot_cutoff) ;
	glLightf(light, GL_SPOT_EXPONENT, spot_exp) ;
}


// ������`��
void DrawString(String& str, GLfloat x, GLfloat y, GLfloat z, void *font)
{
	glRasterPos3f(x, y, z) ;

	for (int i = 1 ; i <= str.Length() ; i ++)
		glutBitmapCharacter(font, str.Character(i)) ;
}

// ������`��
void DrawString(String& str, void *font)
{
	for (int i = 1 ; i <= str.Length() ; i ++)
		glutBitmapCharacter(font, str.Character(i)) ;
}

// �T���v���E�W�b�^�����i-0.5 �` +0.5 �͈̔́j
Vector2d *CreateSampleJitter(int sample, int hint)
{
	Vector2d *jitter ;

	switch (sample)
	{
	case 0:
	case 1:
	case 2:
		sample = 2 ;
		jitter = new Vector2d[sample] ;
		if (hint == HINT_ORDERED_GRID)
		{
			jitter[0](0.5f, 0.25f) ;
			jitter[1](0.5f, 0.75f) ;
		}
		else if (hint == HINT_SHEAR_GRID)
		{
			jitter[0](0.25f, 0.75f) ;
			jitter[1](0.75f, 0.25f) ;
		}
		else	// if (hint == HINT_NICEST_GRID)
		{
			jitter[0](0.25f, 0.75f) ;
			jitter[1](0.75f, 0.25f) ;
/*
			float r ;
			r = 27.0f ;	// from 3dfx paper
			float s = Sin(r) ;
			float c = Cos(r) ;
			float j[2][2] = { { 0.0f, -0.25f }, { 0.0f, 0.25f } } ;
			for (int i = 0 ; i < 2 ; i ++)
				jitter[i](Repeat(j[i][0] * c - j[i][1] * s + 0.5f), Repeat(j[i][0] * s + j[i][1] * c + 0.5f)) ;
*/
		}
		break ;
	case 3:
		jitter = new Vector2d[sample] ;
		{
			jitter[0](0.5033922635f, 0.8317967229f) ;
			jitter[1](0.7806016275f, 0.2504380877f) ;
			jitter[2](0.2261828938f, 0.4131553612f) ;
		}
		break ;
	case 4:
		jitter = new Vector2d[sample] ;
		if (hint == HINT_SHEAR_GRID)
		{
			jitter[0](0.375f, 0.25f) ;
			jitter[1](0.125f, 0.75f) ;
			jitter[2](0.875f, 0.25f) ;
			jitter[3](0.625f, 0.75f) ;
		}
		else
		{
			float r ;
			if (hint == HINT_ORDERED_GRID)
				r = 0.0f ;
			else
				r = 27.0f ;	// from 3dfx paper
//				r = 26.5650511770779893515721937204533 ;	// atan(0.5?)
//				r = 26.0f ;

			float s = Sin(r) ;
			float c = Cos(r) ;
			float j[4][2] = { { -0.25f, -0.25f }, { 0.25f, -0.25f }, { -0.25f, 0.25f }, { 0.25f, 0.25 } } ;
			for (int i = 0 ; i < 4 ; i ++)
				jitter[i](Repeat(j[i][0] * c - j[i][1] * s + 0.5f), Repeat(j[i][0] * s + j[i][1] * c + 0.5f)) ;
		}
		break ;
	case 5:
		jitter = new Vector2d[sample] ;
		jitter[0](0.5f, 0.5f) ;
		jitter[1](0.3f, 0.1f) ;
		jitter[2](0.7f, 0.9f) ;
		jitter[3](0.9f, 0.3f) ;
		jitter[4](0.1f, 0.7f) ;
		break ;

	case 6:
	case 7:
		jitter = new Vector2d[sample] ;
		jitter[0](0.4646464646f, 0.4646464646f) ;
		jitter[1](0.1313131313f, 0.7979797979f) ;
		jitter[2](0.5353535353f, 0.8686868686f) ;
		jitter[3](0.8686868686f, 0.5353535353f) ;
		jitter[4](0.7979797979f, 0.1313131313f) ;
		jitter[5](0.2020202020f, 0.2020202020f) ;
		{
			for (int i = 6 ; i < sample ; i ++)
				jitter[i]((GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX) ;
		}
		break ;

	case 8:
		jitter = new Vector2d[sample] ;
		jitter[0](0.5625f, 0.4375f) ;
		jitter[1](0.0625f, 0.9375f) ;
		jitter[2](0.3125f, 0.6875f) ;
		jitter[3](0.6875f, 0.8125f) ;
		jitter[4](0.8125f, 0.1875f) ;
		jitter[5](0.9375f, 0.5625f) ;
		jitter[6](0.4375f, 0.0625f) ;
		jitter[7](0.1875f, 0.3125f) ;
		break ;

	case 9:
	case 10:
	case 11:
		jitter = new Vector2d[sample] ;
		if (hint == HINT_SHEAR_GRID)
		{
			jitter[0](0.5f         , 0.5f         ) ;
			jitter[1](0.1666666666f, 0.9444444444f) ;
			jitter[2](0.5f         , 0.1666666666f) ;
			jitter[3](0.5f         , 0.8333333333f) ;
			jitter[4](0.1666666666f, 0.2777777777f) ;
			jitter[5](0.8333333333f, 0.3888888888f) ;
			jitter[6](0.1666666666f, 0.6111111111f) ;
			jitter[7](0.8333333333f, 0.7222222222f) ;
			jitter[8](0.8333333333f, 0.0555555555f) ;
		}
		else if (hint == HINT_ORDERED_GRID)
		{
/*
			jitter[0](0.1666666666f, 0.1666666666f) ;
			jitter[1](0.5f         , 0.1666666666f) ;
			jitter[2](0.8333333333f, 0.1666666666f) ;
			jitter[3](0.1666666666f, 0.5f         ) ;
			jitter[4](0.5f         , 0.5f         ) ;
			jitter[5](0.8333333333f, 0.5f         ) ;
			jitter[6](0.1666666666f, 0.8333333333f) ;
			jitter[7](0.5f         , 0.8333333333f) ;
			jitter[8](0.8333333333f, 0.8333333333f) ;
*/
			float r ;
			r = 0.0f ;
			float s = Sin(r) ;
			float c = Cos(r) ;
			float j[9][2] =
			{
				{ -0.3333333333f, -0.3333333333f }, { 0.0f, -0.3333333333f }, { 0.3333333333f, -0.3333333333f },
				{ -0.3333333333f,  0.0f          }, { 0.0f,  0.0f          }, { 0.3333333333f,  0.0f          },
				{ -0.3333333333f,  0.3333333333f }, { 0.0f,  0.3333333333f }, { 0.3333333333f,  0.3333333333f }
			} ;

			for (int i = 0 ; i < 9 ; i ++)
				jitter[i](Repeat(j[i][0] * c - j[i][1] * s + 0.5f), Repeat(j[i][0] * s + j[i][1] * c + 0.5f)) ;
		}
		else
		{
			float r ;
//			r = 12.0f ;
			r = 20.0f ;

			float s = Sin(r) ;
			float c = Cos(r) ;
			float j[9][2] =
			{
/*
				{ -0.3333333333f + 0.08f, -0.3333333333f - 0.08f }, { 0.0f + 0.08f, -0.3333333333f + 0.08f }, { 0.3333333333f + 0.08f, -0.3333333333f },
				{ -0.3333333333f - 0.08f,  0.0f          - 0.08f }, { 0.0f - 0.08f,  0.0f          + 0.08f }, { 0.3333333333f - 0.08f,  0.0f          },
				{ -0.3333333333f,  0.3333333333f - 0.08f }, { 0.0f,  0.3333333333f + 0.08f }, { 0.3333333333f,  0.3333333333f }
*/
				{ -0.3333333333f, -0.3333333333f }, { 0.0f, -0.3333333333f }, { 0.3333333333f, -0.3333333333f },
				{ -0.3333333333f,  0.0f          }, { 0.0f,  0.0f          }, { 0.3333333333f,  0.0f          },
				{ -0.3333333333f,  0.3333333333f }, { 0.0f,  0.3333333333f }, { 0.3333333333f,  0.3333333333f }
			} ;

			for (int i = 0 ; i < 9 ; i ++)
				jitter[i](Repeat(j[i][0] * c - j[i][1] * s + 0.5f), Repeat(j[i][0] * s + j[i][1] * c + 0.5f)) ;
		}

		{
			for (int i = 9 ; i < sample ; i ++)
				jitter[i]((GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX) ;
		}
		break ;

	case 12:
	case 13:
	case 14:
	case 15:
		jitter = new Vector2d[sample] ;
		if (hint == HINT_ORDERED_GRID)
		{
			for (int y = 0 ; y < 4 ; y ++)
			{
				for (int x = 0 ; x < 3 ; x ++)
				{
					int n = y * 3 + x ;
					jitter[n](x * 0.3333333333f + 0.1666666666f, y * 0.25f + 0.125f) ;
				}
			}
		}
		else
		{
			jitter[ 0](0.4166666666f, 0.625f) ;
			jitter[ 1](0.9166666666f, 0.875f) ;
			jitter[ 2](0.25f        , 0.375f) ;
			jitter[ 3](0.4166666666f, 0.125f) ;
			jitter[ 4](0.75f        , 0.125f) ;
			jitter[ 5](0.0833333333f, 0.125f) ;
			jitter[ 6](0.75f        , 0.625f) ;
			jitter[ 7](0.25f        , 0.875f) ;
			jitter[ 8](0.5833333333f, 0.375f) ;
			jitter[ 9](0.9166666666f, 0.375f) ;
			jitter[10](0.0833333333f, 0.625f) ;
			jitter[11](0.5833333333f, 0.875f) ;

			if (hint != HINT_SHEAR_GRID)
			{
				float r ;
				r = 12.0f ;

				float s = Sin(r) ;
				float c = Cos(r) ;
				for (int i = 0 ; i < 12 ; i ++)
				{
					jitter[i](Repeat((jitter[i].x - 0.5f) * c - (jitter[i].y - 0.5f) * s + 0.5f),
							  Repeat((jitter[i].x - 0.5f) * s + (jitter[i].y - 0.5f) * c + 0.5f)) ;
				}
			}
		}

		{
			for (int i = 12 ; i < sample ; i ++)
				jitter[i]((GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX) ;
		}
		break ;

	case 16:
		sample = 16 ;
		jitter = new Vector2d[sample] ;
		if (hint == HINT_ORDERED_GRID)
		{
			for (int y = 0 ; y < 4 ; y ++)
			{
				for (int x = 0 ; x < 4 ; x ++)
				{
					int n = y * 4 + x ;
					jitter[n](x * 0.25f + 0.125f, y * 0.25f + 0.125f) ;
				}
			}
		}
		else
		{
			jitter[ 0](0.375f, 0.4375f) ;
			jitter[ 1](0.625f, 0.0625f) ;
			jitter[ 2](0.875f, 0.1875f) ;
			jitter[ 3](0.125f, 0.0625f) ;
			jitter[ 4](0.375f, 0.6875f) ;
			jitter[ 5](0.875f, 0.4375f) ;
			jitter[ 6](0.625f, 0.5625f) ;
			jitter[ 7](0.375f, 0.9375f) ;
			jitter[ 8](0.625f, 0.3125f) ;
			jitter[ 9](0.125f, 0.5625f) ;
			jitter[10](0.125f, 0.8125f) ;
			jitter[11](0.375f, 0.1875f) ;
			jitter[12](0.875f, 0.9375f) ;
			jitter[13](0.875f, 0.6875f) ;
			jitter[14](0.125f, 0.3125f) ;
			jitter[15](0.625f, 0.8125f) ;

			if (hint != HINT_SHEAR_GRID)
			{
				float r ;
				r = 10.0f ;

				float s = Sin(r) ;
				float c = Cos(r) ;
				for (int i = 0 ; i < 16 ; i ++)
				{
					jitter[i](Repeat((jitter[i].x - 0.5f) * c - (jitter[i].y - 0.5f) * s + 0.5f),
							  Repeat((jitter[i].x - 0.5f) * s + (jitter[i].y - 0.5f) * c + 0.5f)) ;
				}
			}
		}
		break ;
	
	default:
		return NULL ;
	}

	for (int i = 0 ; i < sample ; i ++)
	{
		jitter[i].x -= 0.5f ;
		jitter[i].y -= 0.5f ;
	}

	return jitter ;
}

void DeleteSampleJitter(Vector2d *jitter)
{
	if (jitter) delete [] jitter ;
}

// ��ʊE�[�x�p�T���v���E�W�b�^�����i-1.0 �` +1.0 �͈̔́j
Vector2d *CreateSampleDepthOfFieldJitter(int sample)
{
	Vector2d *jitter ;

	switch (sample)
	{
	case 0:
	case 1:
	case 2:
		sample = 2 ;
		jitter = new Vector2d[sample] ;
		jitter[0](-1.0f, 0.0f) ;
		jitter[1]( 1.0f, 0.0f) ;
		break ;
	case 3:
		sample = 3 ;
		jitter = new Vector2d[sample] ;
		for (int i = 0 ; i < 3 ; i ++)
		{
			float rad = Rad(360.0f / 3 * i + 90.0f) ;
			jitter[i](cos(rad), sin(rad)) ;
		}
		break ;
	case 4:
		sample = 4 ;
		jitter = new Vector2d[sample] ;
		for (int i = 0 ; i < 4 ; i ++)
		{
			float rad = Rad(360.0f / 4 * i + 45.0f) ;
			jitter[i](cos(rad), sin(rad)) ;
		}
		break ;
	case 5:
		sample = 5 ;
		jitter = new Vector2d[sample] ;

		for (int i = 0 ; i < 4 ; i ++)
		{
			float rad = Rad(360.0f / 4 * i + 45.0f) ;
			jitter[i + 1](cos(rad), sin(rad)) ;
		}

		jitter[0](0.0f, 0.0f) ;
		break ;
	case 6:
	case 7:
		sample = 7 ;
		jitter = new Vector2d[sample] ;

		for (int i = 0 ; i < 6 ; i ++)
		{
			float rad = Rad(360.0f / 6 * i + 90.0f) ;
			jitter[i + 1](cos(rad), sin(rad)) ;
		}

		jitter[0](0.0f, 0.0f) ;
		break ;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		sample = 12 ;
		jitter = new Vector2d[sample] ;

		for (int i = 0 ; i < 8 ; i ++)
		{
			float rad = Rad(360.0f / 8 * i + 360.0 / 16.0f) ;
			jitter[i + 4](cos(rad), sin(rad)) ;
		}

		for (int i = 0 ; i < 4 ; i ++)
		{
			float rad = Rad(360.0f / 4 * i + 360.0 / 8.0f) ;
			jitter[i](cos(rad) * 0.48f, sin(rad) * 0.48f) ;
		}
		break ;
	
	default:
		return NULL ;
	}

	return jitter ;
}

Vector3d& Vector3d::Unit()
{
	GLfloat len = sqrt(X()*X() + Y()*Y() + Z()*Z()) ;
	if (len != 0.0f) *this /= len ;
	return *this ;
}

/*
const Vector3d Unit(Vector3d& vec)
{
	return (Vector3d(vec).Unit()) ;
}
*/
Vector3d Unit(const Vector3d& vec)
{
	return (Vector3d(vec).Unit()) ;
}

/*
const Vector3d UnitNormal(Vector3d& v1, Vector3d& v2)
{
	return Unit(v1 | v2) ;
}
const Vector3d UnitNormal(Vector3d& v1, const Vector3d& v2)
{
	return Unit(v1 | v2) ;
}
const Vector3d UnitNormal(const Vector3d& v1, Vector3d& v2)
{
	return Unit(v1 | v2) ;
}
*/
Vector3d UnitNormal(const Vector3d& v1, const Vector3d& v2)
{
	return Unit(v1 | v2) ;
}

/*
const Vector3d operator |(Vector3d& v1, Vector3d& v2)
{
	return Vector3d(v1.Y()*v2.Z() - v1.Z()*v2.Y(),
			v1.Z()*v2.X() - v1.X()*v2.Z(),
			v1.X()*v2.Y() - v1.Y()*v2.X()) ;
}
const Vector3d operator |(Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.Y()*v2.Z() - v1.Z()*v2.Y(),
			v1.Z()*v2.X() - v1.X()*v2.Z(),
			v1.X()*v2.Y() - v1.Y()*v2.X()) ;
}
const Vector3d operator |(const Vector3d& v1, Vector3d& v2)
{
	return Vector3d(v1.Y()*v2.Z() - v1.Z()*v2.Y(),
			v1.Z()*v2.X() - v1.X()*v2.Z(),
			v1.X()*v2.Y() - v1.Y()*v2.X()) ;
}
*/
Vector3d operator |(const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.Y()*v2.Z() - v1.Z()*v2.Y(),
			v1.Z()*v2.X() - v1.X()*v2.Z(),
			v1.X()*v2.Y() - v1.Y()*v2.X()) ;
}

// �s��ō��W�ϊ�
Vector3d& Vector3d::Transform(const GLfloat m[16])
{
	int      i ;
	Vector3d w = *this ;
	for (i = 0 ; i < 3 ; i ++)
		v[i] = m[i]*w.v[0] + m[4+i]*w.v[1] + m[8+i]*w.v[2] + m[12+i] ;
	return *this ;
}

// �s��ō��W�ϊ��i��]�^�g��k�������݂̂̉��Z �@���x�N�g���ϊ��p�j
Vector3d& Vector3d::Transform3x3(const GLfloat m[16])
{
	int      i ;
	Vector3d w = *this ;
	for (i = 0 ; i < 3 ; i ++)
		v[i] = m[i]*w.v[0] + m[4+i]*w.v[1] + m[8+i]*w.v[2] ;
	return *this ;
}

// Sphere Mapping �ϊ�
Vector3d& Vector3d::SphericalVertex()
{
	GLfloat m = 2.0f * sqrt(X()*X() + Y()*Y() + (Z() + 1.0f)*(Z() + 1.0f)) ;

	if (m != 0.0f)
	{
		X() = X() / m + 0.5f ;
		Y() = Y() / m + 0.5f ;
	}
	else
	{
		X() = 0.0f ;
		Y() = 0.5f ;
	}

	return *this ;
}

Vector3d SphericalVertex(Vector3d vec)
{
	return (vec.SphericalVertex()) ;
}


// �J���[�ƌ��Ȃ����ۂ̍ʓx��ω�
Vector3d& Vector3d::ChangeSaturation(float vividness)
{
	if (vividness == 1.0f) return *this ;

	// �ʓx�[���̏ꍇ�� RGB �P�x�i0�`255�j
	float bright = v[0] * GRAY_RATIO_R + v[1] * GRAY_RATIO_G + v[2] * GRAY_RATIO_B ;
	if (bright == 0.0f) return *this ;

	// �}�C�i�X�����̓`�F�b�N���邽�߂ɃN�����v
	v[0] = Clump((bright - v[0]) * (1.0f - vividness) + v[0], 0.0f, 100.0f) ;
	v[1] = Clump((bright - v[1]) * (1.0f - vividness) + v[1], 0.0f, 100.0f) ;
	v[2] = Clump((bright - v[2]) * (1.0f - vividness) + v[2], 0.0f, 100.0f) ;

	// ���X�� bright �̖��邳�ɕ␳
	float ratio = v[0] * GRAY_RATIO_R + v[1] * GRAY_RATIO_G + v[2] * GRAY_RATIO_B ;
	ratio /= bright ;
	v[0] *= ratio ;
	v[1] *= ratio ;
	v[2] *= ratio ;

	return *this ;
}

Vector3d ChangeSaturation(Vector3d src, float vividness)
{
	return (src.ChangeSaturation(vividness)) ;
}


ostream& operator <<(ostream& os, const Vector3d& vec)
{
	os << vec.X() << ", " << vec.Y() << ", " << vec.Z() ;
	return os ;
}


Object& Object::MakePolygon(int polNo, int v1, int v2, int v3, const GLfloat data[][3], const GLfloat m[16])
{
	polygon[polNo].vertex[0].X() = data[v1][0] ;
	polygon[polNo].vertex[0].Y() = data[v1][1] ;
	polygon[polNo].vertex[0].Z() = data[v1][2] ;
	if (m) polygon[polNo].vertex[0].Transform(m) ;

	polygon[polNo].vertex[1].X() = data[v2][0] ;
	polygon[polNo].vertex[1].Y() = data[v2][1] ;
	polygon[polNo].vertex[1].Z() = data[v2][2] ;
	if (m) polygon[polNo].vertex[1].Transform(m) ;

	polygon[polNo].vertex[2].X() = data[v3][0] ;
	polygon[polNo].vertex[2].Y() = data[v3][1] ;
	polygon[polNo].vertex[2].Z() = data[v3][2] ;
	if (m) polygon[polNo].vertex[2].Transform(m) ;

	polygon[polNo].pNormal   = polygon[polNo].normal[0] =
	polygon[polNo].normal[1] = polygon[polNo].normal[2] =
		UnitNormal(polygon[polNo].vertex[1] - polygon[polNo].vertex[0],
			   polygon[polNo].vertex[2] - polygon[polNo].vertex[1]) ;

	return *this ;
}

Object& Object::MakePolygon(int polNo, int v1, int v2, int v3, int v4, const GLfloat data[][3], const GLfloat m[16])
{
	polygon[polNo].vertex[0].X() = data[v1][0] ;
	polygon[polNo].vertex[0].Y() = data[v1][1] ;
	polygon[polNo].vertex[0].Z() = data[v1][2] ;
	if (m) polygon[polNo].vertex[0].Transform(m) ;

	polygon[polNo].vertex[1].X() = data[v2][0] ;
	polygon[polNo].vertex[1].Y() = data[v2][1] ;
	polygon[polNo].vertex[1].Z() = data[v2][2] ;
	if (m) polygon[polNo].vertex[1].Transform(m) ;

	polygon[polNo].vertex[2].X() = data[v3][0] ;
	polygon[polNo].vertex[2].Y() = data[v3][1] ;
	polygon[polNo].vertex[2].Z() = data[v3][2] ;
	if (m) polygon[polNo].vertex[2].Transform(m) ;

	polygon[polNo].vertex[3].X() = data[v4][0] ;
	polygon[polNo].vertex[3].Y() = data[v4][1] ;
	polygon[polNo].vertex[3].Z() = data[v4][2] ;
	if (m) polygon[polNo].vertex[3].Transform(m) ;

	polygon[polNo].pNormal   = polygon[polNo].normal[0] =
	polygon[polNo].normal[1] = polygon[polNo].normal[2] =
	polygon[polNo].normal[3] = 
		UnitNormal(polygon[polNo].vertex[1] - polygon[polNo].vertex[0],
			   polygon[polNo].vertex[2] - polygon[polNo].vertex[1]) ;

	return *this ;
}

Object& Object::AverageNormal(int pNo, int vNo, int pNo1, int pNo2, int pNo3, int pNo4, int pNo5, int pNo6)
{
	Vector3d sum = polygon[pNo1].pNormal + polygon[pNo2].pNormal ;

	if (pNo3 >= 0) sum += polygon[pNo3].pNormal ;
	if (pNo4 >= 0) sum += polygon[pNo4].pNormal ;
	if (pNo5 >= 0) sum += polygon[pNo5].pNormal ;
	if (pNo6 >= 0) sum += polygon[pNo6].pNormal ;

	polygon[pNo].normal[vNo] = Unit(sum) ;

	return *this ;
}

Object& Object::DrawTriangle(int p, int depth, int average, int flatFlag, int normalFlag,
							 int target0, float *s0, float *t0,
							 int target1, float *s1, float *t1,
							 int target2, float *s2, float *t2,
							 int target3, float *s3, float *t3)
{
	int      i, pFlag = TRUE ;	// �@�����L�t���O
	GLfloat vtx[6][3] ;
	Object   obj(5) ;

	// �t���b�g�w��܂��́A�e���_�̖@�����S�ē����ꍇ
	if (flatFlag || (polygon[p].normal[0] == polygon[p].normal[1] &&
					 polygon[p].normal[1] == polygon[p].normal[2])) pFlag = FALSE ;

	if (depth <= 0)
	{
		if (flatFlag)	// �t���b�g���́ADrawTriangles() �ŁAglBegin() �ς�
		{
			// 99-09-23		// �t���b�g�Œ��_���ω��Ȃ��̏ꍇ�ADrawTriangles() �� glNormal �ς�
			if (average && normalFlag) glNormal3fv(polygon[p].normal[0].v) ;

			Vertex3fvWithTexAxis(polygon[p].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			Vertex3fvWithTexAxis(polygon[p].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			Vertex3fvWithTexAxis(polygon[p].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
		}
		else	// �t���b�g�w��Ȃ����iglBegin(), glNormal() �K�v�j
		{
			// �����܂ŗ���̂́A�@�����S�ē����|���S����
			// ���߂��� depth = 0 �Ɏw�肳�ꂽ����
			// �@�����Ⴄ�ꍇ�i�X���[�Y�V�F�[�f�B���O�p�j�́A��{�I�� depth == 1 �̎��ɏ����j
			glBegin(GL_TRIANGLES) ;
			{
				if (normalFlag) glNormal3fv(polygon[p].normal[0].v) ;
				Vertex3fvWithTexAxis(polygon[p].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				// �ŏ����� depth == 0 �̂��̂́A�@�������_���ɈႤ�\������
				if (pFlag && normalFlag) glNormal3fv(polygon[p].normal[1].v) ;
				Vertex3fvWithTexAxis(polygon[p].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (pFlag && normalFlag) glNormal3fv(polygon[p].normal[2].v) ;
				Vertex3fvWithTexAxis(polygon[p].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
			glEnd() ;
		}
		return *this ;
	}

	// �|���S���ו�������

	VectorToArray(vtx[0], polygon[p].vertex[0]) ;
	VectorToArray(vtx[1], polygon[p].vertex[1]) ;
	VectorToArray(vtx[2], polygon[p].vertex[2]) ;

	if (average)
	{
		float a3 = (polygon[p].vertex[0].Abs() + polygon[p].vertex[1].Abs()) / 2.0f,
			   a4 = (polygon[p].vertex[1].Abs() + polygon[p].vertex[2].Abs()) / 2.0f,
			   a5 = (polygon[p].vertex[2].Abs() + polygon[p].vertex[0].Abs()) / 2.0f ;

		VectorToArray(vtx[3], Unit(polygon[p].vertex[0] + polygon[p].vertex[1]) * a3) ;
		VectorToArray(vtx[4], Unit(polygon[p].vertex[1] + polygon[p].vertex[2]) * a4) ;
		VectorToArray(vtx[5], Unit(polygon[p].vertex[2] + polygon[p].vertex[0]) * a5) ;
	}
	else
	{

		VectorToArray(vtx[3], (polygon[p].vertex[0] + polygon[p].vertex[1]) / 2.0f) ;
		VectorToArray(vtx[4], (polygon[p].vertex[1] + polygon[p].vertex[2]) / 2.0f) ;
		VectorToArray(vtx[5], (polygon[p].vertex[2] + polygon[p].vertex[0]) / 2.0f) ;
	}

	obj.MakePolygon(0, 0,3,5, vtx) ;
	obj.MakePolygon(1, 3,1,4, vtx) ;
	obj.MakePolygon(2, 5,4,2, vtx) ;
	obj.MakePolygon(3, 3,4,5, vtx) ;

	// �����O�̃|���S���̖@�������_���ɈႤ�ꍇ�͕��ω������@�����v�Z
	// �����������ꍇ�̓|���S���������Ɍv�Z���ꂽ�@�������̂܂܎g�p
	if (pFlag)
	{
		obj.polygon[0].normal[0] = polygon[p].normal[0] ;
		obj.polygon[1].normal[1] = polygon[p].normal[1] ;
		obj.polygon[2].normal[2] = polygon[p].normal[2] ;

		obj.polygon[0].normal[1] = obj.polygon[1].normal[0] = obj.polygon[3].normal[0] =
			Unit(polygon[p].normal[0] + polygon[p].normal[1]) ;
		obj.polygon[1].normal[2] = obj.polygon[2].normal[1] = obj.polygon[3].normal[1] =
			Unit(polygon[p].normal[1] + polygon[p].normal[2]) ;
		obj.polygon[0].normal[2] = obj.polygon[2].normal[0] = obj.polygon[3].normal[2] =
			Unit(polygon[p].normal[2] + polygon[p].normal[0]) ;
	}

	// depth == 1 �ŁAflatFlag �w�肪�Ȃ�
	// �Ȃ���������̖@�����ׂ̃|���S���Ƌ��L���Ă���ꍇ�i!average || pFlag�j
	if (depth == 1 && !flatFlag && (!average || pFlag))
	{
// EXT_vertex_array ���T�|�[�g����Ă��炸�A
// OpenGL-1.0 �܂��� DONOT_USE_GL_1_1_VERTEX_ARRAY ����`����Ă���ꍇ
//#if !defined GL_EXT_vertex_array && (!defined GL_VERSION_1_1 || defined DONOT_USE_GL_1_1_VERTEX_ARRAY)

		if (!pFlag)
		{
			glBegin(GL_TRIANGLES) ;

			for (int p = 0 ; p < 4 ; p ++)
			{
				if (normalFlag) glNormal3fv(obj.polygon[p].normal[0].v) ;

				Vertex3fvWithTexAxis(obj.polygon[p].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
				Vertex3fvWithTexAxis(obj.polygon[p].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				// �ŏ��̒��_�ȊO�̖@���́A�@���̕��ω����s���Ă��Ȃ��ꍇ�͕K�v�Ȃ�
//				if (pFlag) glNormal3fv(obj.polygon[p].normal[1].v) ;
				Vertex3fvWithTexAxis(obj.polygon[p].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				// �ŏ��̒��_�ȊO�̖@���́A�@���̕��ω����s���Ă��Ȃ��ꍇ�͕K�v�Ȃ�
//				if (pFlag) glNormal3fv(obj.polygon[p].normal[2].v) ;
				Vertex3fvWithTexAxis(obj.polygon[p].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
			glEnd() ;
		}
		else	// if (pFlag)
		{
			// GL_TRIANGLE_STRIP �łR���i0, 3, 1�j+ GL_TRIANGLES �łP���i2�j

			glBegin(GL_TRIANGLE_STRIP) ;
			{
				if (normalFlag) glNormal3fv(obj.polygon[1].normal[1].v) ;
				Vertex3fvWithTexAxis(obj.polygon[1].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[1].normal[2].v) ;
				Vertex3fvWithTexAxis(obj.polygon[1].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[1].normal[0].v) ;
				Vertex3fvWithTexAxis(obj.polygon[1].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[0].normal[2].v) ;
				Vertex3fvWithTexAxis(obj.polygon[0].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[0].normal[0].v) ;
				Vertex3fvWithTexAxis(obj.polygon[0].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
			glEnd() ;

			glBegin(GL_TRIANGLES) ;
			{
				if (normalFlag) glNormal3fv(obj.polygon[2].normal[0].v) ;
				Vertex3fvWithTexAxis(obj.polygon[2].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[2].normal[1].v) ;
				Vertex3fvWithTexAxis(obj.polygon[2].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(obj.polygon[2].normal[2].v) ;
				Vertex3fvWithTexAxis(obj.polygon[2].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
			glEnd() ;
		}
/*
		// GL_TRIANGLE_STRIP �łR���i0, 3, 1�j+ GL_TRIANGLES �łP���i2�j

		glBegin(GL_TRIANGLE_STRIP) ;

			glNormal3fv(obj.polygon[1].normal[1].v) ;
			glVertex3fv(polygon[1].vertex[1].v) ;

			// �ŏ��̒��_�ȊO�̖@���́A�@���̕��ω����s���Ă��Ȃ��ꍇ�͕K�v�Ȃ�
			if (pFlag) glNormal3fv(obj.polygon[1].normal[2].v) ;
			glVertex3fv(obj.polygon[1].vertex[2].v) ;

			if (pFlag) glNormal3fv(obj.polygon[0].normal[1].v) ;
			glVertex3fv(obj.polygon[0].vertex[1].v) ;

			if (pFlag) glNormal3fv(obj.polygon[0].normal[2].v) ;
			glVertex3fv(obj.polygon[0].vertex[2].v) ;

			if (pFlag) glNormal3fv(obj.polygon[0].normal[0].v) ;
			glVertex3fv(obj.polygon[0].vertex[0].v) ;

		glEnd() ;

		glBegin(GL_TRIANGLES) ;

			glNormal3fv(obj.polygon[0].normal[0].v) ;
			glVertex3fv(obj.polygon[0].vertex[0].v) ;

			if (pFlag) glNormal3fv(obj.polygon[0].normal[1].v) ;
			glVertex3fv(obj.polygon[0].vertex[1].v) ;

			if (pFlag) glNormal3fv(obj.polygon[0].normal[2].v) ;
			glVertex3fv(obj.polygon[0].vertex[2].v) ;

		glEnd() ;
*/


/*
#else // OpenGL-1.1�A�܂��� GL_EXT_vertex_array ���g�p�\�ȏꍇ

		Vector3d normals[6] ;

		normals[0] = obj.polygon[0].normal[0] ;
		normals[1] = obj.polygon[1].normal[1] ;
		normals[2] = obj.polygon[2].normal[2] ;
		normals[3] = obj.polygon[0].normal[1] ;
		normals[4] = obj.polygon[1].normal[2] ;
		normals[5] = obj.polygon[0].normal[2] ;

// OpenGL-1.0 �� GL_EXT_vertex_array ���T�|�[�g����Ă��邩�A
// DONOT_USE_GL_1_1_VERTEX_ARRAY ����`����Ă���ꍇ
#if (!defined GL_VERSION_1_1 && defined GL_EXT_vertex_array) || defined DONOT_USE_GL_1_1_VERTEX_ARRAY

		glEnable(GL_VERTEX_ARRAY_EXT) ;
		glEnable(GL_NORMAL_ARRAY_EXT) ;

DONOT_USE_GL_1_1_VERTEX_ARRAY;

		glVertexPointerEXT(3, GL_FLOAT, 0, 6, (GLfloat *)(&vtx[0][0])) ;
		glNormalPointerEXT(GL_FLOAT, sizeof(Vector3d), 6, (GLfloat *)(&normals[0].v[0])) ;

		glBegin(GL_TRIANGLES) ;
			glArrayElement(0) ;
			glArrayElement(3) ;
			glArrayElement(5) ;

			glArrayElement(3) ;
			glArrayElement(1) ;
			glArrayElement(4) ;

			glArrayElement(5) ;
			glArrayElement(4) ;
			glArrayElement(2) ;

			glArrayElement(3) ;
			glArrayElement(4) ;
			glArrayElement(5) ;
		glEnd() ;

#else

		GLubyte indices[] = { 0, 3, 5,  3, 1, 4,  5, 4, 2,  3, 4, 5 } ;

		glEnableClientState(GL_VERTEX_ARRAY) ;
		glEnableClientState(GL_NORMAL_ARRAY) ;

		glVertexPointer(3, GL_FLOAT, 0, (GLfloat *)(&vtx[0][0])) ;
		glNormalPointer(GL_FLOAT, sizeof(Vector3d), (GLfloat *)(&normals[0].v[0])) ;

		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices) ;

#endif
#endif
*/
		return *this ;
	}

//	for (i = 0 ; i < 4 ; i ++) obj.DrawTriangle(i, depth - 1, average, flatFlag, normalFlag, s, t) ;

	for (i = 0 ; i < 4 ; i ++)
		obj.DrawTriangle(i, depth - 1, average, flatFlag, normalFlag,
						 target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

	return *this ;
}

// flatFlag �c �t���b�g�V�F�[�f�B���O�Ɖ���
//		�e�|���S�����\�����钸�_���S�Ă��Ȃ��@���������̉��肵�ĕ`��
// normalFlag
//		FALSE �̎��́A�@���̐ݒ����؍s��Ȃ�
Object& Object::DrawTriangles(int depth, int average, int flatFlag, int normalFlag,
							  int target0, float *s0, float *t0,
							  int target1, float *s1, float *t1,
							  int target2, float *s2, float *t2,
							  int target3, float *s3, float *t3)
{
	int i ;

	// �ו����Ȃ��̏ꍇ�́A���ω����Ȃ�
	if (depth <= 0) average = FALSE ;

	// �t���b�g�V�F�[�f�B���O�Ɖ��肳�ꂽ�ꍇ�i�܂�e�|���S���̒��_���̖@�������ׂē����j
	if (flatFlag)
	{
		glBegin(GL_TRIANGLES) ;

			for (i = 0 ; i < nPolygons ; i ++)
			{
				// �t���b�g�V�F�[�f�B���O�Œ��_���W�𕽋ω����Ȃ��ꍇ�́A�ŏ��ɖ@���̂O�Ԃ��w��
				if (!average && normalFlag) glNormal3fv(polygon[i].normal[0].v) ;

				// �O�p�|���S���`��
				DrawTriangle(i, depth, average, TRUE /* flatFlag */, normalFlag,
							 target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}

		glEnd() ;
	}
	else	// �ʏ�̕��������̏ꍇ
	{
		for (i = 0 ; i < nPolygons ; i ++)
			DrawTriangle(i, depth, average, flatFlag /* FALSE */, normalFlag,
						 target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
	}

	return *this ;
}


RollingObject& RollingObject::MakeRollingPolygons(int u, int v, GLfloat data[][2], GLfloat x, GLfloat y, GLfloat z)
{
	int      i ;
	GLfloat (*vertex)[3] ;
	if (u < 3 || v < 2) return *this ;

	vertex = new GLfloat[v * 2][3] ;

	uDiv = u ;
	vDiv = v ;

	if (data[    0][0] == 0.0f) fType = 1 ;
	else                       fType = 0 ;
	if (data[v - 1][0] == 0.0f) eType = 1 ;
	else                       eType = 0 ;

	for (i = 0 ; i < u ; i ++)
	{
		int    j, pNo = i * (v - 1) ;
		float rad = 2.0f * PAI / u * i, pRad = 2.0f * PAI / u * (i - 1) ;

		for (j = 0 ; j < v ; j ++)
		{
			vertex[j * 2    ][0] = data[j][0] * x * sin( rad) ;
			vertex[j * 2    ][1] = data[j][0] * y * cos( rad) ;
			vertex[j * 2    ][2] = data[j][1] * z ;

			vertex[j * 2 + 1][0] = data[j][0] * x * sin(pRad) ;
			vertex[j * 2 + 1][1] = data[j][0] * y * cos(pRad) ;
			vertex[j * 2 + 1][2] = data[j][1] * z ;
		}

		if (fType) MakePolygon(pNo        , 0          , 2          , 3        , vertex) ;
		if (eType) MakePolygon(pNo + v - 2, (v - 2) * 2, (v - 1) * 2, v * 2 - 3, vertex) ;

		for (j = fType ; j < v - 1 - eType ; j ++)
			MakePolygon(pNo + j, j * 2, j * 2 + 2, j * 2 + 3, j * 2 + 1, vertex) ;
	}

	delete [] vertex ;
	return *this ;
}

int RollingObject::VFlag(int v, int ud, int vFlag, int vFlags[][2])
{
	if (vFlag)
	{
		if (vFlags) return vFlags[v][ud] ;
		else        return TRUE ;
	}
	else            return FALSE ;
}

RollingObject& RollingObject::AverageNormals(int uFlag, int vFlag, int vFlags[][2]) //, int vNo)
{
	int u ;
	if (uDiv < 3 || vDiv < 2) return *this ;

	for (u = 0 ; u < uDiv ; u ++)
	{
		int v, pNo = u * (vDiv - 1), pPNo = (u - 1) * (vDiv - 1), nPNo = (u + 1) * (vDiv - 1) ;

		if      (u ==        0) pPNo = (uDiv - 1) * (vDiv - 1) ;
		else if (u == uDiv - 1) nPNo = 0 ;

		for (v = 0 /*vNo*/ ; v < vDiv - 1 ; v ++)
		{
			int p = pNo + v, pp = pPNo + v, np = nPNo + v ;

			// Vertex 0
			if (!v && uFlag)
			{
				if (fType) AverageNormal(p, 0, p,np, pp) ;
				else       AverageNormal(p, 0, p,np) ;
			}
			else if (uFlag)
			{
				if (VFlag(v, 0, vFlag, vFlags)) AverageNormal(p, 0, p,np,p-1,np-1) ;
				else                            AverageNormal(p, 0, p,np) ;
			}
			else if (!uFlag && VFlag(v, 0, vFlag, vFlags)) AverageNormal(p, 0, p,p-1) ;

			// Vertex 1
			if (v == vDiv - 2 && uFlag)
			{
				if (eType) AverageNormal(p, 1, p,np,pp) ;
				else       AverageNormal(p, 1, p,np) ;
			}
			else if (uFlag)
			{
				if (VFlag(v, 1, vFlag, vFlags)) AverageNormal(p, 1, p,np,p+1,np+1) ;
				else                            AverageNormal(p, 1, p,np) ;
			}
			else if (!uFlag && VFlag(v, 1, vFlag, vFlags)) AverageNormal(p, 1, p,p+1) ;

			// Vertex 2
			if (v == vDiv - 2 && uFlag)
			{
				if (eType && VFlag(v, 1, vFlag, vFlags)) AverageNormal(p, 2, p,pp,p-1,pp-1) ;
				else                                     AverageNormal(p, 2, p,pp) ;
			}
			else if (uFlag)
			{
				if (VFlag(v, 1, vFlag, vFlags)) AverageNormal(p, 2, p,pp,p+1,pp+1) ;
				else                            AverageNormal(p, 2, p,pp) ;
			}
			else if (!uFlag && VFlag(v, 1, vFlag, vFlags)) AverageNormal(p, 2, p,p+1) ;

			// Vertex 3
			if (!v && uFlag) { if (!fType) AverageNormal(p, 3, p,pp) ; }
			else if (uFlag)
			{
				if (VFlag(v, 0, vFlag, vFlags)) AverageNormal(p, 3, p,pp,p-1,pp-1) ;
				else                            AverageNormal(p, 3, p,pp) ;
			}
			else if (!uFlag && VFlag(v, 0, vFlag, vFlags)) AverageNormal(p, 3, p,p-1) ;
		}
	}
	return *this ;
}

RollingObject& RollingObject::TopNormal(GLfloat x, GLfloat y, GLfloat z)
{
	int u ;

	if (!fType)
	{
		for (u = 0 ; u < uDiv ; u ++)
		{
			int pNo = u * (vDiv - 1) ;

			polygon[pNo].normal[0].v[0] = x ;
			polygon[pNo].normal[0].v[1] = y ;
			polygon[pNo].normal[0].v[2] = z ;

			polygon[pNo].normal[3].v[0] = x ;
			polygon[pNo].normal[3].v[1] = y ;
			polygon[pNo].normal[3].v[2] = z ;
		}
	}
	else
	{
		for (u = 0 ; u < uDiv ; u ++)
		{
			int pNo = u * (vDiv - 1) ;

			polygon[pNo].normal[0].v[0] = x ;
			polygon[pNo].normal[0].v[1] = y ;
			polygon[pNo].normal[0].v[2] = z ;
		}
	}

	return *this ;
}

RollingObject& RollingObject::BottomNormal(GLfloat x, GLfloat y, GLfloat z)
{
	int u ;

	if (!eType)
	{
		for (u = 0 ; u < uDiv ; u ++)
		{
			int pNo = u * (vDiv - 1) + vDiv - 2 ;

			polygon[pNo].normal[1].v[0] = x ;
			polygon[pNo].normal[1].v[1] = y ;
			polygon[pNo].normal[1].v[2] = z ;

			polygon[pNo].normal[2].v[0] = x ;
			polygon[pNo].normal[2].v[1] = y ;
			polygon[pNo].normal[2].v[2] = z ;
		}
	}
	else
	{
		for (u = 0 ; u < uDiv ; u ++)
		{
			int pNo = u * (vDiv - 1) + vDiv - 2 ;

			polygon[pNo].normal[1].v[0] = x ;
			polygon[pNo].normal[1].v[1] = y ;
			polygon[pNo].normal[1].v[2] = z ;
		}
	}

	return *this ;
}


// ��]�̃I�u�W�F�N�g�̕`��i�@���A���_���W�j
// normalFlag �� FALSE �̎��́A�@������؃Z�b�g���Ȃ�
void RollingObject::DrawObject(int normalFlag,
							   int target0, float *s0, float *t0,
							   int target1, float *s1, float *t1,
							   int target2, float *s2, float *t2,
							   int target3, float *s3, float *t3)
{
	int u, v ;

	for (v = 0 ; v < vDiv - 1 ; v ++)
	{
		if (v == 0 && fType) // �Ă��؂�̎O�p�`
		{
			int pNo = (uDiv - 1) * (vDiv - 1) ;

			glBegin(GL_TRIANGLE_FAN) ;
			{
				if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				for (u = uDiv - 1 ; u >= 0 ; u --)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

					pNo -= vDiv - 1 ;
				}
			}
			glEnd() ;
		}
		else if (v == vDiv - 2 && eType) // ��̎O�p�`
		{
			int pNo = v ;

			glBegin(GL_TRIANGLE_FAN) ;
			{
				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				for (u = 0 ; u < uDiv ; u ++)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

					pNo += vDiv - 1 ;
				}
			}
			glEnd() ;
		}
		else  // �ʏ�̎l�p�`
		{
			int pNo = v ;

			glBegin(GL_QUAD_STRIP) ;
			{
				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[3].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[3].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

				for (u = 0 ; u < uDiv ; u ++)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

					pNo += vDiv - 1 ;
				}
			}
			glEnd() ;
		}
	}
}


// 2000.08
// ���C���f�N�X�t���ŕ`��
// �c�����ɕ`�悵�AstartAlpha ���珇�Ƀ��l���Z�b�g
// �F�� color ���g�p
// glColor4fv ���g�p���邽��
// �\�� glColorMaterial ����K�؂ɃZ�b�g���Ă����v����
// normalFlag �� FALSE �̎��́A�@������؃Z�b�g���Ȃ�
void RollingObject::DrawObjectWithAlphaIndex(int normalFlag, const Vector3d& color, int startAlpha, float alphaScale,
											 float *s, float *t)
{
	GLfloat acolor[4] = { color.v[0], color.v[1], color.v[2], 0.0f } ;

	int strip = FALSE ;

	if (!normalFlag)
		strip = TRUE ;
	else
	{
		// V �����̖@���𒲍�
		// ���ׂĂ����L���_�ł���΃X�g���b�v��
		int i ;
		for (i = 0 ; i < vDiv - 2 ; i ++)
		{
			int pNo = i ;
			if (polygon[pNo].normal[1] != polygon[pNo + 1].normal[0])
				break ;
		}

		if (i == vDiv - 2)
			strip = TRUE ;
	}

//	cout << "strip: " << strip << endl ;

	for (int i = 0 ; i < uDiv ; i ++)
	{
		acolor[3] = (startAlpha + i) * alphaScale ;
		glColor4fv(acolor) ;

		int pNo, j ;

		if (strip)
		{
			glBegin(GL_QUAD_STRIP) ;
			{
				for (j = 0 ; j < vDiv - 1 ; j ++)
				{
					pNo = i * (vDiv - 1) + j ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[3].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[3].v, 0, s, t) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, 0, s, t) ;
				}

//				pNo ++ ;
				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, 0, s, t) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, 0, s, t) ;

			}
			glEnd() ;
		}
		else
		{
			glBegin(GL_QUADS) ;
			{
				for (j = 0 ; j < vDiv - 1 ; j ++)
				{
					pNo = i * (vDiv - 1) + j ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, 0, s, t) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, 0, s, t) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, 0, s, t) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[3].v) ;
					Vertex3fvWithTexAxis(polygon[pNo].vertex[3].v, 0, s, t) ;
				}
			}
			glEnd() ;
/*
			pNo ++ ;
			glBegin(GL_TRIANGLES) ;
			{
				if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[0].v, 0, s, t) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[1].v, 0, s, t) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				Vertex3fvWithTexAxis(polygon[pNo].vertex[2].v, 0, s, t) ;
			}
			glEnd() ;
*/
		}
	}
}


PositivePolyhedron& PositivePolyhedron::Smooth()
{
	int i, j ;
	
	for (i = 0 ; i < nPolygons ; i ++)
		for (j = 0 ; j < 3 ; j ++)
			polygon[i].normal[j] = Unit(polygon[i].vertex[j]) ;

	return *this ;
}


Octahedron& Octahedron::Make(GLfloat x, GLfloat y, GLfloat z, int d, int a, int smooth)
{
	int      i ;
	GLfloat m[] = {   x, 0.0f, 0.0f, 0.0f,
					 0.0f,   y, 0.0f, 0.0f,
					 0.0f, 0.0f,   z, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f } ;

	if (d >= 0) depth   = d ;
	if (a >= 0) average = a ;

	NPolygons(8) ;
	for (i = 0 ; i < 8 ; i ++) MakePolygon(i, o_o[i][0],o_o[i][1],o_o[i][2], o_v, m) ;

	if (smooth) Smooth() ;

	return *this ;
}

void Octahedron::DrawPolyhedron(GLfloat r, int normalFlag,
								int target0, float *s0, float *t0,
								int target1, float *s1, float *t1,
								int target2, float *s2, float *t2,
								int target3, float *s3, float *t3)
{
	GLfloat v[6][3] ;

	for (int i = 0 ; i < 6 ; i ++)
	{
		v[i][0] = o_v[i][0] * r ;
		v[i][1] = o_v[i][1] * r ;
		v[i][2] = o_v[i][2] * r ;
	}

	Octahedron obj(r, r, r) ;
/*
#if defined GL_VERSION_1_1 && !defined DONOT_USE_GL_1_1_VERTEX_ARRAY
	glEnableClientState(GL_VERTEX_ARRAY) ;
	glVertexPointer(3, GL_FLOAT, 0, (GLfloat *)(&v[0][0])) ;
#endif
*/

	if (normalFlag)
	{
		glBegin(GL_TRIANGLES) ;
		{
			for (int i = 0 ; i < 8 ; i ++)
			{
				if (normalFlag) glNormal3fv(obj.polygon[i].normal[0].v) ;
/*
#if defined GL_VERSION_1_1 && !defined DONOT_USE_GL_1_1_VERTEX_ARRAY
				glArrayElement(o_o[i][0]) ;
				glArrayElement(o_o[i][1]) ;
				glArrayElement(o_o[i][2]) ;
#else
*/

				Vertex3fvWithTexAxis(v[o_o[i][0]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
				Vertex3fvWithTexAxis(v[o_o[i][1]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
				Vertex3fvWithTexAxis(v[o_o[i][2]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

/*
#endif
*/
			}
		}
		glEnd() ;
	}
	else
	{
		// �@�����s�v�̏ꍇ�� FAN �ōœK��
		glBegin(GL_TRIANGLE_FAN) ;
		{
			// �㒸�_
			Vertex3fvWithTexAxis(v[4], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

			for (int i = 0 ; i < 5 ; i ++)
			{
				int n = i % 4 ;
				Vertex3fvWithTexAxis(v[n], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
		}
		glEnd() ;

		glBegin(GL_TRIANGLE_FAN) ;
		{
			// �����_
			Vertex3fvWithTexAxis(v[5], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

			for (int i = 0 ; i < 5 ; i ++)
			{
				int n = (4 - i) % 4 ;
				Vertex3fvWithTexAxis(v[n], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
		}
		glEnd() ;
	}
}

GLfloat Octahedron::o_v[][3] = { {  0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, {  0.0f,-1.0f, 0.0f },
								 {  1.0f, 0.0f, 0.0f }, {  0.0f, 0.0f, 1.0f }, {  0.0f, 0.0f,-1.0f } } ;

int Octahedron::o_o[][3] = { { 0, 1, 4 }, { 1, 2, 4 }, { 2, 3, 4 }, { 3, 0, 4 },
							 { 1, 0, 5 }, { 2, 1, 5 }, { 3, 2, 5 }, { 0, 3, 5 } } ;


Icosahedron& Icosahedron::Make(GLfloat x, GLfloat y, GLfloat z, int d, int a, int smooth)
{
	int      i ;
	GLfloat m[] = {   x, 0.0f, 0.0f, 0.0f,
					 0.0f,   y, 0.0f, 0.0f,
					 0.0f, 0.0f,   z, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f } ;

	if (d >= 0) depth   = d ;
	if (a >= 0) average = a ;

	NPolygons(20) ;
	for (i = 0 ; i < 20 ; i ++) MakePolygon(i, i_o[i][2],i_o[i][1],i_o[i][0], i_v, m) ;

	if (smooth) Smooth() ;

	return *this ;
}

void Icosahedron::DrawPolyhedron(GLfloat r, int normalFlag,
								 int target0, float *s0, float *t0,
								 int target1, float *s1, float *t1,
								 int target2, float *s2, float *t2,
								 int target3, float *s3, float *t3)
{
	GLfloat v[12][3] ;

	for (int i = 0 ; i < 12 ; i ++)
	{
		v[i][0] = i_v[i][0] * r ;
		v[i][1] = i_v[i][1] * r ;
		v[i][2] = i_v[i][2] * r ;
	}

	Icosahedron obj(r, r, r) ;
/*
#if defined GL_VERSION_1_1 && !defined DONOT_USE_GL_1_1_VERTEX_ARRAY
	glEnableClientState(GL_VERTEX_ARRAY) ;
	glVertexPointer(3, GL_FLOAT, 0, (GLfloat *)(&v[0][0])) ;
#endif
*/

	if (normalFlag)
	{
		glBegin(GL_TRIANGLES) ;
		{
			for (int i = 0 ; i < 20 ; i ++)
			{
				if (normalFlag) glNormal3fv(obj.polygon[i].normal[0].v) ;
/*
#if defined GL_VERSION_1_1 && !defined DONOT_USE_GL_1_1_VERTEX_ARRAY
				glArrayElement(i_o[i][2]) ;
				glArrayElement(i_o[i][1]) ;
				glArrayElement(i_o[i][0]) ;
#else
*/

				Vertex3fvWithTexAxis(v[i_o[i][2]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
				Vertex3fvWithTexAxis(v[i_o[i][1]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
				Vertex3fvWithTexAxis(v[i_o[i][0]], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;

/*
#endif
*/
			}
		}
		glEnd() ;
	}
	else
	{
		int tfan1[ 7] = { 4,  0, 1, 8, 5, 9, 0 } ;
		int strip[12] = { 0, 6, 1,10, 8, 3, 5, 2, 9,11, 0, 6 } ;
		int tfan2[ 7] = { 7,  3,10, 6,11, 2, 3 } ;

		// �@�����s�v�̏ꍇ�� FAN �� STRIP �ōœK��
		glBegin(GL_TRIANGLE_FAN) ;
		{
			for (int i = 0 ; i < 7 ; i ++)
			{
				int n = tfan1[i] ;
				Vertex3fvWithTexAxis(v[n], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
		}
		glEnd() ;

		glBegin(GL_TRIANGLE_STRIP) ;
		{
			for (int i = 0 ; i < 12 ; i ++)
			{
				int n = strip[i] ;
				Vertex3fvWithTexAxis(v[n], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
		}
		glEnd() ;

		glBegin(GL_TRIANGLE_FAN) ;
		{
			for (int i = 0 ; i < 7 ; i ++)
			{
				int n = tfan2[i] ;
				Vertex3fvWithTexAxis(v[n], target0, s0, t0, target1, s1, t1, target2, s2, t2, target3, s3, t3) ;
			}
		}
		glEnd() ;
	}
}


// ���ܕ`��i���܊֌W�f�[�^�v�Z�AOpenGL �`�揈���j
// ���}�b�v�`��͂܂���
// glEnable(GL_TEXTURE_2D) ;
// glDisable(GL_LIGHTING) ;
RefractRollingObject& RefractRollingObject::DrawRefractObject(const Vector3d& r_c, const Vector3d& s_c)
{
	int     u, v ;
	GLfloat matrix[16] ;

	// ���݂̃��f���r���[�s��Q�b�g
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix) ;

	// ���_�P�ʂ̋��܃f�[�^�i�e�N�X�`�����W�A���߁A���ːF�v�Z�j
	Vertex(0, 0).CalculateVertex(matrix, r_c, s_c) ; // �Ă��؂�̒��_
	Vertex(0, vDiv - 1).CalculateVertex(matrix, r_c, s_c) ; // ��̒��_

	// ����ȊO�i�ʏ�̉�]���_�j
	for (v = 0 ; v < vDiv - 1 ; v ++)
	{
		for (u = 0 ; u < uDiv ; u ++)
			Vertex(u, v).CalculateVertex(matrix, r_c, s_c) ;

		// ������Ė߂��Ă������_�͍ŏ��Ɠ���
		Vertex(uDiv, v) = Vertex(0, v) ;
	}

	// OpenGL �`��

	// �Ă��؂�̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glColor3fv(Vertex(0, 0).refraction_color.v) ;
		glTexCoord2fv(Vertex(0, 0).texture.v) ;
		glVertex3fv(Vertex(0, 0).vertex.v) ;

		for (u = 0 ; u <= uDiv ; u ++)
		{
			glColor3fv(Vertex(u, 1).refraction_color.v) ;
			glTexCoord2fv(Vertex(u, 1).texture.v) ;
			glVertex3fv(Vertex(u, 1).vertex.v) ;
		}
	}
	glEnd() ;

	// ��̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glColor3fv(Vertex(0, vDiv - 1).refraction_color.v) ;
		glTexCoord2fv(Vertex(0, vDiv - 1).texture.v) ;
		glVertex3fv(Vertex(0, vDiv - 1).vertex.v) ;

		for (u = uDiv ; u >= 0 ; u --)
		{
			glColor3fv(Vertex(u, vDiv - 2).refraction_color.v) ;
			glTexCoord2fv(Vertex(u, vDiv - 2).texture.v) ;
			glVertex3fv(Vertex(u, vDiv - 2).vertex.v) ;
		}
	}
	glEnd() ;

	// ����ȊO�i�ʏ�� QUAD_STRIP�j
	for (v = 1 ; v < vDiv - 1 ; v ++)
	{
		glBegin(GL_QUAD_STRIP) ;
		{
			for (u = 0 ; u <= uDiv ; u ++)
			{
				// ��
				glColor3fv(Vertex(u, v).refraction_color.v) ;
				glTexCoord2fv(Vertex(u, v).texture.v) ;
				glVertex3fv(Vertex(u, v).vertex.v) ;
				// ��
				glColor3fv(Vertex(u, v + 1).refraction_color.v) ;
				glTexCoord2fv(Vertex(u, v + 1).texture.v) ;
				glVertex3fv(Vertex(u, v + 1).vertex.v) ;
			}
		}
		glEnd() ;
	}

	return *this ;
}

// ���ܕ`��i���܊֌W�f�[�^�v�Z�AOpenGL �`�揈���j
// ���}�b�v�`��͂܂���
// ���ߗ��A���˗��͌v�Z���Ȃ��i�A�v���P�[�V���������O�� glColor() �����s�j
// glEnable(GL_TEXTURE_2D) ;
// glDisable(GL_LIGHTING) ;
// glColor*() ;
RefractRollingObject& RefractRollingObject::DrawRefractObject()
{
	int     u, v ;
	GLfloat matrix[16] ;

	// ���݂̃��f���r���[�s��Q�b�g
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix) ;

	// ���_�P�ʂ̋��܃f�[�^�i�e�N�X�`�����W�A���߁A���ːF�v�Z�j
	Vertex(0, 0).CalculateVertex(matrix) ; // �Ă��؂�̒��_
	Vertex(0, vDiv - 1).CalculateVertex(matrix) ; // ��̒��_

	// ����ȊO�i�ʏ�̉�]���_�j
	for (v = 0 ; v < vDiv - 1 ; v ++)
	{
		for (u = 0 ; u < uDiv ; u ++)
			Vertex(u, v).CalculateVertex(matrix) ;

		// ������Ė߂��Ă������_�͍ŏ��Ɠ���
		Vertex(uDiv, v) = Vertex(0, v) ;
	}

	// OpenGL �`��

	// �Ă��؂�̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glTexCoord2fv(Vertex(0, 0).texture.v) ;
		glVertex3fv(Vertex(0, 0).vertex.v) ;

		for (u = 0 ; u <= uDiv ; u ++)
		{
			glTexCoord2fv(Vertex(u, 1).texture.v) ;
			glVertex3fv(Vertex(u, 1).vertex.v) ;
		}
	}
	glEnd() ;

	// ��̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glTexCoord2fv(Vertex(0, vDiv - 1).texture.v) ;
		glVertex3fv(Vertex(0, vDiv - 1).vertex.v) ;

		for (u = uDiv ; u >= 0 ; u --)
		{
			glTexCoord2fv(Vertex(u, vDiv - 2).texture.v) ;
			glVertex3fv(Vertex(u, vDiv - 2).vertex.v) ;
		}
	}
	glEnd() ;

	// ����ȊO�i�ʏ�� QUAD_STRIP�j
	for (v = 1 ; v < vDiv - 2 ; v ++)
	{
		glBegin(GL_QUAD_STRIP) ;
		{
			for (u = 0 ; u <= uDiv ; u ++)
			{
				// ��
				glTexCoord2fv(Vertex(u, v).texture.v) ;
				glVertex3fv(Vertex(u, v).vertex.v) ;
				// ��
				glTexCoord2fv(Vertex(u, v + 1).texture.v) ;
				glVertex3fv(Vertex(u, v + 1).vertex.v) ;
			}
		}
		glEnd() ;
	}

	return *this ;
}


// ���ܕ`��i�䗬�t�F�C�N���܌v�Z�AOpenGL �`�揈���j
// ���}�b�v�`��͂܂���
// glEnable(GL_TEXTURE_2D) ;
// glDisable(GL_LIGHTING) ;
RefractRollingObject& RefractRollingObject::DrawFakeRefractObject(const Vector3d& r_c, const Vector3d& s_c)
{
	int     u, v ;
	GLfloat matrix[16] ;

	// ���݂̃��f���r���[�s��Q�b�g
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix) ;

	// ���_�P�ʂ̋��܃f�[�^�i�e�N�X�`�����W�A���߁A���ːF�v�Z�j
	Vertex(0, 0).CalculateFakeVertex(matrix, r_c, s_c) ; // �Ă��؂�̒��_
	Vertex(0, vDiv - 1).CalculateFakeVertex(matrix, r_c, s_c) ; // ��̒��_

	// ����ȊO�i�ʏ�̉�]���_�j
	for (v = 0 ; v < vDiv - 1 ; v ++)
	{
		for (u = 0 ; u < uDiv ; u ++)
			Vertex(u, v).CalculateFakeVertex(matrix, r_c, s_c) ;

		// ������Ė߂��Ă������_�͍ŏ��Ɠ���
		Vertex(uDiv, v) = Vertex(0, v) ;
	}

	// OpenGL �`��

	// �Ă��؂�̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glColor3fv(Vertex(0, 0).refraction_color.v) ;
		glTexCoord2fv(Vertex(0, 0).texture.v) ;
		glVertex3fv(Vertex(0, 0).vertex.v) ;

		for (u = 0 ; u <= uDiv ; u ++)
		{
			glColor3fv(Vertex(u, 1).refraction_color.v) ;
			glTexCoord2fv(Vertex(u, 1).texture.v) ;
			glVertex3fv(Vertex(u, 1).vertex.v) ;
		}
	}
	glEnd() ;

	// ��̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glColor3fv(Vertex(0, vDiv - 1).refraction_color.v) ;
		glTexCoord2fv(Vertex(0, vDiv - 1).texture.v) ;
		glVertex3fv(Vertex(0, vDiv - 1).vertex.v) ;

		for (u = uDiv ; u >= 0 ; u --)
		{
			glColor3fv(Vertex(u, vDiv - 2).refraction_color.v) ;
			glTexCoord2fv(Vertex(u, vDiv - 2).texture.v) ;
			glVertex3fv(Vertex(u, vDiv - 2).vertex.v) ;
		}
	}
	glEnd() ;

	// ����ȊO�i�ʏ�� QUAD_STRIP�j
	for (v = 1 ; v < vDiv - 1 ; v ++)
	{
		glBegin(GL_QUAD_STRIP) ;
		{
			for (u = 0 ; u <= uDiv ; u ++)
			{
				// ��
				glColor3fv(Vertex(u, v).refraction_color.v) ;
				glTexCoord2fv(Vertex(u, v).texture.v) ;
				glVertex3fv(Vertex(u, v).vertex.v) ;
				// ��
				glColor3fv(Vertex(u, v + 1).refraction_color.v) ;
				glTexCoord2fv(Vertex(u, v + 1).texture.v) ;
				glVertex3fv(Vertex(u, v + 1).vertex.v) ;
			}
		}
		glEnd() ;
	}

	return *this ;
}


// ���ܕ`��i���܊֌W�f�[�^�v�Z�AOpenGL �`�揈���j
// ���}�b�v�`��͂܂���
// ���ߗ��A���˗��͌v�Z���Ȃ��i�A�v���P�[�V���������O�� glColor() �����s�j
// glEnable(GL_TEXTURE_2D) ;
// glDisable(GL_LIGHTING) ;
// glColor*() ;
RefractRollingObject& RefractRollingObject::DrawFakeRefractObject()
{
	int     u, v ;
	GLfloat matrix[16] ;

	// ���݂̃��f���r���[�s��Q�b�g
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix) ;

	// ���_�P�ʂ̋��܃f�[�^�i�e�N�X�`�����W�A���߁A���ːF�v�Z�j
	Vertex(0, 0).CalculateFakeVertex(matrix) ; // �Ă��؂�̒��_
	Vertex(0, vDiv - 1).CalculateFakeVertex(matrix) ; // ��̒��_

	// ����ȊO�i�ʏ�̉�]���_�j
	for (v = 0 ; v < vDiv - 1 ; v ++)
	{
		for (u = 0 ; u < uDiv ; u ++)
			Vertex(u, v).CalculateFakeVertex(matrix) ;

		// ������Ė߂��Ă������_�͍ŏ��Ɠ���
		Vertex(uDiv, v) = Vertex(0, v) ;
	}

	// OpenGL �`��

	// �Ă��؂�̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glTexCoord2fv(Vertex(0, 0).texture.v) ;
		glVertex3fv(Vertex(0, 0).vertex.v) ;

		for (u = 0 ; u <= uDiv ; u ++)
		{
			glTexCoord2fv(Vertex(u, 1).texture.v) ;
			glVertex3fv(Vertex(u, 1).vertex.v) ;
		}
	}
	glEnd() ;

	// ��̎O�p�`�t�@��
	glBegin(GL_TRIANGLE_FAN) ;
	{
		glTexCoord2fv(Vertex(0, vDiv - 1).texture.v) ;
		glVertex3fv(Vertex(0, vDiv - 1).vertex.v) ;

		for (u = uDiv ; u >= 0 ; u --)
		{
			glTexCoord2fv(Vertex(u, vDiv - 2).texture.v) ;
			glVertex3fv(Vertex(u, vDiv - 2).vertex.v) ;
		}
	}
	glEnd() ;

	// ����ȊO�i�ʏ�� QUAD_STRIP�j
	for (v = 1 ; v < vDiv - 2 ; v ++)
	{
		glBegin(GL_QUAD_STRIP) ;
		{
			for (u = 0 ; u <= uDiv ; u ++)
			{
				// ��
				glTexCoord2fv(Vertex(u, v).texture.v) ;
				glVertex3fv(Vertex(u, v).vertex.v) ;
				// ��
				glTexCoord2fv(Vertex(u, v + 1).texture.v) ;
				glVertex3fv(Vertex(u, v + 1).vertex.v) ;
			}
		}
		glEnd() ;
	}

	return *this ;
}


// ���C���O���X�`��i�@���A���_���W�j
void WineGlass::DrawObject(int normalFlag, float *s, float *t)
{
	int u, v ;

	for (v = 0 ; v < N_VERTICIES - 1 ; v ++)
	{
		if (v == 0) // �Ă��؂�̎O�p�`
		{
			int pNo = (uDiv - 1) * (N_VERTICIES - 1) ;

			glBegin(GL_TRIANGLE_FAN) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
//				glNormal3f(0.0, 0.0, 1.0) ;	// ��ԏ�̒��_���W�͖@����^���
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[0] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[0].v) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[1] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[1].v) ;

				for (u = uDiv - 1 ; u >= 0 ; u --)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
					if (s && t)
					{
						Vector3d& v = polygon[pNo].vertex[2] ;
						TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
					}
					glVertex3fv(polygon[pNo].vertex[2].v) ;

					pNo -= N_VERTICIES - 1 ;
				}

			glEnd() ;
		}
		else if (v == N_VERTICIES - 2 ) // ��̎O�p�`
		{
			int pNo = v ;

			glBegin(GL_TRIANGLE_FAN) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
//				glNormal3d(0.0, 0.0, -1.0) ;	// ��ԉ��̒��_���W�͖@����^����
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[1] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[1].v) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[2] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[2].v) ;

				for (u = 0 ; u < uDiv ; u ++)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					if (s && t)
					{
						Vector3d& v = polygon[pNo].vertex[0] ;
						TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
					}
					glVertex3fv(polygon[pNo].vertex[0].v) ;

					pNo += N_VERTICIES - 1 ;
				}

			glEnd() ;
		}
		else  // �ʏ�̎l�p�`
		{
			int pNo = v ;

			glBegin(GL_QUAD_STRIP) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[2].v) ;
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[2] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[2].v) ;

				if (normalFlag) glNormal3fv(polygon[pNo].normal[3].v) ;
				if (s && t)
				{
					Vector3d& v = polygon[pNo].vertex[3] ;
					TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
				}
				glVertex3fv(polygon[pNo].vertex[3].v) ;

				for (u = 0 ; u < uDiv ; u ++)
				{
					if (normalFlag) glNormal3fv(polygon[pNo].normal[1].v) ;
					if (s && t)
					{
						Vector3d& v = polygon[pNo].vertex[1] ;
						TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
					}
					glVertex3fv(polygon[pNo].vertex[1].v) ;

					if (normalFlag) glNormal3fv(polygon[pNo].normal[0].v) ;
					if (s && t)
					{
						Vector3d& v = polygon[pNo].vertex[0] ;
						TexCoord2f(s[0] * v.X() + s[1] * v.Y() + s[2] * v.Z(), t[0] * v.X() + t[1] * v.Y() + t[2] * v.Z()) ;
					}
					glVertex3fv(polygon[pNo].vertex[0].v) ;

					pNo += N_VERTICIES - 1 ;
				}

			glEnd() ;
		}
	}
}

void WineGlass::DrawPolyhedron(int divide, GLfloat r, int normalFlag, float *s, float *t)
{
	WineGlass obj(divide, r,r,r) ;
	obj.DrawObject(normalFlag, s, t) ;
}

void Cylinder::DrawPolyhedron(int divide, GLfloat tr, int tCap, GLfloat br, int bCap, GLfloat h,
							  int normalFlag,
							  int target0, float *s0, float *t0,
							  int target1, float *s1, float *t1,
							  int target2, float *s2, float *t2,
							  int target3, float *s3, float *t3)
{
	Cylinder obj(divide, tr, tCap, br, bCap, h) ;
	obj.DrawObject(normalFlag,
				   target0, s0, t0,
				   target1, s1, t1,
				   target2, s2, t2,
				   target3, s3, t3) ;
}

void Torus::DrawPolyhedron(GLfloat innerRadius, GLfloat outerRadius, int sides, int rings,
						   int normalFlag, float *s, float *t)
{
	Torus obj(innerRadius, outerRadius, sides, rings) ;
	obj.DrawObject(normalFlag, s, t) ;
}


// �����̂̕`��i�@���x�N�g���A���_���W�j
void HalfSphere::DrawObject()
{
	for (int v = 0 ; v < vDiv - 1 ; v ++)
	{
		int pNo = v ;

		glBegin(GL_QUAD_STRIP) ;

			glNormal3fv(polygon[pNo].normal[2].v) ;
			glVertex3fv(polygon[pNo].vertex[2].v) ;

			glNormal3fv(polygon[pNo].normal[3].v) ;
			glVertex3fv(polygon[pNo].vertex[3].v) ;

			for (int u = 0 ; u < uDiv ; u ++)
			{
				glNormal3fv(polygon[pNo].normal[1].v) ;
				glVertex3fv(polygon[pNo].vertex[1].v) ;

				glNormal3fv(polygon[pNo].normal[0].v) ;
				glVertex3fv(polygon[pNo].vertex[0].v) ;

				pNo += vDiv - 1 ;
			}

		glEnd() ;
	}
}

// �����̂̕`��i�e�N�X�`�����W�A���_���W�j
void HalfSphere::DrawObjectWithNormalMapping()
{
	// �e�N�X�`�����W
	Vector3d t ;

	for (int v = 0 ; v < vDiv - 1 ; v ++)
	{
		int pNo = v ;

		glBegin(GL_QUAD_STRIP) ;

//			glNormal3fv(polygon[pNo].normal[2].v) ;
			t = SphericalVertex(-polygon[pNo].normal[2]) ;
//			t = SphericalVertex(polygon[pNo].normal[2]) ;
			glTexCoord2fv(t.v) ;
			glVertex3fv(polygon[pNo].vertex[2].v) ;

//			glNormal3fv(polygon[pNo].normal[3].v) ;
			t = SphericalVertex(-polygon[pNo].normal[3]) ;
//			t = SphericalVertex(polygon[pNo].normal[3]) ;
			glTexCoord2fv(t.v) ;
			glVertex3fv(polygon[pNo].vertex[3].v) ;

			for (int u = 0 ; u < uDiv ; u ++)
			{
//				glNormal3fv(polygon[pNo].normal[1].v) ;
				t = SphericalVertex(-polygon[pNo].normal[1]) ;
//				t = SphericalVertex(polygon[pNo].normal[1]) ;
				glTexCoord2fv(t.v) ;
				glVertex3fv(polygon[pNo].vertex[1].v) ;

//				glNormal3fv(polygon[pNo].normal[0].v) ;
				t = SphericalVertex(-polygon[pNo].normal[0]) ;
//				t = SphericalVertex(polygon[pNo].normal[0]) ;
				glTexCoord2fv(t.v) ;
				glVertex3fv(polygon[pNo].vertex[0].v) ;

				pNo += vDiv - 1 ;
			}

		glEnd() ;
	}
}

// �����̂̕`��i�e�N�X�`�����W�A���_���W�j
// ���܃}�b�s���O�p
void HalfSphere::DrawObjectWithNormalMapping2()
{
	// �e�N�X�`�����W
	Vector3d t ;

	for (int v = 0 ; v < vDiv - 1 ; v ++)
	{
		int pNo = v ;

		glBegin(GL_QUAD_STRIP) ;

//			glNormal3fv(polygon[pNo].normal[2].v) ;
//			t = SphericalVertex(-polygon[pNo].normal[2]) ;
			t = SphericalVertex(polygon[pNo].normal[2]) ;
			glTexCoord2fv(t.v) ;
			glVertex3fv(polygon[pNo].vertex[2].v) ;

//			glNormal3fv(polygon[pNo].normal[3].v) ;
//			t = SphericalVertex(-polygon[pNo].normal[3]) ;
			t = SphericalVertex(polygon[pNo].normal[3]) ;
			glTexCoord2fv(t.v) ;
			glVertex3fv(polygon[pNo].vertex[3].v) ;

			for (int u = 0 ; u < uDiv ; u ++)
			{
//				glNormal3fv(polygon[pNo].normal[1].v) ;
//				t = SphericalVertex(-polygon[pNo].normal[1]) ;
				t = SphericalVertex(polygon[pNo].normal[1]) ;
				glTexCoord2fv(t.v) ;
				glVertex3fv(polygon[pNo].vertex[1].v) ;

//				glNormal3fv(polygon[pNo].normal[0].v) ;
//				t = SphericalVertex(-polygon[pNo].normal[0]) ;
				t = SphericalVertex(polygon[pNo].normal[0]) ;
				glTexCoord2fv(t.v) ;
				glVertex3fv(polygon[pNo].vertex[0].v) ;

				pNo += vDiv - 1 ;
			}

		glEnd() ;
	}
}

// �����̂𒼐ڕ`��
void HalfSphere::DrawPolyhedron(int divide, int vDivide, GLfloat r)
{
	HalfSphere obj(divide, vDivide, r,r,r) ;
	obj.DrawObject() ;
}

// �����̂𒼐ڕ`��
// ���˃}�b�s���O�p
void HalfSphere::DrawPolyhedronWithNormalMapping(int divide, int vDivide, GLfloat r)
{
	HalfSphere obj(divide, vDivide, r,r,r) ;
	obj.DrawObjectWithNormalMapping() ;
}

// �����̂𒼐ڕ`��
// ���܃}�b�s���O�p
void HalfSphere::DrawPolyhedronWithNormalMapping2(int divide, int vDivide, GLfloat r)
{
	HalfSphere obj(divide, vDivide, r,r,r) ;
	obj.DrawObjectWithNormalMapping2() ;
}



GLfloat Icosahedron::X = 0.525731112119133606f, Icosahedron::Z = 0.850650808352039932f ;

GLfloat Icosahedron::i_v[][3] = { {  -Icosahedron::X, 0.0f,   Icosahedron::Z }, {   Icosahedron::X, 0.0f,   Icosahedron::Z }, {  -Icosahedron::X, 0.0f,  -Icosahedron::Z }, {   Icosahedron::X, 0.0f,  -Icosahedron::Z },
								 { 0.0f,   Icosahedron::Z,   Icosahedron::X }, { 0.0f,   Icosahedron::Z,  -Icosahedron::X }, { 0.0f,  -Icosahedron::Z,   Icosahedron::X }, { 0.0f,  -Icosahedron::Z,  -Icosahedron::X },
								 {   Icosahedron::Z,   Icosahedron::X, 0.0f }, {  -Icosahedron::Z,   Icosahedron::X, 0.0f }, {   Icosahedron::Z,  -Icosahedron::X, 0.0f }, {  -Icosahedron::Z,  -Icosahedron::X, 0.0f } } ;

int Icosahedron::i_o[][3] = { { 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 },{ 4, 8, 1 },
							  { 8,10, 1 }, { 8, 3,10 }, { 5, 3, 8 }, { 5, 2, 3 },{ 2, 7, 3 },
							  { 7,10, 3 }, { 7, 6,10 }, { 7,11, 6 }, {11, 0, 6 },{ 0, 1, 6 },
							  { 6, 1,10 }, { 9, 0,11 }, { 9,11, 2 }, { 9, 2, 5 },{ 7, 2,11 } } ;

GLfloat WineGlass::vertexes[N_VERTICIES][2] =
{
	{ 0.0f, 0.0f }, { 4.0f, 0.2f }, { 8.0f, 1.5f }, { 10.5f, 3.2f }, { 13.0f, 5.8f },
	{ 14.0f, 8.0f }, { 14.2f, 10.0f }, { 14.1f, 12.0f }, { 13.5f, 15.0f }, { 12.2f, 19.0f },
	{ 12.2f, 19.5f }, { 12.3f, 19.7f }, { 12.5f, 19.6f }, { 12.6f, 19.3f }, { 14.0f, 15.0f },
	{ 14.6f, 12.0f }, { 14.8f, 10.0f }, { 14.4f, 7.8f }, { 13.3f, 5.4f }, { 11.2f, 2.8f },
	{ 7.8f, 0.4f }, { 4.0f, -1.1f }, { 3.0f, -1.8f }, { 2.2f, -3.0f }, { 1.8f, -4.2f },
	{ 1.5f, -8.0f }, { 1.5f, -12.0f }, { 1.7f, -15.0f }, { 2.0f, -16.0f }, { 2.7f, -16.7f },
	{ 5.5f, -17.8f }, { 11.0f, -18.7f }, { 12.5f, -19.0f }, { 13.0f, -19.5f }, { 13.0f, -19.8f },
	{ 12.5f, -19.9f }, { 6.0f, -19.9f }, { 3.0f, -19.5f }, { 1.0f, -18.3f }, { 0.0f, -18.0f }
} ;


const Vector3d Vector3d::white(1.0f, 1.0f, 1.0f) ;


// from nVIDIA cube mapping sample code.
// simple teapot
static int patchdata[][16] =
{
    /* rim */
  {102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15},
    /* body */
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27},
  {24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40},
    /* lid */
  {96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,
    101, 0, 1, 2, 3,},
  {0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117},
    /* bottom */
  {118, 118, 118, 118, 124, 122, 119, 121, 123, 126,
    125, 120, 40, 39, 38, 37},
    /* handle */
  {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56},
  {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
    28, 65, 66, 67},
    /* spout */
  {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83},
  {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
    92, 93, 94, 95}
};


static float cpdata[][3] =
{
    {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
    -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
    {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
    0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
    2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
    2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
    {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
    1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
    {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
    0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
    0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
    {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
    {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
    -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
    -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
    2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
    2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
    2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
    {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
    -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
    1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
    -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
    1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
    0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
    0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
    {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
    -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
    2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
    {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
    {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
    {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
    3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
    3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
    -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
    2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
    2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
    2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
    {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
    -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
    0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
    {0.84, -1.5, 0.075}
};


// This "fastTeapot" routine is faster than glutSolidTeapot.
void
fastSolidTeapot(GLint grid, GLdouble scale)
{
  float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
  long i, j, k, l;

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_MAP2_VERTEX_3);
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
  glTranslatef(0.0, 0.0, -1.5);
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 3; l++) {
          p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
          q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
          if (l == 1)
            q[j][k][l] *= -1.0;
          if (i < 6) {
            r[j][k][l] =
              cpdata[patchdata[i][j * 4 + (3 - k)]][l];
            if (l == 0)
              r[j][k][l] *= -1.0;
            s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
            if (l == 0)
              s[j][k][l] *= -1.0;
            if (l == 1)
              s[j][k][l] *= -1.0;
          }
        }
      }
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &p[0][0][0]);
    glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &q[0][0][0]);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    if (i < 6) {
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &r[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &s[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    }
  }
}

#ifdef WIN32

// Win32 ��p
// �f�B�X�v���C���[�h�R���g���[���N���X

int DisplaySettingsCtrl::EnumAllSettings()
{
	return TRUE ;
}

DisplaySettingsCtrl::DisplaySettingsCtrl()
{
	nSettings = 0 ;
	devmode = NULL ;
}

DisplaySettingsCtrl::~DisplaySettingsCtrl()
{
}

#endif	// #ifdef WIN32

TextureObjectCtrl TextureObjectCtrl::textureObjectCtrl ;
