
#ifndef __ENV_GLASS_H__
#define __ENV_GLASS_H__

#ifdef   WIN32
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#define USE_TIME_GET_TIME
#ifdef USE_TIME_GET_TIME
#include <mmsystem.h>
#endif

//#define USE_PERFORMANCE_COUNTER
#ifdef USE_PERFORMANCE_COUNTER
#include <winbase.h>
#endif

#else
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "Option.H"
#include "GLObject.H"
#include "PnmIO.H"


// �E�B���h�E�^�C�g��
#define TITLE			"Indexed Shadow Mapping -- 'H' Toggle Help Information"

#define VERSION_INFO	"IShadowMap-1.2"
#define AUTHOR			"September 2000 by Masa (Masaki Kawase)\n<E-Mail: masa@daionet.gr.jp>\n<http://www.daionet.gr.jp/~masa/>"

// �r���[�|�C���g�����C�g�ɂ����ꍇ
// ���̃��C�g����̉e�͎g�p���Ȃ��i���e�X�g�𖳌��j
#define DISABLE_LIGHT_VIEW_SHADOW

// ���s�����̎��̓��C�g��`�悵�Ȃ�
#define DISABLE_RENDER_PARALLEL_LIGHT

// FPS �v�Z
#define CALC_FPS_INTERVAL	1000

// �\�����ׂ��傫���ς��\���̂���ꍇ�A�Q��قǁA���̊Ԋu�� FPS �Čv�Z���s��
#define SWITCH_FPS_INTERVAL	1

#define SPOT_IMAGE_FILE		"spot"
#define SPOT2_IMAGE_FILE	"spot2"
#define OBJECT_IMAGE_FILE	"object"
#define FLOOR_IMAGE_FILE	"floor.ppm"
#define GLOSS_IMAGE_FILE	"floor.pgm"
#define HELP_IMAGE_FILE		"help"

#define NM_VOLUME_LIGHT_PLANES		8
#define VOLUME_LIGHT_INTENSITY		0.75f
#define VOLUME_LIGHT_INTENSITY_REF	(VOLUME_LIGHT_INTENSITY * 5.0f)
#define VOLUME_LIGHT_NEAR_PLANE		0.7f
#define VOLUME_LIGHT_FAR_PLANE		4.0f

#define LIGHT_MAX_DISTANCE			16.0f
#define LIGHT_PLANE_SIZE			0.4f
#define LIGHT_STACK					24

// �K��
#define VOLUME_LIGHT_FORCE_SPOT_FOV	60.0f

#define LIGHT_PARALLEL_SCALE		10.0f

#define SHADOW_MAPPING_EDGE_FAT				0.05f
#define SHADOW_MAPPING_EDGE_FAT_MIN			0.04f
#define SHADOW_MAPPING_EDGE_FAT_TORUS_OUTER	0.075f

#define DEFAULT_ALPHA_BIAS			-0.5f

typedef int	STATUS ;

struct ObjectStatus
{
	RotateVector	angle ;
} ;

struct LightStatus
{
	Vector3d		position ;
	GLfloat			matrix[16] ;

	float			distance ;		// from center
	float			dbase ;
//	float			dangle ;
//	float			vdangle ;

	float			pitch ;		// pitch for center

	RotateVector	angle ;		// pitch yaw for position, roll
	RotateVector	angle2 ;	// distance, center pitch
} ;

#define MAX_LIGHTS	4
#define MAX_OBJECTS	5

#define MAX_MAX_LIGHTS	7

#define DEFAULT_LIGHTS	2
#define DEFAULT_OBJECTS	4


// �f�t�H���g�̃E�B���h�E�T�C�Y
#define WIDTH			480
#define HEIGHT			480

// ���̋��ܗ�
#define REFRACTION_RATE	2.0f
//#define REFRACTION_RATE	2.4f

#define PER_VERTEX_FRESNEL	1

// �O���X�I�u�W�F�N�g�̌o�x����������
#define GLASS_DIVIDE	16
#define TEAPOT_DETAIL	5

// �}�E�X���슴�x
#define MOUSE_SPEED		160.0f

//#define START_SPIN_X	1.0f
//#define START_SPIN_Y	0.7f
#define START_SPIN_X	0.0f
#define START_SPIN_Y	0.0f

// OpenGL�ɐݒ肷��e�N�X�`����t�B���^
#define TEX_FILTER		GL_LINEAR_MIPMAP_LINEAR

// ���ۂ�OpenGL�ɐݒ肷��e�N�X�`���̃T�C�Y�i�Q�̂���j
#define ENV_TEX_SIZE	8

// �}�E�X���x
#define MOUSE_FTP_RATIO	20.0f


// �֐��v���g�^�C�v

double GetErapsedTime() ;

STATUS Initialize(Option& option) ;
STATUS OpenGLInitialize(Option& option) ;

void CheckColorBuffer() ;
void CheckOpenGLEnvironment() ;

void ObjectInitialize() ;

void InitializeLights() ;

// OpenGL �̈�ʓI�Ȑݒ�
void SetMiscParmeters() ;

void SetAlphaBias() ;

// �f�B�X�v���C���X�g��`
void DefineDisplayList() ;
void DefineLightList() ;
void DefineObjectLists() ;
void DefineGroundList() ;
void DefineSpotCopyList() ;
void DefineReflectionTransformList() ;
void DefineVolumeLightLists() ;
void DefineVolumeLightList(int lNo) ;
void DefineHelpMessageList() ;

void DefineShadowMapTexEnvModeList() ;
void DefineGlossMapTexEnvModeList() ;

void RenderHelpMessage(float intensity) ;

void Draw3Cylinders(float radius, int alphaStartIndex, int shadowFlag = FALSE) ;
void DrawObject0(float radius, int alphaStartIndex, int shadowFlag = FALSE) ;

void DefineObject0List(int obj) ;
void DefineObject1List(int obj) ;
void DefineObject2List(int obj) ;
void DefineObject3List(int obj) ;
void DefineObject4List(int obj) ;

// ����̃e�N�X�`���̃Z�b�g�A�b�v
void SetupTexture2D(const String& file, GLint wrap, GLint filter) ;
// �e�N�X�`���̃Z�b�g�A�b�v
void SetupTextures(Option& option) ;
// ���t���e�N�X�`���̃Z�b�g�A�b�v
void SetupTexture2DWithAlpha(const String& file, const String& alphaFile, GLint wrap, GLint filter) ;

void DrawGround(int vFlag = FALSE,
				float *color0 = NULL,
				float *color1 = NULL,
				float *color2 = NULL,
				float *color3 = NULL,
				int shadowObj = FALSE) ;

void DrawLightPlane(int div, float radius, float z) ;
void DrawLightSourcePlane(int div, float radius, float z) ;

void DrawPerspectiveVolumeLight(int lNo, float intensity = 1.0f) ;
void DrawParallelVolumeLight(int lNo, float intensity = 1.0f) ;

// ���݃o�C���h����Ă���e�N�X�`���̃t�B���^���Z�b�g
void SetTextureFilter(GLint filter = GL_LINEAR_MIPMAP_LINEAR) ;

// ���݃o�C���h����Ă���e�N�X�`���̍ő�ٕ������Z�b�g
void SetTextureMaxAnisotropy(GLfloat anisotropy = 1.0f) ;

// �S�Ẵe�N�X�`���̍ő�ٕ������Z�b�g
void SetAllTexturesMaxAnisotropy(GLfloat anisotropy = 1.0f) ;

void LoadTextureImage(TRUEIMAGE **image, const String &name) ;

// image ���e�N�X�`���ɃZ�b�g
void SetTextureImage(TRUEIMAGE *image, String internalFormat = "RGB", int arrayComponents = 3) ;

STATUS GLUTInitialize(Option& option) ;
void SetGLUTCallback() ;

// �R�[���o�b�N�֐�
void ReshapeWindow(int x, int y) ;
void HandleKey(unsigned char key, int x, int y) ;
void ObjectProc() ;
void Redisplay() ;
void MouseProc(int button, int state, int x, int y) ;
void MouseMotion(int x, int y) ;
void FramesPerSecond(int value) ;

void MakeStatusString() ;
void UpdateStatusList(GLenum mode = GL_COMPILE) ;

// �X�e�[�^�X�\��
void DrawStatus() ;

// ���_����
void ControlView() ;

// �I�u�W�F�N�g�ړ�
void MoveObjects(int fixSpeed = FALSE) ;
void MoveLights(float msec) ;
void MovePolyhedron(float msec) ;

void GradationBG() ;

// �R�c�`��
void RenderScene() ;

// �`��
void Render() ;

void EnableAmbient() ;
void EnableDiffuse(int lNo) ;

// �o�b�N�J���[�Ŕ������œh��Ԃ�
void DrawBackgroundColor(int n) ;

void RenderObjectsWithReflection() ;
void RenderObjects(int reflectMode = FALSE) ;

void RenderVolumeLights(int reflectMode = FALSE) ;
void RenderVolumeLight(int lNo, int reflectMode = FALSE) ;

void RenderLightObjects() ;
void RenderLightObject(int lNo) ;
void RenderLightObjectsAmbientPass() ;
void RenderLightObjectAmbientPass(int lNo) ;

void RenderPolyhedron(int reflectMode = FALSE) ;
void RenderLocalPolyhedron(int obj) ;

// ���[���h�I�u�W�F�N�g�}�g���N�X����Z
void TransformWorld() ;

// ���[�J���I�u�W�F�N�g�}�g���N�X����Z
void TransformLocal(int obj) ;

// ���C�g�I�u�W�F�N�g�}�g���N�X����Z
void TransformLight(int lNo) ;

void UpdateLights() ;
void UpdateLight(int lNo) ;

void UpdateShadowMaps() ;
void UpdateShadowMap(int lNo) ;
void RenderObjectsForShadow(int lNo) ;
void RenderLightObjectsForShadow(int lNo) ;
void RenderLightObjectForShadow(int lNo) ;
void RenderPolyhedronForShadow() ;
void RenderLocalPolyhedronForShadow(int obj) ;

void SetLightViewAndProjection(int lNo) ;
void TransformLightView(int lNo) ;
void SetViewAndProjection(int vPoint = -1) ;

void SetProjectionTextureObject(int shadow) ;
void SetProjectionTextureEnvMode(int shadow) ;

void SetGlossMappingTextureEnvMode() ;
void SetShwdowMappingTextureEnvMode() ;

void InitializeShadowTextures() ;
void InitializeProjectionPlanes() ;


// �ꎞ�I�ȃE�B���h�E�^�C�g���Z�b�g
// ���b�Ԉꎞ�I�Ƀ^�C�g�����Z�b�g
void SetTemporaryWindowTitle(const String& title, int wait = 3) ;

// �E�B���h�E�^�C�g���Z�b�g
// SetTemporaryWindowTitle()
// �ݒ��̏ꍇ�A��莞�Ԉȏ�o���Ă��Ȃ���Ζ���
void SetWindowTitle(const String& title) ;


// �f�B�X�v���C���X�g����уe�N�X�`���l�[���m��
GLuint AllocAList(GLuint& list) ;
GLuint AllocATexture(GLuint& list) ;

void CheckOpenGLError() ;

// �I������
void ExitProcedure(STATUS state = SUCCESS) ;


#endif
