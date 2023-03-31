
#ifndef ___OPTION_H___
#define ___OPTION_H___


#include "MString.H"


class Option
{
    int     argc ;
    String  *argv ;
    char    **orgArgv ;

    Option& Del(int c = 0, int n = 1) ;

  public:

    // �R���X�g���N�^
    Option(int c, char *v[]) ;

	// �f�X�g���N�^
    ~Option() { delete [] argv ; }

    // �A�N�Z�T
    int  ArgC() { return argc ; }
    char **ArgV() { return orgArgv ; }

    // �w��I�v�V�����𒲂ׂ�
    int    Get(String opt, int nStr = -1) ;
    int    GetInt(String opt, int def, int nStr = -1) ;
    double GetDouble(String opt, double def, int nStr = -1) ;
    String GetString(String opt, String def, int nStr = -1) ;

	// 99-12-16 �ǉ�
	// �c���Ă���i��������Ă��Ȃ��j���ׂẴI�v�V������A�����ĕԂ�
	// �I�v�V�����̍폜�͍s��Ȃ�
	String GetUnusedString() ;

    // ���p�֐�
    String GetDisplay(String def = "", int nStr = 5) ;       // -display
    String GetTitle(String def = "Untitled", int nStr = 6) ; // -title
    String GetGeometry(String def = "", int nStr = 5) ;      // -geometry
} ;


// �R���X�g���N�^
inline Option::Option(int c, char *v[])
{
    argc = c ;
    argv = new String[c] ;
    orgArgv = v ;
    for (int i = 0 ; i < c ; i ++) argv[i] = v[i] ;
}

// �w��ԍ� c ����An �� ���������菜��
inline Option& Option::Del(int c, int n)
{
//#ifdef WIN32
	String	*w = new String[argc -= n] ;
//#else
//	String  w[argc -= n] ;
//#endif

	int i ;

    for (i = 0 ; i < argc ; i ++)
    {
	if (i >= c) w[i] = argv[i + n] ;
	else        w[i] = argv[i] ;
    }
    delete [] argv ;

//    argv = new String[argc] ;
//    for (i = 0 ; i < argc ; i ++) argv[i] = w[i] ;

	argv = w ;
    return *this ;
}

inline int Option::Get(String opt, int nStr)
{
    int n = 0 ;
    for (int i = 0 ; i < argc ; i ++)
    {
	if (argv[i].Equ(opt, nStr))
	{
	    n ++ ;
	    Del(i --) ;
	}
    }
    return n ;
}

inline int Option::GetInt(String opt, int def, int nStr)
{
    for (int i = 0 ; i < argc ; i ++)
    {
	if (argv[i].Equ(opt, nStr) && i < argc - 1)
	{
	    def = atoi(argv[i + 1]) ;
	    Del(i, 2) ;
		break ;
	}
    }
    return def ;
}

inline double Option::GetDouble(String opt, double def, int nStr)
{
    for (int i = 0 ; i < argc ; i ++)
    {
	if (argv[i].Equ(opt, nStr) && i < argc - 1)
	{
	    def = atof(argv[i + 1]) ;
	    Del(i, 2) ;
		break ;
	}
    }
    return def ;
}

inline String Option::GetString(String opt, String def, int nStr)
{
    for (int i = 0 ; i < argc ; i ++)
    {
	if (argv[i].Equ(opt, nStr) && i < argc - 1)
	{
	    def = argv[i + 1] ;
	    Del(i, 2) ;
		break ;
	}
    }
    return def ;
}

// 99-12-16 �ǉ�
// �c���Ă���i��������Ă��Ȃ��j���ׂẴI�v�V������A�����ĕԂ�
// �I�v�V�����̍폜�͍s��Ȃ�
inline String Option::GetUnusedString()
{
	String str ;

	// argv[0] �̓A�v���P�[�V�������Ȃ̂Ŗ���
	if (argc >= 2)
		str = argv[1] ;

    for (int i = 2 ; i < argc ; i ++)
		str += " " + argv[i] ;

    return str ;
}

// -display �I�v�V�����Q�b�g
inline String Option::GetDisplay(String def, int nStr)
{
    return GetString("-display", def, nStr) ;
}

// -title �I�v�V�����Q�b�g
inline String Option::GetTitle(String def, int nStr)
{
    return GetString("-title", def, nStr) ;
}

// -geometry �I�v�V�����Q�b�g
inline String Option::GetGeometry(String def, int nStr)
{
    return GetString("-geometry", def, nStr) ;
}


#endif