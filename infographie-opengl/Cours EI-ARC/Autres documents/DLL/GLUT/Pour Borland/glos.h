// GLOS.H
//
// This is an OS specific header file

// Voir commentaire dans glut.h sur ATEXIT
 #define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>

// disable data conversion warnings

//#pragma warning(disable : 4305)     // MIPS
//#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4309)     // X86
//#pragma warning(disable : 4051)     // ALPHA
