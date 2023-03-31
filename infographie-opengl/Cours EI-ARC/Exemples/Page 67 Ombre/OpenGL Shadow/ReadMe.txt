

===========================================================================

			IShadowMap-1.2
		http://www.daionet.gr.jp/~masa/ishadowmap

		2000.09 Masa (Masaki Kawase)
		E-Mail: masa@daionet.gr.jp
		URL   : http://www.daionet.gr.jp/~masa/

===========================================================================

======== Contents ========

- What is IShadowMap?
- System Requirements
- Installation
- Techniques
- History


======== What is IShadowMap? ========

IShadowMap is a OpenGL Shadow Mapping demo including
- Atmospheric Effect
- Reflection
- Fresnel Effect
- Gloss Mapping
etc.

======== System Requirements ========

- Intel 80x86 compatible CPU
- Microsoft Windows 95/98/NT/2000
- OpenGL-1.1 or later that supports
  GL_ARB_multitexture or GL_EXT_multitexture or GL_SGIS_multitexture
are required to execute.

Additionally,
- at least 4 bits alpha plane
- GL_EXT_texture_env_combine
are required to enable shadow and gloss mapping effects.

This demo program is optimized for nVIDIA GeForce series.
It works on Riva TNT based video cards too, but has some bugs with positional
lights.
On GeForce based video cards, reference driver 5.x or later is highly
recommended.
And on TNT based video cards, 6.x or later is recommended.
Otherwise, it will work very slowly :-(


======== Installation ========

Extract all files to the folder that you want to install.
Execute "ishadowmap.exe".
Press 'h' key to display the help information.


========  Techniques ========

This demo's shadow mapping uses unique index number of each convex object
instead of depth value from the light.
Therefore, shadowing uses only one texture blending stage and 4 bits alpha plane.


======== History ========

- 2000.09.09	IShadowMap-1.2 Release
		- Supprting anisotropic filtering
		    If GL_EXT_texture_filter_anisotropic extension is supported,
		    max degree of anisotropy is set to 2.0 by default and you
		    can increase/decrease the max degree of anisotropy by
		    pushing 'u'/'U'.
		    Especially the floor texture looks better.

- 2000.09.04	IShadowMap-1.1 Release
		- Supprting nVIDIA Riva TNT series (works fine only with
		  directional lights)
		- Changing some textures, etc.

- 2000.08.30	IShadowMap-1.0 Release
