
#include "GLextensions.H"


static char		*current_MultiTextureInterfaceName = NULL ;
static String	current_MultiTextureInterfaceNameString ;
static GLint	current_maxTextureUnits = 1 ;

static char		*current_SeparateSpecularColorInterfaceName = NULL ;
static String	current_SeparateSpecularColorInterfaceNameString ;

static char		*current_TextureEnvAddInterfaceName = NULL ;
static String	current_TextureEnvAddInterfaceNameString ;

static char		*current_TextureEnvCombineInterfaceName = NULL ;
static String	current_TextureEnvCombineInterfaceNameString ;
static char		*current_TextureEnvCombine4InterfaceName = NULL ;
static String	current_TextureEnvCombine4InterfaceNameString ;

static char		*current_TextureFilterAnisotropicInterfaceName = NULL ;
static String	current_TextureFilterAnisotropicInterfaceNameString ;

static char		*current_TextureObjectInterfaceName = NULL ;
static String	current_TextureObjectInterfaceNameString ;

static char		*current_PolygonOffsetInterfaceName = NULL ;
static String	current_PolygonOffsetInterfaceNameString ;

static char		*current_TextureCubeMapInterfaceName = NULL ;
static String	current_TextureCubeMapInterfaceNameString ;
static char		*current_TexgenReflectionInterfaceName = NULL ;
static String	current_TexgenReflectionInterfaceNameString ;

static char		*current_TextureCompressionInterfaceEnumName = NULL ;
static String	current_TextureCompressionInterfaceEnumNameString ;

static char		*current_TextureCompressionS3TCInterfaceName = NULL ;
static String	current_TextureCompressionS3TCInterfaceNameString ;

static char		*current_S3TCInterfaceName = NULL ;
static String	current_S3TCInterfaceNameString ;

static char		*current_TextureCompressionFXT1InterfaceName = NULL ;
static String	current_TextureCompressionFXT1InterfaceNameString ;


// OpenGL Extension �֘A
#if defined(WIN32) && !defined(MESA)

// ARB_multitexture
PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB   = NULL ;
PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB = NULL ;

// SGIS_multitexture
PFNGLSELECTTEXTURESGISPROC			glSelectTextureSGIS         = NULL ;
PFNGLSELECTTEXTURECOORDSETSGISPROC	glSelectTextureCoordSetSGIS = NULL ;
PFNGLMULTITEXCOORD2FSGISPROC		glMultiTexCoord2fSGIS       = NULL ;

// EXT_multitexture
PFNGLSELECTTEXTUREEXTPROC			glSelectTextureEXT         = NULL ;
PFNGLSELECTTEXTURECOORDSETEXTPROC	glSelectTextureCoordSetEXT = NULL ;
PFNGLMULTITEXCOORD2FEXTPROC			glMultiTexCoord2fEXT       = NULL ;

// EXT_texture_object
PFNGLGENTEXTURESEXTPROC				glGenTexturesEXT    = NULL ;
PFNGLDELETETEXTURESEXTPROC			glDeleteTexturesEXT = NULL ;
PFNGLBINDTEXTUREEXTPROC				glBindTextureEXT    = NULL ;
PFNGLISTEXTUREEXTPROC				glIsTextureEXT      = NULL ;

// EXT_polygon_offset
PFNGLPOLYGONOFFSETEXTPROC			glPolygonOffsetEXT  = NULL ;

#endif	// #if defined(WIN32) && !defined(MESA)


// OpenGL �� multitexture ���T�|�[�g���Ȃ��o�[�W�����̏ꍇ�i1.3 �ŃT�|�[�g�H�j
//#ifndef GL_VERSION_multitexture

// �}���`�e�N�X�`���𓝍������C���^�t�F�[�X�i���ʎq�͊� ^^;�j
PFNGLACTIVETEXTUREPROC   p_glActiveTexture   = NULL ;
PFNGLMULTITEXCOORD2FPROC p_glMultiTexCoord2f = NULL ;

GLenum DEF_GL_MAX_TEXTURE_UNITS = (GLenum)0 ;

GLenum DEF_GL_TEXTURE0 = (GLenum)0 ;
GLenum DEF_GL_TEXTURE1 = (GLenum)0 ;
GLenum DEF_GL_TEXTURE2 = (GLenum)0 ;
GLenum DEF_GL_TEXTURE3 = (GLenum)0 ;

//#endif	// #ifndef GL_VERSION_multitexture


// �e�N�X�`���E�I�u�W�F�N�g�����C���^�t�F�[�X
PFNGLGENTEXTURESPROC	p_glGenTextures    = NULL ;
PFNGLDELETETEXTURESPROC	p_glDeleteTextures = NULL ;
PFNGLBINDTEXTUREPROC	p_glBindTexture    = NULL ;
PFNGLISTEXTUREPROC		p_glIsTexture      = NULL ;


// �|���S���E�I�t�Z�b�g�����C���^�t�F�[�X
PFNGLPOLYGONOFFSETPROC	p_glPolygonOffset = NULL ;

GLenum DEF_GL_POLYGON_OFFSET_POINT  = (GLenum)0 ;
GLenum DEF_GL_POLYGON_OFFSET_LINE   = (GLenum)0 ;
GLenum DEF_GL_POLYGON_OFFSET_FILL   = (GLenum)0 ;
GLenum DEF_GL_POLYGON_OFFSET_FACTOR = (GLenum)0 ;
GLenum DEF_GL_POLYGON_OFFSET_UNITS  = (GLenum)0 ;


// OpenGL �o�[�W�����i�����_�ȉ��P���A�܂荶����R���j
float GetOpenGLVersion()
{
//	static float OpenGL_Version = -1.0f ;
	float OpenGL_Version = -1.0f ;

	if (OpenGL_Version < 1.0f)
	{
		const char *str = (const char *)glGetString(GL_VERSION) ;
		if (str)
		{
			String ver(str, 3) ;	// ������R��
			OpenGL_Version = strtod(ver, NULL) ;
		}
		else
			OpenGL_Version = 1.0f ;	// �f�t�H���g�� 1.0

		// error?
		if (OpenGL_Version < 1.0f)
			OpenGL_Version = 1.0f ;
	}

	return OpenGL_Version ;
}


void CopyTexSubImage2D(GLenum target, int level, GLint xoffset, GLint yoffset,
					   GLint x, GLint y, GLsizei width, GLsizei height)
{
#ifdef GL_VERSION_1_1
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) ;

#else

	return ;
#endif	// #ifndef GL_VERSION_1_1
}


// OpenGL Extension �T�|�[�g�`�F�b�N
int IsSupported_OpenGLExtension(const String& name)
{
//	static String extensions ;
	String extensions ;

	if (extensions == "")
	{
		const char *str = (const char *)glGetString(GL_EXTENSIONS) ;
		if (str)
			extensions = str ;
	}

	if (strstr(extensions, name))
		return TRUE ;
	else
		return FALSE ;
}


/* �g�p��
	int has_ARB_multitexture = IsSupported_ARB_multitexture() ;

#ifdef GL_ARB_multitexture
	if (has_ARB_multitexture)
		glActiveTextureARB(GL_TEXTURE0_ARB) ;
#endif
*/
int IsSupported_ARB_multitexture()
{
#ifndef GL_ARB_multitexture
	return FALSE ;

#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_multitexture))
		return FALSE ;	// ARB_multitexture not supported

	// Get proc address (WGL only)
#if defined(WIN32) && !defined(MESA)
	if (!(glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB")) &&
		!(glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glActiveTextureARB")) &&		//	��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glActiveTextureARB@4")))	//	��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	if (!(glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB")) &&
		!(glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glMultiTexCoord2fARB")) &&	//	��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glMultiTexCoord2fARB@12")))	//	��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;
#endif	// #if defined(WIN32) && !defined(MESA)

	p_glActiveTexture   = glActiveTextureARB ;
	p_glMultiTexCoord2f = glMultiTexCoord2fARB ;

	DEF_GL_MAX_TEXTURE_UNITS = GL_MAX_TEXTURE_UNITS_ARB ;

	DEF_GL_TEXTURE0 = GL_TEXTURE0_ARB ;
	DEF_GL_TEXTURE1 = GL_TEXTURE1_ARB ;
	DEF_GL_TEXTURE2 = GL_TEXTURE2_ARB ;
	DEF_GL_TEXTURE3 = GL_TEXTURE3_ARB ;

	current_MultiTextureInterfaceName = CURRENT_NAME_GL_ARB_multitexture ;
	current_MultiTextureInterfaceNameString = current_MultiTextureInterfaceName ;
	return TRUE ;

#endif	// #ifndef GL_ARB_multitexture ... #else
}


/* �g�p��
	int has_SGIS_multitexture = IsSupported_SGIS_multitexture() ;

#ifdef GL_SGIS_multitexture
	if (has_SGIS_multitexture)
		glSelectTextureSGIS(GL_TEXTURE0_SGIS) ;
#endif
*/
// Mesa �ł͒l������Ă����肷�邽�߁A
// IsSupported_SGIS_multitexture() �͒��ڃR�[������
// IsSupported_multitexture() �ł܂Ƃ߂���������
// ARB, EXT �̕����D�悳��邽�߁AMesa �ł� ARB, EXT �̂����ꂩ�������I�������͂�
int IsSupported_SGIS_multitexture()
{
#ifndef GL_SGIS_multitexture
	return FALSE ;

#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_SGIS_multitexture))
		return FALSE ;	// SGIS_multitexture not supported

	// Get proc address (WGL only)
#if defined(WIN32) && !defined(MESA)
	if (!(glSelectTextureSGIS = (PFNGLSELECTTEXTURESGISPROC)wglGetProcAddress("glSelectTextureSGIS")) &&
		!(glSelectTextureSGIS = (PFNGLSELECTTEXTURESGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glSelectTextureSGIS")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glSelectTextureSGIS = (PFNGLSELECTTEXTURESGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glSelectTextureSGIS@4")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	// glMTexCoord* �� glMultiTexCoord* �̂Q��ޑ��݂��邽�ߑo�����`�F�b�N
	if (!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)wglGetProcAddress("glMultiTexCoord2fSGIS")) &&
		!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)wglGetProcAddress("glMTexCoord2fSGIS"    )) &&
		!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glMultiTexCoord2fSGIS"    )) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glMultiTexCoord2fSGIS@12")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glMTexCoord2fSGIS"        )) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glMultiTexCoord2fSGIS = (PFNGLMULTITEXCOORD2FSGISPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glMTexCoord2fSGIS@12"    )))		// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;
#endif	// #if defined(WIN32) && !defined(MESA)

	p_glActiveTexture   = glSelectTextureSGIS ;
	p_glMultiTexCoord2f = glMultiTexCoord2fSGIS ;

#ifndef MESA
	// Mesa �ȊO
	DEF_GL_TEXTURE0 = GL_TEXTURE0_SGIS ;
	DEF_GL_TEXTURE1 = GL_TEXTURE1_SGIS ;

#else
	// Mesa �ł͉��̂��萔���قȂ�
	// ������ɂ��� IsSupported_SGIS_multitexture() �͒��ڃR�[������
	// IsSupported_multitexture() �ł܂Ƃ߂���������
	// ARB, EXT �̕����D�悳��邽�߁AMesa �ł� ARB, EXT �̂����ꂩ�������I�������
	DEF_GL_MAX_TEXTURE_UNITS = GL_MAX_TEXTURES_SGIS ;

	DEF_GL_TEXTURE0 = GL_TEXTURE0_SGIS ;
	DEF_GL_TEXTURE1 = GL_TEXTURE1_SGIS ;
	DEF_GL_TEXTURE2 = GL_TEXTURE2_SGIS ;
	DEF_GL_TEXTURE3 = GL_TEXTURE3_SGIS ;

#endif	// #ifndef MESA ... #else

	current_MultiTextureInterfaceName = CURRENT_NAME_GL_SGIS_multitexture ;
	current_MultiTextureInterfaceNameString = current_MultiTextureInterfaceName ;
	return TRUE ;

#endif	// #ifndef GL_SGIS_multitexture ... #else
}


/* �g�p��
	int has_EXT_multitexture = IsSupported_EXT_multitexture() ;

#ifdef GL_EXT_multitexture
	if (has_EXT_multitexture)
		SelectTextureEXT(GL_TEXTURE0_EXT) ;
#endif
*/
int IsSupported_EXT_multitexture()
{
#ifndef GL_EXT_multitexture
	return FALSE ;

#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_multitexture))
		return FALSE ;	// EXT_multitexture not supported

	// Get proc address (WGL only)
#if defined(WIN32) && !defined(MESA)
	if (!(glSelectTextureEXT = (PFNGLSELECTTEXTUREEXTPROC)wglGetProcAddress("glSelectTextureEXT")) &&
		!(glSelectTextureEXT = (PFNGLSELECTTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glSelectTextureEXT")) &&		// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glSelectTextureEXT = (PFNGLSELECTTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glSelectTextureEXT@4")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	if (!(glMultiTexCoord2fEXT = (PFNGLMULTITEXCOORD2FEXTPROC)wglGetProcAddress("glMultiTexCoord2fEXT")) &&
		!(glMultiTexCoord2fEXT = (PFNGLMULTITEXCOORD2FEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glMultiTexCoord2fEXT")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glMultiTexCoord2fEXT = (PFNGLMULTITEXCOORD2FEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glMultiTexCoord2fEXT@12")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
			return FALSE ;
#endif	// #if defined(WIN32) && !defined(MESA)

	p_glActiveTexture   = glSelectTextureEXT ;
	p_glMultiTexCoord2f = glMultiTexCoord2fEXT ;

	DEF_GL_MAX_TEXTURE_UNITS = GL_MAX_TEXTURES_EXT ;

	DEF_GL_TEXTURE0 = GL_TEXTURE0_EXT ;
	DEF_GL_TEXTURE1 = GL_TEXTURE1_EXT ;
	DEF_GL_TEXTURE2 = GL_TEXTURE2_EXT ;
	DEF_GL_TEXTURE3 = GL_TEXTURE3_EXT ;

	current_MultiTextureInterfaceName = CURRENT_NAME_GL_EXT_multitexture ;
	current_MultiTextureInterfaceNameString = current_MultiTextureInterfaceName ;
	return TRUE ;

#endif	// #ifndef GL_EXT_multitexture ... #else
}


// ������p
// multitexture �g�p���̍ő�e�N�X�`�����j�b�g��
// �J�����g�� Mesa �ȊO�� SGIS_multitexture �̏ꍇ�͂Q�Œ�
// IsSupported_*_multitexture() �����R�[���̏ꍇ�P
GLint __GetMaxTextureUnits()
{
	if (current_MultiTextureInterfaceNameString == "")
	{
		current_maxTextureUnits = 1 ;
		return current_maxTextureUnits ;
	}

#ifndef MESA
	if (current_MultiTextureInterfaceNameString == CURRENT_NAME_GL_SGIS_multitexture)
	{
		current_maxTextureUnits = 2 ;	// Mesa �ȊO�� SGIS_multitexture �ł́A�������Q�Ƃ݂Ȃ��i���̎��_�ŏ����I���j
		return current_maxTextureUnits ;
	}
#endif	// #ifndef MESA

	// ARB_multitexture or EXT_multitexture�A�������� Mesa �� SGIS_multitexture �Ȃ�A
	// OpenGL ����ő�e�N�X�`�����j�b�g�����擾
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &current_maxTextureUnits) ;	// �e�N�X�`���̍ő僆�j�b�g��

	return current_maxTextureUnits ;
}


// ���炩�� multitexture ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� multitexture �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Multi-Texture" �c�c�c�c�c�c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-1.3 �ȍ~�H�j
// "GL_ARB_multitexture"
// "GL_EXT_multitexture"
// "GL_SGIS_multitexture"
// NULL
//
// �R���p�C������ multitexture �𐳎��T�|�[�g����o�[�W�����ŁA
// ���A�����^�C���������T�|�[�g���Ă��Ȃ��o�[�W�����̏ꍇ
// �����^�C�����Ƀ����N�ł��Ȃ����߁A���s�s�\
//
/* �g�p��
	char *multitex = IsSupported_multitexture() ;
	if (multitex)
		glActiveTexture(GL_TEXTURE0) ;
*/
char *IsSupported_multitexture(int flag_ARB, int flag_EXT, int flag_SGIS)
{
	current_MultiTextureInterfaceName = NULL ;

#ifdef GL_VERSION_multitexture
	// �R���p�C���E���s���o���ŁAmultitexture ���T�|�[�g����o�[�W�����ȍ~�Ȃ�
	if (GetOpenGLVersion() >= GL_VERSION_multitexture_F)
		current_MultiTextureInterfaceName = CURRENT_NAME_GL_VERSION_multitexture ;

#endif	// #ifdef GL_VERSION_multitexture

	// ARB_multitexture
	if (!current_MultiTextureInterfaceName && flag_ARB)
		IsSupported_ARB_multitexture() ;

	// EXT_multitexture
	if (!current_MultiTextureInterfaceName && flag_EXT)
		IsSupported_EXT_multitexture() ;

	// SGIS_multitexture
	if (!current_MultiTextureInterfaceName && flag_SGIS)
		IsSupported_SGIS_multitexture() ;

	if (current_MultiTextureInterfaceName)
		current_MultiTextureInterfaceNameString = current_MultiTextureInterfaceName ;

	current_maxTextureUnits = __GetMaxTextureUnits() ;

	return current_MultiTextureInterfaceName ;
}


// multitexture coord �w��
//
// target ���w�肷��ꍇ�́A�K�����O��
// IsSupported_multitexture() �ɂ��g�p�@�\�̓o�^���K�v
// 
// IsSupported_SGIS_multitexture() �͎g�p���Ȃ������ǂ�
// �܂��ASGIS �ł͊�{�I��
// GL_MAX_TEXTURE_UNITS �͎g�p�s�i���Ȃ炸�Q���j�b�g�Ƃ݂Ȃ��������ǂ��j
//
// target �̎w�肪�Ȃ��ꍇ glTexCoord2f() �ő�p
void TexCoord2f(GLfloat s, GLfloat t, int target)
{
#ifdef GL_VERSION_1_1
	if (target && GL_TEXTURE0)
		glMultiTexCoord2f((GLenum)((int)GL_TEXTURE0 + target), s, t) ;
	else
		glTexCoord2f(s, t) ;
#else
	glTexCoord2f(s, t) ;
#endif
}


// glVertex3f() �̑���ɃR�[����
//
// s, t �ɂ����W�w�肪�L���ȏꍇ�́A
// glVetex() �̑O�� glTexCoord2f() �R�[��
//
// target ���w�肳�ꂽ�ꍇ�A
// �e target �̎����e�N�X�`�����j�b�g�Ƀe�N�X�`�����W�Z�b�g
//
// target ���w�肷��ꍇ�́A���O��
// IsSupported_multitexture() �ɂ��g�p�@�\�̓o�^���K�v
// 
// IsSupported_SGIS_multitexture() �͎g�p���Ȃ������ǂ�
// �܂��ASGIS �ł͊�{�I��
// GL_MAX_TEXTURE_UNITS �͎g�p�s�i���Ȃ炸�Q���j�b�g�Ƃ݂Ȃ��������ǂ��j
void Vertex3fWithTexAxis(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat *s0, GLfloat *t0)
{
	Vertex3fWithTexAxis(vx, vy, vz, -1, s0, t0) ;
}

void Vertex3fWithTexAxis(GLfloat vx, GLfloat vy, GLfloat vz,
						 int target0, GLfloat *s0, GLfloat *t0,
						 int target1, GLfloat *s1, GLfloat *t1,
						 int target2, GLfloat *s2, GLfloat *t2,
						 int target3, GLfloat *s3, GLfloat *t3)
{
	// �b��
	static const int MAX_TEX_UNITS = 4 ;

	GLfloat *s[MAX_TEX_UNITS] ;
	GLfloat *t[MAX_TEX_UNITS] ;
	int      u[MAX_TEX_UNITS] ;

	s[0] = s0 ; t[0] = t0 ; u[0] = target0 ;
	s[1] = s1 ; t[1] = t1 ; u[1] = target1 ;
	s[2] = s2 ; t[2] = t2 ; u[2] = target2 ;
	s[3] = s3 ; t[3] = t3 ; u[3] = target3 ;

	// �e�e�N�X�`�����j�b�g�ɑ΂��e�N�X�`�����W���Z�b�g
//	for (int i = 0 ; i < MAX_TEX_UNITS && i < current_maxTextureUnits ; i ++)
	for (int i = 0 ; i < MAX_TEX_UNITS ; i ++)
	{
		if (s[i] && t[i])
		{
#ifdef GL_VERSION_1_1
			// OpenGL-1.1 �ȏ�̂ݗL��
//			if (u[i] > 0 && GL_TEXTURE0)
			if (GL_TEXTURE0 && u[i] > 0 && u[i] < current_maxTextureUnits)
			{
/*
				if ((int)GL_TEXTURE0 + u[i] != 0x84C0 && (int)GL_TEXTURE0 + u[i] != 0x84C1)
				{
					DEF_GL_TEXTURE0 = GL_TEXTURE0 ;
					DEF_GL_TEXTURE1 = GL_TEXTURE1 ;
				}
*/

				// �^�[�Q�b�g�w�肳��Ă���ꍇ
				glMultiTexCoord2f((GLenum)((int)GL_TEXTURE0 + u[i]),
								  s[i][0] * vx + s[i][1] * vy + s[i][2] * vz,
								  t[i][0] * vx + t[i][1] * vy + t[i][2] * vz) ;
			}
			else
#endif
			{
				// �^�[�Q�b�g�w�肳��Ă��Ȃ��A�������� OpenGL-1.0 �̏ꍇ
				glTexCoord2f(s[i][0] * vx + s[i][1] * vy + s[i][2] * vz,
							 t[i][0] * vx + t[i][1] * vy + t[i][2] * vz) ;

//				if (u[i] < 0)
//					break ;
			}
		}

#ifndef GL_VERSION_1_1
		// OpenGL-1.0 �̏ꍇ�ŏ��̂P�̂ݗL��
		break ;
#endif
	}

	// �Ō�ɒ��_���W�Z�b�g
	glVertex3f(vx, vy, vz) ;

/*
	if (GL_TEXTURE0 != 0x84C0 || GL_TEXTURE1 != 0x84C1)
	{
			DEF_GL_TEXTURE0 = GL_TEXTURE0 ;
			DEF_GL_TEXTURE1 = GL_TEXTURE1 ;
	}
*/
}


// glVertex3fv() �̑���ɃR�[����
//
// s, t �ɂ����W�w�肪�L���ȏꍇ�́A
// glVetex() �̑O�� glTexCoord2f() �R�[��
//
// target ���w�肳�ꂽ�ꍇ�A
// �e target �̎����e�N�X�`�����j�b�g�Ƀe�N�X�`�����W�Z�b�g
//
// target ���w�肷��ꍇ�́A���O��
// IsSupported_multitexture() �ɂ��g�p�@�\�̓o�^���K�v
// 
// IsSupported_SGIS_multitexture() �͎g�p���Ȃ������ǂ�
// �܂��ASGIS �ł͊�{�I��
// GL_MAX_TEXTURE_UNITS �͎g�p�s�i���Ȃ炸�Q���j�b�g�Ƃ݂Ȃ��������ǂ��j
void Vertex3fvWithTexAxis(GLfloat v[3], GLfloat *s0, GLfloat *t0)
{
	Vertex3fvWithTexAxis(v, -1, s0, t0) ;
}

void Vertex3fvWithTexAxis(GLfloat v[3],
						  int target0, GLfloat *s0, GLfloat *t0,
						  int target1, GLfloat *s1, GLfloat *t1,
						  int target2, GLfloat *s2, GLfloat *t2,
						  int target3, GLfloat *s3, GLfloat *t3)
{
	// �b��
	static const int MAX_TEX_UNITS = 4 ;

	GLfloat *s[MAX_TEX_UNITS] ;
	GLfloat *t[MAX_TEX_UNITS] ;
	int      u[MAX_TEX_UNITS] ;

	s[0] = s0 ; t[0] = t0 ; u[0] = target0 ;
	s[1] = s1 ; t[1] = t1 ; u[1] = target1 ;
	s[2] = s2 ; t[2] = t2 ; u[2] = target2 ;
	s[3] = s3 ; t[3] = t3 ; u[3] = target3 ;


	// �e�e�N�X�`�����j�b�g�ɑ΂��e�N�X�`�����W���Z�b�g
//	for (int i = 0 ; i < MAX_TEX_UNITS && i < current_maxTextureUnits ; i ++)
	for (int i = 0 ; i < MAX_TEX_UNITS ; i ++)
	{
		if (s[i] && t[i])
		{
#ifdef GL_VERSION_1_1
			// OpenGL-1.1 �ȏ�̂ݗL��
//			if (u[i] > 0 && GL_TEXTURE0)
			if (GL_TEXTURE0 && u[i] > 0 && u[i] < current_maxTextureUnits)
			{
/*
				if ((int)GL_TEXTURE0 + u[i] != 0x84C0 && (int)GL_TEXTURE0 + u[i] != 0x84C1)
				{
					DEF_GL_TEXTURE0 = GL_TEXTURE0 ;
					DEF_GL_TEXTURE1 = GL_TEXTURE1 ;
				}
*/

				// �^�[�Q�b�g�w�肳��Ă���ꍇ
				glMultiTexCoord2f((GLenum)((int)GL_TEXTURE0 + u[i]),
								  s[i][0]*v[0] + s[i][1]*v[1] + s[i][2]*v[2],
								  t[i][0]*v[0] + t[i][1]*v[1] + t[i][2]*v[2]) ;
			}
			else
#endif
			{
				// �^�[�Q�b�g�w�肳��Ă��Ȃ��A�������� OpenGL-1.0 �̏ꍇ
				glTexCoord2f(s[i][0]*v[0] + s[i][1]*v[1] + s[i][2]*v[2],
							 t[i][0]*v[0] + t[i][1]*v[1] + t[i][2]*v[2]) ;

//				if (u[i] < 0)
//					break ;
			}
		}

#ifndef GL_VERSION_1_1
		// OpenGL-1.0 �̏ꍇ�ŏ��̂P�̂ݗL��
		break ;
#endif
	}

	// �Ō�ɒ��_���W�Z�b�g
	glVertex3fv(v) ;

/*
	if (GL_TEXTURE0 != 0x84C0 || GL_TEXTURE1 != 0x84C1)
	{
			DEF_GL_TEXTURE0 = GL_TEXTURE0 ;
			DEF_GL_TEXTURE1 = GL_TEXTURE1 ;
	}
*/
}


// multitexture �g�p���̍ő�e�N�X�`�����j�b�g��
// �J�����g�� Mesa �ȊO�� SGIS_multitexture �̏ꍇ�͂Q�Œ�
// IsSupported_*_multitexture() �����R�[���̏ꍇ�P
GLint GetMaxTextureUnits()
{
	return current_maxTextureUnits ;
}


// multitexture �g�p���̍ő�e�N�X�`�����j�b�g��
// �J�����g�� Mesa �ȊO�� SGIS_multitexture �̏ꍇ�͂Q�Œ�
// IsSupported_*_multitexture() �����R�[���̏ꍇ�P
/*
GLint GetMaxTextureUnits()
{
	static String pre_MultiTextureInterfaceName ;

	if (!current_MultiTextureInterfaceName)
		maxTextureUnits = 1 ;

	if (current_MultiTextureInterfaceNameString == pre_MultiTextureInterfaceName)
		return maxTextureUnits ;

	// �V���Ƀ}���`�e�N�X�`���C���^�t�F�[�X���Z�b�g����Ă���ꍇ��
	// glGet*() �Ŏ擾
	pre_MultiTextureInterfaceName = current_MultiTextureInterfaceNameString ;

#ifndef MESA
	if (current_MultiTextureInterfaceNameString == CURRENT_NAME_GL_SGIS_multitexture)
	{
		maxTextureUnits = 2 ;	// Mesa �ȊO�� SGIS_multitexture �ł́A�������Q�Ƃ݂Ȃ��i���̎��_�ŏ����I���j
		return maxTextureUnits ;
	}
#endif	// #ifndef MESA

	// ARB_multitexture or EXT_multitexture�A�������� Mesa �� SGIS_multitexture �Ȃ�A
	// OpenGL ����ő�e�N�X�`�����j�b�g�����擾
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTextureUnits) ;	// �e�N�X�`���̍ő僆�j�b�g��

	return maxTextureUnits ;
}
*/


// anisotropic filtering �g�p���̍ő� max anisotropy
GLfloat GetMaxTextureMaxAnisotropy()
{
	if (current_TextureFilterAnisotropicInterfaceNameString == "")
		return 1.0f ;

	GLfloat maxTextureMaxAnisotropy ;
	GLenum errCode = glGetError() ;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxTextureMaxAnisotropy) ;	// maximum degree of anisotropy

	// for fixing nVIDIA old driver's anisotropic filtering error...
	// ignore "Invalid Enum" Error
	errCode = glGetError() ;
	if (errCode == GL_INVALID_ENUM)
		maxTextureMaxAnisotropy = 1.0f ;

	return maxTextureMaxAnisotropy ;
}


// �t�H���E�V�F�[�f�B���O
// WIN_phong_shading
// �֐��̒ǉ��͂Ȃ��A�p�����^�̒ǉ��݂̂ł��邽�߁A�����^�C���݂̂̑Ή��� OK
//
/* �g�p��
	int phongshade = IsSupported_WIN_phong_shading() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (phongshade)
		glShadeModel(GL_PHONG_WIN) ;
*/
int IsSupported_WIN_phong_shading()
{
//#ifndef GL_WIN_phong_shading
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension("GL_WIN_phong_shading"))
		return FALSE ;	// WIN_phong_shading not supported

	return TRUE ;

//#endif	// #ifndef GL_WIN_phong_shading ... #else
}


// GL_ARB_texture_cube_map �T�|�[�g�`�F�b�N
//
/* �g�p��
	int has_ARB_texture_cube_map = IsSupported_ARB_texture_cube_map() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_ARB_texture_cube_map)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_ARB) ;

	if (has_ARB_texture_cube_map)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_ARB) ;
*/
int IsSupported_ARB_texture_cube_map()
{
//#ifndef GL_EXT_texture_cube_map
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_texture_cube_map))
		return FALSE ;	// GL_ARB_texture_cube_map not supported

	// texture_cube_map �֘A�ɂ��Ă͊֐����擾�ł����ꍇ�̂݃Z�b�g
//	current_TextureCubeMapInterfaceName = CURRENT_NAME_GL_ARB_texture_cube_map ;
//	current_TextureCubeMapInterfaceNameString = current_TextureCubeMapInterfaceName ;

	current_TexgenReflectionInterfaceName = CURRENT_NAME_GL_ARB_texture_cube_map ;
	current_TexgenReflectionInterfaceNameString = current_TexgenReflectionInterfaceName ;

	return TRUE ;
//#endif	// #ifndef GL_ARB_texture_cube_map
}

// GL_EXT_texture_cube_map �T�|�[�g�`�F�b�N
//
/* �g�p��
	int has_EXT_texture_cube_map = IsSupported_EXT_texture_cube_map() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texture_cube_map)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT) ;

	if (has_EXT_texture_cube_map)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT) ;
*/
int IsSupported_EXT_texture_cube_map()
{
//#ifndef GL_EXT_texture_cube_map
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_cube_map))
		return FALSE ;	// GL_EXT_texture_cube_map not supported

	// texture_cube_map �֘A�ɂ��Ă͊֐����擾�ł����ꍇ�̂݃Z�b�g
//	current_TextureCubeMapInterfaceName = CURRENT_NAME_GL_EXT_texture_cube_map ;
//	current_TextureCubeMapInterfaceNameString = current_TextureCubeMapInterfaceName ;

	current_TexgenReflectionInterfaceName = CURRENT_NAME_GL_EXT_texture_cube_map ;
	current_TexgenReflectionInterfaceNameString = current_TexgenReflectionInterfaceName ;

	return TRUE ;
//#endif	// #ifndef GL_EXT_texture_cube_map
}


// GL_EXT_texgen_reflection �T�|�[�g�`�F�b�N
//
/* �g�p��
	int has_EXT_texgen_reflection = IsSupported_EXT_texgen_reflection() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT) ;

	if (has_EXT_texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT) ;
*/
int IsSupported_EXT_texgen_reflection()
{
//#ifndef GL_EXT_texgen_reflection
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texgen_reflection))
		return FALSE ;	// GL_EXT_texgen_reflection not supported

	current_TexgenReflectionInterfaceName = CURRENT_NAME_GL_EXT_texgen_reflection ;
	current_TexgenReflectionInterfaceNameString = current_TexgenReflectionInterfaceName ;
	return TRUE ;
//#endif	// #ifndef GL_EXT_texgen_reflection
}


// GL_NV_texgen_reflection �T�|�[�g�`�F�b�N
//
/* �g�p��
	int has_NV_texgen_reflection = IsSupported_NV_texgen_reflection() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_NV_texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_NV) ;

	if (has_NV_texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV) ;
*/
int IsSupported_NV_texgen_reflection()
{
//#ifndef GL_NV_texgen_reflection
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_NV_texgen_reflection))
		return FALSE ;	// GL_NV_texgen_reflection not supported

	current_TexgenReflectionInterfaceName = CURRENT_NAME_GL_NV_texgen_reflection ;
	current_TexgenReflectionInterfaceNameString = current_TexgenReflectionInterfaceName ;
	return TRUE ;
//#endif	// #ifndef GL_NV_texgen_reflection
}


// texgen_reflection �֘A�T�|�[�g�`�F�b�N
// GL_ARB_texture_cube_map ��������
// GL_EXT_texture_cube_map ��������
// GL_EXT_texgen_reflection ��������
// GL_NV_texgen_reflection ���T�|�[�g���Ă��邩
//
/* �g�p��
	char *texgen_reflection = IsSupported_texgen_reflection() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP) ;

	if (texgen_reflection)
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP) ;
*/
char *IsSupported_texgen_reflection(int flag_ARB_texture_cube_map,
									int flag_EXT_texture_cube_map,
									int flag_EXT_texgen_reflection,
									int flag_NV_texgen_reflection)
{
	// GL_ARB_texture_cube_map
	if (flag_ARB_texture_cube_map && IsSupported_ARB_texture_cube_map())
		return current_TexgenReflectionInterfaceName ;

	// GL_EXT_texture_cube_map
	if (flag_EXT_texture_cube_map && IsSupported_EXT_texture_cube_map())
		return current_TexgenReflectionInterfaceName ;

	// GL_EXT_texgen_reflection
	if (flag_EXT_texgen_reflection && IsSupported_EXT_texgen_reflection())
		return current_TexgenReflectionInterfaceName ;

	// GL_NV_texgen_reflection
	if (flag_NV_texgen_reflection && IsSupported_NV_texgen_reflection())
		return current_TexgenReflectionInterfaceName ;

	// not supported
	return NULL ;
}


// Separate Specular Color �֘A
// �d�l��������Ȃ����ߕۗ�
// �����_�ł́AOpenGL-1.2 �̃p�����^�����̂܂܎g�p

// ARB_separate_specular_color
/* �g�p��
	int has_ARB_separate_specular_color = IsSupported_ARB_separate_specular_color() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_ARB_separate_specular_color)
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_ARB, GL_SEPARATE_SPECULAR_COLOR_ARB) ;

	if (has_ARB_separate_specular_color)
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_ARB, GL_SINGLE_COLOR_ARB) ;
*/
int IsSupported_ARB_separate_specular_color()
{
//#ifndef GL_ARB_separate_specular_color
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_separate_specular_color))
		return FALSE ;	// ARB_separate_specular_color not supported

	current_SeparateSpecularColorInterfaceName = CURRENT_NAME_GL_ARB_separate_specular_color ;
	current_SeparateSpecularColorInterfaceNameString = current_SeparateSpecularColorInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_ARB_separate_specular_color ... #else
}

// EXT_separate_specular_color
/* �g�p��
	int has_EXT_separate_specular_color = IsSupported_EXT_separate_specular_color() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_separate_specular_color)
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT) ;

  if (has_EXT_separate_specular_color)
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SINGLE_COLOR_EXT) ;
*/
int IsSupported_EXT_separate_specular_color()
{
//#ifndef GL_EXT_separate_specular_color
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_separate_specular_color))
		return FALSE ;	// EXT_separate_specular_color not supported

	current_SeparateSpecularColorInterfaceName = CURRENT_NAME_GL_EXT_separate_specular_color ;
	current_SeparateSpecularColorInterfaceNameString = current_SeparateSpecularColorInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_EXT_separate_specular_color ... #else
}


// ���炩�� separate_specular_color ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� separate_specular_color �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.2 Separate Specular Ccolor" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-1.2 �ȍ~�j
// "GL_ARB_separate_specular_color"
// "GL_EXT_separate_specular_color"
// NULL
//
/* �g�p��
	char *separate_specular_color = IsSupported_separate_specular_color() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (separate_specular_color)
		glLightModeli(GL_COLOR_LIGHT_MODEL, GL_SEPARATE_SPECULAR_COLOR) ;

	if (separate_specular_color)
		glLightModeli(GL_COLOR_LIGHT_MODEL, GL_SINGLE_COLOR) ;
*/
char *IsSupported_separate_specular_color(int flag_ARB, int flag_EXT)
{
//#ifdef GL_VERSION_separate_specular_color	// �R���p�C���E���s���o���ŁAseparate_specular_color ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� separate_specular_color ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_separate_specular_color_F)
	{
		current_SeparateSpecularColorInterfaceName = CURRENT_NAME_GL_VERSION_separate_specular_color ;
		current_SeparateSpecularColorInterfaceNameString = current_SeparateSpecularColorInterfaceName ;
		return current_SeparateSpecularColorInterfaceName ;
	}

//#endif	// #ifdef GL_VERSION_separate_specular_color	// �`�F�b�N�s�v

	// ARB_separate_specular_color
	if (flag_ARB && IsSupported_ARB_separate_specular_color())
		return current_SeparateSpecularColorInterfaceName ;

	// EXT_separate_specular_color
	if (flag_EXT && IsSupported_EXT_separate_specular_color())
		return current_SeparateSpecularColorInterfaceName ;

	// not supported
	return NULL ;
}


// Texture Env Add �֘A

// ARB_texture_env_add
/* �g�p��
	int has_ARB_texture_env_add = IsSupported_ARB_texture_env_add() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_ARB_texture_env_add)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD) ;
	}
*/
int IsSupported_ARB_texture_env_add()
{
//#ifndef GL_ARB_texture_env_add
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_env_add))
		return FALSE ;	// ARB_texture_env_add not supported

	current_TextureEnvAddInterfaceName = CURRENT_NAME_GL_ARB_texture_env_add ;
	current_TextureEnvAddInterfaceNameString = current_TextureEnvAddInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_ARB_texture_env_add ... #else
}

// EXT_texture_env_add
/* �g�p��
	int has_EXT_texture_env_add = IsSupported_EXT_texture_env_add() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texture_env_add)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD) ;
	}
*/
int IsSupported_EXT_texture_env_add()
{
//#ifndef GL_EXT_texture_env_add
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_env_add))
		return FALSE ;	// EXT_texture_env_add not supported

	current_TextureEnvAddInterfaceName = CURRENT_NAME_GL_EXT_texture_env_add ;
	current_TextureEnvAddInterfaceNameString = current_TextureEnvAddInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_EXT_texture_env_add ... #else
}


// ���炩�� texture_env_add ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_env_add �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Env Add" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-���� �ȍ~�j
// "GL_EXT_texture_env_add"
// "GL_ARB_texture_env_add"
// NULL
//
/* �g�p��
	char *texture_env_add = IsSupported_texture_env_add() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_env_add)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD) ;
	}
*/
char *IsSupported_texture_env_add(int flag_ARB, int flag_EXT)
{
//#ifdef GL_VERSION_texture_env_add	// �R���p�C���E���s���o���ŁAtexture_env_add ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� texture_env_add ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_env_add_F)
	{
		current_TextureEnvAddInterfaceName = CURRENT_NAME_GL_VERSION_texture_env_add ;
		current_TextureEnvAddInterfaceNameString = current_TextureEnvAddInterfaceName ;
		return current_TextureEnvAddInterfaceName ;
	}

//#endif	// #ifdef GL_VERSION_texture_env_add	// �`�F�b�N�s�v

	// ARB_texture_env_add
	if (flag_ARB && IsSupported_ARB_texture_env_add())
		return current_TextureEnvAddInterfaceName ;

	// EXT_texture_env_add
	if (flag_EXT && IsSupported_EXT_texture_env_add())
		return current_TextureEnvAddInterfaceName ;

	// not supported
	return NULL ;
}


// Texture Env Combine �֘A

// NV_texture_env_combine4
/* �g�p��
	int has_NV_texture_env_combine4 = IsSupported_NV_texture_env_combine4() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_NV_texture_env_combine4)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE4_NV) ;
	}
*/
int IsSupported_NV_texture_env_combine4()
{
//#ifndef GL_NV_texture_env_combine4
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_NV_texture_env_combine4))
		return FALSE ;	// NV_texture_env_combine4 not supported

	current_TextureEnvCombine4InterfaceName = CURRENT_NAME_GL_NV_texture_env_combine4 ;
	current_TextureEnvCombine4InterfaceNameString = current_TextureEnvCombine4InterfaceName ;
	current_TextureEnvCombineInterfaceName = CURRENT_NAME_GL_NV_texture_env_combine4 ;
	current_TextureEnvCombineInterfaceNameString = current_TextureEnvCombineInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_NV_texture_env_combine4 ... #else
}

// EXT_texture_env_combine
/* �g�p��
	int has_EXT_texture_env_combine = IsSupported_EXT_texture_env_combine() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texture_env_combine)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT) ;
	}
*/
int IsSupported_EXT_texture_env_combine()
{
//#ifndef GL_EXT_texture_env_combine
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_env_combine))
		return FALSE ;	// EXT_texture_env_combine not supported

	current_TextureEnvCombineInterfaceName = CURRENT_NAME_GL_EXT_texture_env_combine ;
	current_TextureEnvCombineInterfaceNameString = current_TextureEnvCombineInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_EXT_texture_env_combine ... #else
}


// ���炩�� texture_env_combine ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_env_combine �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Env Combine" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-���� �ȍ~�j
// "GL_NV_texture_env_combine4"
// "GL_EXT_texture_env_combine"
// NULL
//
/* �g�p��
	char *texture_env_combine = IsSupported_texture_env_combine() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_env_combine)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE) ;
	}
*/
char *IsSupported_texture_env_combine(int flag_NV, int flag_EXT)
{
//#ifdef GL_VERSION_texture_env_combine	// �R���p�C���E���s���o���ŁAtexture_env_combine ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� texture_env_combine ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_env_combine_F)
	{
		current_TextureEnvCombineInterfaceName = CURRENT_NAME_GL_VERSION_texture_env_combine ;
		current_TextureEnvCombineInterfaceNameString = current_TextureEnvCombineInterfaceName ;
		return current_TextureEnvCombineInterfaceName ;
	}

//#endif	// #ifdef GL_VERSION_texture_env_combine	// �`�F�b�N�s�v

	// NV_texture_env_combine4
	if (flag_NV && IsSupported_NV_texture_env_combine4())
		return current_TextureEnvCombineInterfaceName ;

	// EXT_texture_env_combine
	if (flag_NV && IsSupported_EXT_texture_env_combine())
		return current_TextureEnvCombineInterfaceName ;

	// not supported
	return NULL ;
}

// ���炩�� texture_env_combine4 ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_env_combine4 �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Env Combine4" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-���� �ȍ~�j
// "GL_NV_texture_env_combine4"
// NULL
//
/* �g�p��
	char *texture_env_combine4 = IsSupported_texture_env_combine4() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_env_combine4)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE4) ;
	}
*/
char *IsSupported_texture_env_combine4(int flag_NV)
{
//#ifdef GL_VERSION_texture_env_combine4	// �R���p�C���E���s���o���ŁAtexture_env_combine4 ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� texture_env_combine4 ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_env_combine4_F)
	{
		current_TextureEnvCombine4InterfaceName = CURRENT_NAME_GL_VERSION_texture_env_combine4 ;
		current_TextureEnvCombine4InterfaceNameString = current_TextureEnvCombine4InterfaceName ;
		current_TextureEnvCombineInterfaceName = CURRENT_NAME_GL_VERSION_texture_env_combine4 ;
		current_TextureEnvCombineInterfaceNameString = current_TextureEnvCombineInterfaceName ;
		return current_TextureEnvCombine4InterfaceName ;
	}

//#endif	// #ifdef GL_VERSION_texture_env_combine	// �`�F�b�N�s�v

	// NV_texture_env_combine4
	if (flag_NV && IsSupported_NV_texture_env_combine4())
		return current_TextureEnvCombine4InterfaceName ;

	// not supported
	return NULL ;
}


// Texture Filter Anisotropic �֘A

// EXT_texture_filter_anisotropic
/* �g�p��
	int has_EXT_texture_filter_anisotropic = IsSupported_EXT_texture_filter_anisotropic() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texture_filter_anisotropic)
	{
		float max_anisotropy ;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy) ;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy) ;
	}
*/
int IsSupported_EXT_texture_filter_anisotropic()
{
//#ifndef GL_EXT_texture_filter_anisotropic
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_filter_anisotropic))
		return FALSE ;	// EXT_texture_filter_anisotropic not supported

	current_TextureFilterAnisotropicInterfaceName = CURRENT_NAME_GL_EXT_texture_filter_anisotropic ;
	current_TextureFilterAnisotropicInterfaceNameString = current_TextureFilterAnisotropicInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_EXT_texture_filter_anisotropic ... #else
}


// ���炩�� texture_filter_anisotropic ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_filter_anisotropic �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Filter Anisotropic" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-���� �ȍ~�j
// "GL_EXT_texture_filter_anisotropic"
// NULL
//
/* �g�p��
	char *texture_filter_anisotropic = IsSupported_texture_filter_anisotropic() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_filter_anisotropic)
	{
		float max_anisotropy ;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &max_anisotropy) ;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, max_anisotropy) ;
	}
*/
char *IsSupported_texture_filter_anisotropic(int flag_EXT)
{
//#ifdef GL_VERSION_texture_filter_anisotropic	// �R���p�C���E���s���o���ŁAseparate_specular_color ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� texture_filter_anisotropic ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_filter_anisotropic_F)
	{
		current_TextureFilterAnisotropicInterfaceName = CURRENT_NAME_GL_VERSION_texture_filter_anisotropic ;
		current_TextureFilterAnisotropicInterfaceNameString = current_TextureFilterAnisotropicInterfaceName ;
		return current_TextureFilterAnisotropicInterfaceName ;
	}

//#endif	// #ifdef GL_VERSION_texture_filter_anisotropic	// �`�F�b�N�s�v

	// EXT_texture_filter_anisotropic
	if (flag_EXT && IsSupported_EXT_texture_filter_anisotropic())
		return current_TextureFilterAnisotropicInterfaceName ;

	// not supported
	return NULL ;
}


// Texture Object �֘A

// EXT_texture_object
/* �g�p��
	int has_EXT_texture_object = IsSupported_EXT_texture_object() ;

#ifdef GL_EXT_texture_object
	if (has_EXT_texture_object)
		BindTextureEXT(GL_TEXTURE_2D, texture) ;
#endif
*/
int IsSupported_EXT_texture_object()
{
#ifndef GL_EXT_texture_object
	return FALSE ;

#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_object))
		return FALSE ;	// GL_EXT_texture_object not supported

	// Get proc address (WGL only)
#if defined(WIN32) && !defined(MESA)
	if (!(glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)wglGetProcAddress("glGenTexturesEXT")) &&
		!(glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glGenTexturesEXT")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glGenTexturesEXT@8")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	if (!(glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC) wglGetProcAddress("glDeleteTexturesEXT")) &&
		!(glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glDeleteTexturesEXT")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glDeleteTexturesEXT@8")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	if (!(glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)wglGetProcAddress("glBindTextureEXT")) &&
		!(glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glBindTextureEXT")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glBindTextureEXT@8")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;

	if (!(glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)wglGetProcAddress("glIsTextureEXT")) &&
		!(glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glIsTextureEXT")) &&	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glIsTextureEXT@4")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;
#endif	// #if defined(WIN32) && !defined(MESA)

	p_glGenTextures    = glGenTexturesEXT ;
	p_glDeleteTextures = glDeleteTexturesEXT ;
	p_glBindTexture    = glBindTextureEXT ;
	p_glIsTexture      = glIsTextureEXT ;

	current_TextureObjectInterfaceName = CURRENT_NAME_GL_EXT_texture_object ;
	current_TextureObjectInterfaceNameString = current_TextureObjectInterfaceName ;
	return TRUE ;

#endif	// #ifndef GL_EXT_texture_object ... #else
}


// ���炩�� texture_object ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_object �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.1 Texture Object" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-1.1 �ȍ~�j
// "GL_EXT_texture_object"
// NULL
//
/* �g�p��
	char *texture_object = IsSupported_texture_object() ;

	if (texture_object)
		glBindTexture(GL_TEXTURE_2D, texture) ;
*/
char *IsSupported_texture_object(int flag_EXT)
{
#ifdef GL_VERSION_texture_object
	// �R���p�C���E���s���o���ŁAtexture_object ���T�|�[�g����o�[�W�����ȍ~�Ȃ�
	if (GetOpenGLVersion() >= GL_VERSION_texture_object_F)
	{
		current_TextureObjectInterfaceName = CURRENT_NAME_GL_VERSION_texture_object ;
		current_TextureObjectInterfaceNameString = current_TextureObjectInterfaceName ;
		return current_TextureObjectInterfaceName ;
	}

#endif	// #ifdef GL_VERSION_separate_specular_color

	// EXT_texture_object
	if (flag_EXT && IsSupported_EXT_texture_object())
		return current_TextureObjectInterfaceName ;

	// not supported
	return NULL ;
}


// Polygon Offset �֘A

// EXT_polygon_offset
/* �g�p��
	int has_EXT_polygon_offset = IsSupported_EXT_polygon_offset() ;

#ifdef GL_EXT_polygon_offset
	if (has_EXT_polygon_offset)
	{
		glPolygonOffsetEXT(units, bias) ;
		glEnable(GL_POLYGON_OFFSET_EXT) ;

		glGetFloatv(GL_POLYGON_OFFSET_FACTOR_EXT, &facter) ;
		glGetFloatv(GL_POLYGON_OFFSET_BIAS_EXT, &bias) ;
	}
#endif
*/
int IsSupported_EXT_polygon_offset()
{
#ifndef GL_EXT_polygon_offset
	return FALSE ;

#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_object))
		return FALSE ;	// GL_EXT_polygon_offset not supported

	// Get proc address (WGL only)
#if defined(WIN32) && !defined(MESA)
	if (!(glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC)wglGetProcAddress("glPolygonOffsetEXT")) &&
		!(glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("glPolygonOffsetEXT")) &&		// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		!(glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC)OpenGLDLLCtrl::openGLDLLCtrl.GetProcAddress("_glPolygonOffsetEXT@8")))	// ��Ŏ擾�ł��Ȃ������Ƃ��́ADLL ����C���|�[�g�iMesa DLL �p�j
		return FALSE ;
#endif	// #if defined(WIN32) && !defined(MESA)

	p_glPolygonOffset = glPolygonOffsetEXT ;

	DEF_GL_POLYGON_OFFSET_POINT  = GL_POLYGON_OFFSET_EXT ;	// EXT_polygon_offset �ł́A���ׂċ��ʁi�L���Ȃ̂� FILL �̂݁H�j
	DEF_GL_POLYGON_OFFSET_LINE   = GL_POLYGON_OFFSET_EXT ;
	DEF_GL_POLYGON_OFFSET_FILL   = GL_POLYGON_OFFSET_EXT ;
	DEF_GL_POLYGON_OFFSET_FACTOR = GL_POLYGON_OFFSET_FACTOR_EXT ;
	DEF_GL_POLYGON_OFFSET_UNITS  = GL_POLYGON_OFFSET_BIAS_EXT ;

	current_PolygonOffsetInterfaceName = CURRENT_NAME_GL_EXT_polygon_offset ;
	current_PolygonOffsetInterfaceNameString = current_PolygonOffsetInterfaceName ;
	return TRUE ;

#endif	// #ifndef GL_EXT_polygon_offset ... #else
}


// ���炩�� polygon_offset ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� polygon_offset �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.1 Polygon Offset" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-1.1 �ȍ~�j
// "GL_EXT_polygon_offset"
// NULL
//
/* �g�p��
	char *polygon_offset = IsSupported_polygon_offset() ;

	if (polygon_offset)
	{
		glPolygonOffset(facter, units) ;
		glEnable(GL_POLYGON_OFFSET_FILL) ;	// EXT_polygon_offset �̏ꍇ POINT, LINE ������

		glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &facter) ;
		glGetFloatv(GL_POLYGON_OFFSET_UNITS, &units) ;
	}
*/
char *IsSupported_polygon_offset(int flag_EXT)
{
#ifdef GL_VERSION_polygon_offset
	// �R���p�C���E���s���o���ŁApolygon_offset ���T�|�[�g����o�[�W�����ȍ~�Ȃ�
	if (GetOpenGLVersion() >= GL_VERSION_polygon_offset_F)
	{
		current_PolygonOffsetInterfaceName = CURRENT_NAME_GL_VERSION_polygon_offset ;
		current_PolygonOffsetInterfaceNameString = current_PolygonOffsetInterfaceName ;
		return current_PolygonOffsetInterfaceName ;
	}

#endif	// #ifdef GL_VERSION_separate_specular_color

	// EXT_polygon_offset
	if (flag_EXT && IsSupported_EXT_polygon_offset())
		return current_PolygonOffsetInterfaceName ;

	// not supported
	return NULL ;
}



// Texture Compression Enum �֘A

// GL_ARB_texture_compression
/* �g�p��
	int hasEnum_ARB_texture_compression = IsSupportedEnum_ARB_texture_compression() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (hasEnum_ARB_texture_compression)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB_ARB, ...) ;
	}
*/
int IsSupported_ARB_texture_compression_Enum()
{
//#ifndef GL_ARB_texture_compression
//	return FALSE ;
//
//#else
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_texture_compression))
		return FALSE ;	// GL_ARB_texture_compression not supported

	current_TextureCompressionInterfaceEnumName = CURRENT_NAME_GL_ARB_texture_compression ;
	current_TextureCompressionInterfaceEnumNameString = current_TextureCompressionInterfaceEnumName ;
	return TRUE ;

//#endif	// #ifndef GL_ARB_texture_compression ... #else
}


// ���炩�� texture_compression ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_compression �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Compression" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�iOpenGL-���� �ȍ~�j
// "GL_ARB_texture_compression"
// NULL
//
/* �g�p��
	char *enum_texture_compression = IsSupportedEnum_texture_compression() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (enum_texture_compression)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB, ...) ;
	}
*/
char *IsSupported_texture_compression_Enum(int flag_ARB)
{
//#ifdef GL_VERSION_texture_compression	// �R���p�C���E���s���o���ŁAtexture_compression ���T�|�[�g����o�[�W�����ȍ~�Ȃ�

	// �����^�C���� texture_compression ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_compression_F)
	{
		current_TextureCompressionInterfaceEnumName = CURRENT_NAME_GL_VERSION_texture_compression ;
		current_TextureCompressionInterfaceEnumNameString = current_TextureCompressionInterfaceEnumName ;
		return current_TextureCompressionInterfaceEnumName ;
	}

//#endif	// #ifdef GL_VERSION_texture_compression	// �`�F�b�N�s�v

	// ARB_texture_compression
	if (flag_ARB && IsSupported_ARB_texture_compression_Enum())
		return current_TextureCompressionInterfaceEnumName ;

	// not supported
	return NULL ;
}


// Texture Compression S3TC �֘A

// GL_EXT_texture_compression_s3tc
/* �g�p��
	int has_EXT_texture_compression_s3tc = IsSupported_EXT_texture_compression_s3tc() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_EXT_texture_compression_s3tc)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB_S3TC_DXT1_EXT, ...) ;
	}
*/
int IsSupported_EXT_texture_compression_s3tc()
{
//#ifndef GL_EXT_texture_compression_s3tc
//	return FALSE ;
//
//#else
	// GL_ARB_texture_compression �K�{
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_texture_compression) ||
		!IsSupported_OpenGLExtension(CURRENT_NAME_GL_EXT_texture_compression_s3tc))
		return FALSE ;	// GL_EXT_texture_compression_s3tc not supported

	current_TextureCompressionS3TCInterfaceName = CURRENT_NAME_GL_EXT_texture_compression_s3tc ;
	current_TextureCompressionS3TCInterfaceNameString = current_TextureCompressionS3TCInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_EXT_texture_compression_s3tc ... #else
}


// ���炩�� texture_compression_s3tc ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_compression_s3tc �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Compression S3TC" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�i������Ȃ��H�j
// "GL_EXT_texture_compression_s3tc"
// NULL
//
/* �g�p��
	char *texture_compression_S3TC = IsSupported_texture_compression_s3tc() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_compression_S3TC)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB_S3TC_DXT1, ...) ;
	}
*/
char *IsSupported_texture_compression_s3tc(int flag_EXT)
{
	// �����^�C���� texture_compression_s3tc ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_compression_s3tc_F)
	{
		current_TextureCompressionS3TCInterfaceName = CURRENT_NAME_GL_VERSION_texture_compression_s3tc ;
		current_TextureCompressionS3TCInterfaceNameString = current_TextureCompressionS3TCInterfaceName ;
		return current_TextureCompressionS3TCInterfaceName ;
	}

	// EXT_texture_compression_s3tc
	if (flag_EXT && IsSupported_EXT_texture_compression_s3tc())
		return current_TextureCompressionS3TCInterfaceName ;

	// not supported
	return NULL ;
}


// S3 original S3TC �֘A

// GL_S3_s3tc
/* �g�p��
	int has_S3_s3tc = IsSupported_S3_s3tc() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_S3_s3tc)
	{
		glTexImage2D( ..., GL_RGB_S3TC, ...) ;
	}
*/
int IsSupported_S3_s3tc()
{
//#ifndef GL_S3_s3tc
//	return FALSE ;
//
//#else
	// GL_ARB_texture_compression �s�v
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_S3_s3tc))
		return FALSE ;	// GL_EXT_texture_compression_s3tc not supported

	current_S3TCInterfaceName = CURRENT_NAME_GL_S3_s3tc ;
	current_S3TCInterfaceNameString = current_S3TCInterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_S3_s3tc ... #else
}


// ���炩�� S3_s3tc ���T�|�[�g���邩�i���ۂɂ� GL_S3_s3tc �̂݁j
// ���^�[���l�� �T�|�[�g���� s3tc �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "GL_S3_s3tc"
// NULL
//
/* �g�p��
	char *supported_S3TC = IsSupported_s3tc() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (supported_S3TC)
	{
		glTexImage2D( ..., GL_RGB_S3TC, ...) ;
	}
*/
char *IsSupported_s3tc(int flag_S3)
{
	// S3_s3tc
	if (flag_S3 && IsSupported_S3_s3tc())
		return current_S3TCInterfaceName ;

	// not supported
	return NULL ;
}


// Texture Compression FXT1 �֘A

// GL_3DFX_texture_compression_FXT1
/* �g�p��
	int has_3DFX_texture_compression_FXT1 = IsSupported_3DFX_texture_compression_FXT1() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (has_3DFX_texture_compression_FXT1)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB_FXT1_3DFX, ...) ;
	}
*/
int IsSupported_3DFX_texture_compression_FXT1()
{
//#ifndef GL_3DFX_texture_compression_FXT1
//	return FALSE ;
//
//#else
	// GL_ARB_texture_compression �K�{
	if (!IsSupported_OpenGLExtension(CURRENT_NAME_GL_ARB_texture_compression) ||
		!IsSupported_OpenGLExtension(CURRENT_NAME_GL_3DFX_texture_compression_FXT1))
		return FALSE ;	// GL_EXT_texture_compression_s3tc not supported

	current_TextureCompressionFXT1InterfaceName = CURRENT_NAME_GL_3DFX_texture_compression_FXT1 ;
	current_TextureCompressionFXT1InterfaceNameString = current_TextureCompressionFXT1InterfaceName ;
	return TRUE ;

//#endif	// #ifndef GL_3DFX_texture_compression_FXT1 ... #else
}


// ���炩�� texture_compression_FXT1 ���T�|�[�g���邩
// ���^�[���l�� �T�|�[�g���� texture_compression_FXT1 �̖��̃|�C���^�܂��� NULL
// �D�揇��
// "OpenGL-1.? Texture Compression FXT1" �c�c�c OpenGL �ɂ��l�C�e�B�u�T�|�[�g�i������Ȃ��H�j
// "GL_3DFX_texture_compression_FXT1"
// NULL
//
/* �g�p��
	char *texture_compression_FXT1 = IsSupported_texture_compression_FXT1() ;

	// �֐��̒ǉ����Ȃ����� #ifdef �͕s�v
	if (texture_compression_FXT1)
	{
		glTexImage2D( ..., GL_COMPRESSED_RGB_FXT1, ...) ;
	}
*/
char *IsSupported_texture_compression_FXT1(int flag_3DFX)
{
	// �����^�C���� texture_compression_FXT1 ���T�|�[�g����o�[�W�����ȍ~�Ȃ� OK
	// �p�����^�̒ǉ��݂̂ŗǂ�����
	if (GetOpenGLVersion() >= GL_VERSION_texture_compression_FXT1_F)
	{
		current_TextureCompressionFXT1InterfaceName = CURRENT_NAME_GL_VERSION_texture_compression_FXT1 ;
		current_TextureCompressionFXT1InterfaceNameString = current_TextureCompressionFXT1InterfaceName ;
		return current_TextureCompressionFXT1InterfaceName ;
	}

	// 3DFX_texture_compression_FXT1
	if (flag_3DFX && IsSupported_3DFX_texture_compression_FXT1())
		return current_TextureCompressionFXT1InterfaceName ;

	// not supported
	return NULL ;
}



// ���ݗL���ɂȂ��Ă��铝���C���^�t�F�[�X
String CurrentInterface_multitexture()
{
	return current_MultiTextureInterfaceNameString ;
}

String CurrentInterface_separate_specular_color()
{
	return current_SeparateSpecularColorInterfaceNameString ;
}

String CurrentInterface_texture_object()
{
	return current_TextureObjectInterfaceNameString ;
}

String CurrentInterface_polygon_offset()
{
	return current_PolygonOffsetInterfaceNameString ;
}

String CurrentInterface_texture_cube_map()
{
	return current_TextureCubeMapInterfaceNameString ;
}

String CurrentInterface_texgen_reflection()
{
	return current_TexgenReflectionInterfaceNameString ;
}

String CurrentInterfaceEnum_texture_compression()
{
	return current_TextureCompressionInterfaceEnumNameString ;
}

String CurrentInterface_texture_compression_s3tc()
{
	return current_TextureCompressionS3TCInterfaceNameString ;
}


// Texture Internal Formats
// Default: 3
GLint InternalFormat(String str)
{
	GLint format ;

	format = (int)(str.Character(1) - '0') ;
	if (format < 0 || format > 4)
		format = 0 ;

	str.Upper() ;
	if (!format && Left(str, 3) != "GL_")
		str = "GL_" + str ;

	// "_ALPHA" ���Ȃ� "_A" ������ "RGB" �������ꍇ
	// !"RGB" �́A RGB5_A1 ���ɔ��������Ȃ���
	if (!(str / "_ALPHA") && (str / "_A") && !(str / "RGB"))
		str.ReplaceString("_A", "_ALPHA") ;

	if (!(str / "_LUMINANCE"))	str.ReplaceString("_L", "_LUMINANCE") ;
	if (!(str / "_INTENSITY"))	str.ReplaceString("_I", "_INTENSITY") ;
	if (!(str / "_COMPRESSED"))	str.ReplaceString("_C", "_COMPRESSED") ;

	if (GetOpenGLVersion() >= 1.1f)
	{
		format = GL_RGB ;	// default internal format = GL_RGB

		// Is s3tc available
		if (current_S3TCInterfaceName)
		{
			if      (str == "GL_RGB_S3TC")		format = GL_RGB_S3TC ;
			else if (str == "GL_RGB4_S3TC")		format = GL_RGB4_S3TC ;
			else if (str == "GL_RGBA_S3TC")		format = GL_RGBA_S3TC ;
			else if (str == "GL_RGBA4_S3TC")	format = GL_RGBA4_S3TC ;
		}

		// Is texture_compression available
		if (current_TextureCompressionInterfaceEnumName)
		{
			// Is texture_compression_s3tc available
			if (current_TextureCompressionS3TCInterfaceName)
			{
				if      (str / "GL_COMPRESSED_RGB_S3TC_DXT1")	format = GL_COMPRESSED_RGB_S3TC_DXT1 ;
				else if (str / "GL_COMPRESSED_RGBA_S3TC_DXT1")	format = GL_COMPRESSED_RGBA_S3TC_DXT1 ;
				else if (str / "GL_COMPRESSED_RGBA_S3TC_DXT3")	format = GL_COMPRESSED_RGBA_S3TC_DXT3 ;
				else if (str / "GL_COMPRESSED_RGBA_S3TC_DXT5")	format = GL_COMPRESSED_RGBA_S3TC_DXT5 ;
			}

			if (!current_S3TCInterfaceName && !current_TextureCompressionS3TCInterfaceName)	// S3_s3tc �� EXT_texture_compression_s3tc ���T�|�[�g���Ă��Ȃ��Ȃ�
			{
				if      (str / "GL_COMPRESSED_RGB_S3TC_DXT1" || str / "RGB_S3TC" || str / "RGB4_S3TC")		format = GL_COMPRESSED_RGB ;
				else if (str / "GL_COMPRESSED_RGBA_S3TC_DXT" || str / "RGBA_S3TC" || str / "RGBA4_S3TC")	format = GL_COMPRESSED_RGBA ;	// RGBA_DXT? or RGBA?_S3TC
			}

			// Is texture_compression_FXT1 available
			if (current_TextureCompressionFXT1InterfaceName)
			{
				if      (str / "GL_COMPRESSED_RGB_FXT1")	format = GL_COMPRESSED_RGB_FXT1 ;
				else if (str / "GL_COMPRESSED_RGBA_FXT1")	format = GL_COMPRESSED_RGBA_FXT1 ;
			}
			else
			{
				if      (str / "GL_COMPRESSED_RGB_FXT1")	format = GL_COMPRESSED_RGB ;
				else if (str / "GL_COMPRESSED_RGBA_FXT1")	format = GL_COMPRESSED_RGBA ;
			}

			if      (str == "GL_COMPRESSED_ALPHA"           || str == "GL_COMPRESSED_ALPHA_ARB")			format = GL_COMPRESSED_ALPHA ;
			else if (str == "GL_COMPRESSED_LUMINANCE"       || str == "GL_COMPRESSED_LUMINANCE_ARB")		format = GL_COMPRESSED_LUMINANCE ;
			else if (str == "GL_COMPRESSED_LUMINANCE_ALPHA" || str == "GL_COMPRESSED_LUMINANCE_ALPHA_ARB")	format = GL_COMPRESSED_LUMINANCE_ALPHA ;
			else if (str == "GL_COMPRESSED_INTENSITY"       || str == "GL_COMPRESSED_INTENSITY_ARB")		format = GL_COMPRESSED_INTENSITY ;
			else if (str == "GL_COMPRESSED_RGB"             || str == "GL_COMPRESSED_RGB_ARB")				format = GL_COMPRESSED_RGB ;
			else if (str == "GL_COMPRESSED_RGBA"            || str == "GL_COMPRESSED_RGBA_ARB")				format = GL_COMPRESSED_RGBA ;
		}
		else	// (!current_TextureCompressionInterfaceEnumName)
		{
			// Is s3tc available
			if (current_S3TCInterfaceName)
			{
				if      (str / "GL_COMPRESSED_RGB")		format = GL_RGB_S3TC ;
				else if (str / "GL_COMPRESSED_RGBA")	format = GL_RGBA_S3TC ;
			}

			if (format == GL_RGB)
			{
				if      (str / "GL_COMPRESSED_ALPHA")			format = GL_ALPHA ;
				else if (str / "GL_COMPRESSED_LUMINANCE")		format = GL_LUMINANCE ;
				else if (str / "GL_COMPRESSED_LUMINANCE_ALPHA")	format = GL_LUMINANCE_ALPHA ;
				else if (str / "GL_COMPRESSED_INTENSITY")		format = GL_INTENSITY ;
				else if (str / "GL_COMPRESSED_RGB")				format = GL_RGB ;
				else if (str / "GL_COMPRESSED_RGBA")			format = GL_RGBA ;
			}
		}

		if      (str == "GL_ALPHA")		format = GL_ALPHA ;
		else if (str == "GL_ALPHA4")	format = GL_ALPHA4 ;
		else if (str == "GL_ALPHA8")	format = GL_ALPHA8 ;
		else if (str == "GL_ALPHA12")	format = GL_ALPHA12 ;
		else if (str == "GL_ALPHA16")	format = GL_ALPHA16 ;

		else if (str == "1")				format = 1 ;
		else if (str == "GL_LUMINANCE")		format = GL_LUMINANCE ;
		else if (str == "GL_LUMINANCE4")	format = GL_LUMINANCE4 ;
		else if (str == "GL_LUMINANCE8")	format = GL_LUMINANCE8 ;
		else if (str == "GL_LUMINANCE12")	format = GL_LUMINANCE12 ;
		else if (str == "GL_LUMINANCE16")	format = GL_LUMINANCE16 ;

		else if (str == "2")						format = 2 ;
		else if (str == "GL_LUMINANCE_ALPHA")		format = GL_LUMINANCE_ALPHA ;
		else if (str == "GL_LUMINANCE4_ALPHA4")		format = GL_LUMINANCE4_ALPHA4 ;
		else if (str == "GL_LUMINANCE6_ALPHA2")		format = GL_LUMINANCE6_ALPHA2 ;
		else if (str == "GL_LUMINANCE8_ALPHA8")		format = GL_LUMINANCE8_ALPHA8 ;
		else if (str == "GL_LUMINANCE12_ALPHA4")	format = GL_LUMINANCE12_ALPHA4 ;
		else if (str == "GL_LUMINANCE12_ALPHA12")	format = GL_LUMINANCE12_ALPHA12 ;
		else if (str == "GL_LUMINANCE16_ALPHA16")	format = GL_LUMINANCE16_ALPHA16 ;

		else if (str == "GL_INTENSITY")		format = GL_INTENSITY ;
		else if (str == "GL_INTENSITY4")	format = GL_INTENSITY4 ;
		else if (str == "GL_INTENSITY8")	format = GL_INTENSITY8 ;
		else if (str == "GL_INTENSITY12")	format = GL_INTENSITY12 ;
		else if (str == "GL_INTENSITY16")	format = GL_INTENSITY16 ;

		else if (str == "3")			format = 3 ;
		else if (str == "GL_RGB")		format = GL_RGB ;
		else if (str == "GL_R3_G3_B2")	format = GL_R3_G3_B2 ;
		else if (str == "GL_RGB4")		format = GL_RGB4 ;
		else if (str == "GL_RGB5")		format = GL_RGB5 ;
		else if (str == "GL_RGB8")		format = GL_RGB8 ;
		else if (str == "GL_RGB10")		format = GL_RGB10 ;
		else if (str == "GL_RGB12")		format = GL_RGB12 ;
		else if (str == "GL_RGB16")		format = GL_RGB16 ;

		else if (str == "4")			format = 4 ;
		else if (str == "GL_RGBA")		format = GL_RGBA ;
		else if (str == "GL_RGBA2")		format = GL_RGBA2 ;
		else if (str == "GL_RGBA4")		format = GL_RGBA4 ;
		else if (str == "GL_RGB5_A1")	format = GL_RGB5_A1 ;
		else if (str == "GL_RGBA8")		format = GL_RGBA8 ;
		else if (str == "GL_RGB10_A2")	format = GL_RGB10_A2 ;
		else if (str == "GL_RGBA12")	format = GL_RGBA12 ;
		else if (str == "GL_RGBA16")	format = GL_RGBA16 ;
	}
	else
	{
		format = 3 ;	// default component = 3 (GL_RGB)

		if      (str == "1")				format = 1 ;
		else if (str == "GL_LUMINANCE")		format = 1 ;
		else if (str == "GL_LUMINANCE4")	format = 1 ;
		else if (str == "GL_LUMINANCE8")	format = 1 ;
		else if (str == "GL_LUMINANCE12")	format = 1 ;
		else if (str == "GL_LUMINANCE16")	format = 1 ;

		else if (str == "2")						format = 2 ;
		else if (str == "GL_LUMINANCE_ALPHA")		format = 2 ;
		else if (str == "GL_LUMINANCE4_ALPHA4")		format = 2 ;
		else if (str == "GL_LUMINANCE6_ALPHA2")		format = 2 ;
		else if (str == "GL_LUMINANCE8_ALPHA8")		format = 2 ;
		else if (str == "GL_LUMINANCE12_ALPHA4")	format = 2 ;
		else if (str == "GL_LUMINANCE12_ALPHA12")	format = 2 ;
		else if (str == "GL_LUMINANCE16_ALPHA16")	format = 2 ;

		else if (str == "3")			format = 3 ;
		else if (str == "GL_RGB")		format = 3 ;
		else if (str == "GL_R3_G3_B2")	format = 3 ;
		else if (str == "GL_RGB4")		format = 3 ;
		else if (str == "GL_RGB5")		format = 3 ;
		else if (str == "GL_RGB8")		format = 3 ;
		else if (str == "GL_RGB10")		format = 3 ;
		else if (str == "GL_RGB12")		format = 3 ;
		else if (str == "GL_RGB16")		format = 3 ;

		else if (str == "4")			format = 4 ;
		else if (str == "GL_RGBA")		format = 4 ;
		else if (str == "GL_RGBA2")		format = 4 ;
		else if (str == "GL_RGBA4")		format = 4 ;
		else if (str == "GL_RGB5_A1")	format = 4 ;
		else if (str == "GL_RGBA8")		format = 4 ;
		else if (str == "GL_RGB10_A2")	format = 4 ;
		else if (str == "GL_RGBA12")	format = 4 ;
		else if (str == "GL_RGBA16")	format = 4 ;
	}

	return format ;
}


String InternalFormatString(GLint internalFormat)
{
	String str ;

	switch (internalFormat)
	{
	case 1:	str = "1 component (GL_LUMINANCE)" ;		break ;
	case 2:	str = "2 components (GL_LUMINANCE_ALPHA)" ;	break ;
	case 3:	str = "3 components (GL_RGB)" ;				break ;
	case 4:	str = "4 components (GL_RGBA)" ;			break ;

	case GL_ALPHA:		str = "GL_ALPHA" ;		break ;
	case GL_ALPHA4:		str = "GL_ALPHA4" ;		break ;
	case GL_ALPHA8:		str = "GL_ALPHA8" ;		break ;
	case GL_ALPHA12:	str = "GL_ALPHA12" ;	break ;
	case GL_ALPHA16:	str = "GL_ALPHA16" ;	break ;

	case GL_LUMINANCE:		str = "GL_LUMINANCE" ;		break ;
	case GL_LUMINANCE4:		str = "GL_LUMINANCE4" ;		break ;
	case GL_LUMINANCE8:		str = "GL_LUMINANCE8" ;		break ;
	case GL_LUMINANCE12:	str = "GL_LUMINANCE12" ;	break ;
	case GL_LUMINANCE16:	str = "GL_LUMINANCE16" ;	break ;

	case GL_LUMINANCE_ALPHA:		str = "GL_LUMINANCE_ALPHA" ;		break ;
	case GL_LUMINANCE4_ALPHA4:		str = "GL_LUMINANCE4_ALPHA4" ;		break ;
	case GL_LUMINANCE6_ALPHA2:		str = "GL_LUMINANCE6_ALPHA2" ;		break ;
	case GL_LUMINANCE8_ALPHA8:		str = "GL_LUMINANCE8_ALPHA8" ;		break ;
	case GL_LUMINANCE12_ALPHA4:		str = "GL_LUMINANCE12_ALPHA4" ;		break ;
	case GL_LUMINANCE12_ALPHA12:	str = "GL_LUMINANCE12_ALPHA12" ;	break ;
	case GL_LUMINANCE16_ALPHA16:	str = "GL_LUMINANCE16_ALPHA16" ;	break ;

	case GL_INTENSITY:		str = "GL_INTENSITY" ;		break ;
	case GL_INTENSITY4:		str = "GL_INTENSITY4" ;		break ;
	case GL_INTENSITY8:		str = "GL_INTENSITY8" ;		break ;
	case GL_INTENSITY12:	str = "GL_INTENSITY12" ;	break ;
	case GL_INTENSITY16:	str = "GL_INTENSITY16" ;	break ;

	case GL_RGB:		str = "GL_RGB" ;		break ;
	case GL_R3_G3_B2:	str = "GL_R3_G3_B2" ;	break ;
	case GL_RGB4:		str = "GL_RGB4" ;		break ;
	case GL_RGB5:		str = "GL_RGB5" ;		break ;
	case GL_RGB8:		str = "GL_RGB8" ;		break ;
	case GL_RGB10:		str = "GL_RGB10" ;		break ;
	case GL_RGB12:		str = "GL_RGB12" ;		break ;
	case GL_RGB16:		str = "GL_RGB16" ;		break ;

	case GL_RGBA:		str = "GL_RGBA" ;		break ;
	case GL_RGBA2:		str = "GL_RGBA2" ;		break ;
	case GL_RGBA4:		str = "GL_RGBA4" ;		break ;
	case GL_RGB5_A1:	str = "GL_RGB5_A1" ;	break ;
	case GL_RGBA8:		str = "GL_RGBA8" ;		break ;
	case GL_RGB10_A2:	str = "GL_RGB10_A2" ;	break ;
	case GL_RGBA12:		str = "GL_RGBA12" ;		break ;
	case GL_RGBA16:		str = "GL_RGBA16" ;		break ;

	// compressed format
	case GL_COMPRESSED_ALPHA:			str = "GL_COMPRESSED_ALPHA" ;			break ;
	case GL_COMPRESSED_LUMINANCE:		str = "GL_COMPRESSED_LUMINANCE" ;		break ;
	case GL_COMPRESSED_LUMINANCE_ALPHA:	str = "GL_COMPRESSED_LUMINANCE_ALPHA" ;	break ;
	case GL_COMPRESSED_INTENSITY:		str = "GL_COMPRESSED_INTENSITY" ;		break ;
	case GL_COMPRESSED_RGB:				str = "GL_COMPRESSED_RGB" ;				break ;
	case GL_COMPRESSED_RGBA:			str = "GL_COMPRESSED_RGBA" ;			break ;

	// EXT s3tc format
	case GL_COMPRESSED_RGB_S3TC_DXT1:	str = "GL_COMPRESSED_RGB_S3TC_DXT1" ;	break ;
	case GL_COMPRESSED_RGBA_S3TC_DXT1:	str = "GL_COMPRESSED_RGBA_S3TC_DXT1" ;	break ;
	case GL_COMPRESSED_RGBA_S3TC_DXT3:	str = "GL_COMPRESSED_RGBA_S3TC_DXT3" ;	break ;
	case GL_COMPRESSED_RGBA_S3TC_DXT5:	str = "GL_COMPRESSED_RGBA_S3TC_DXT5" ;	break ;

	// S3 s3tc format
	case GL_RGB_S3TC:	str = "GL_RGB_S3TC" ;	break ;
	case GL_RGB4_S3TC:	str = "GL_RGB4_S3TC" ;	break ;
	case GL_RGBA_S3TC:	str = "GL_RGBA_S3TC" ;	break ;
	case GL_RGBA4_S3TC:	str = "GL_RGBA4_S3TC" ;	break ;

	// FXT1 format
	case GL_COMPRESSED_RGB_FXT1:	str = "GL_COMPRESSED_RGB_FXT1" ;	break ;
	case GL_COMPRESSED_RGBA_FXT1:	str = "GL_COMPRESSED_RGBA_FXT1" ;	break ;

	default:
		str = "Unknown format" ; break ;
	}

	return str ;
}


// Win32
// opengl32.dll �����[�h
// ���݂̂Ƃ���AWin32 �� Mesa DLL ���g�p����ꍇ�p
#ifdef WIN32
OpenGLDLLCtrl OpenGLDLLCtrl::openGLDLLCtrl ;
#endif	// #ifdef WIN32
