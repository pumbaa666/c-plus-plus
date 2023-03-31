
#include "ishadowmap.h"

#ifdef WIN32
#define TIMER_PERIOD	1
static MMRESULT resultTimeBeginPeriod ;
#endif

static GLint	width, height ;
static int		outputFPS ;
static GLint	texFilter ;

static float	bg0[] = { 0.0f, 0.5f, 1.0f, 0.0f } ;
static float	bg1[] = { 0.0f, 0.0f, 0.0f, 0.0f } ;
static float	bg[4] ;
static int		animationCount = 0 ;

static unsigned int glutBuff ;
static int		winIDglut = 0 ;

static int		dragL = FALSE, dragR = FALSE ;
static GLint 	dragX, dragY, mouseX, mouseY ;
static GLfloat	spinX = START_SPIN_X, spinY = START_SPIN_Y, mSpeed ;
static float	distance = 8, tdistance = 16 ;

static int		volumeLight = TRUE ;
static int		reflection = TRUE ;
static int		depthMask = TRUE ;
static int		fresnel = TRUE, perVertexFresnel ;
static float	visibility, reflectRatio[4] ;
static int		shadow ;
static int		canShadow = TRUE ;
static int		spotLight = TRUE ;
static int		gloss ;
static int		canGloss = TRUE ;

static int		pause = FALSE ;
static int		reconstShadowMapFlag = TRUE ;
static GLint	shadowTexFilter ;

static float	tHelpIntensity = 0.0f ;
static float	helpIntensity = 0.0f ;

static String title ;
static int		changeTitleWait = 0 ;

static const Vector3d csAxis(1.0f, 0.0f, -1.0f), ctAxis(0.0f, -1.0f, 1.0f) ;
static Vector3d	sAxis, tAxis ;

static int		viewPoint = -1 ;

// フレームカウンタ
static unsigned int frameCount = 0 ;
static int			f_cnt = 0 ;
static float		fps ;
static String		str_fps ;
static String		str_status ;
static Vector3d		fps_position ;

static double		nTick, oTick, mSecStep, oldMSecStep ;
static double		timeRes ;

static GLfloat	colorWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f } ;

static GLfloat	lightpos[4] = { 0.0f, 0.0f, 0.0f, 1.0f } ;
static GLfloat	plightpos[4] = { 0.0f, 0.0f, 1.0f, 0.0f } ;
static GLfloat	lightdir[3] = { 0.0f, 0.0f, -1.0f } ;

// ライト用グローバルライト（環境光パスでライトオブジェクト描画時のみ使用）
static GLfloat	alightpos[4] = { 0.0f, 0.0f, 1.0f, 0.0f } ;
static GLfloat	alightcol[4] = { 1.0f, 1.0f, 1.0f, 1.0f } ;

static GLfloat	s_plane[4] = { 1.0f, 0.0f, 0.0f, 0.0f } ;
static GLfloat	t_plane[4] = { 0.0f, 1.0f, 0.0f, 0.0f } ;
static GLfloat	q_plane[4] = { 0.0f, 0.0f, 1.0f, 0.0f } ;

//static GLfloat	ambient[4] = { 0.38f, 0.38f, 0.44f, 1.0f } ;
static GLfloat	ambient[4] = { 0.34f, 0.34f, 0.40f, 1.0f } ;
static GLfloat	gambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f } ;
static GLfloat	nambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f } ;

static GLfloat	lightColor[MAX_MAX_LIGHTS][4] =
{
	{ 0.9f, 0.9f, 0.9f, 1.0f },
	{ 0.9f, 0.9f, 0.9f, 1.0f },
	{ 1.0f, 0.3f, 1.0f, 1.0f },
	{ 0.3f, 1.0f, 0.4f, 1.0f },

	{ 0.3f, 0.3f, 1.0f, 1.0f },
	{ 1.0f, 0.3f, 0.3f, 1.0f },
	{ 0.3f, 1.0f, 0.3f, 1.0f },
//	{ 1.0f, 0.3f, 1.0f, 1.0f },
} ;

static GLfloat	lightSourceColor[MAX_LIGHTS][4] ;

static GLfloat	lightObjectColor[MAX_MAX_LIGHTS][4] =
{
	{ 0.4f, 1.0f, 0.4f, 1.0f },
	{ 1.0f, 0.4f, 1.0f, 1.0f },
	{ 1.0f, 0.9f, 0.1f, 1.0f },
	{ 0.4f, 0.4f, 1.0f, 1.0f },

	{ 1.0f, 0.4f, 0.4f, 1.0f },
	{ 0.4f, 1.0f, 0.4f, 1.0f },
	{ 1.0f, 0.4f, 1.0f, 1.0f },
//	{ 1.0f, 0.3f, 1.0f, 1.0f },
} ;

/*
static GLfloat	lightCenter[MAX_MAX_LIGHTS][3] =
{
	{  0.0f, -1.0f, -1.0f },
	{  1.0f,  0.0f, -1.0f },
	{  0.0f,  1.0f, -1.0f },
	{ -1.0f,  0.0f, -1.0f },

	{  0.0f, -1.0f, -1.0f },
	{  1.0f,  0.0f, -1.0f },
	{ -1.0f,  0.0f, -1.0f },
//	{  0.0f,  1.0f, -1.0f },
} ;
*/
static GLfloat	lightCenter[MAX_MAX_LIGHTS][3] =
{
	{  0.0f,  0.0f,  0.0f },
	{  0.0f,  0.0f,  0.0f },
	{  0.0f,  0.0f,  0.0f },
	{  0.0f,  0.0f,  0.0f },

	{  0.0f,  0.0f,  0.0f },
	{  0.0f,  0.0f,  0.0f },
	{  0.0f,  0.0f,  0.0f },
//	{  0.0f,  0.0f,  0.0f },
} ;


// 床座標
static Vector3d groundVertices[5] =
{
	Vector3d(-5.0f, -5.0f, -2.0f),
	Vector3d( 5.0f, -5.0f, -2.0f),
	Vector3d( 5.0f,  5.0f, -2.0f),
	Vector3d(-5.0f,  5.0f, -2.0f),

	Vector3d(-0.0f,  0.0f, -2.0f),	// center
} ;

static int groundAlphaIndex = 12 ;
static int torusAlphaIndex  =  4 ;

static int torus2AlphaIndex = 50 ;


// 射影行列セット（gluPerspective）用のパラメタ
static GLdouble	fov, aspectRatio, nearClip, farClip ;

static GLuint	OBJECT_LIST[MAX_OBJECTS], S_OBJECT_LIST[MAX_OBJECTS] ;
static GLuint	LIGHT_LIST, S_LIGHT_LIST, PARALLEL_LIGHT_LIST, S_PARALLEL_LIGHT_LIST ;
static GLuint	LIGHT_PLANE_LIST, PARALLEL_LIGHT_PLANE_LIST, LIGHT_SOURCE_PLANE_LIST, PARALLEL_LIGHT_SOURCE_PLANE_LIST ;
static GLuint	LIGHT_MATERIAL_LIST[MAX_LIGHTS] ;
static GLuint	STATUS_STRING_LIST ;
static GLuint	VOLUME_LIGHT_LIST[MAX_LIGHTS], R_VOLUME_LIGHT_LIST[MAX_LIGHTS] ;
static GLuint	PARALLEL_VOLUME_LIGHT_LIST[MAX_LIGHTS], R_PARALLEL_VOLUME_LIGHT_LIST[MAX_LIGHTS] ;
static GLuint	GROUND_LIST, V_GROUND_LIST, T_GROUND_LIST, TV_GROUND_LIST, S_GROUND_LIST ;
static GLuint	REFLECT_TRANSFORM_LIST, HELP_LIST ;

static GLuint	SPOT_TEXTURE[MAX_LIGHTS], PROJECT_TEXTURE[MAX_LIGHTS], SHADOW_TEXTURE[MAX_LIGHTS], SPOT_COPY_LIST ;
static GLuint	OBJECT_TEXTURE, FLOOR_TEXTURE, FLOOR_WITH_GLOSS_TEXTURE ;
static GLuint	HELP_TEXTURE ;

static GLuint	SHADOW_MAP_TEX_ENV_MODE_LIST, GLOSS_MAP_TEX_ENV_MODE_LIST ;

// 操作累積行列
static GLfloat	controlObjectMatrix[16] ;

static ObjectStatus	world, object[MAX_OBJECTS] ;
static LightStatus	light[MAX_LIGHTS];
static int			nLights, nObjects ;

static float		lightPlaneSize, tLightPlaneSize ;

static char		*has_texture_env_combine ;
static char		*has_multitexture ;
static int		maxActiveTextures, maxTextureSize ;
static char		*has_texture_filter_anisotropic ;
static float	maxAnisotropy, currentAnisotropy ;

static GLint	stencilBits, alphaBits, bpp ;
static float	alphaRes, alphaBias ;

static String	glVendor, glRenderer, glVersion ;
static int		isTNT = FALSE ;
static int		activeTexGenerate, activeTexExplicit ;

static GLsizei	shadowTexWidth, shadowTexHeight ;

static int	activeRenderingLight ;


#if defined WIN32 && defined USE_PERFORMANCE_COUNTER
static int isSupportedPerformanceCount = -1 ;
#else	// #ifdef WIN32
static int isSupportedPerformanceCount = FALSE ;
#endif	// #ifdef WIN32 ... #else

static double mSecResolution ;

double GetErapsedTime()
{
	double msec ;

#if defined WIN32 && defined USE_PERFORMANCE_COUNTER
	static LARGE_INTEGER performanceCount ;

	if (isSupportedPerformanceCount == -1)
	{
		static LARGE_INTEGER frequency ;
		isSupportedPerformanceCount = QueryPerformanceFrequency(&frequency) ;
		mSecResolution = (double)frequency.LowPart  / 1000.0f +
						 (double)frequency.HighPart / 1000.0f * double(0xffffffffL) + 1.0 ;
	}
	else if (isSupportedPerformanceCount)
	{
		QueryPerformanceCounter(&performanceCount) ;
		msec = ((double)performanceCount.LowPart +
			    (double)performanceCount.HighPart * double(0xffffffffL) + 1.0) / mSecResolution ;
	}

#endif	// #if defined WIN32 && defined USE_PERFORMANCE_COUNTER

	if (!isSupportedPerformanceCount)
	{
#if defined WIN32 && defined USE_TIME_GET_TIME
		msec = (double)timeGetTime() ;
#else
		msec = (double)glutGet((GLenum)GLUT_ELAPSED_TIME) ;
#endif
	}

	return msec ;
}

double MeasureTimerResolution()
{
	double msec = GetErapsedTime() ;
	double startTime = msec, last ;
	int count = 0 ;
	double interval = 0.0 ;

	if (isSupportedPerformanceCount)
	{
		interval = 1.0 / mSecResolution ;
	}
	else
	{
		while (msec - startTime < 5000.0 && startTime <= msec && count < 20)
		{
			count ++ ;
			last = msec ;

			while ((msec = GetErapsedTime()) == last) ;
			interval += msec - last ;	// 実際の変化量
		}

		if (startTime >= msec)
			interval = 0.0 ;

		if (count)
			interval /= count ;
	}

	return interval ;
}

// ミリ秒単位時間取得の有効な間隔を測定
double TimerResolution()
{
	double interval = MeasureTimerResolution() ;
	if (interval == 0.0) interval = MeasureTimerResolution() ;

//	cout << interval << endl ;

	return interval ;
}


// 全体の初期化
STATUS Initialize(Option& option)
{
	srand( (unsigned)time( NULL ) );

	cout << VERSION_INFO << endl ;
	cout << AUTHOR << endl << endl ;

#ifdef WIN32
	resultTimeBeginPeriod = timeBeginPeriod(TIMER_PERIOD) ;
#endif	// #ifdef WIN32


	width  = option.GetInt("-width",  WIDTH,  2) ;
	height = option.GetInt("-height", HEIGHT, 2) ;

	int filter ;
	texFilter = NONE ;
	filter        = option.Get      ("-N",                       2) ;
	if (filter) texFilter = GL_NEAREST ;
	filter        = option.Get      ("-L",                       2) ;
	if (filter) texFilter = GL_LINEAR ;
	filter        = option.Get      ("-LL",                      3) ;
	if (filter) texFilter = GL_LINEAR_MIPMAP_LINEAR ;

	if (texFilter == NONE) texFilter = TEX_FILTER ;

	mSpeed        = option.GetDouble("-mspeed",   MOUSE_SPEED,   3) ;
	outputFPS     = option.Get      ("-FPS",                     2) ;

	glutBuff      = option.Get      ("-SINGLE",                  2) ;
	if (glutBuff) glutBuff = GLUT_SINGLE ;
	else          glutBuff = GLUT_DOUBLE ;

	// デフォルトで頂点単位のフレネル計算
	perVertexFresnel = option.GetInt("-vfresnel", PER_VERTEX_FRESNEL, 4) ;

	alphaBias = option.GetDouble("-abias", DEFAULT_ALPHA_BIAS) ;

	activeRenderingLight = -1 ;

	fps = 0.0f ;
	ObjectInitialize() ;

	sAxis = csAxis ;
	tAxis = ctAxis ;
	sAxis.Unit() ;
	tAxis.Unit() ;
	sAxis /= 3.0f ;
	tAxis /= 3.0f ;

	STATUS state ;
	state = OpenGLInitialize(option) ;

	timeRes = TimerResolution() ;
	nTick = GetErapsedTime() ;
	oTick = nTick ;
	mSecStep = oldMSecStep = 0.0f ;

	// 一度すべてを動かして適切な値をセット
	nLights = MAX_LIGHTS ;
	nObjects = MAX_OBJECTS ;
	MoveObjects() ;
	nLights = DEFAULT_LIGHTS ;
	nObjects = DEFAULT_OBJECTS ;

	return state ;
}


void ObjectInitialize()
{
	nLights = DEFAULT_LIGHTS ;
	nObjects = DEFAULT_OBJECTS ;

	tLightPlaneSize = LIGHT_PLANE_SIZE ;
	lightPlaneSize = LIGHT_PLANE_SIZE * 0.1f ;

	// Lights
	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
	{
		float sign = (i % 2) * 2.0f - 1.0f ;	// -1, 1

		light[i].dbase = i * 0.5f + 7.0f ;
//		light[i].dbase = i * 0.5f + 1.5f ;

		light[i].angle2.Initialize(Random(360.0), Random(360.0), 0.0f,
								   CRandom(1.0, 2.0), CRandom(1.0, 2.0), 0.0f) ;
		light[i].angle.Initialize(Random(360.0), Random(360.0), Random(360.0),
								  CRandom(0.5, 1.0), Random(1.0, 3.0) * (sign), Random(1.0, 2.0) * (-sign)) ;

		// ステンド色セット
		for (int c = 0 ; c < 3 ; c ++)
		{
			lightSourceColor[i][c] = lightColor[i][c] * 2.0f ;
			if (lightSourceColor[i][c] > 1.0f)
				lightSourceColor[i][c] = 1.0f ;
		}
		lightSourceColor[i][3] = 1.0f ;
	}

	// World
	world.angle.Initialize(0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f) ;

	// Objects
	for (int i = 0 ; i < MAX_OBJECTS ; i ++)
	{
		object[i].angle.Initialize(Random(360.0), Random(360.0), Random(360.0),
								   CRandom(0.5, 1.5), CRandom(0.5, 1.5), CRandom(0.5, 1.5)) ;
	}
}


void CheckColorBuffer()
{
	bpp = glutGet((GLenum)GLUT_WINDOW_BUFFER_SIZE) ;
	glGetIntegerv(GL_ALPHA_BITS, &alphaBits) ;
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits) ;

	if (alphaBits < 4)
	{
		canShadow = FALSE ;

		String message = "Enough alpha plane is not supported (disable shadows)." ;
		cout << message << endl ;
	}

	if (alphaBits < 4)
	{
		canGloss = FALSE ;

		String message = "Enough alpha plane is not supported (disable gloss mapping)." ;
		cout << message << endl ;
	}

	if (canShadow && canGloss)
	{
		String message = IntToString(alphaBits) + " bits Alpha plane is supported." ;
		cout << message << endl ;
	}


	int tAlphaBits ;
	if      (alphaBits <=  8)	tAlphaBits =  8 ;
	else if (alphaBits <= 12)	tAlphaBits = 12 ;
	else						tAlphaBits = 16 ;
	alphaRes = 1.0f / Pow(2, tAlphaBits) ;

	// とりあえず
	stencilBits = 0 ;
}

void CheckOpenGLEnvironment()
{
	const char *glStr ;
	glStr = (const char *)glGetString(GL_VENDOR) ;
	if (glStr) glVendor = glStr ;
	glStr = (const char *)glGetString(GL_RENDERER) ;
	if (glStr) glRenderer = glStr ;
	glStr = (const char *)glGetString(GL_VERSION) ;
	if (glStr) glVersion = glStr ;

	String renderer = glRenderer ;
	renderer.Upper() ;
	if (renderer.Search("TNT"))
		isTNT = TRUE ;
}

STATUS CheckOpenGLExtensions()
{
	has_texture_env_combine = IsSupported_texture_env_combine() ;
	if (!has_texture_env_combine)
	{
		canShadow = FALSE ;
		canGloss = FALSE ;
		String message = "Texture env combine extension is not supported (disable shadows, gloss mapping)." ;
		cout << message << endl ;
	}
	else
	{
		String message = String(has_texture_env_combine) + " is supported." ;
		cout << message << endl ;
	}

	has_multitexture = IsSupported_multitexture() ;
	if (!has_multitexture)
	{
		String message = "Multi texture extension is required." ;
#ifdef WIN32
		MessageBox(NULL, message, _T("Initialize Failure"), MB_OK | MB_ICONSTOP) ;
#endif
		cerr << message << endl ;
		return FAILURE ;
	}
	else
	{
		String message = String(has_multitexture) + " is supported." ;
		cout << message << endl ;
		maxActiveTextures = GetMaxTextureUnits() ;
	}

	has_texture_filter_anisotropic = IsSupported_texture_filter_anisotropic() ;
	maxAnisotropy = GetMaxTextureMaxAnisotropy() ;
	if (has_texture_filter_anisotropic)
	{
		String message = String(has_texture_filter_anisotropic) + " (max anisotropy: " + IntToString(maxAnisotropy) + ")" + " is supported." ;
		cout << message << endl ;
	}

	if (maxAnisotropy >= 2.0f)
		currentAnisotropy = 2.0f ;
	else
		currentAnisotropy = 1.0f ;

	// テクスチャの最大サイズ
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize) ;

	return SUCCESS ;
}


STATUS OpenGLInitialize(Option& option)
{
	STATUS state ;

	state = GLUTInitialize(option) ;
	if (state != SUCCESS)
		return state ;

	// Alpha plane, stencil bits
	CheckColorBuffer() ;

	CheckOpenGLEnvironment() ;

	if (isTNT)
	{
		shadowTexFilter = GL_NEAREST ;
		spotLight = FALSE ;

		activeTexGenerate = 1 ;
		activeTexExplicit = 0 ;
	}
	else
	{
		shadowTexFilter = GL_LINEAR ;

		activeTexGenerate = 1 ;
		activeTexExplicit = 0 ;
	}


	// OpenGL Extension
	state = CheckOpenGLExtensions() ;
	if (state != SUCCESS)
		return state ;

	if (!canShadow)
	{
		shadow = FALSE ;
		gloss  = FALSE ;

		String message = "At least 4 bits alpha plane and\n" ;
		message += "texture env combine extension\n" ;
		message += "is required for shadow and gloss mapping." ;

		if (alphaBits < 4 && bpp < 32)
			message += "\n32 bits display setting is recommended." ;

		cout << message << endl ;
#ifdef WIN32
		MessageBox(NULL, message, _T("Can't Enable some Effects"), MB_OK | MB_ICONEXCLAMATION) ;
#endif
	}
	else
	{
		shadow = TRUE ;		// シャドウマップ可能ならデフォルトで ON
		gloss  = TRUE ;		// シャドウマップ可能ならグロスマップも可能
	}

	cout << endl ;

	SetGLUTCallback() ;		// GLUT コールバック登録
	SetupTextures(option) ;	// テクスチャセットアップ
	DefineDisplayList() ;	// ディスプレイリスト定義

	InitializeLights() ;

	SetMiscParmeters() ;	// その他の設定

	return SUCCESS ;
}


void SetMiscParmeters()
{
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;


	// クリア値設定
	glClearColor(bg[0], bg[1], bg[2], bg[3]) ;

	if (stencilBits)
		glClearStencil(0) ;

	glClearDepth(1.0f) ;
	glDepthFunc(GL_LESS) ;

	glShadeModel(GL_SMOOTH) ;

	glFrontFace(GL_CCW) ;
	glEnable(GL_CULL_FACE) ;
	glCullFace(GL_BACK) ;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	glPushMatrix() ;
	{
		glRotatef(-150.0f, 1.0f,0.0f,0.0f) ; // ｘ軸回転
//		glRotatef(0.0f, 1.0f,0.0f,0.0f) ; // ｘ軸回転
		glRotatef(-12.0f, 0.0f,1.0f,0.0f) ; // ｙ軸回転
		glGetFloatv(GL_MODELVIEW_MATRIX, controlObjectMatrix) ;
	}
	glPopMatrix() ;

	SetMaterial(GL_FRONT_AND_BACK, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f) ;

	// カラーマテリアル（設定のみ）
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;

	// for TNT
	glPolygonOffset(-0.5f, -1.0f) ;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) ;


	// ライト用グローバルライト（環境光パスでライトオブジェクト描画時のみ使用）
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	glPushMatrix() ;
	{
		SetDirectionalLight(GL_LIGHT7, alightpos, alightcol) ;
	}
	glPopMatrix() ;

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ;

	glEnable(GL_DITHER) ;
	glDisable(GL_SCISSOR_TEST) ;

	SetAlphaBias() ;
}


void SetAlphaBias()
{
	// Alpha Func
	glAlphaFunc(GL_EQUAL, 0.5f + alphaBias * alphaRes) ;
}


// 各ディスプレイリスト定義
void DefineDisplayList()
{
	// ライトオブジェクトのディスプレイリスト定義
	DefineLightList() ;

	// オブジェクトのリスト定義
	DefineObjectLists() ;

	// 床のディスプレイリスト定義
	DefineGroundList() ;

	// シャドウマップにスポットライト描画
	DefineSpotCopyList() ;

	// 反射変換リスト
	DefineReflectionTransformList() ;

	// ボリュームライトリスト定義
	DefineVolumeLightLists() ;

	// ヘルプメッセージ表示リスト
	DefineHelpMessageList() ;

	// FPS用ディスプレイリスト（確保のみ）
	AllocAList(STATUS_STRING_LIST) ;

	// Shadow Map のコンバイナ設定（２ステージ使用）
	DefineShadowMapTexEnvModeList() ;

	// Gloss Map のコンバイナ設定（２ステージのみ）
	DefineGlossMapTexEnvModeList() ;
}


void DefineShadowMapTexEnvModeList()
{
	glNewList(AllocAList(SHADOW_MAP_TEX_ENV_MODE_LIST), GL_COMPILE) ;
	{
		SetShwdowMappingTextureEnvMode() ;
	}
	glEndList() ;
}

void DefineGlossMapTexEnvModeList()
{
	glNewList(AllocAList(GLOSS_MAP_TEX_ENV_MODE_LIST), GL_COMPILE) ;
	{
		SetGlossMappingTextureEnvMode() ;
	}
	glEndList() ;
}


void RenderHelpMessage(float intensity)
{
	if (intensity <= 0.02f)
		return ;

	glPushAttrib(GL_ALL_ATTRIB_BITS) ;
	{
		glMatrixMode(GL_TEXTURE) ;
//		glPushMatrix() ;
		glLoadIdentity() ;

		glMatrixMode(GL_PROJECTION) ;
//		glPushMatrix() ;
		glLoadIdentity() ;

		glMatrixMode(GL_MODELVIEW) ;
//		glPushMatrix() ;
		glLoadIdentity() ;

		{
			glDisable(GL_DEPTH_TEST) ;
			glDisable(GL_LIGHTING) ;

			glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
			glDisable(GL_TEXTURE_2D) ;

			glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
			glBindTexture(GL_TEXTURE_2D, HELP_TEXTURE) ;
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
			glEnable(GL_TEXTURE_2D) ;

			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR) ;
			glEnable(GL_BLEND) ;

			// ヘルプ文字描画
			if (intensity >= 0.98f)
			{
				glColor3f(intensity, intensity, intensity) ;
				glCallList(HELP_LIST) ;
			}
			else
			{
				for (int i = 0 ; i < 4 ; i ++)
				{
					float l = 0.38f ;

					glPushMatrix() ;
					{
						glTranslatef((i - 1.5f) * (1.0f - intensity) * 0.1f, 0.0f, 0.0f) ;
						glColor3f(intensity * l, intensity * l, intensity * l) ;
						glCallList(HELP_LIST) ;
					}
					glPopMatrix() ;
				}
			}
		}

		glMatrixMode(GL_TEXTURE) ;
//		glPopMatrix() ;

		glMatrixMode(GL_PROJECTION) ;
//		glPopMatrix() ;

		glMatrixMode(GL_MODELVIEW) ;
//		glPopMatrix() ;
	}
	glPopAttrib() ;
}

void DefineHelpMessageList()
{
	glNewList(AllocAList(HELP_LIST), GL_COMPILE) ;
	{
		// ヘルプ文字描画
		glBegin(GL_QUADS) ;
		{
			glTexCoord2f(0.0f, 0.0f) ;
			glVertex2f(-0.9f, -0.9f) ;

			glTexCoord2f(1.0f, 0.0f) ;
			glVertex2f( 0.9f, -0.9f) ;

			glTexCoord2f(1.0f, 1.0f) ;
			glVertex2f( 0.9f,  0.9f) ;

			glTexCoord2f(0.0f, 1.0f) ;
			glVertex2f(-0.9f,  0.9f) ;
		}
		glEnd() ;
	}
	glEndList() ;
}

void DefineSpotCopyList()
{
	glNewList(AllocAList(SPOT_COPY_LIST), GL_COMPILE) ;
	{
		glMatrixMode(GL_MODELVIEW) ;
		glLoadIdentity() ;	// clear modelview matrix
		glMatrixMode(GL_PROJECTION) ;
		glLoadIdentity() ;

		glColor3f(1.0f, 1.0f, 1.0f) ;
		glBegin(GL_QUADS) ;
		{
			glTexCoord2f(0.0f, 0.0f) ;
			glVertex2f(-1.0f, -1.0f) ;

			glTexCoord2f(1.0f, 0.0f) ;
			glVertex2f(1.0f, -1.0f) ;

			glTexCoord2f(1.0f, 1.0f) ;
			glVertex2f(1.0f, 1.0f) ;

			glTexCoord2f(0.0f, 1.0f) ;
			glVertex2f(-1.0f, 1.0f) ;
		}
		glEnd() ;
	}
	glEndList() ;
}

void DefineObjectLists()
{
	DefineObject0List(0) ;
	DefineObject1List(3) ;
	DefineObject2List(2) ;
	DefineObject3List(1) ;
//	DefineObject4List(4) ;
}


void Draw3Cylinders(float radius, int alphaStartIndex, int shadowFlag)
{
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 0.0f } ;
	GLfloat cylnderRadius = radius * 0.2f ;

	// 3 Cylinders
	glPushMatrix() ;
	{
		glTranslatef(-0.8f, 0.0f, 0.0f) ;
		for (int i = 0 ; i < 3 ; i ++)
		{
			if (i)
				glTranslatef(0.8f, 0.0f, 0.0f) ;

			color[3] = (alphaStartIndex + i) * alphaRes ;
			glColor4fv(color) ;
			if (!shadowFlag)
				Cylinder::DrawPolyhedron(16, cylnderRadius, TRUE, cylnderRadius, TRUE, radius, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
			else
				Cylinder::DrawPolyhedron(16, cylnderRadius + SHADOW_MAPPING_EDGE_FAT_MIN, TRUE,
										 cylnderRadius + SHADOW_MAPPING_EDGE_FAT_MIN, TRUE,
										 radius + SHADOW_MAPPING_EDGE_FAT_MIN, FALSE) ;
		}
	}
	glPopMatrix() ;
}

void DrawObject0(float radius, int alphaStartIndex, int shadowFlag)
{
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 0.0f } ;
	int alpha ;

	glPushMatrix() ;
	{
		alpha = 0 ;
		glTranslatef(0.0f, -radius * 0.2f, 0.0f) ;
		Draw3Cylinders(radius, alphaStartIndex + alpha, shadowFlag) ;

		alpha = 3 ;
		glTranslatef(0.0f, -radius * 0.6f, 0.0f) ;
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f) ;
		Draw3Cylinders(radius, alphaStartIndex + alpha, shadowFlag) ;
	}
	glPopMatrix() ;

	glPushMatrix() ;
	{
		alpha = 6 ;
		color[3] = (alphaStartIndex + alpha) * alphaRes ;
		glColor4fv(color) ;

		glTranslatef(0.0f, radius * 0.8f, 0.0f) ;

		float r = radius * 0.7f ;
		if (!shadowFlag)
		{
			Octahedron obj(r, r, r, 1, TRUE, FALSE) ;
			obj.Draw(NONE, NONE, FALSE, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
		}
		else
		{
			Octahedron obj(r + SHADOW_MAPPING_EDGE_FAT_MIN,
						   r + SHADOW_MAPPING_EDGE_FAT_MIN,
						   r + SHADOW_MAPPING_EDGE_FAT_MIN, 1, TRUE, TRUE) ;
			obj.Draw(NONE, NONE, FALSE, FALSE) ;
		}
	}
	glPopMatrix() ;
}


void DefineObject0List(int obj)
{
	float radius = 1.2f ;
	glNewList(AllocAList(OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glPushAttrib(GL_COLOR_MATERIAL | GL_COLOR_MATERIAL_FACE) ;
		{
			glColorMaterial(GL_FRONT, GL_DIFFUSE) ;
			glEnable(GL_COLOR_MATERIAL) ;
//			Torus obj(0.45f * radius, 1.0f * radius, 24, 32, TRUE, TRUE) ;
//			obj.DrawObjectWithAlphaIndex(TRUE, Vector3d::white, torusAlphaIndex,alphaRes, sAxis.v, tAxis.v) ;

			DrawObject0(radius, torusAlphaIndex) ;
		}
		glPopAttrib() ;
	}
	glEndList() ;

	glNewList(AllocAList(S_OBJECT_LIST[obj]), GL_COMPILE) ;
	{
//		Torus obj(0.45f * radius - SHADOW_MAPPING_EDGE_FAT, 1.0f * radius + SHADOW_MAPPING_EDGE_FAT_TORUS_OUTER, 16, 32, FALSE, FALSE) ;
//		obj.DrawObjectWithAlphaIndex(TRUE, Vector3d::white, torusAlphaIndex,alphaRes, sAxis.v, tAxis.v) ;

		DrawObject0(radius, torusAlphaIndex, TRUE) ;
	}
	glEndList() ;
}

void DefineObject4List(int obj)
{
	float radius = 1.0f ;
	glNewList(AllocAList(OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glPushAttrib(GL_COLOR_MATERIAL | GL_COLOR_MATERIAL_FACE) ;
		{
			glColorMaterial(GL_FRONT, GL_DIFFUSE) ;
			glEnable(GL_COLOR_MATERIAL) ;
			Torus obj(0.45f * radius, 1.0f * radius, 6, 8, FALSE, FALSE) ;
			obj.DrawObjectWithAlphaIndex(TRUE, Vector3d::white, torus2AlphaIndex,alphaRes, sAxis.v, tAxis.v) ;
		}
		glPopAttrib() ;
	}
	glEndList() ;

	glNewList(AllocAList(S_OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		Torus obj(0.45f * radius - SHADOW_MAPPING_EDGE_FAT, 1.0f * radius + SHADOW_MAPPING_EDGE_FAT_TORUS_OUTER, 16, 32, FALSE, FALSE) ;
		obj.DrawObjectWithAlphaIndex(TRUE, Vector3d::white, torus2AlphaIndex,alphaRes, sAxis.v, tAxis.v) ;
	}
	glEndList() ;
}

void DefineObject1List(int obj)
{
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 0 * alphaRes } ;

	float radius = 1.0f ;
	glNewList(AllocAList(OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color) ;
		Icosahedron obj(radius, radius, radius, 2, TRUE, TRUE) ;
		obj.Draw(NONE, NONE, FALSE, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
	}
	glEndList() ;

	glNewList(AllocAList(S_OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glColor4fv(color) ;
		Icosahedron obj(radius + SHADOW_MAPPING_EDGE_FAT,
						radius + SHADOW_MAPPING_EDGE_FAT,
						radius + SHADOW_MAPPING_EDGE_FAT, 2, TRUE, TRUE) ;
		obj.Draw(NONE, NONE, FALSE, FALSE) ;
	}
	glEndList() ;
}

void DefineObject2List(int obj)
{
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 1 * alphaRes } ;

	float radius = 0.9f ;
	glNewList(AllocAList(OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color) ;
//		Octahedron::DrawPolyhedron(radius, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
		Cylinder::DrawPolyhedron(32, radius * 0.6f, TRUE, radius, TRUE, radius * 0.8, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
	}
	glEndList() ;

	glNewList(AllocAList(S_OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glColor4fv(color) ;
//		Octahedron::DrawPolyhedron(radius + SHADOW_MAPPING_EDGE_FAT, FALSE, activeTexExplicit, sAxis.v, tAxis.v) ;
		Cylinder::DrawPolyhedron(32, (radius + SHADOW_MAPPING_EDGE_FAT) * 0.6f, TRUE,
								 radius + SHADOW_MAPPING_EDGE_FAT, TRUE,
								 radius * 0.8f + SHADOW_MAPPING_EDGE_FAT, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
	}
	glEndList() ;
}

void DefineObject3List(int obj)
{
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 2 * alphaRes } ;

	float radius = 1.0f ;
	glNewList(AllocAList(OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color) ;
		Icosahedron::DrawPolyhedron(radius, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
	}
	glEndList() ;

	glNewList(AllocAList(S_OBJECT_LIST[obj]), GL_COMPILE) ;
	{
		glColor4fv(color) ;
		Icosahedron::DrawPolyhedron(radius + SHADOW_MAPPING_EDGE_FAT, FALSE, activeTexExplicit, sAxis.v, tAxis.v) ;
	}
	glEndList() ;
}


// 反射変換リスト
void DefineReflectionTransformList()
{
	glNewList(AllocAList(REFLECT_TRANSFORM_LIST), GL_COMPILE) ;
	{
		// 床への映りこみ用反転
		glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
		glTranslatef(0.0f, 0.0f, -2.0f) ;
		glScalef(1.0f, 1.0f, -1.0f) ;
		glTranslatef(0.0f, 0.0f, 2.0f) ;
		glRotatef(-90.0f, 1.0f, 0.0, 0.0f) ;
	}
	glEndList() ;
}


// ボリュームライトリスト
void DefineVolumeLightLists()
{
	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
		DefineVolumeLightList(i) ;
}

void DefineVolumeLightList(int lNo)
{
	glNewList(AllocAList(VOLUME_LIGHT_LIST[lNo]), GL_COMPILE) ;
	{
		DrawPerspectiveVolumeLight(lNo, VOLUME_LIGHT_INTENSITY) ;
	}
	glEndList() ;

	glNewList(AllocAList(R_VOLUME_LIGHT_LIST[lNo]), GL_COMPILE) ;
	{
		DrawPerspectiveVolumeLight(lNo, VOLUME_LIGHT_INTENSITY_REF) ;
	}
	glEndList() ;


	glNewList(AllocAList(PARALLEL_VOLUME_LIGHT_LIST[lNo]), GL_COMPILE) ;
	{
		DrawParallelVolumeLight(lNo, VOLUME_LIGHT_INTENSITY) ;
	}
	glEndList() ;

	glNewList(AllocAList(R_PARALLEL_VOLUME_LIGHT_LIST[lNo]), GL_COMPILE) ;
	{
		DrawParallelVolumeLight(lNo, VOLUME_LIGHT_INTENSITY_REF) ;
	}
	glEndList() ;
}

void DrawPerspectiveVolumeLight(int lNo, float intensity)
{
	glBegin(GL_QUADS) ;
	{
		float step = 1.0f / ((NM_VOLUME_LIGHT_PLANES + 2) - 1) ;
		intensity *= 1.0f / NM_VOLUME_LIGHT_PLANES ;

		for (int u = 0 ; u < NM_VOLUME_LIGHT_PLANES ; u ++)
		{
			float base = (u - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) * step * 2.0f ;
			float farPlaneScale = Cos(VOLUME_LIGHT_FORCE_SPOT_FOV * ((u - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) / NM_VOLUME_LIGHT_PLANES)) ;
//			cout << (farPlaneScale) << endl ;

			glColor3f(lightColor[lNo][0] * intensity, lightColor[lNo][1] * intensity, lightColor[lNo][2] * intensity) ;
			glVertex3f(base * VOLUME_LIGHT_NEAR_PLANE,  VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glVertex3f(base * VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glColor3f(0.0f, 0.0f, 0.0f) ;
			glVertex3f(base * VOLUME_LIGHT_FAR_PLANE * farPlaneScale, -VOLUME_LIGHT_FAR_PLANE * farPlaneScale, -VOLUME_LIGHT_FAR_PLANE * farPlaneScale) ;
			glVertex3f(base * VOLUME_LIGHT_FAR_PLANE * farPlaneScale,  VOLUME_LIGHT_FAR_PLANE * farPlaneScale, -VOLUME_LIGHT_FAR_PLANE * farPlaneScale) ;
		}

		for (int v = 0 ; v < NM_VOLUME_LIGHT_PLANES ; v ++)
		{
//			float base = v * step * 2.0f - 1.0f ;
			float base = (v - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) * step * 2.0f ;
			float farPlaneScale = Cos(VOLUME_LIGHT_FORCE_SPOT_FOV * ((v - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) / NM_VOLUME_LIGHT_PLANES)) ;

			glColor3f(lightColor[lNo][0] * intensity, lightColor[lNo][1] * intensity, lightColor[lNo][2] * intensity) ;
			glVertex3f(-VOLUME_LIGHT_NEAR_PLANE, base * VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glVertex3f( VOLUME_LIGHT_NEAR_PLANE, base * VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glColor3f(0.0f, 0.0f, 0.0f) ;
			glVertex3f( VOLUME_LIGHT_FAR_PLANE * farPlaneScale, base * VOLUME_LIGHT_FAR_PLANE * farPlaneScale, -VOLUME_LIGHT_FAR_PLANE * farPlaneScale) ;
			glVertex3f(-VOLUME_LIGHT_FAR_PLANE * farPlaneScale, base * VOLUME_LIGHT_FAR_PLANE * farPlaneScale, -VOLUME_LIGHT_FAR_PLANE * farPlaneScale) ;
		}
	}
	glEnd() ;

//	CheckOpenGLError() ;
}

void DrawParallelVolumeLight(int lNo, float intensity)
{
	glBegin(GL_QUADS) ;
	{
//		float step = 1.0f / (NM_VOLUME_LIGHT_PLANES - 1) ;
//		intensity *= step ;
		float step = 1.0f / ((NM_VOLUME_LIGHT_PLANES + 2) - 1) ;
		intensity *= 1.0f / NM_VOLUME_LIGHT_PLANES ;

		for (int u = 0 ; u < NM_VOLUME_LIGHT_PLANES ; u ++)
		{
			float base = (u - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) * step * 2.0f ;
			glColor3f(lightColor[lNo][0] * intensity, lightColor[lNo][1] * intensity, lightColor[lNo][2] * intensity) ;
			glVertex3f(base * LIGHT_PARALLEL_SCALE,  1.0f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glVertex3f(base * LIGHT_PARALLEL_SCALE, -1.0f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glColor3f(0.0f, 0.0f, 0.0f) ;
			glVertex3f(base * LIGHT_PARALLEL_SCALE, -1.0f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_FAR_PLANE) ;
			glVertex3f(base * LIGHT_PARALLEL_SCALE,  1.0f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_FAR_PLANE) ;
		}

		for (int v = 0 ; v < NM_VOLUME_LIGHT_PLANES ; v ++)
		{
			float base = (v - (NM_VOLUME_LIGHT_PLANES - 1) * 0.5f) * step * 2.0f ;
			glColor3f(lightColor[lNo][0] * intensity, lightColor[lNo][1] * intensity, lightColor[lNo][2] * intensity) ;
			glVertex3f(-1.0f * LIGHT_PARALLEL_SCALE, base * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glVertex3f( 1.0f * LIGHT_PARALLEL_SCALE, base * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE) ;
			glColor3f(0.0f, 0.0f, 0.0f) ;
			glVertex3f( 1.0f * LIGHT_PARALLEL_SCALE, base * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_FAR_PLANE) ;
			glVertex3f(-1.0f * LIGHT_PARALLEL_SCALE, base * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_FAR_PLANE) ;
		}
	}
	glEnd() ;

//	CheckOpenGLError() ;
}


// 光源オブジェクトのディスプレイリスト定義
void DefineLightList()
{
	glNewList(AllocAList(LIGHT_LIST), GL_COMPILE) ;
	{
//		Icosahedron::DrawPolyhedron(1.2f, TRUE, activeTexExplicit, sAxis.v, tAxis.v) ;
		glPushMatrix() ;
		{
			glTranslatef(0.0f, 0.0f, -(VOLUME_LIGHT_NEAR_PLANE * 0.25f * 3.0f)) ;
			Cylinder::DrawPolyhedron(LIGHT_STACK, VOLUME_LIGHT_NEAR_PLANE * 0.5, TRUE, VOLUME_LIGHT_NEAR_PLANE, FALSE, VOLUME_LIGHT_NEAR_PLANE * 0.25f, TRUE) ;
		}
		glPopMatrix() ;
	}
	glEndList() ;

	glNewList(AllocAList(S_LIGHT_LIST), GL_COMPILE) ;
	{
			glTranslatef(0.0f, 0.0f, -(VOLUME_LIGHT_NEAR_PLANE * 0.25f * 3.0f)) ;
			Cylinder::DrawPolyhedron(LIGHT_STACK, VOLUME_LIGHT_NEAR_PLANE * 0.5f, TRUE, VOLUME_LIGHT_NEAR_PLANE, TRUE, VOLUME_LIGHT_NEAR_PLANE * 0.25f, TRUE) ;
	}
	glEndList() ;


	glNewList(AllocAList(PARALLEL_LIGHT_LIST), GL_COMPILE) ;
	{
		glPushMatrix() ;
		{
			glTranslatef(0.0f, 0.0f, -(VOLUME_LIGHT_NEAR_PLANE * 0.25f * 3.0f)) ;
			Cylinder::DrawPolyhedron(LIGHT_STACK, 1.0f * LIGHT_PARALLEL_SCALE, TRUE, 1.0f * LIGHT_PARALLEL_SCALE, FALSE, VOLUME_LIGHT_NEAR_PLANE * 0.25f, TRUE) ;
		}
		glPopMatrix() ;
	}
	glEndList() ;

	glNewList(AllocAList(S_PARALLEL_LIGHT_LIST), GL_COMPILE) ;
	{
			glTranslatef(0.0f, 0.0f, -(VOLUME_LIGHT_NEAR_PLANE * 0.25f * 3.0f)) ;
			Cylinder::DrawPolyhedron(LIGHT_STACK, 1.0f * LIGHT_PARALLEL_SCALE, TRUE, 1.0f * LIGHT_PARALLEL_SCALE, TRUE, VOLUME_LIGHT_NEAR_PLANE * 0.25f, TRUE) ;
	}
	glEndList() ;


	glNewList(AllocAList(LIGHT_PLANE_LIST), GL_COMPILE) ;
	{
		DrawLightPlane(LIGHT_STACK, VOLUME_LIGHT_NEAR_PLANE, -VOLUME_LIGHT_NEAR_PLANE) ;
	}
	glEndList() ;

	glNewList(AllocAList(PARALLEL_LIGHT_PLANE_LIST), GL_COMPILE) ;
	{
		DrawLightPlane(LIGHT_STACK, 1.0f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE) ;
	}
	glEndList() ;


	glNewList(AllocAList(LIGHT_SOURCE_PLANE_LIST), GL_COMPILE) ;
	{
		DrawLightSourcePlane(LIGHT_STACK, VOLUME_LIGHT_NEAR_PLANE * 0.84f, -VOLUME_LIGHT_NEAR_PLANE * 0.85f) ;
	}
	glEndList() ;

	glNewList(AllocAList(PARALLEL_LIGHT_SOURCE_PLANE_LIST), GL_COMPILE) ;
	{
		DrawLightSourcePlane(LIGHT_STACK, 0.99f * LIGHT_PARALLEL_SCALE, -VOLUME_LIGHT_NEAR_PLANE * 0.75f) ;
	}
	glEndList() ;


	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
	{
		glNewList(AllocAList(LIGHT_MATERIAL_LIST[i]), GL_COMPILE) ;
		{
			SetMaterial(GL_FRONT, lightObjectColor[i][0], lightObjectColor[i][1], lightObjectColor[i][2], 1.0f, 0.85f, 1.0f, 16.0f) ;
			SetMaterial(GL_BACK, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) ;
			glMaterialfv(GL_BACK, GL_EMISSION, lightColor[i]) ;
		}
		glEndList() ;
	}

/*
	glNewList(AllocAList(LIGHT_MATERIAL_LIST[1]), GL_COMPILE) ;
	{
		SetMaterial(GL_FRONT, 1.0f, 0.4f, 1.0f, 1.0f, 0.85f, 1.0f, 16.0f) ;
		SetMaterial(GL_BACK, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f) ;
	}
	glEndList() ;
*/
}


void DrawLightPlane(int div, float radius, float z)
{
	glBegin(GL_TRIANGLE_FAN) ;
	{
		// Center
		glTexCoord2f(0.5f, 0.5f) ;
		glVertex3f(0.0f, 0.0f, z) ;

		for (int i = 0 ; i <= div ; i ++)
		{
			int		r = (i % div) ;
			float	deg = r * 360.0f / div ;
			float	s = Sin(deg), c = Cos(deg) ;

			TexCoord2f(-s * 0.5f + 0.5f, -c * 0.5f + 0.5f, activeTexExplicit) ;
			glVertex3f(s * radius, c * radius, z) ;
		}
	}
	glEnd() ;
}


// 光源（面）
// 光源色でテクスチャなし
// 法泉は裏向き
void DrawLightSourcePlane(int div, float radius, float z)
{
	glBegin(GL_TRIANGLE_FAN) ;
	{
		// Center
//		glTexCoord2f(0.5f, 0.5f) ;
//		glNormal3f(0.0f, 0.0f, 1.0f) ;
		glVertex3f(0.0f, 0.0f, z) ;

		for (int i = 0 ; i <= div ; i ++)
		{
			int		r = (i % div) ;
			float	deg = r * 360.0f / div ;
			float	s = Sin(deg), c = Cos(deg) ;

//			glTexCoord2f(-s * 0.5f + 0.5f, -c * 0.5f + 0.5f) ;
			glVertex3f(s * radius, c * radius, z) ;
		}
	}
	glEnd() ;
}


void DefineGroundList()
{
	// GROUND_LIST, S_GROUND_LIST はαインデクス付き
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, groundAlphaIndex * alphaRes } ;

	glNewList(AllocAList(GROUND_LIST), GL_COMPILE) ;
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color) ;
		DrawGround() ;
	}
	glEndList() ;

	glNewList(AllocAList(V_GROUND_LIST), GL_COMPILE) ;
	{
//		glColor4fv(color) ;
		DrawGround(TRUE) ;
	}
	glEndList() ;

	// シャドウマップ用（少し大きく描画）
	glNewList(AllocAList(S_GROUND_LIST), GL_COMPILE) ;
	{
		glPushMatrix() ;
		{
			glScalef(1.05f, 1.051f, 1.0f) ;
			glColor4fv(color) ;
			DrawGround(TRUE, NULL, NULL, NULL, NULL, TRUE) ;
		}
		glPopMatrix() ;
	}
	glEndList() ;

	glNewList(AllocAList(T_GROUND_LIST), GL_COMPILE) ;
	{
		glPushMatrix() ;
		{
			glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
			DrawGround() ;
		}
		glPopMatrix() ;
	}
	glEndList() ;

	// 映りこみマスク
	glNewList(AllocAList(TV_GROUND_LIST), GL_COMPILE) ;
	{
		glPushMatrix() ;
		{
			glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
//			glScalef(0.98f, 0.98f, 1.0f) ;
			DrawGround(TRUE) ;
		}
		glPopMatrix() ;
	}
	glEndList() ;
}


void DrawGround(int vFlag,
				float *color0,
				float *color1,
				float *color2,
				float *color3,
				int shadowObj)
{
	glBegin(GL_QUADS) ;
	{
		if (!vFlag)
		{
			glNormal3f(0.0f, 0.0f, 1.0f) ;
			TexCoord2f(0.0, 0.0f, activeTexExplicit) ;
		}
		if (color0) glColor4fv(color0) ;
		glVertex3fv(groundVertices[0].v) ;

		if (!vFlag)
		{
			TexCoord2f(2.0, 0.0f, activeTexExplicit) ;
		}
		if (color1) glColor4fv(color1) ;
		glVertex3fv(groundVertices[1].v) ;

		if (!vFlag)
		{
			TexCoord2f(2.0,  2.0f, activeTexExplicit) ;
		}
		if (color2) glColor4fv(color2) ;
		glVertex3fv(groundVertices[2].v) ;

		if (!vFlag)
		{
			TexCoord2f(0.0,  2.0f, activeTexExplicit) ;
		}
		if (color3) glColor4fv(color3) ;
		glVertex3fv(groundVertices[3].v) ;
	}
	glEnd() ;
}


// α付きテクスチャのセットアップ
void SetupTexture2DWithAlpha(const String& file, const String& alphaFile, GLint wrap, GLint filter)
{
	// ppm 画像読み込み
	if (file != "")
	{
		TRUEIMAGE *image, *alpha ;
		LoadTextureImage(&image, file) ;
		LoadTextureImage(&alpha, alphaFile) ;

		RGBtoRGBA(image, alpha) ;
		SetTextureImage(image, "RGBA", 4) ;
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->width, image->height, GL_RGBA, GL_UNSIGNED_BYTE, image->dataptr) ;

		freeimage(image) ;
		freeimage(alpha) ;
	}

	// ラップセット
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap) ;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap) ;

	// テクスチャフィルタセット
	SetTextureFilter(filter) ;
}

// 特定のテクスチャのセットアップ
void SetupTexture2D(const String& file, GLint wrap, GLint filter)
{
	// ppm 画像読み込み
	if (file != "")
	{
		TRUEIMAGE *image ;
		LoadTextureImage(&image, file) ;
		SetTextureImage(image) ;
		freeimage(image) ;
	}

	// ラップセット
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap) ;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap) ;

	// テクスチャフィルタセット
	SetTextureFilter(filter) ;
}


// テクスチャのセットアップ
void SetupTextures(Option& option)
{
	// スポットテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(SPOT_TEXTURE[0])) ;
	SetupTexture2D(SPOT_IMAGE_FILE, GL_CLAMP, GL_LINEAR) ;

	// スポットテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(SPOT_TEXTURE[1])) ;
	SetupTexture2D(SPOT2_IMAGE_FILE, GL_CLAMP, GL_LINEAR) ;

	for (int i = 2 ; i < MAX_LIGHTS ; i ++)
		SPOT_TEXTURE[i] = SPOT_TEXTURE[i % 2] ;

	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
		SHADOW_TEXTURE[i] = 0 ;
	InitializeShadowTextures() ;

	// オブジェクトテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(OBJECT_TEXTURE)) ;
	SetupTexture2D(OBJECT_IMAGE_FILE, GL_REPEAT, texFilter) ;

	// フロアテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(FLOOR_TEXTURE)) ;
	SetupTexture2D(FLOOR_IMAGE_FILE, GL_REPEAT, texFilter) ;

	// グロス用α付きフロアテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(FLOOR_WITH_GLOSS_TEXTURE)) ;
	SetupTexture2DWithAlpha(FLOOR_IMAGE_FILE, GLOSS_IMAGE_FILE, GL_REPEAT, texFilter) ;


	// ヘルプテクスチャ
	glBindTexture(GL_TEXTURE_2D, AllocATexture(HELP_TEXTURE)) ;
	SetupTexture2D(HELP_IMAGE_FILE, GL_CLAMP, texFilter) ;

	// TEXTURE1 は投影
	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR) ;
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR) ;
	glTexGenf(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR) ;
	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;

	SetAllTexturesMaxAnisotropy(currentAnisotropy) ;
}

void SetTextureProjectionMatrix()
{
//	glPushAttrib(GL_MATRIX_MODE) ;
	{
		glMatrixMode(GL_TEXTURE) ;
		glLoadIdentity() ;
		glScalef(0.5f, 0.5f, 1.0f) ;
		glTranslatef(1.0f, 1.0f, 0.0f) ;
	}
//	glPopAttrib() ;
	glMatrixMode(GL_MODELVIEW) ;
}

void ClearTextureMatrix()
{
//	glPushAttrib(GL_MATRIX_MODE) ;
	{
		glMatrixMode(GL_TEXTURE) ;
		glLoadIdentity() ;
	}
//	glPopAttrib() ;
	glMatrixMode(GL_MODELVIEW) ;
}


// グロスマッピング
// 環境マッピングパス時の設定
// TEXTURE0 にグロスマップをセット
// カレントカラー（ディフューズ）に diffuse * 2.0f - 1.0f をセット
// αブレンドで描画するが、バッファのαプレーンにはフラグメントのα値を書き込みたいため２パス必要
// １パス目で床をαブレンドで描画
// ２パス目はブレンドなしでα値のみ描画 glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE)
// 床のライト加算時はα値をリードオンリー glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE) にし、
// ブレンド関数 glBlendFunc(GL_DST_ALPHA, GL_ONE) で描画
void SetGlossMappingTextureEnvMode()
{
	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE) ;

	// RGB function = Modulate (PC * TC)
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR) ;

	// Alpha function = Add Signed
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_ADD_SIGNED) ;

	// Arg0: SA
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_PRIMARY_COLOR) ; // GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA) ;
	// Arg1: TA
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA) ;

/*
	// Alpha function = SA * (1 - TA) + TA
	//                = 1 * TA + SA * (1-TA)
	// Arg0 * (Arg2) + Arg1 * (1-Arg2)
	// Arg0: CONSTANT(alpha:1), Arg1: SA, Arg2: TA
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_INTERPOLATE) ;

	// Arg0: CONSTANT(alpha:1)
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, colorWhite) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_CONSTANT) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA) ;
	// Arg1: SA
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_PRIMARY_COLOR) ; // GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA) ;
	// Arg2: TA
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, GL_SRC_ALPHA) ;
*/
}

void SetShwdowMappingTextureEnvMode()
{
	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA) ;

	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_ADD_SIGNED) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PRIMARY_COLOR) ;	// GL_PREVIOUS
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_TEXTURE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
}

void SetProjectionTextureEnvMode(int shadow)
{
	if (shadow)
	{
		glCallList(SHADOW_MAP_TEX_ENV_MODE_LIST) ;
	}
	else
	{
		glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
	}
}

void EnableProjectionTexture()
{
	SetTextureProjectionMatrix() ;

//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;

	glEnable(GL_TEXTURE_2D) ;
	glEnable(GL_TEXTURE_GEN_S) ;
	glEnable(GL_TEXTURE_GEN_T) ;

	if (spotLight)
		glEnable(GL_TEXTURE_GEN_Q) ;
	else
		glDisable(GL_TEXTURE_GEN_Q) ;
}


void EnableSolidTexture()
{
	ClearTextureMatrix() ;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;
	glEnable(GL_TEXTURE_2D) ;
}


// 現在バインドされているテクスチャのフィルタを設定
void SetTextureFilter(GLint filter)
{
	GLint gl_mag_filter, gl_min_filter ;

	switch (filter)
	{
	case GL_NEAREST:
		gl_mag_filter = gl_min_filter = GL_NEAREST ;
		break ;

	case GL_LINEAR:
		gl_mag_filter = gl_min_filter = GL_LINEAR ;
		break ;

	case GL_NEAREST_MIPMAP_NEAREST:
		gl_mag_filter = GL_NEAREST ;
		gl_min_filter = GL_NEAREST_MIPMAP_NEAREST ;
		break ;

	case GL_LINEAR_MIPMAP_NEAREST:
		gl_mag_filter = GL_LINEAR ;
		gl_min_filter = GL_LINEAR_MIPMAP_NEAREST ;
		break ;

	case GL_NEAREST_MIPMAP_LINEAR:
		gl_mag_filter = GL_NEAREST ;
		gl_min_filter = GL_NEAREST_MIPMAP_LINEAR ;
		break ;

	case GL_LINEAR_MIPMAP_LINEAR:
		gl_mag_filter = GL_LINEAR ;
		gl_min_filter = GL_LINEAR_MIPMAP_LINEAR ;
		break ;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter) ;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter) ;
}


// 現在バインドされているテクスチャの最大異方性を設定
void SetTextureMaxAnisotropy(GLfloat anisotropy)
{
	if (has_texture_filter_anisotropic)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropy) ;
}


// 全テクスチャの最大異方性をセット
void SetAllTexturesMaxAnisotropy(GLfloat anisotropy)
{
	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
	{
		glBindTexture(GL_TEXTURE_2D, SPOT_TEXTURE[i]) ;
		SetTextureMaxAnisotropy(anisotropy) ;
	}

//	glBindTexture(GL_TEXTURE_2D, OBJECT_TEXTURE) ;
//	SetTextureMaxAnisotropy(anisotropy) ;

	glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE) ;
	SetTextureMaxAnisotropy(anisotropy) ;

	glBindTexture(GL_TEXTURE_2D, FLOOR_WITH_GLOSS_TEXTURE) ;
	SetTextureMaxAnisotropy(anisotropy) ;

	glBindTexture(GL_TEXTURE_2D, HELP_TEXTURE) ;
	SetTextureMaxAnisotropy(anisotropy) ;
}


void LoadTextureImage(TRUEIMAGE **image, const String& name)
{
	String	effectivePath ;
	*image = LoadTextureImage(name, 0, NULL, &effectivePath) ;

	if (!(*image))
	{
		cerr << "Can't open file \"" << name << "\" in path." << endl ;

#ifdef WIN32
		MessageBox(NULL, _T(String("Can't open file \"") + name + "\" in path."), _T("Loading Image Error"), MB_OK | MB_ICONSTOP) ;
#endif
		ExitProcedure(FAILURE) ;
	}
	else
		cout << "Loading ... \"" << effectivePath << "\"." << endl ;
}


// image をテクスチャにセット
void SetTextureImage(TRUEIMAGE *image, String internalFormat, int arrayComponents)
{
//	GLint  bits = 3 ;
	GLenum tformat = InternalFormat(internalFormat) ;

//	if (texFilter == GL_LINEAR_MIPMAP_LINEAR)
	{
		GLint err ;
//		if (err = gluBuild2DMipmaps(GL_TEXTURE_2D, bits, image->width, image->height, tformat, GL_UNSIGNED_BYTE, image->dataptr))
		if (err = Build2DMipmaps(image, tformat, arrayComponents))
		{
			cerr << "GLU Error: " << (char *)gluErrorString((GLenum)err) << endl ;

#ifdef WIN32
			MessageBox(NULL, _T((char *)gluErrorString((GLenum)err)), _T("GLU Error"), MB_OK | MB_ICONSTOP) ;
#endif
			ExitProcedure(FAILURE) ;
		}
	}
//	else
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, bits, image->width, image->height, 0, tformat, GL_UNSIGNED_BYTE, image->dataptr) ;
//	}
}


STATUS GLUTInitialize(Option& option)
{
	int argc = option.ArgC() ;

	glutInit(&argc, option.ArgV()) ;
	glutInitDisplayMode(glutBuff | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA) ;	//  | GLUT_STENCIL) ;

	glutInitWindowSize(width, height) ;

	title = option.GetString("-title", TITLE, 2) ;
	winIDglut = glutCreateWindow(title) ;

	return SUCCESS ;
}

// glut コールバック登録
void SetGLUTCallback()
{
	glutReshapeFunc(ReshapeWindow) ;
	glutKeyboardFunc(HandleKey);
	glutDisplayFunc(ObjectProc) ;
	glutMouseFunc(MouseProc) ;
//	glutSpecialFunc(SpecialKeyProc) ;
	glutMotionFunc(MouseMotion) ;
	glutIdleFunc(Redisplay) ;
	glutTimerFunc(CALC_FPS_INTERVAL, FramesPerSecond, 0) ;
}

// コールバック関数
// ウィンドウのコンフィギュレーションイベントハンドラ
void ReshapeWindow(int x, int y)
{
	glViewport(0,0, x,y) ;

	// ウィンドウの縦横比によって変化（しかしなんつー無駄）
	static GLdouble sn30 = Sin(50.0*0.5) ;

	if (x <= y)
	{
		fov         = 25.0 * 2.0 ;
	}
	else
	{
		GLdouble sn = sn30 * (GLdouble)y / x, cs ;
		cs = 1.0 - sn * sn ;
		fov         = 25.0 + ATan2(sn, cs) ;
	}
	aspectRatio = (GLdouble)x / y ;


//	glGetFloatv(GL_PROJECTION_MATRIX, projection) ;
	glMatrixMode(GL_MODELVIEW) ;

	// Save Now Window size for Mouse evnet
	width  = x ;
	height = y ;

	// FPS 描画位置計算
	fps_position.X() = -0.9f ;
	fps_position.Y() = 1.0 - (1.0 / width * 15.0) - 0.1 ;
	fps_position.Z() = 0.0f ;

	// 直ちに FPS 再計算
	glutTimerFunc(SWITCH_FPS_INTERVAL, FramesPerSecond, 1) ;

	// テクスチャサイズ適宜変更
	InitializeShadowTextures() ;
}

// キーボードイベントハンドラ
void HandleKey(unsigned char key, int x, int y)
{
    switch (key)
	{
	case 0x1b:	// ESC で終了
		ExitProcedure() ;
		break ;

	case 'o':	// 'o' 'O' で FPS ON/OFF
	case 'O':
		if (!outputFPS)
		{
			outputFPS = TRUE ;
			UpdateStatusList() ;
		}
		else
		{
            outputFPS = FALSE ;
		}
		break ;

	case 'e':	// 'e' 'E' で View 変更
		{
			viewPoint ++ ;
			if (viewPoint >= nLights)
				viewPoint = -1 ;

			if (viewPoint < 0)
				SetTemporaryWindowTitle("Eye View.") ;
			else
				SetTemporaryWindowTitle("Light " + IntToString(viewPoint) + " View.") ;
		}
		UpdateStatusList() ;
		break ;

	case 'E':
		{
			viewPoint -- ;
			if (viewPoint < -1) viewPoint = nLights -1 ;

			if (viewPoint < 0)
				SetTemporaryWindowTitle("Eye View.") ;
			else
				SetTemporaryWindowTitle("Light " + IntToString(viewPoint) + " View.") ;
		}
		UpdateStatusList() ;
		break ;

	case 'v':
	case 'V':	// 'v' 'V' でボリュームライト ON/OFF
		{
			if (volumeLight)
			{
				volumeLight = FALSE ;
				SetTemporaryWindowTitle("Disable Atmospheric Effect.") ;
			}
			else
			{
				volumeLight = TRUE ;
				SetTemporaryWindowTitle("Enable Atmospheric Effect.") ;
			}
		}
		UpdateStatusList() ;
		break ;

	case 'r':
	case 'R':	// 'r' 'R' で床への映りこみ ON/OFF
		{
			if (reflection)
			{
				reflection = FALSE ;
				SetTemporaryWindowTitle("Disable Reflection.") ;
			}
			else
			{
				reflection = TRUE ;
				SetTemporaryWindowTitle("Enable Reflection.") ;
			}
		}
		UpdateStatusList() ;
		break ;

	case 'd':
	case 'D':	// 'd' 'D' でマスク ON/OFF
		{
			if (depthMask)
			{
				depthMask = FALSE ;
				SetTemporaryWindowTitle("Disable Masking Reflection.") ;
			}
			else
			{
				depthMask = TRUE ;
				SetTemporaryWindowTitle("Enable Masking Reflection.") ;
			}
		}
		UpdateStatusList() ;
		break ;

	case 'f':
	case 'F':	// 'f' 'F' で床への映りこみのフレネル効果 ON/OFF
		{

			if (fresnel)
			{
				fresnel = FALSE ;
				SetTemporaryWindowTitle("Disable Fresnel Effect.") ;
			}
			else
			{
				fresnel = TRUE ;
				SetTemporaryWindowTitle("Enable Fresnel Effect.") ;
			}

/*
			if (perVertexFresnel)
				perVertexFresnel = FALSE ;
			else
				perVertexFresnel = TRUE ;
*/
		}
		UpdateStatusList() ;
		break ;

	case 's':
	case 'S':	// 's' 'S' で可能なら Shadow Map ON/OFF
		if (canShadow)
		{
			if (shadow)
			{
				shadow = FALSE ;
				SetTemporaryWindowTitle("Disable Shadow Mapping.") ;
			}
			else
			{
				shadow = TRUE ;
				SetTemporaryWindowTitle("Enable Shadow Mapping.") ;
			}

			InitializeShadowTextures() ;
		}
		else
		{
			SetTemporaryWindowTitle("Can't Enable Shadow Mapping.") ;
		}
		UpdateStatusList() ;
		break ;

	case 'g':
	case 'G':	// 'g' 'G' で可能なら Gloss Map ON/OFF
		if (canGloss)
		{
			if (gloss)
			{
				gloss = FALSE ;
				SetTemporaryWindowTitle("Disable Gloss Mapping.") ;
			}
			else
			{
				gloss = TRUE ;
				SetTemporaryWindowTitle("Enable Gloss Mapping.") ;
			}
		}
		else
		{
			SetTemporaryWindowTitle("Can't Enable Gloss Mapping.") ;
		}
		UpdateStatusList() ;
		break ;

	case 'l':
	case 'L':	// 'l' 'L' で平行光源、スポットライト変更
		{
			if (spotLight)
			{
				spotLight = FALSE ;
				SetTemporaryWindowTitle("Parallel Light Source.") ;
			}
			else
			{
				spotLight = TRUE ;
				SetTemporaryWindowTitle("Spot Light Source.") ;
			}

			InitializeLights() ;
			InitializeProjectionPlanes() ;
		}
		UpdateStatusList() ;
		break ;

	case 'p':
	case 'P':	// 'p' 'P' でポーズ
		{
			if (pause)
			{
				pause = FALSE ;
			}
			else
			{
				pause = TRUE ;
				SetTemporaryWindowTitle("Pause!!") ;
			}

			reconstShadowMapFlag = TRUE ;
		}
		break ;

	case ' ':	// Space でシングルステップ
//		if (pause)
		{
			pause = TRUE ;
			MoveObjects(TRUE) ;
//			SetTemporaryWindowTitle("Step!!") ;
		}
		break ;

	case 'h':
	case 'H':	// 'h' 'H' でヘルプ表示
		{
			if (tHelpIntensity > 0.0f)
				tHelpIntensity = 0.0f ;
			else
				tHelpIntensity = 1.0f ;
		}
		break ;

	case 't':
	case 'T':	// 't' 'T' でシャドウテクスチャのフィルタ変更
		{
			if (shadowTexFilter == GL_NEAREST)
			{
				shadowTexFilter = GL_LINEAR ;
				SetTemporaryWindowTitle("Shadow Map Filter: Bi-linear") ;
			}
			else
			{
				shadowTexFilter = GL_NEAREST ;
				SetTemporaryWindowTitle("Shadow Map Filter: Nearest Point") ;
			}

			InitializeShadowTextures() ;
		}
		break ;

	case 'u':
	case 'U':	// 'u' 'U' でテクスチャの異方性フィルタ変更
		if (has_texture_filter_anisotropic)
		{
			if (key == 'u')
			{
				currentAnisotropy *= 2.0f ;
				if (currentAnisotropy > maxAnisotropy)
					currentAnisotropy = 1.0f ;
			}
			else	// if (key == 'U')
			{
				currentAnisotropy *= 0.5f ;
				if (currentAnisotropy < 1.0f)
					currentAnisotropy = maxAnisotropy ;
			}

			SetAllTexturesMaxAnisotropy(currentAnisotropy) ;

			if (currentAnisotropy == 1.0f)
				SetTemporaryWindowTitle("Disable Anisotropic Filtering (Max Anisotropy: 1).") ;
			else
				SetTemporaryWindowTitle(String("Enable Anisotropic Filtering (Max Anisotropy: ") + IntToString((int)currentAnisotropy) + ").") ;
		}
		else
			SetTemporaryWindowTitle("Can't Enable Enable Anisotropic Filtering. (Max Anisotropy: 1).") ;
		break ;

	case '0':	case '1':	case '2':	case '3':	case '4':	// '0' ～ '4' でライト数変更
//	case '5':	case '6':	case '7':	case '8':
		{
			EnableDiffuse(-1) ;
			nLights = (int)(key - '0') ;
			InitializeLights() ;

			if (nLights)
				SetTemporaryWindowTitle(IntToString(nLights) + " Light Source(s).") ;
			else
				SetTemporaryWindowTitle("Ambient Only.") ;
		}
		UpdateStatusList() ;
		break ;

	case '5':	case '6':	case '7':	case '8':	//	case '9':	// '5' ～ '9' でオブジェクト数 1 ～ 5
		{
			nObjects = (int)(key - '0') - 4 ;
			InitializeLights() ;
		}
		UpdateStatusList() ;
		break ;

	case 'a':	// 'a' でαバイアスインクリメント
		{
			alphaBias += 0.5f ;
			SetAlphaBias() ;

			String t ;
			t.Format("Alpha Bias: %3.1f", alphaBias) ;
			SetTemporaryWindowTitle(t) ;
		}
		break ;

	case 'A':	// 'A' でαバイアスデクリメント
		{
			alphaBias -= 0.5f ;
			SetAlphaBias() ;

			String t ;
			t.Format("Alpha Bias: %3.1f", alphaBias) ;
			SetTemporaryWindowTitle(t) ;
		}
		break ;
	}
}


void InitializeProjectionPlanes()
{
	s_plane[0] = 1.0f ;	s_plane[1] = 0.0f ;	s_plane[2] = 0.0f ;	s_plane[3] = 0.0f ;
	t_plane[0] = 0.0f ;	t_plane[1] = 1.0f ;	t_plane[2] = 0.0f ;	t_plane[3] = 0.0f ;
	q_plane[0] = 0.0f ;	q_plane[1] = 0.0f ;	q_plane[2] = 1.0f ;	q_plane[3] = 0.0f ;

	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
	glTexGenfv(GL_S, GL_EYE_PLANE, s_plane) ;
	glTexGenfv(GL_T, GL_EYE_PLANE, t_plane) ;
	glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane) ;
}


// shadow によって 投影テクスチャのバインドNo をセット
void SetProjectionTextureObject(int shadow)
{
	if (canShadow && shadow)
	{
		for (int i = 0 ; i < MAX_LIGHTS ; i ++)
			PROJECT_TEXTURE[i] = SHADOW_TEXTURE[i] ;
//			PROJECT_TEXTURE[i] = SPOT_TEXTURE[i] ;
	}
	else
	{
		// スポットおよびシャドウマップテクスチャ
		for (int i = 0 ; i < MAX_LIGHTS ; i ++)
			PROJECT_TEXTURE[i] = SPOT_TEXTURE[i] ;
	}
}


// ディスプレイイベントハンドラ
// オブジェクトの動作＆描画
void ObjectProc()
{
	CheckOpenGLError() ;

	oTick = nTick ;
	nTick = GetErapsedTime() ;
	oldMSecStep = mSecStep ;
	mSecStep = nTick - oTick ;

	// コントロール
	ControlView() ;

	// ヘルプ輝度
	helpIntensity += (tHelpIntensity - helpIntensity) * 0.3f ;
//	cout << "h: " << helpIntensity << "  tH: " << tHelpIntensity << endl ;

	// オブジェクト移動
	if (!pause)
		MoveObjects() ;

	// 描画
	Render() ;

	// フレームカウント
	frameCount ++ ;
	f_cnt ++ ;
}

// 再描画イベント強制発行
// アイドル時コールバック
void Redisplay()
{
	glutPostRedisplay() ;
}

// マウスボタンイベントハンドラ
// ドラッグ ＯＮ，ＯＦＦ
void MouseProc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// ドラッグＯＮ時はマウスのドラッグ前の位置に現在の位置を保存
		if (state == GLUT_DOWN)
		{
			dragL = TRUE  ;
			dragX = x ;
			dragY = y ;
		}
		else if (state == GLUT_UP)
			dragL = FALSE ;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			dragR = TRUE ;
		}
		else if (state == GLUT_UP)
			dragR = FALSE ;
	}

	mouseX = x ;
	mouseY = y ;
}

// マウス移動コールバック
void MouseMotion(int x, int y)
{
	mouseX = x ;
	mouseY = y ;
}


// 一時的なウィンドウタイトルセット
// 数秒間一時的にタイトルをセット
void SetTemporaryWindowTitle(const String& title, int wait)
{
//	if (loop_count < 10)
//		return ;

	changeTitleWait = wait ;
	glutSetWindowTitle(title) ;
}


// ウィンドウタイトルセット
// SetTemporaryWindowTitle()
// 設定後の場合、一定時間以上経っていなければ無視
void SetWindowTitle(const String& title)
{
	if (!changeTitleWait)
		glutSetWindowTitle(title) ;
}


// タイマーイベントコールバック（FPS計算）
void FramesPerSecond(int value)
{
	static int  o_tick = 0, n_tick = 0 ;
	static char c_fps[32] = "____.__ FPS _____.___ kTPS" ;

	if (changeTitleWait)
		changeTitleWait -- ;

	o_tick = n_tick ;
	n_tick = GetErapsedTime() ;

	// f_cnt が 0、つまりまったく同じループでコールされた場合は、それ以上計算しない
	if (f_cnt)
	{
		if (n_tick > o_tick)
			fps = f_cnt / ((float)(n_tick - o_tick) / 1000) ;

/*
		int nPolygons = nmGlassPolygons * (nObjects + nLights) ;
		nPolygons *= nLights + 1 ;	// diffuse pass + ambient

		if (volumeLight)
			nPolygons += NM_VOLUME_LIGHT_PLANES * 2 * nLights ;

		if (reflection)
			nPolygons *= 2 ;

		// floor
		nPolygons += nLights + 1 ;
		if (reflection)
			nPolygons += 1 ;

		sprintf(c_fps, "%7.2f FPS %9.3f kTPS", fps, nPolygons * fps * 0.001) ;
*/
		sprintf(c_fps, "%7.2f FPS", fps) ;

		str_fps = String(c_fps) ;
//		if (outputFPS) cout << str_fps << endl ;

		f_cnt = 0 ;
	}

	SetWindowTitle(str_fps + " " + title) ;

	if (value == 1)
		glutTimerFunc(SWITCH_FPS_INTERVAL, FramesPerSecond, 2) ;
	else if (value == 0)
		glutTimerFunc(CALC_FPS_INTERVAL, FramesPerSecond, 0) ;
}


void MakeStatusString()
{
	str_status = str_fps ;

/*
	int pass = nLights ;
	if (shadow) pass *= 2 ;	// Shwdow Mapping
	pass += 1 ;	// Ambient Pass
	if (reflection) pass *= 2 ;

	str_status.Format("FPS: %4.2f\n", fps) ;
	str_status.AddFormat("Rendering Pass: %d\n", pass) ;
	str_status.AddFormat("Lights: %d\n", nLights) ;
	str_status.AddFormat("Objects: %d\n", nObjects) ;
	str_status.AddFormat("Objects: %d\n", nObjects) ;

	if (viewPoint < 0)
		str_status.AddFormat("View: Eye\n") ;
	else
		str_status.AddFormat("View: Light %d\n", viewPoint) ;

	if (canShadow)
	{
		if (shadow)
			str_status.AddFormat("Shadow: ON\n") ;
		else
			str_status.AddFormat("Shadow: OFF\n") ;
	}
	else
		str_status.AddFormat("Shadow: N/A\n") ;

	if (volumeLight)
		str_status.AddFormat("Atmospheric: ON\n") ;
	else
		str_status.AddFormat("Atmospheric: OFF\n") ;

	if (reflection)
	{
		str_status.AddFormat("Reflection: ON\n") ;
		if (fresnel)
			str_status.AddFormat("Fresnel: ON\n") ;
		else
			str_status.AddFormat("Fresnel: OFF\n") ;
	}
	else
	{
		str_status.AddFormat("Reflection: OFF\n") ;
		str_status.AddFormat("Fresnel: N/A\n") ;
	}
*/
}


void UpdateStatusList(GLenum mode)
{
	if (STATUS_STRING_LIST)
		glDeleteLists(STATUS_STRING_LIST, 1) ;

	MakeStatusString() ;

	glNewList(STATUS_STRING_LIST, mode) ;
	{
		DrawStatus() ;
	}
	glEndList() ;
}


// ウィンドウ左上に FPS表示
void DrawStatus()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS) ;
	{
		glDisable(GL_LIGHTING) ;
		glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
		glDisable(GL_TEXTURE_2D) ;      // テクスチャＯＦＦ
		glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
		glDisable(GL_TEXTURE_2D) ;      // テクスチャＯＦＦ
		glDisable(GL_DEPTH_TEST) ;      // デプステストＯＦＦ（必ず表示）

		glPushMatrix() ;
		{
			glLoadIdentity() ;      // モデルビュー行列を単位行列に

			glMatrixMode(GL_PROJECTION) ;
			glPushMatrix() ;
			{
				glLoadIdentity() ;      // 射影行列を単位行列に

				glColor3f(0.7f, 0.7f, 0.5f) ;
//				DrawString(str_fps, fps_position.X() + 2.0f / width ,fps_position.Y(),fps_position.Z()) ;
				DrawString(str_status, fps_position.X() + 2.0f / width ,fps_position.Y(),fps_position.Z(), GLUT_BITMAP_8_BY_13) ;

				glColor3f(0.9f, 0.9f, 0.7f) ;
//				DrawString(str_fps, fps_position.X(),fps_position.Y(),fps_position.Z()) ;
				DrawString(str_status, fps_position.X(),fps_position.Y(),fps_position.Z(), GLUT_BITMAP_8_BY_13) ;
			}
			glPopMatrix() ;
			glMatrixMode(GL_MODELVIEW) ;
		}
		glPopMatrix() ;
	}
	glPopAttrib() ;
}



// オブジェクト移動
void MoveObjects(int fixSpeed)
{
	animationCount ++ ;
	reconstShadowMapFlag = TRUE ;

	float msec ;
	if (fixSpeed)
	{
		msec = 16.6666f ;
	}
	else
	{
/*
		float g, s ;
		g = (float)Max(mSecStep, oldMSecStep) ;
		s = (float)Min(mSecStep, oldMSecStep) ;
		if (s <= 0 || g <= 0 ||
			(g / s > 1.2f))

//		cout << s << "  " << g << endl ;
*/

		if (timeRes >= 3.0f || timeRes <= 0.0f)
		{
			if (fps <= 0.0f)
				msec = 16.6666f ;
			else
				msec = 1000.0f / fps ;
		}
		else
		{
			msec = mSecStep ;
		}

		if (msec > 50.0f)
			msec = 50.0f ;
		else if (msec < 5.0f)
			msec = 5.0f ;
	}

//	cout << "timeRes: " << timeRes << ", mSecStep: " << mSecStep << endl ;

	MoveLights(msec) ;
	MovePolyhedron(msec) ;

	GradationBG() ;
}

void GradationBG()
{
/*
	float ratio = (float)(animationCount & 1023) / 512.0f ;	// 0.0 ～ 2.0

	if (ratio < 0.5f)
		ratio *= 2.0f ;
	else if (ratio < 1.0f)
		ratio = 1.0f ;
	else if (ratio < 1.5f)
		ratio = 3.0f - ratio * 2.0f ;
	else
		ratio = 0.0f ;
*/
	float ratio = (Sin(animationCount * 360.0f / 1024.0f - 90.0f)) * 0.5f + 0.5 ;

	bg[0] = bg0[0] * ratio + bg1[0] * (1 - ratio) ;
	bg[1] = bg0[1] * ratio + bg1[1] * (1 - ratio) ;
	bg[2] = bg0[2] * ratio + bg1[2] * (1 - ratio) ;
	bg[3] = bg0[3] * ratio + bg1[3] * (1 - ratio) ;

	// クリア値設定
	glClearColor(bg[0], bg[1], bg[2], bg[3]) ;
}

void MoveLights(float msec)
{
	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
	{
//		GLfloat	mat[16] ;

		for (int i = 0 ; i < nLights ; i ++)
		{
			// Distance from center, pitch
//			light[i].dangle += light[i].vdangle ;
//			light[i].distance = light[i].dbase + sin(Rad(light[i].dangle)) * 0.1 ;

			// pitch yaw for position, local roll
			light[i].angle.Transform(msec) ;

			// distance, pitch
			light[i].angle2.Transform(msec) ;
			light[i].distance = light[i].dbase + Sin(light[i].angle2.status.X()) * 1.0f ;
			light[i].pitch = (Sin(light[i].angle2.status.Y()) - 0.75f) * 12.0f ;

			light[i].position(0.0f, 0.0f, light[i].distance) ;
			float pospitch = (sin(Rad(light[i].angle.status.X())) + 1.5f) * 30.0 ;
			float s = sin(Rad(pospitch)), c = cos(Rad(pospitch)) ;
			float wy = light[i].position.Y(), wz = light[i].position.Z() ;
			light[i].position.Y() = c * wy - s * wz ;
			light[i].position.Z() = s * wy + c * wz ;

			s = sin(Rad(light[i].angle.status.Z())) ;
			c = cos(Rad(light[i].angle.status.Z())) ;
			float wx = light[i].position.X() ;
			wz = light[i].position.Z() ;
			light[i].position.Z() = c * wz - s * wx ;
			light[i].position.X() = s * wz + c * wx ;

			{
				glPushMatrix() ;
				{
					static GLfloat lightmat[16] ;

					glLoadIdentity() ;
					glRotatef(light[i].angle.status.Y(), 0.0f, 0.0f, 1.0f) ;
					glRotatef(light[i].pitch, 1.0f, 0.0f, 0.0f) ;
					gluLookAt(light[i].position.X(), light[i].position.Y(), light[i].position.Z(),
							  lightCenter[i][0], lightCenter[i][1], lightCenter[i][2],  0.0f, 1.0f, 0.0f) ;

					glGetFloatv(GL_MODELVIEW_MATRIX, lightmat) ;

					// ３ｘ３は転置行列（逆行列）
					light[i].matrix[0] = lightmat[0] ;
					light[i].matrix[1] = lightmat[4] ;
					light[i].matrix[2] = lightmat[8] ;
					light[i].matrix[3] = 0.0f ;	// lightmat[3] ;
					light[i].matrix[4] = lightmat[1] ;
					light[i].matrix[5] = lightmat[5] ;
					light[i].matrix[6] = lightmat[9] ;
					light[i].matrix[7] = 0.0f ;	// lightmat[7] ;
					light[i].matrix[8] = lightmat[2] ;
					light[i].matrix[9] = lightmat[6] ;
					light[i].matrix[10] = lightmat[10] ;
					light[i].matrix[11] = 0.0f ;	// lightmat[11] ;

					light[i].matrix[12] = light[i].position.X() ;
					light[i].matrix[13] = light[i].position.Y() ;
					light[i].matrix[14] = light[i].position.Z() ;

					light[i].matrix[15] = 1.0f ;	// lightmat[15] ;
				}
				glPopMatrix() ;
			}
		}
	}
	glPopMatrix() ;

//	cout << light[0].angle.status.Z() << endl ;
//	cout << light[0].position.X() << ", " ;
//	cout << light[0].position.Y() << ", " ;
//	cout << light[0].position.Z() << endl ;
}

void MovePolyhedron(float msec)
{
	world.angle.Transform(msec) ;

	for (int i = 0 ; i < nObjects ; i ++)
	{
		object[i].angle.Transform(msec) ;
	}
}

// 視点操作
void ControlView()
{
	float x = 0.0f, y = 0.0f ;

	if (dragL && (mouseX != dragX || mouseY != dragY))
	{
		spinX = (mouseX - dragX) * mSpeed / width ;
		spinY = (mouseY - dragY) * mSpeed / height ;

		dragX = mouseX ;
		dragY = mouseY ;
	}
	else
	{
		spinX *= 0.9f ;
		spinY *= 0.9f ;
	}

	x = spinX ;
	y = spinY ;

/*
	// さらに FPS によっても変化
	if (fps)
	{
		x *= MOUSE_FTP_RATIO / fps ;
		y *= MOUSE_FTP_RATIO / fps ;
	}
*/

	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
	{
		glLoadIdentity() ;

		if (x != 0.0f || y != 0.0f)
		{
			static Vector3d axis ;

			axis(y, x, 0.0f) ;
			axis.Unit() ;
			glRotatef(sqrt(x * x + y * y), axis.X(), axis.Y(), axis.Z()) ;
		}

		glMultMatrixf(controlObjectMatrix) ;
		glGetFloatv(GL_MODELVIEW_MATRIX, controlObjectMatrix) ;
	}
	glPopMatrix() ;


	// カメラ距離＆ステンドサイズ
	if (dragR)
	{
		float fx = (float)mouseX / width ;	// 0.0 ～ 1.0
		tLightPlaneSize = Pow(4.0f, fx * 2.0f) / 4.0f * LIGHT_PLANE_SIZE ;

		float fy = (float)mouseY / height ;	// 0.0 ～ 1.0
		tdistance = 32.0f - fy * 32.0f ;
	}

	if (!pause)
		lightPlaneSize += (tLightPlaneSize - lightPlaneSize) * 0.1f ;

	distance += (tdistance - distance) * 0.1f ;
}


// 描画
void Render()
{
	// シャドウマップアップデート
	if (shadow && reconstShadowMapFlag)
	{
		UpdateShadowMaps() ;
		reconstShadowMapFlag = FALSE ;
	}

	// ３Ｄシーン描画
	RenderScene() ;

	// ヘルプ表示
	RenderHelpMessage(helpIntensity) ;

	// ステータス表示
	if (outputFPS)
	{
		if (f_cnt == 0)
		{
			UpdateStatusList(GL_COMPILE_AND_EXECUTE) ;
		}
		else
			glCallList(STATUS_STRING_LIST) ;
	}

	// バッファのスワップおよびレクエストバッファのフラッシュ
	if (glutBuff == GLUT_DOUBLE) glutSwapBuffers() ;
	else glFlush() ;
}


void UpdateShadowMaps()
{
	glPushAttrib(GL_ENABLE_BIT) ;
	{
		glDisable(GL_DITHER) ;
		glDisable(GL_LIGHTING) ;
		glEnable(GL_SCISSOR_TEST) ;

		for (int i = 0 ; i < nLights ; i ++)
		{
			UpdateShadowMap(i) ;
		}
	}
	glPopAttrib() ;
}

void UpdateShadowMap(int lNo)
{
	glViewport(0, 0, shadowTexWidth, shadowTexHeight) ;
	SetLightViewAndProjection(lNo) ;

	// バッファクリア
	glClear(GL_DEPTH_BUFFER_BIT) ;
	RenderObjectsForShadow(lNo) ;

	// バッファからテクスチャへコピー
	glBindTexture(GL_TEXTURE_2D, SHADOW_TEXTURE[lNo]) ;
	CopyTexSubImage2D(GL_TEXTURE_2D, 0,  0, 0,  0, 0,  shadowTexWidth, shadowTexHeight) ;
}

void RenderObjectsForShadow(int lNo)
{
	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
	glDisable(GL_TEXTURE_2D) ;
	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
	glDisable(GL_TEXTURE_2D) ;

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE) ;
	glDepthFunc(GL_LESS) ;
	glEnable(GL_DEPTH_TEST) ;
	glDepthMask(GL_TRUE) ;

	// Render Polyhedron
	glPushMatrix() ;
	{
		glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
		RenderPolyhedronForShadow() ;
	}
	glPopMatrix() ;

#ifdef DISABLE_RENDER_PARALLEL_LIGHT
	// Render Light Objects
	// ライトの影は無視？
//	if (spotLight)
//		RenderLightObjectsForShadow(lNo) ;

#else	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT
//	RenderLightObjectsForShadow(lNo) ;

#endif	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT ... #else

	glActiveTexture(GL_TEXTURE0) ;
	glEnable(GL_TEXTURE_2D) ;
	glBindTexture(GL_TEXTURE_2D, SPOT_TEXTURE[lNo]) ;

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE) ;
//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) ;
	glDisable(GL_DEPTH_TEST) ;

	glCallList(SPOT_COPY_LIST) ;
}

void SetLightViewAndProjection(int lNo)
{
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	if (spotLight)
		glFrustum(-lightPlaneSize, lightPlaneSize, -lightPlaneSize, lightPlaneSize, 1.0f, LIGHT_MAX_DISTANCE) ;
	else
		glOrtho(-lightPlaneSize * LIGHT_PARALLEL_SCALE, lightPlaneSize * LIGHT_PARALLEL_SCALE,
				-lightPlaneSize * LIGHT_PARALLEL_SCALE, lightPlaneSize * LIGHT_PARALLEL_SCALE,
				1.0f, LIGHT_MAX_DISTANCE) ;

	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	TransformLightView(lNo) ;
}

void TransformLightView(int lNo)
{
	glRotatef(light[lNo].angle.status.Y(), 0.0f, 0.0f, 1.0f) ;
	glRotatef(light[lNo].pitch, -1.0f, 0.0f, 0.0f) ;
	gluLookAt(light[lNo].position.X(), light[lNo].position.Y(), light[lNo].position.Z(),
			  lightCenter[lNo][0], lightCenter[lNo][1], lightCenter[lNo][2],  0.0f, -1.0f, 0.0f) ;
}

void SetViewAndProjection(int vPoint)
{
	if (vPoint == -1)
	{
		glMatrixMode(GL_PROJECTION) ;
		glLoadIdentity() ;

		nearClip = distance - 10.0f ;
		farClip  = distance + 10.0f ;
		if (nearClip <= 0.5) nearClip = 0.5f ;
		gluPerspective(fov, aspectRatio, nearClip, farClip) ;

		// カメラセット
		glMatrixMode(GL_MODELVIEW) ;
		glLoadIdentity() ;
		gluLookAt(0.0f,0.0f,0.0f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f) ;

		// コントロール
		glTranslatef(0.0f, 0.0f, -distance) ;
		glMultMatrixf(controlObjectMatrix) ;
	}
	else	// Light view
	{
		SetLightViewAndProjection(vPoint) ;
	}
}


// ３Ｄシーン描画
void RenderScene()
{
	glViewport(0,0, width,height) ;
	SetViewAndProjection(viewPoint) ;

	// View 行列から床のビジビリティを計算
	if (reflection)
	{
		// ループ後、center の visibility がセットされている
		int start ;
		if (perVertexFresnel)
			start = 0 ;
		else
			start = 4 ;

		for (int i = start ; i < 5 ; i ++)
		{
			GLfloat vmatrix[16] ;

			glPushMatrix() ;
			{
				glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
				glGetFloatv(GL_MODELVIEW_MATRIX, vmatrix) ;
			}
			glPopMatrix() ;

			Vector3d origin(groundVertices[i]), normal(groundVertices[i] + Vector3d(0.0f, 0.0f, 1.0f)), vdir ;
			normal.Transform(vmatrix) ;
			origin.Transform(vmatrix) ;

			normal = normal - origin ;
			vdir = -Unit(origin) ;
			visibility = vdir.X() * normal.X() + vdir.Y() * normal.Y() + vdir.Z() * normal.Z() ;
			if (visibility < 0.0f)
				visibility = 0.0f ;

			// 頂点毎に反射を計算する場合は、中央の可視性チェックに反射係数は不要
			if (!perVertexFresnel || (i < 4 && perVertexFresnel))
			{
				if (fresnel)
					reflectRatio[i] = FresnelTermByCos(visibility, REFRACTION_RATE) ;
//					reflectRatio[i] = ReflectAlphaByCos(visibility, 0.2f, 4.0f) ;
				else
					reflectRatio[i] = 0.25f ;
			}
		}
	}
	else
		visibility = 0.0f ;

	RenderObjectsWithReflection() ;
}


// バックカラーで半透明で塗りつぶし
void DrawBackgroundColor(int n)
{
	// モデルビュー行列を初期化
	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
	glLoadIdentity() ;

	// 射影行列を初期化
	glMatrixMode(GL_PROJECTION) ;
	glPushMatrix() ;
	glLoadIdentity() ;

	// 矩形塗りつぶし
	glColor4f(bg[0], bg[1], bg[2], 1.0 / n) ;
//	glRectf(-1.0f, -1.0f, 1.0f, 1.0f) ;
	glBegin(GL_QUADS) ;
	{
		glVertex3f(-1.0f, -1.0f,  0.9999f) ;
		glVertex3f( 1.0f, -1.0f,  0.9999f) ;
		glVertex3f( 1.0f,  1.0f,  0.9999f) ;
		glVertex3f(-1.0f,  1.0f,  0.9999f) ;
	}
	glEnd() ;

	glPopMatrix() ;
	glMatrixMode(GL_MODELVIEW) ;
	glPopMatrix() ;
}


// 光源初期設定
void InitializeLights()
{
	reconstShadowMapFlag = TRUE ;

	GLfloat intensity = 1.0f / (nLights + 0.5f) + 0.3f ;

	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
	{
		GLenum lightNo = (GLenum)((int)GL_LIGHT0 + i) ;

		if (spotLight)
		{
			SetPositionalLight(lightNo, lightpos, lightColor[i],
							   0.0f,		// ambient
							   0.0f,		// specular
							   intensity,	// intensity
//							   0.0f,		// constant attenuation
//							   0.25f,		// linear attenuation
							   1.1f,		// constant attenuation
							   0.02f,		// linear attenuation
							   0.0f,		// quadratic attenuation
							   lightdir,	// spot direction
							   180.0f) ;	// spot cutoff
		}
		else	// directional light
		{
			SetPositionalLight(lightNo, plightpos, lightColor[i],
							   0.0f,		// ambient
							   0.0f,		// specular
							   intensity * 0.6f) ;	// intensity

			SetDirectionalLight(lightNo, plightpos, lightColor[i],
								0.0f,			// ambient
								0.0f,			// specular
								intensity * 0.6f) ;	// intensity
		}
	}
}


// 光源更新
// コール時点で GL_MODELVIEW_MATRIX に適切な行列がセットされており、
// さらに glActiveTexture(GL_TEXTUREi) で適切なテクスチャがアクティブになっている必要あり
void UpdateLights()
{
	for (int i = 0 ; i < nLights ; i ++)
	{
		UpdateLight(i) ;
	}
}

void UpdateLight(int lNo)
{
	GLenum lightNo = (GLenum)((int)GL_LIGHT0 + lNo) ;

	glPushMatrix() ;
	{
		TransformLight(lNo) ;

		if (spotLight)
		{
			glLightfv(lightNo, GL_POSITION, lightpos) ;
			glLightfv(lightNo, GL_SPOT_DIRECTION, lightdir) ;

			q_plane[2] = lightPlaneSize ;
			glTexGenfv(GL_S, GL_EYE_PLANE, s_plane) ;
			glTexGenfv(GL_T, GL_EYE_PLANE, t_plane) ;
			glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane) ;
		}
		else
		{
			glLightfv(lightNo, GL_POSITION, plightpos) ;

			s_plane[0] = t_plane[1] = -1.0f / (lightPlaneSize * LIGHT_PARALLEL_SCALE) ;
			glTexGenfv(GL_S, GL_EYE_PLANE, s_plane) ;
			glTexGenfv(GL_T, GL_EYE_PLANE, t_plane) ;
//			glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane) ;
		}
	}
	glPopMatrix() ;
}


GLsizei AdjustTextureSizeRoundUp(int size)
{
	GLsizei	texSize ;
	double	d ;
	int		n ;
	d = Log(2, size) ;
	if ((int)d != d)
		n = (int)(d + 1.0) ;
	else
		n = (int)d ;

	texSize = Pow(2, n) ;

	if (texSize > maxTextureSize)
		texSize = maxTextureSize ;

	return texSize ;
}


GLsizei AdjustTextureSizeRoundDown(int size)
{
	GLsizei	texSize ;
	double	d ;
	int		n ;
	d = Log(2, size) ;
	n = (int)d ;

	texSize = Pow(2, n) ;

	if (texSize > maxTextureSize)
		texSize = maxTextureSize ;

	return texSize ;
}


// シャドウマップ用テクスチャを新規アロケート
void InitializeShadowTextures()
{
	for (int i = 0 ; i < MAX_LIGHTS ; i ++)
	{
		if (SHADOW_TEXTURE[i] >= 1)
			glDeleteTextures(1, &SHADOW_TEXTURE[i]) ;
	}

	if (shadow)
	{
		reconstShadowMapFlag = TRUE ;

		shadowTexWidth = AdjustTextureSizeRoundDown(width) ;
		shadowTexHeight = AdjustTextureSizeRoundDown(height) ;

		glScissor(0, 0, shadowTexWidth, shadowTexHeight) ;

		// 内部フォーマット
		GLint internalFormat ;
		if      (alphaBits <= 4)	internalFormat = GL_RGBA4 ;
		if      (alphaBits <= 8)	internalFormat = GL_RGBA8 ;
		else if (alphaBits <= 12)	internalFormat = GL_RGBA12 ;
		else						internalFormat = GL_RGBA16 ;

		for (int i = 0 ; i < MAX_LIGHTS ; i ++)
		{
			glBindTexture(GL_TEXTURE_2D, AllocATexture(SHADOW_TEXTURE[i])) ;
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, shadowTexWidth, shadowTexHeight, 0,
									 GL_RGB, GL_UNSIGNED_BYTE, NULL) ;	// GL_RGB 以降の引数（３つ）はダミー

//			SetupTexture2D("", GL_REPEAT, shadowTexFilter) ;
			SetupTexture2D("", GL_CLAMP, shadowTexFilter) ;
		}
	}

	SetProjectionTextureObject(shadow) ;
	SetProjectionTextureEnvMode(shadow) ;
}

// ワールドオブジェクトマトリクスを乗算
void TransformWorld()
{
	glRotatef(8.0f, 0.0f, 1.0, 0.0f) ;
	glRotatef(world.angle.status.Z(), 0.0f, 0.0, 1.0f) ;
	glRotatef(8.0f, 0.0f, 1.0, 0.0f) ;
}

void EnableAmbient()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient) ;

	for (int i = 0 ; i < nLights ; i ++)
	{
		GLenum lightNo = (GLenum)((int)GL_LIGHT0 + i) ;
		glDisable(lightNo) ;
	}
}

void EnableDiffuse(int lNo)
{
	for (int i = 0 ; i < nLights ; i ++)
	{
		if (i == lNo) continue ;

		GLenum lightNo = (GLenum)((int)GL_LIGHT0 + i) ;
		glDisable(lightNo) ;
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, nambient) ;

	if (lNo >= 0)
	{
		GLenum lightNo = (GLenum)((int)GL_LIGHT0 + lNo) ;
		glEnable(lightNo) ;
		UpdateLight(lNo) ;
	}
}


void RenderObjectsWithReflection()
{
	if (reflection)
	{
/*
		if (stencilBits)
		{
			// バッファクリア
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) ;
			glCallList(T_GROUND_LIST) ;
		}
		else
*/
		{
			if (depthMask)
				glClearDepth(0.0f) ;
			else
				glClearDepth(1.0f) ;

			glDepthMask(GL_TRUE) ;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
			glDepthRange(1.0f, 1.0f) ;
			glEnable(GL_DEPTH_TEST) ;
			glDepthFunc(GL_ALWAYS) ;
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE) ;

			glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
			glDisable(GL_TEXTURE_2D) ;
			glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
			glDisable(GL_TEXTURE_2D) ;
			glDisable(GL_LIGHTING) ;

			glCallList(TV_GROUND_LIST) ;

			glDepthRange(0.0f, 1.0f) ;
			glDepthFunc(GL_LESS) ;
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) ;
		}

		glPushMatrix() ;
		{
			// 床への映りこみ用反転
			glCallList(REFLECT_TRANSFORM_LIST) ;

			glFrontFace(GL_CW) ;
			RenderObjects(TRUE) ;
			glFrontFace(GL_CCW) ;
		}
		glPopMatrix() ;

		if (stencilBits)
		{
		}
		else
		{
			glClearDepth(1.0f) ;
			glClear(GL_DEPTH_BUFFER_BIT) ;
		}

		RenderObjects() ;
	}
	else	// !reflection
	{
		// バッファクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
		RenderObjects() ;
	}
}


void RenderObjects(int reflectMode)
{
	activeRenderingLight = -1 ;

	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
	glDisable(GL_TEXTURE_2D) ;
	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
	glBindTexture(GL_TEXTURE_2D, OBJECT_TEXTURE) ;
	EnableSolidTexture() ;

	EnableAmbient() ;
	glEnable(GL_DEPTH_TEST) ;
	glDepthFunc(GL_LESS) ;
	glDepthMask(GL_TRUE) ;
	glEnable(GL_LIGHTING) ;

	glDisable(GL_BLEND) ;

	// Render Polyhedron
	glPushMatrix() ;
	{
		glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
		RenderPolyhedron(reflectMode) ;
	}
	glPopMatrix() ;

#ifdef DISABLE_RENDER_PARALLEL_LIGHT
	// Render Light Objects
	if (spotLight)
		RenderLightObjectsAmbientPass() ;

#else	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT
	RenderLightObjectsAmbientPass() ;

#endif	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT ... #else

	// for TNT
	if (isTNT)
		glEnable(GL_POLYGON_OFFSET_FILL) ;

	// If shadow, Enable Alpha Test
	if (shadow)
		glEnable(GL_ALPHA_TEST) ;
	else
		glDisable(GL_ALPHA_TEST) ;

	for (int i = 0 ; i < nLights ; i ++)
	{
		activeRenderingLight = i ;

		if (i == 0)
		{
			glDepthMask(GL_FALSE) ;
			glDepthFunc(GL_LEQUAL) ;
			glBlendFunc(GL_ONE, GL_ONE) ;
			glEnable(GL_BLEND) ;
		}

		{
			glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
			glBindTexture(GL_TEXTURE_2D, PROJECT_TEXTURE[i]) ;
			EnableProjectionTexture() ;
		}

//		glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;
		EnableDiffuse(i) ;

		glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;

#ifdef DISABLE_LIGHT_VIEW_SHADOW
		if (shadow && i == viewPoint)
			glDisable(GL_ALPHA_TEST) ;
#endif	// #ifdef DISABLE_LIGHT_VIEW_SHADOW

		// Render Polyhedron
		glPushMatrix() ;
		{
			glRotatef(90.0f, 1.0f, 0.0, 0.0f) ;
			RenderPolyhedron(reflectMode) ;
		}
		glPopMatrix() ;

#ifdef DISABLE_RENDER_PARALLEL_LIGHT
		// Render Light Objects
		// ライトは環境光のみ？
//		if (spotLight)
//			RenderLightObjects() ;

#else	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT
//		RenderLightObjects() ;

#endif	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT ... #else


#ifdef DISABLE_LIGHT_VIEW_SHADOW
		if (shadow && i == viewPoint)
			glEnable(GL_ALPHA_TEST) ;
#endif	// #ifdef DISABLE_LIGHT_VIEW_SHADOW

//		glDepthMask(GL_TRUE) ;
//		glDisable(GL_BLEND) ;
	}

	activeRenderingLight = -1 ;

	// If shadow, Disable Alpha Test
	if (shadow)
		glDisable(GL_ALPHA_TEST) ;

	// for TNT
	if (isTNT)
		glDisable(GL_POLYGON_OFFSET_FILL) ;

	// ボリュームライト描画
#ifdef DISABLE_RENDER_PARALLEL_LIGHT
	if (volumeLight && spotLight)
#else	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT
	if (volumeLight)
#endif	// #ifndef DISABLE_RENDER_PARALLEL_LIGHT ... #else
	{
		glEnable(GL_BLEND) ;
//		glBlendFunc(GL_ONE, GL_ONE) ;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR) ;
		glDepthMask(GL_FALSE) ;
		glDepthFunc(GL_LESS) ;
		glDisable(GL_LIGHTING) ;
		glDisable(GL_CULL_FACE) ;

		glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
		glDisable(GL_TEXTURE_2D) ;

		RenderVolumeLights(reflectMode) ;

		glEnable(GL_CULL_FACE) ;
	}

	glDepthMask(GL_TRUE) ;
	glDisable(GL_BLEND) ;
}

void RenderVolumeLights(int reflectMode)
{
	glActiveTexture(activeTexGenerate + GL_TEXTURE0) ;

	for (int i = 0 ; i < nLights ; i ++)
	{
		if (viewPoint != i)
		{
			glBindTexture(GL_TEXTURE_2D, PROJECT_TEXTURE[i]) ;
			UpdateLight(i) ;
			RenderVolumeLight(i, reflectMode) ;
		}
	}
}

void RenderVolumeLight(int lNo, int reflectMode)
{
	glPushMatrix() ;
	{
		TransformLight(lNo) ;
		glScalef(lightPlaneSize, lightPlaneSize, 1.0f) ;
		if (reflectMode &&depthMask)
		{
			if (spotLight)
				glCallList(R_VOLUME_LIGHT_LIST[lNo]) ;
			else
				glCallList(R_PARALLEL_VOLUME_LIGHT_LIST[lNo]) ;
		}
		else
		{
			if (spotLight)
				glCallList(VOLUME_LIGHT_LIST[lNo]) ;
			else
				glCallList(PARALLEL_VOLUME_LIGHT_LIST[lNo]) ;
		}
	}
	glPopMatrix() ;
}


void RenderLightObjectsAmbientPass()
{
//	glActiveTexture(activeTexExplicit + GL_TEXTURE0) ;
//	glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE) ;
	glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING | GL_BLEND) ;
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;

		glDisable(GL_TEXTURE_2D) ;

		// 環境光パスのみグローバル光源を有効に
		glEnable(GL_LIGHT7) ;

		for (int i = 0 ; i < nLights ; i ++)
		{
			// ビューポイントにあるライトは描画の必要なし
			if (i != viewPoint)
			{
				glCallList(LIGHT_MATERIAL_LIST[i]) ;
				RenderLightObjectAmbientPass(i) ;
			}
		}
	}
	glPopAttrib() ;
}

void RenderLightObjects()
{
	glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING) ;
	{
		glDisable(GL_TEXTURE_2D) ;

		for (int i = 0 ; i < nLights ; i ++)
		{
			// 自分自身に光は当たらないため加算の必要なし
			// さらに、ビューポイントにあるライトは描画の必要なし
			if (i != activeRenderingLight && i != viewPoint)
			{
				if (activeRenderingLight < 0)
					glCallList(LIGHT_MATERIAL_LIST[i % 2]) ;

				RenderLightObject(i) ;
			}
		}
	}
	glPopAttrib() ;
}

void RenderLightObject(int lNo)
{
	glPushMatrix() ;
	{
		TransformLight(lNo) ;
		glScalef(lightPlaneSize, lightPlaneSize, 1.0f) ;
		glEnable(GL_NORMALIZE) ;
		if (spotLight)
			glCallList(LIGHT_LIST) ;
		else
			glCallList(PARALLEL_LIGHT_LIST) ;
		glDisable(GL_NORMALIZE) ;
	}
	glPopMatrix() ;
}

void RenderLightObjectAmbientPass(int lNo)
{
	glPushMatrix() ;
	{
		TransformLight(lNo) ;
		glScalef(lightPlaneSize, lightPlaneSize, 1.0f) ;

		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT) ;
		{
			glEnable(GL_NORMALIZE) ;
			glDisable(GL_CULL_FACE) ;

			if (spotLight)
				glCallList(LIGHT_LIST) ;
			else
				glCallList(PARALLEL_LIGHT_LIST) ;

			glEnable(GL_CULL_FACE) ;

			glDisable(GL_LIGHTING) ;
			glColor3fv(lightSourceColor[lNo]) ;
			if (spotLight)
				glCallList(LIGHT_SOURCE_PLANE_LIST) ;
			else
				glCallList(PARALLEL_LIGHT_SOURCE_PLANE_LIST) ;

			glEnable(GL_TEXTURE_2D) ;
			glBindTexture(GL_TEXTURE_2D, SPOT_TEXTURE[lNo]) ;
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;

			glEnable(GL_BLEND) ;

			glColor4f(1.0f, 1.0f, 1.0f, 0.5f) ;

			if (spotLight)
				glCallList(LIGHT_PLANE_LIST) ;
			else
				glCallList(PARALLEL_LIGHT_PLANE_LIST) ;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;
		}
		glPopAttrib() ;
	}
	glPopMatrix() ;
}

void RenderLightObjectsForShadow(int lNo)
{
	for (int i = 0 ; i < nLights ; i ++)
	{
		// 自分自身のライトの影は描画しない
		if (i != lNo)
			RenderLightObjectForShadow(i) ;
	}
}

void RenderLightObjectForShadow(int lNo)
{
	glPushMatrix() ;
	{
		TransformLight(lNo) ;
		glScalef(lightPlaneSize, lightPlaneSize, 1.0f) ;
		glEnable(GL_NORMALIZE) ;
		if (spotLight)
			glCallList(S_LIGHT_LIST) ;
		else
			glCallList(S_PARALLEL_LIGHT_LIST) ;
		glDisable(GL_NORMALIZE) ;
	}
	glPopMatrix() ;
}


void RenderPolyhedron(int reflectMode)
{
	// Draw Ground
	if (!reflectMode)
	{
		// 環境光描画パス時のみ裏面も描画
		if (activeRenderingLight < 0)
		{
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gambient) ;
			glDisable(GL_CULL_FACE) ;
//			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;
		}

		// reflection で見えている時は、スネルに基づく半透明で描画
		// reflection なし時は visibility = 0
		if (visibility > 0.0f)
		{
			GLfloat color[4][4] ;

			if (activeRenderingLight >= 0)
			{
				// スポットライト描画パス
				glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE) ;

				if (gloss)
				{
					// グロスマッピング時はバッファのαを使用するため、
					// 頂点単位だろうが中心だろうが
					// 明るさを調整する必要は一切なし
					// ブレンド関数のセットのみ
					glBlendFunc(GL_DST_ALPHA, GL_ONE) ;
					glCallList(GROUND_LIST) ;
					glBlendFunc(GL_ONE, GL_ONE) ;
				}
				else	// !gloss
				{
					if (perVertexFresnel)
					{
						// 頂点単位にフレネル計算
						for (int v = 0 ; v < 4 ; v ++)
						{
							// 明るさをディフューズ（１－反射係数）にセット（α値は床のインデクス）
							color[v][0] = color[v][1] = color[v][2] = 1.0f - reflectRatio[v] ;
							color[v][3] = groundAlphaIndex * alphaRes ;
						}
						glEnable(GL_COLOR_MATERIAL) ;
						DrawGround(FALSE, color[0], color[1], color[2], color[3]) ;
						glColor4f(1.0f, 1.0f, 1.0f, 1.0f) ;
						glDisable(GL_COLOR_MATERIAL) ;
					}
					else
					{
						// 中央の１点のみのフレネルを使用
						// 明るさを１－反射係数にセット（α値は床のインデクス）
						// [0] のみ使用
						color[0][0] = color[0][1] = color[0][2] = 1.0f - reflectRatio[4] ;
						color[0][3] = groundAlphaIndex * alphaRes ;
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[0]) ;
						DrawGround() ;
						color[0][0] = color[0][1] = color[0][2] = color[0][3] = 1.0f ;
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[0]) ;
					}
				}
			}
			else
			{
				// 環境光描画パス
				if (gloss)
				{
					glBindTexture(GL_TEXTURE_2D, FLOOR_WITH_GLOSS_TEXTURE) ;

					if (perVertexFresnel)
					{
						// 頂点単位にフレネル計算
						for (int v = 0 ; v < 4 ; v ++)
						{
							color[v][0] = color[v][1] = color[v][2] = 1.0f ;
							color[v][3] = 1.0f - reflectRatio[v] ;
//							color[v][3] = 1.0f - reflectRatio[v] * 2.0f ;	// diffuse * 2 - 1	// color[v][3] = (1.0f - reflectRatio[v]) * 2.0f - 1.0f ;
						}

						glPushAttrib(GL_ALL_ATTRIB_BITS) ;
						{
							glEnable(GL_COLOR_MATERIAL) ;
							glCallList(GLOSS_MAP_TEX_ENV_MODE_LIST) ;	// テクスチャ関数セット Alpha = SA * (1 - TA) + TA

							// １パス目で床をαブレンドで描画
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
							glEnable(GL_BLEND) ;
							glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE) ;
							DrawGround(FALSE, color[0], color[1], color[2], color[3]) ;

							// ２パス目はブレンドなしでα値のみ描画
							glDepthFunc(GL_LEQUAL) ;
							glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE) ;
							glDisable(GL_BLEND) ;
							DrawGround(FALSE, color[0], color[1], color[2], color[3]) ;
						}
						glPopAttrib() ;
//						glColor4f(1.0f, 1.0f, 1.0f, 1.0f) ;
//						glDisable(GL_COLOR_MATERIAL) ;
					}
					else
					{
						// 中央の１点のみのフレネルを使用
						color[0][0] = color[0][1] = color[0][2] = 1.0f ;
						color[0][3] = 1.0f - reflectRatio[4] ;
//						color[0][3] = 1.0f - reflectRatio[4] * 2.0f ;		// diffuse * 2 - 1	// color[0][3] = (1.0f - reflectRatio[4]) * 2.0f - 1.0f ;

						glPushAttrib(GL_ALL_ATTRIB_BITS) ;
						{
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[0]) ;
							glCallList(GLOSS_MAP_TEX_ENV_MODE_LIST) ;	// テクスチャ関数セット Alpha = SA * (1 - TA) + TA

							// １パス目で床をαブレンドで描画
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
							glEnable(GL_BLEND) ;
							glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE) ;
							glCallList(GROUND_LIST) ;

							// ２パス目はブレンドなしでα値のみ描画
							glDepthFunc(GL_LEQUAL) ;
							glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE) ;
							glDisable(GL_BLEND) ;
							DrawGround(GROUND_LIST) ;
						}
						glPopAttrib() ;
					}

					// 以後αプレーンはリードオンリー
					glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE) ;
				}
				else	// !gloss
				{
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
					glEnable(GL_BLEND) ;

					glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE) ;

					if (perVertexFresnel)
					{
						// 頂点単位にフレネル計算
						for (int v = 0 ; v < 4 ; v ++)
						{
							color[v][0] = color[v][1] = color[v][2] = 1.0f ;
							color[v][3] = 1.0f - reflectRatio[v] ;
						}
						glEnable(GL_COLOR_MATERIAL) ;
						DrawGround(FALSE, color[0], color[1], color[2], color[3]) ;
						glColor4f(1.0f, 1.0f, 1.0f, 1.0f) ;
						glDisable(GL_COLOR_MATERIAL) ;
					}
					else
					{
						// 中央の１点のみのフレネルを使用
						color[0][0] = color[0][1] = color[0][2] = 1.0f ;
						color[0][3] = 1.0f - reflectRatio[4] ;
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[0]) ;
						DrawGround(FALSE) ;
						color[0][3] = 1.0f ;
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[0]) ;
					}

					glBlendFunc(GL_ONE, GL_ONE) ;
					glDisable(GL_BLEND) ;
				}
			}
		}
		else	// if (visibility <= 0.0f)
		{
			// 反射なし時
			glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE) ;
			glCallList(GROUND_LIST) ;
		}

		if (activeRenderingLight < 0)
		{
			glEnable(GL_CULL_FACE) ;
//			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient) ;
		}
	}

	glBindTexture(GL_TEXTURE_2D, OBJECT_TEXTURE) ;

	// Rotate base
	TransformWorld() ;

	// Draw polyhedron
	for (int i = 0 ; i < nObjects ; i ++)
	{
		RenderLocalPolyhedron(i) ;
	}
}


void RenderPolyhedronForShadow()
{
	// Draw Ground
	glDisable(GL_CULL_FACE) ;
	glCallList(S_GROUND_LIST) ;
	glEnable(GL_CULL_FACE) ;

	// Rotate base
	TransformWorld() ;

	// Draw polyhedron
	for (int i = 0 ; i < nObjects ; i ++)
	{
		RenderLocalPolyhedronForShadow(i) ;
	}
}


void RenderLocalPolyhedron(int obj)
{
	glPushMatrix() ;
	{
		TransformLocal(obj) ;
		glCallList(OBJECT_LIST[obj]) ;
	}
	glPopMatrix() ;
}


void RenderLocalPolyhedronForShadow(int obj)
{
	glPushMatrix() ;
	{
		TransformLocal(obj) ;
		glCallList(S_OBJECT_LIST[obj]) ;
	}
	glPopMatrix() ;
}

// ローカルオブジェクトマトリクスを乗算
void TransformLocal(int obj)
{
	if (obj && nObjects > 1)
	{
		glRotatef((float)obj * 360.0f / (nObjects - 1),  0.0f, 0.0f, 1.0f) ;
		glTranslatef(3.0f, 0.0f, 0.0f) ;
	}

	switch (obj % 2)
	{
	case 0:
		glRotatef(object[obj].angle.status.X(), 1.0f, 0.0, 0.0f) ;
		glRotatef(object[obj].angle.status.Y(), 0.0f, 1.0, 0.0f) ;
		glRotatef(object[obj].angle.status.Z(), 0.0f, 0.0, 1.0f) ;
		break ;
	case 1:
		glRotatef(object[obj].angle.status.Y(), 0.0f, 1.0, 0.0f) ;
		glRotatef(object[obj].angle.status.Z(), 0.0f, 0.0, 1.0f) ;
		glRotatef(object[obj].angle.status.X(), 1.0f, 0.0, 0.0f) ;
		break ;
	case 2:
		glRotatef(object[obj].angle.status.Z(), 0.0f, 0.0, 1.0f) ;
		glRotatef(object[obj].angle.status.X(), 1.0f, 0.0, 0.0f) ;
		glRotatef(object[obj].angle.status.Y(), 0.0f, 1.0, 0.0f) ;
		break ;
	}
}

// ライトオブジェクトマトリクスを乗算
void TransformLight(int lNo)
{
	glMultMatrixf(light[lNo].matrix) ;

/*
	// Set Position
	glTranslatef(light[lNo].position.X(), light[lNo].position.Y(), light[lNo].position.Z()) ;

	// Set Direction
	Vector3d dir, axis, forward(0.0f, 0.0f, 1.0f) ;
	dir = -Unit(light[lNo].position) ;
	axis = forward | dir ;



	float degree = Deg(acos(axis.X() * forward.X() + axis.Y() * forward.Y() + axis.Y() * forward.Y())) ;
	glRotatef(degree, axis.X(), axis.Y(), axis.Z()) ;
*/
}


// 終了処理
void ExitProcedure(STATUS state)
{
#ifdef WIN32
	if (resultTimeBeginPeriod == TIMERR_NOERROR)
		timeEndPeriod(TIMER_PERIOD) ;
#endif

	if (winIDglut)
		glutDestroyWindow(winIDglut) ;

	if (state == SUCCESS)
		exit(EXIT_SUCCESS) ;
	else
		exit(EXIT_FAILURE) ;
}


// ディスプレイリストおよびテクスチャネーム確保
GLuint AllocAList(GLuint& list)
{
	if (!(list = glGenLists(1)))
	{
		cerr << "Can't allocate Display Lists." << endl ;

#ifdef WIN32
		MessageBox(NULL, _T("Can't allocate Display Lists"), _T("Indexed Shadow Mapping Error"), MB_OK | MB_ICONSTOP) ;
#endif
		ExitProcedure(FAILURE) ;
	}
	return list ;
}

GLuint AllocATexture(GLuint& list)
{
	glGenTextures(1, &list) ;
	return list ;
}


void CheckOpenGLError()
{
	GLenum errCode = glGetError() ;

	if (errCode != GL_NO_ERROR)
	{
		String error ;
		switch (errCode)
		{
		case GL_INVALID_ENUM:
			error = "GL_INVALID_ENUM" ;
			break ;
		case GL_INVALID_VALUE:
			error = "GL_INVALID_VALUE" ;
			break ;
		case GL_INVALID_OPERATION:
			error = "GL_INVALID_OPERATION" ;
			break ;
		case GL_STACK_OVERFLOW:
			error = "GL_STACK_OVERFLOW" ;
			break ;
		case GL_STACK_UNDERFLOW:
			error = "GL_STACK_UNDERFLOW" ;
			break ;
		case GL_OUT_OF_MEMORY:
			error = "GL_OUT_OF_MEMORY" ;
			break ;
		}

		String errlog ;
		errlog.Format(String("OpenGL Error: ") + error + ": %s\n", (char *)gluErrorString((GLenum)errCode)) ;
		cerr << errlog ;

#ifdef WIN32
		MessageBox(NULL, _T((char *)gluErrorString((GLenum)errCode)), "OpenGL Error: " + error, MB_OK | MB_ICONSTOP) ;
#endif

		ExitProcedure(FAILURE) ;
	}
}


// メイン
#if !defined WIN32 || defined _CONSOLE
int main(int argc, char** argv)
{
	Option option(argc, argv) ;

	STATUS state;
	state = Initialize(option) ;
	if (state != SUCCESS)
		exit(EXIT_FAILURE) ;

	glutMainLoop() ;
	return EXIT_SUCCESS ;
}

#else
// Windows メイン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Option option(__argc, __argv) ;

	STATUS state ;
	state = Initialize(option) ;
	if (state != SUCCESS)
		exit(EXIT_FAILURE) ;

	glutMainLoop() ;
	return EXIT_SUCCESS ;
}
#endif
