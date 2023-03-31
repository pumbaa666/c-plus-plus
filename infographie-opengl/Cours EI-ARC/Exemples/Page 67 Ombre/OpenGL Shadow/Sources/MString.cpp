
#include "MString.H"


// �R���X�g���N�^
String::String(int n)
{
	length = n ;

	if (n == 0)
	{
		str = NULL ;
		Clear() ;
	}
	else
	{
		allocated = ShouldAlloc(length) ;
		str = new char[allocated] ;
		memset(str, ' ', length) ;
		str[length] = '\0' ;
	}
}

String::String(const char *c)
{
//      cout << "String::String from const char * OK!!!!!!!" << endl ;

    length = strlen(c) ;
	if (length == 0)
	{
		str = NULL ;
		Clear() ;
		return ;
	}

/*
	if (length < MIN_ALLOC_UNIT)
		allocated = MIN_ALLOC_UNIT ;
	else
		allocated = (length + 1) * 2 ;
*/
	allocated = ShouldAlloc(length) ;
    str = new char[allocated] ;

	// �ŏ�����k�����L�蓾��̂ŁA�k���͕ʓr�ǉ�
    memcpy(str, c, length) ;
    str[length] = '\0' ; // �Ō�Ƀk�������t��
}

String::String(const char *c, int n)
{
//      cout << "String::String from const *char, int OK!!!!!!!" << endl ;

	int slen = strlen(c) ;

    length = n ;
	allocated = ShouldAlloc(length) ;
    str = new char[allocated] ;

    if (slen < length)
    {
        // �R�s�[���̕����Z���ꍇ�͂��܂���󔒂Ŗ��߂�
        memcpy(str, c, slen) ;
		memset(&(str[slen]) , ' ', length - slen) ;
    }
    else
    {
        // �R�s�[���̕��������������ꍇ�͒P���ɕK�v���R�s�[
        memcpy(str, c, length) ;
    }

	// �Ō�Ƀk�������ǉ�
	str[length] = '\0' ;
}

String::String(const String& s)
{
//    cout << "String::String from String OK!!!!!!!" << endl ;
//	if (this == &s) return ;

    length = s.length ;
	allocated = s.allocated ;

    str = new char[allocated] ;
    memcpy(str, s.str, length) ;
    str[length] = '\0' ; // �Ō�Ƀk�������t��

//    *this = String(s.str, s.length) ;
}

String::String(const String& s, int n)
{
//    cout << "String::String from String, int  OK!!!!!!!" << endl ;
    length = n ;
	allocated = ShouldAlloc(length) ;
    str = new char[allocated] ;

    if (s.length < length)
    {
        // �R�s�[���̕����Z���ꍇ�͂��܂���󔒂Ŗ��߂�
        memcpy(str, s.str, s.length) ;
		memset(&(str[s.length]), ' ', length - s.length) ;
    }
    else
    {
        // �R�s�[���̕��������������ꍇ�͒P���ɕK�v���R�s�[
        memcpy(str, s.str, length) ;
    }

	// �Ō�Ƀk�������ǉ�
	str[length] = '\0' ;

//    *this = String(s.str, n) ;
}

String::String(char c)
{
    str = NULL ;
    if (c == '\0')
	{
		str = NULL ;
		Clear() ;
	}
    else
    {
		length = 1 ;
		allocated = MIN_ALLOC_UNIT ;
		str = new char[allocated] ;
		str[0] = c ; str[1] = '\0' ;
    }
}


// ������̒�����ω��i�]���������� ' '�j
String& String::Length(int n)
{
	if (length == n)
		return *this ;
	else if (length > n)
	{
		// �Z���Ȃ����Ƃ�
		Realloc(n) ;
		length = n ;
		return *this ;
	}
	else
	{
		// �����Ȃ����Ƃ��̂݁A���������ɋ󔒂��Z�b�g
		Realloc(n) ;
		memset(&(str[length]), ' ', n - length) ;
//		str[n] = '\0' ;
		length = n ;
		return *this ;
	}

//    return (*this = String(str, n)) ;
}


// n �����ڂ̂P����
char String::Character(int n) const
{
	if (n < 1 || n > length) return '\0' ;
	return str[n - 1] ;
}

// n �����ڂ̕�����ύX
String& String::SetAt(int n, char c)
{
	if (n > 0 && n <= length)
		str[n - 1] = c ;
	return *this ;
}


String& String::ReplaceString(char s, char d)
{
	for (int n = 1 ; n <= length ; n ++)
	{
		if (str[n - 1] == s)
			str[n - 1] = d ;
	}

	return *this ;
}

String& String::ReplaceString(const String& s, const String& d)
{
	if (this == &s || this == &d) return *this ;

	int pos = 1 ;
	while (TRUE)
	{
		int start = Search(s) ;

		// 2000.06.08
		if (start < pos || !start)
			break ;

		int rlen = length - (start + s.length - 1) ;
		String right ;
		if (rlen > 0)
			right = ::Right(*this, rlen) ;

		if (start == 1)
		{
			*this = d + right ;
		}
		else
		{
			Length(start - 1) ;
			*this += d + right ;
		}

		pos = start + d.Length() ;
	}

	return *this ;
}


// Lower, Upper
String& String::Lower()
{
	for (int i = 0 ; i < length ; i ++)
	{
		if (isupper(str[i]))
			str[i] = tolower(str[i]) ;
	}

	return *this ;
}

String& String::Upper()
{
	for (int i = 0 ; i < length ; i ++)
	{
		if (islower(str[i]))
			str[i] = toupper(str[i]) ;
	}

	return *this ;
}


// �t�H�[�}�b�g
String& String::Format(const char* format, ...)
{
	char buf[MAX_LINE_BUF] ;

	va_list args ;
	va_start(args, format) ;
//	int r = vsprintf(buf, format, args) ;
	vsprintf(buf, format, args) ;
	va_end(args) ;

	// ������Z�b�g
	*this = buf ;
	return *this ;
}

// �t�H�[�}�b�g
String& String::AddFormat(const char* format, ...)
{
	char buf[MAX_LINE_BUF] ;

	va_list args ;
	va_start(args, format) ;
//	int r = vsprintf(buf, format, args) ;
	vsprintf(buf, format, args) ;
	va_end(args) ;

	// ������Z�b�g
	*this += buf ;
	return *this ;
}


// �v���C�x�[�g
String& String::ReadAllLines(FILE *fp)
{
	while (TRUE)
	{
		char buf[MAX_LINE_BUF] ;
		char *s ;

		s = fgets(buf, MAX_LINE_BUF, fp) ;
		if (!s)
			break ;

		*this += s ;
	}
	return *this ;
}


// �e�L�X�g�t�@�C���ǂݍ���
String& String::ReadFile(const String& fileName)
{
	FILE *fp ;
	fp = fopen(fileName, "r") ;

	if (!fp)
		*this = "" ;
	else
	{
		*this = ReadAllLines(fp) ;
		fclose(fp) ;
	}

	return *this ;
}


// �g�[�N�����
// �Ԃ��ꂽ�g�[�N���i�ŏ��̕�����j�͍폜�����
// String("") ���Ԃ����܂ŌJ��Ԃ�����
String String::Token(const String& delimiters, const String& comment)
{
	String	token ;

	// ���̃g�[�N���̃X�^�[�g�ʒu������
	int start ;
	for (start = 1 ; start <= Length() ; start ++)
	{
		// �R�����g�s�`�F�b�N
		if (::Mid(*this, start, comment.Length()) == comment)
		{
			// �R�����g�Ȃ�s�̍Ō�܂Ŕ�΂�
			String right = ::Mid(*this, start, Length()) ;
			int next = right.Search('\n') ;

			if (next)
				start = next ;
			else	// ���s���Ȃ��Ƃ������Ƃ͕�����̍Ō�
				start = Length() ;

			continue ;
		}

		int flag = TRUE ;
		for (int c = 1 ; c <= delimiters.Length() ; c ++)
		{
			if (Character(start) == delimiters.Character(c))
			{
				flag = FALSE ;
				break ;
			}
		}

		// �f���~�^�̂ǂ�Ƃ��}�b�`���Ȃ��ꍇ�͌���
		if (flag)
			break ;
	}

	Mid(start, Length()) ;

	// ���̃g�[�N���̏I���̈ʒu������
	int length ;
	for (length = 1 ; length <= Length() ; length ++)
	{
		// �R�����g�`�F�b�N�i�r���ŃR�����g�ɂȂ��Ă���ꍇ�̓R�����g�̒��O�܂Łj
		if (::Mid(*this, length, comment.Length()) == comment)
			break ;

		// �f���~�^�̂ǂꂩ�P�ł��}�b�`����΂��̒��O�܂�
		int flag = FALSE ;
		for (int c = 1 ; c <= delimiters.Length() ; c ++)
		{
			if (Character(length) == delimiters.Character(c))
			{
				flag = TRUE ;
				break ;
			}
		}

		if (flag)
			break ;
	}

	length -- ;
	token = ::Left(*this, length) ;
	Mid(length + 1, Length()) ;

	return token ;
}


// m �����ڂ��� n ����
String& String::Mid(int m, int n)
{
	// �R�s�[�̒����ƈʒu��K����
    if (m < 1) m = 1 ;
    if (m > length || n < 0) return (this->Clear()) ;
	if (m + n > length + 1) n = length + 1 - m ;

	// �d������\�������邽��
    memmove(str, &(str[m - 1]), n) ;

	// ���ʂ�����΍��
	Realloc(n) ;
	length = n ;
	str[length] = '\0' ;

	return *this ;

/*
    if (m < 1) m = 1 ;
    if (m > length || n < 0) return (this->Clear()) ;
    if (m + n > length + 1) n = length + 1 - m ;

    String  w(n) ;
//    for (int i = 0 ; i < n ; i ++) w.str[i] = this->str[m + i - 1] ;
    memcpy(w.str, &(this->str[m - 1]), n) ;

    *this = w ;
    return *this ;
*/
}
String Mid(String s, int m, int n)
{
    return (s.Mid(m, n)) ;
}

// ������ n ����
String& String::Left(int n)
{
    return (this->Mid(1, n)) ;
}
String Left(const String& s, int n)
{
    return (Mid(s, 1, n)) ;
}

// �E���� n ����
String& String::Right(int n)
{
    if (n > length) n = length ;
    this->Mid(length + 1 - n, n) ;
	return *this ;
}
String Right(const String& s, int n)
{
    String  w = s ;
    return (w.Right(n)) ;
}

// �w�肳�ꂽ�t�@�C�����̃f�B���N�g��������Ԃ�
// �E���猟�����A"/" �������� "\" �̎�O�܂ł�Ԃ�
String String::FileDirectory() const
{
#ifdef WIN32
	char dpath = '\\' ;
#else
	char dpath = '/' ;
#endif

	String dir ;

	int locate = length - 1 ;
	while (locate > 0 && str[locate - 1] != dpath) locate -- ;
	if (locate <= 0)
		dir = "" ;
	else
		dir = ::Left(*this, locate - 1) ;

	return dir ;
}

// �w�肳�ꂽ�t�@�C�����̃t�@�C���l�[��������Ԃ�
// �E���猟�����A"/" �������� "\" �̌�݂̂�Ԃ�
String String::FileNamePart() const
{
#ifdef WIN32
	char dpath = '\\' ;
#else
	char dpath = '/' ;
#endif

	String dir ;

	int locate = length - 1 ;
	while (locate > 0 && str[locate - 1] != dpath) locate -- ;
	if (locate <= 0)
		dir = str ;
	else
		dir = ::Right(*this, length - locate) ;

	return dir ;
}

// ������T�[�`�i�ŏ��Ɉ�v�����ꏊ��Ԃ��j
int String::Search(const String& key, int start) const
{
	// �������ׂ������񒷂� 0 �Ȃ� FALSE
	if ((!key.length) || (length < start)) return FALSE ;

	// ������̒�������L�[���������Ƃ���܂ŃT�[�`
	for (int i = start ; i < length - (key.length - 1) ; i ++)
	{
		char tmp = key.str[0] ;
		if (tmp == str[i])
		{
			// �L�[���P�����Ȃ炱�̎��_�Ŋm��
			if (key.length == 1)
				return (i + 1) ;
			// �L�[���Q�����ȏ�̏ꍇ�͂���ɃT�[�`
			else
			{
				int j ;
				for (j = 1 ; j < key.length ; j ++)
					if (str[i + j] != key.str[j]) break ;

				// �L�[�̕����������J��Ԃ��Ă���Ίm��
				if (j == key.length)
					return (i + 1) ;
			}
		}
    }

	return FALSE ;

/*
	// �������ׂ������񒷂� 0 �Ȃ� FALSE
	if ((!key.length) || (length < start)) return FALSE ;

	char *st ;
	if (start <= 1)	st = str ;
	else			st = str + start - 1 ;

	char *s ;
	s = strstr(str[start], key)
*/
}
/*
// ������T�[�`�i�ŏ��Ɉ�v�����ꏊ��Ԃ��j
int String::Search(const String& key) const
{
    if ((!key.length) || (!length)) return FALSE ; // �����񒷂� 0 �Ȃ� FALSE

    // ������̒�������L�[���������Ƃ���܂ŃT�[�`
    for (int i = 0 ; i < length - (key.length - 1) ; i ++)
    {
		char tmp = key.str[0] ;
		if (tmp == str[i])
		{
		    // �L�[���P�����Ȃ炱�̎��_�Ŋm��
		    if (key.length == 1)
				return (i + 1) ;
		    // �L�[���Q�����ȏ�̏ꍇ�͂���ɃT�[�`
		    else
		    {
			int j ;
			for (j = 1 ; j < key.length ; j ++)
			    if (str[i + j] != key.str[j]) break ;

			// �L�[�̕����������J��Ԃ��Ă���Ίm��
			if (j == key.length)
			    return (i + 1) ;
			}
		}
	}

    return FALSE ;
}
*/
int String::Search(const char *key, int start) const
{
    return Search(String(key), start) ;
}
int String::Search(const char key, int start) const
{
    return Search(String(key), start) ;
}


// �I�y���[�^�i/�j�܂�́A�����̕�������T�[�`���A��v�����񐔂�Ԃ�
int String::operator /(const String& key) const
{
    if ((!key.length) || (!length)) return FALSE ; // �����񒷂� 0 �Ȃ� FALSE

    int     n = 0 ;

    // ������̒�������L�[���������Ƃ���܂ŃT�[�`
    for (int i = 0 ; i < length - (key.length - 1) ; i ++)
    {
		char tmp = key.str[0] ;
		if (tmp == str[i])
		{
		    // �L�[���P�����Ȃ炱�̎��_�Ŋm��
		    if (key.length == 1)
				n ++ ;
			// �L�[���Q�����ȏ�̏ꍇ�͂���ɃT�[�`
		    else
		    {
				int j ;
				for (j = 1 ; j < key.length ; j ++)
				    if (str[i + j] != key.str[j]) break ;

				// �L�[�̕����������J��Ԃ��Ă���Ίm��
				if (j == key.length)
			    n ++ ;
		    }
		}
    }

    return n ;
}
int String::operator /(const char *key) const
{
    return *this / String(key) ;
}
int String::operator /(const char key) const
{
    return *this / String(key) ;
}

// �������� String ��
String IntToString(int i)
{
    String  s ;
    if (i < 0)
    {
		s = '-' ;
		i = -i ;
    }

    for (int flg = OFF, d = MAX_DIV_DEF ; d > 1 ; d /= 10)
    {
		if (d > i)
		{
		    if (flg) s += '0' ;
		    continue ;
		}
		flg = ON ;
		s += char(i / d + '0') ;
		i %= d ;
    }
    return (s + char(i + '0')) ;
}

// �I�y���[�^�i=�j������Z�q
String& String::operator =(const String& s)
{
/*
    delete [] str ;
    length = s.length ;
    str = new char[length + 1] ;


//    for (int i = 0 ; i < length ; i ++) str[i] = s.str[i] ;
//    str[length] = '\0' ; // �Ō�Ƀk�������t��

    memcpy(str, s.str, length + 1) ;
    return *this ;
*/
	if (this == &s) return *this ;

	Copy(s) ;
	return *this ;
}
String& String::operator =(const char *c)
{
	int clen = strlen(c) ;
	Realloc(clen) ;
	length = clen ;
	memcpy(str, c, length + 1);
	return *this ;

//    return (*this = String(c)) ;
}
String& String::operator =(const char c)
{
	Realloc(1, FALSE) ;
	length = 1 ;
	str[0] = c ;
	str[1] = '\0' ;
	return *this ;

//	return (*this = String(c)) ;
}


// ������r�i�ŏ��� n ������ s �Ɠ����ŁAn ���オ s �Ɠ������r�؂��j
// String str ;
// str.Equ("abcde",3) �̂悤�� ("abcde", 3) �Ŕ�r����ƁA
// str = "abc", str = "abcd", str = "abcde" �� TRUE
// str �� "abcde"�i5 �����j��蒷������ FALSE
// n <= 0 �܂��� �ȗ�����ƁAn = 1 �Ɠ���
int String::Equ(const String s, int n)
{
    if (n <= 0) n = 1 ;

    if (length > s.length || length < n) return FALSE ;
    String w = s ;
    w.Length(length) ;
    return (*this == w) ;
}

// n �����召��r�istrncmp()�Ɠ��������An ���ȗ�����ƁAstrcmp() �Ɠ����j
int String::Cmp(const String s, int n)
{
    if (n < 0) return strcmp(str, s.str) ;
    else       return strncmp(str, s.str, n) ;
}

/*
// �I�y���[�^�i==, !=�j��r���Z�q
int operator ==(const String& s1, const String& s2)
{
    if (!strcmp(s1.str, s2.str)) return TRUE ;
    else                         return FALSE ;
}
int operator ==(const char *c, const String& s2)
{
    if (!strcmp(c, s2.str)) return TRUE ;
    else                    return FALSE ;
}
int operator !=(const String& s1, const String& s2)
{
    return !(s1 == s2) ;
}
int operator !=(const char *c, const String& s2)
{
    return !(c == s2) ;
}
*/


// �I�y���[�^�i==, !=�j��r���Z�q

// String ���m�̔�r
int String::operator ==(const String& s2) const
{
    if (!strcmp(str, s2.str)) return TRUE ;
    else                      return FALSE ;
}
int String::operator !=(const String& s2) const
{
    if (strcmp(str, s2.str)) return TRUE ;
    else                     return FALSE ;
//	{
//    if (strcmp(str, s2.str)) return TRUE ;
//    else                     return FALSE ;
//	}
}

// char * �Ƃ̔�r
int String::operator ==(const char *c) const
{
    if (!strcmp(str, c)) return TRUE ;
    else                 return FALSE ;
}
int String::operator !=(const char *c) const
{
    if (strcmp(str, c)) return TRUE ;
    else                return FALSE ;
}

// char �Ƃ̔�r
int String::operator ==(const char c) const
{
    if (length == 1 && str[0] == c) return TRUE ;
    else                            return FALSE ;
}
int String::operator !=(const char c) const
{
    return !(*this == c) ;
}

// ���ӂ� char * �Ƃ̔�r
int operator ==(const char *c, const String& s2)
{
    if (!strcmp(c, s2.str)) return TRUE ;
    else                    return FALSE ;
}
int operator !=(const char *c, const String& s2)
{
    if (strcmp(c, s2.str)) return TRUE ;
    else                   return FALSE ;
}

// ���ӂ� char �Ƃ̔�r
int operator ==(const char c, const String& s2)
{
    return (s2 == c) ;
}
int operator !=(const char c, const String& s2)
{
    return (s2 != c) ;
}


/*
// �I�y���[�^�i>, <, >=, <=�j�召��r���Z�q
int operator >(const String& s1, const String& s2)
{
    if (strcmp(s1.str, s2.str) > 0) return TRUE ;
    else                            return FALSE ;
}
int operator >(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) > 0) return TRUE ;
    else                       return FALSE ;
}
int operator <(const String& s1, const String& s2)
{
    if (strcmp(s1.str, s2.str) < 0) return TRUE ;
    else                            return FALSE ;
}
int operator <(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) < 0) return TRUE ;
    else                            return FALSE ;
}
int operator >=(const String& s1, const String& s2)
{
    return (s1 > s2 || s1 == s2) ;
}
int operator >=(const char *c, const String& s2)
{
    return (c > s2 || c == s2) ;
}
int operator <=(const String& s1, const String& s2)
{
    return (s1 < s2 || s1 == s2) ;
}
int operator <=(const char *c, const String& s2)
{
    return (c < s2 || c == s2) ;
}
*/

// �I�y���[�^�i>, <, >=, <=�j�召��r���Z�q

// String ���m�̔�r
int String::operator >(const String& s2) const
{
    if (strcmp(str, s2.str) > 0) return TRUE ;
    else                         return FALSE ;
}
int String::operator <(const String& s2) const
{
    if (strcmp(str, s2.str) < 0) return TRUE ;
    else                         return FALSE ;
}
int String::operator >=(const String& s2) const
{
    if (strcmp(str, s2.str) >= 0) return TRUE ;
    else                          return FALSE ;
}
int String::operator <=(const String& s2) const
{
    if (strcmp(str, s2.str) <= 0) return TRUE ;
    else                          return FALSE ;
}

// char * �Ƃ̔�r
int String::operator >(const char *c) const
{
    if (strcmp(str, c) > 0) return TRUE ;
    else                    return FALSE ;
}
int String::operator <(const char *c) const
{
    if (strcmp(str, c) < 0) return TRUE ;
    else                    return FALSE ;
}
int String::operator >=(const char * c) const
{
    if (strcmp(str, c) >= 0) return TRUE ;
    else                     return FALSE ;
}
int String::operator <=(const char *c) const
{
    if (strcmp(str, c) <= 0) return TRUE ;
    else                     return FALSE ;
}

// char �Ƃ̔�r
int String::operator >(const char c) const
{
    return (*this > String(c)) ;
}
int String::operator <(const char c) const
{
    return (*this < String(c)) ;
}
int String::operator >=(const char c) const
{
    return (*this >= String(c)) ;
}
int String::operator <=(const char c) const
{
    return (*this <= String(c)) ;
}

// ���ӂ� char* �Ƃ̔�r
int operator >(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) > 0) return TRUE ;
    else                       return FALSE ;
}
int operator <(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) < 0) return TRUE ;
    else                       return FALSE ;
}
int operator >=(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) >= 0) return TRUE ;
    else                        return FALSE ;
}
int operator <=(const char *c, const String& s2)
{
    if (strcmp(c, s2.str) <= 0) return TRUE ;
    else                        return FALSE ;
}

// ���ӂ� char �Ƃ̔�r
int operator >(const char c, const String& s2)
{
    return (String(c) > s2) ;
}
int operator <(const char c, const String& s2)
{
    return (String(c) < s2) ;
}
int operator >=(const char c, const String& s2)
{
    return (String(c) >= s2) ;
}
int operator <=(const char c, const String& s2)
{
    return (String(c) <= s2) ;
}


// �I�y���[�^�i()�j������Z�q
String& String::operator ()(const String& s)
{
    return (*this = s) ;
}
String& String::operator ()(const char *c)
{
    return (*this = c) ;
}
String& String::operator ()(const char c)
{
    return (*this = c) ;
}


/*
// �I�y���[�^�i+, +=�j
String operator +(const String& d, const String& s)
{
    String  w(d.str, d.length + s.length) ;
    for (int i = 0 ; i < s.length ; i ++) w.str[i + d.length] = s.str[i] ;
    return w ;
}
String operator +(char d, const String& s)
{
    String wd = String(d), w(wd, s.length + 1) ;
    for (int i = 0 ; i < s.length ; i ++) w.str[i + 1] = s.str[i] ;
    return w ;
}
String operator +(const String& d, char s)
{
    String ws(s), w(d.str, d.length + 1) ;
    for (int i = 0 ; i < ws.length ; i ++) w.str[i + d.length] = ws.str[i] ;
    return w ;
}
String& String::operator +=(const char c)
{
    return (*this = *this + c) ;
}
String& String::operator +=(const String& s)
{
    return (*this = *this + s) ;
}
*/

// �I�y���[�^�i+, +=�j

// String ���m�̘A��
String String::operator +(const String& s) const
{
    String  w(str, length + s.length) ;

//    for (int i = 0 ; i < s.length ; i ++) w.str[i + length] = s.str[i] ;
    memcpy(&(w.str[length]), s.str, s.length) ;

    return w ;
}
// �E�ӂ� char * �Ƃ̘A��
String String::operator +(const char *s) const
{
    int slen = strlen(s) ;
    String  w(str, length + slen) ;

//    for (int i = 0 ; i < slen ; i ++) w.str[i + length] = s[i] ;
    memcpy(&(w.str[length]), s, slen) ;

    return w ;
}
// �E�ӂ� char �Ƃ̘A��
String String::operator +(const char s) const
{
    String w(str, length + 1) ;
    w.str[w.length - 1] = s ;
    return w ;
}

// ���ӂ� char * �Ƃ̘A��
String operator +(const char *d, const String& s)
{
    int     dlen = strlen(d) ;
    String  w(d, dlen + s.length) ;
    for (int i = 0 ; i < s.length ; i ++) w.str[i + dlen] = s.str[i] ;
    return w ;
}

// ���ӂ� char �Ƃ̘A��
String operator +(const char d, const String& s)
{
    String wd(d), w(wd, s.length + 1) ;
    for (int i = 0 ; i < s.length ; i ++) w.str[i + 1] = s.str[i] ;
    return w ;
}

// �A�����
String& String::operator +=(const String& s)
{
	if (this == &s)
	{
		*this += String(s) ;
		return *this ;
	}

	Realloc(length + s.length) ;
	memcpy(&(str[length]), s.str, s.length + 1) ;
	length += s.length ;

	return *this ;
/*
    int len = length ;
    Length(len + s.length) ;
    for (int i = 0 ; i < s.length ; i ++)
      str[i + len] = s.str[i] ;

    return (*this) ;
*/
}
String& String::operator +=(const char *s)
{
	int slen = strlen(s) ;
	Realloc(length + slen) ;
	memcpy(&(str[length]), s, slen + 1) ;
	length += slen ;

	return *this ;

//    return (*this = *this + s) ;
}
String& String::operator +=(const char c)
{
	Realloc(length + 1) ;
	length ++ ;
	str[length - 1] = c ;
	str[length] = '\0' ;

	return *this ;
/*
    Length(length + 1) ;
    str[length - 1] = c ;
    return (*this) ;
*/
}


// �I�y���[�^�i*, *=�j
String String::operator *(int n)
{
	String s(length * n) ;
	for (int i = 0 ; i < n ; i ++)
		memcpy(&(str[length * i]), str, length) ;
	length *= n ;
	return s ;
/*
    String  s ;
    for (int i = 0 ; i < n ; i ++) s += *this ;
    return s ;
*/
}
String& String::operator *=(int n)
{
	Realloc(length * n) ;
	for (int i = 1 ; i < n ; i ++)
		memcpy(&(str[length * i]), str, length) ;
	length *= n ;
	return *this ;

//    return (*this = *this * n) ;
}

// ���o�̓I�y���[�^
ostream& operator <<(ostream& os, const String& s)
{
    os << s.str ;
    return os ;
}
istream& operator >>(istream& is, String& s)
{
    is >> s.str ;
    return is ;
}


// �g��

// ������̐؂�l�߁i�E������󔒂܂��͉��s�܂���TAB���Ȃ��j
String& String::Cut()
{
    int  i ;
    for (i = length ; i >= 1 ; i --)
    {
//	if (Character(i) != ' '  &&
//	    Character(i) != '\n' &&
//	    Character(i) != '\t') break ;
	if (!isspace(Character(i))) break ;
    }
    Length(i) ; // ������̒�����؂�l�߂�

    return *this ;
}


// ������̐؂�l�߁i�E������󔒂܂��͉��s�܂���TAB���Ȃ��j
String& Cut(String s)
{
    return s.Cut() ;
}

// ������̐؂�l�߁i�E������󔒂܂��͉��s�܂���TAB���Ȃ��j
String& Cut(const char *s)
{
    String tmp(s) ;
    return tmp.Cut() ;
}






#ifdef OVERRIDE_NEW_OPERATOR


//��������������������������������������������������������������������������
//      �������m�[�h�\����
//��������������������������������������������������������������������������
typedef struct memnode_tag
{
        struct memnode_tag      *pNext;
        unsigned long                        dwSize;
        int                                     pMem[1];
} MEMNODE;

// �\���̂̃w�b�_�����̃T�C�Y

#define MEMNODE_HDRSIZE (sizeof(MEMNODE*) + sizeof(unsigned long))



//��������������������������������������������������������������������������
//      �n�b�V���e�[�u���֘A
//��������������������������������������������������������������������������
// �n�b�V���e�[�u���̑傫���i�Q�̗ݏ�ł��邱�Ƃ��K�{�j
//#define HASHTABLE_SIZE  0x1000
#define HASHTABLE_SIZE  0x1000

// �n�b�V���e�[�u��
static MEMNODE memtbl[HASHTABLE_SIZE];

// �|�C���^����n�b�V���L�[�����߂�C�����C���֐�
static inline unsigned long GetHashKey( void* p )
{
        return (int)p & (HASHTABLE_SIZE - 1);
}



//��������������������������������������������������������������������������
//      �f�[�^�W�v
//��������������������������������������������������������������������������
// �A���P�[�g�v���񐔁i���s�܂ށj
static int nAllocCtr = 0;

// �t���[�v���񐔁i���s�܂ށj
static int nFreeCtr = 0;

// �A���P�[�g���s��
static int nAllocFail = 0;

// �t���[���s��
static int nFreeFail = 0;

// NULL �t���[��
static int nFreeNull = 0;

// ���݂̃������m�ۗʁi�P���ȑ��a�j
static int nAllocAmt = 0;

// �ő厞�̃������m�ۗ�
static int nAllocAmtMax = 0;

// �����I�`�F�b�N�I��
static int isChecked = FALSE ;


// ���J���������e�[�u��
#define MAX_UNFREE_TABLE 10000
static int nLeaks ;
static MEMNODE *unfree[MAX_UNFREE_TABLE] ;


//��������������������������������������������������������������������������
//      �I�[�o�[���C�h����new���Z�q
//��������������������������������������������������������������������������
void* :: operator new( size_t n )
{
        MEMNODE*        pNewNode;
        MEMNODE*        pNode;
        unsigned long           nKey;

		if (!nAllocCtr)
		{
			for (int i = 0 ; i < HASHTABLE_SIZE ; i ++)
				memtbl[i].pNext = NULL ;
		}

        nAllocCtr++;

        // �Ƃ肠�����̈���m��
        pNewNode = (MEMNODE*)malloc( n + sizeof(MEMNODE) );
        if ( pNewNode == NULL )
        {
                nAllocFail++;
                return NULL;
        }


/*
		else if (//((int)pNewNode) == (0xD82B40) ||
				 //((int)pNewNode) == (0xD82DE0) ||
//				 ((int)pNewNode) == (0xD83830) ||
				 ((int)pNewNode) == (0xD837B0))
		{
			pNewNode = pNewNode ;
//			inline int logprintf(const char* format, ...) ;
//			logprintf("pNewNode:%lX\n", pNewNode) ;
		}

//			inline int logprintf(const char* format, ...) ;
//			logprintf("pNewNode:%lX  pNewNode->pMem:%lX\n", (int)pNewNode, (int)pNewNode->pMem) ;
*/

        pNewNode->pNext = NULL;
        pNewNode->dwSize = n;

        // �������m�ۗʂ̏W�v
        nAllocAmt += n;
        if ( nAllocAmt > nAllocAmtMax ) nAllocAmtMax = nAllocAmt;

        // �n�b�V���e�[�u���̐擪�̃G���g���𓾂�
        nKey    = GetHashKey(pNewNode);
        pNode   = &memtbl[nKey];

        // �A���̍Ō����������
        while ( pNode->pNext != NULL )
        {
                pNode = pNode->pNext;
        }

        // �A���̍Ō���� pNewNode ��ǉ�
        pNode->pNext = pNewNode;

        // pMem���m�ۂ��ꂽ�̈�ƂȂ�
        return (void*)pNewNode->pMem;
}



//��������������������������������������������������������������������������
//      �I�[�o�[���C�h����delete���Z�q
//��������������������������������������������������������������������������
void :: operator delete( void* p )
{
        MEMNODE*        pDelNode;
        MEMNODE*        pNode;
        int                     nKey;

        nFreeCtr++;

		if (!p)
		{
			nFreeFail ++ ;
			nFreeNull ++ ;
			return ;
		}
        
        // �|�C���^p���m�[�h�̃|�C���^���Z�o����
        pDelNode = (MEMNODE*)((int)p - MEMNODE_HDRSIZE);

		if (isChecked)
		{
			for (int i = 0 ; i < nLeaks ; i ++)
			{
				if (unfree[i] == pDelNode)
				{
					unfree[i] = NULL ;
					free(pDelNode) ;
				}
			}

			FILE *fp = fopen("leakcheck.log", "w") ;
			if (fp)
			{
				for (int i = 0 ; i < nLeaks ; i ++)
				{
					if (unfree[i])
						fprintf(fp, "leak: address: 0x%lX\n", (int)unfree[i]) ;
				}
//				fprintf(fp, "already checked!  address: %lX  delete request: %ld\n", ((int)p - MEMNODE_HDRSIZE), nFreeCtr) ;
				fprintf(fp, "delete request: %ld\n", nFreeCtr) ;
				fclose(fp) ;
			}
			return ;
		}

		if ((int)pDelNode == 0x00d729d0)
		{
			pDelNode = pDelNode ;
		}

        // pDelNode���n�b�V���L�[�����߂�
        nKey = GetHashKey(pDelNode);
        
        // �n�b�V���e�[�u�����CpDelNode�̈�O�̃m�[�h��������
        pNode = &memtbl[nKey];
        while ( pNode->pNext != pDelNode && pNode->pNext != NULL )
        {
                pNode = pNode->pNext;
        }

        // �m�[�h��������Ȃ������ꍇ�̏����i�G���[�j
        if ( pNode->pNext == NULL )
        {
                nFreeFail++;
                return;
        }

        // �A���̌q������
        pNode->pNext = pDelNode->pNext;

        // �̈�̊J��
        nAllocAmt -= pDelNode->dwSize;
        free(pDelNode);
}



//��������������������������������������������������������������������������
//      �W�v����
//��������������������������������������������������������������������������
void MemDebugFinal()
{
        char    pStrBuf[256];
        int             i;
		int     leakBytes = 0 ;

		isChecked = TRUE ;
		for (i = 0 ; i < MAX_UNFREE_TABLE ; i ++)
			unfree[i] = NULL ;


//		inline int logprintf(const char* format, ...) ;

		nLeaks = 0 ;

        // �n�b�V���e�[�u���𑖍����C���J���̗̈悪��������x����\���B
        for ( i=0 ; i<HASHTABLE_SIZE ; i++ )
        {
                MEMNODE* pNode = memtbl[i].pNext;

                while ( pNode )
                {
                        MEMNODE* pNext = pNode->pNext;
//                        sprintf( pStrBuf, ">> Memory leak found!!  key: %d  address:%lX  pNext:%lX  size:%d bytes\r\n", i, (int)pNode, (int)pNode->pNext, (int)pNode->dwSize) ;
                        sprintf( pStrBuf, ">> Memory leak found!!  address:%lX  %d bytes\r\n", (int)pNode, (int)pNode->dwSize) ;
//                        logprintf( pStrBuf );
						leakBytes += pNode->dwSize ;
//                        free( pNode );

						unfree[nLeaks] = pNode ;
						nLeaks ++ ;

                        pNode = pNext;
                }
        }

/*
        // �W�v���ʂ��o��
        sprintf( pStrBuf, ">> new    request : %ld times\r\n", nAllocCtr );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> delete request : %ld times\r\n", nFreeCtr );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> new    failure : %ld times\r\n", nAllocFail );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> delete failure : %ld times\r\n", nFreeFail );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> delete NULL    : %ld times\r\n", nFreeNull );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> allocation max : %ld bytes\r\n", nAllocAmtMax );
        logprintf( pStrBuf );

        sprintf( pStrBuf, ">> total %d bytes leak\r\n", leakBytes );
        logprintf( pStrBuf );
*/
}


#endif	// #ifdef OVERRIDE_NEW_OPERATOR
