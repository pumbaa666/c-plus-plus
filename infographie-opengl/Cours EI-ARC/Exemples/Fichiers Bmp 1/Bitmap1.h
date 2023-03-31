/*
 * "$Id: bitmap.h,v 1.2 1996/01/09 22:52:53 mike Exp mike $"
 *
 *   Device Independent Bitmap definitions for OpenGL under MS Windows.
 *
 * Revision History:
 *
 * 06. 01. 2006 : PCH
 * Changer le nom du fichier :
 * Bitmap.h  --> Bitmap1.h
 *
 *   $Log: bitmap.h,v $
 *   Revision 1.2  1996/01/09  22:52:53  mike
 *   Added PrintDIBitmap.
 *
 *   Revision 1.1  1995/12/31  07:26:54  mike
 *   Initial revision
 */

/*
 * Include necessary headers.
 */

#ifndef _BITMAP1_H_
#  define _BITMAP1_H_

#  include <stdio.h>
#  include <stdlib.h>
#  include <errno.h>
#  include <windows.h>
#  include <wingdi.h>

#  include <GL/gl.h>


/*
 * Make this header file work with C and C++ source code...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

extern void	*LoadDIBitmap(char *filename, BITMAPINFO **info);
extern int	SaveDIBitmap(char *filename, BITMAPINFO *info, void *bits);
extern void	*ReadDIBitmap(BITMAPINFO **info);
extern int	PrintDIBitmap(HWND owner, BITMAPINFO *info, void *bits);

extern GLubyte	*ConvertRGB(BITMAPINFO *info, void *bits);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_BITMAP1_H_ */

/*
 * End of "$Id: bitmap.h,v 1.2 1996/01/09 22:52:53 mike Exp mike $".
 */
