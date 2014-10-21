# Things to do
* ~~Make a Sphere shape~~
* ~~make a 2D Ring object~~
* ~~figure out how to do textures~~
* Make a Planet object that can be used for all of the planets. It should hold the following:
	* ~~Texture~~
	* ~~Swisseph const relating to the planet it represents~~
	* ~~orbital period in days or seconds regarding~~
	* ~~period for rotating around the axis in days or seconds~~
	* ~~specifying which local axes the planet should spin on~~
	* ~~Distance from sun~~
* ~~Instead, make the Planet objects hold the mat4s to handle **size**, **position**, and **texture/color**. That way, we only need ONE sphere.~~
* ~~Add a background~~
* Figure out drag and drop
* ~~make sure to either limit year input or find alternate ways for representing datetime~~
* ~~Make rings actually transparent~~
* ~~Smooth pan the camera~~

# Compilation notes for freetype and ftgl
* had to use msys in mingw
* had to get g++ for mingw
* --with-ft-prefix=/x/freetype
* --with-gl-inc=/c/MinGW/include
* --with-gl-lib=/c/MinGW/lib
* ./configure --prefix=/ --host=i686-mingw32 --with-ft-prefix=/x/freetype --with-gl-inc=/c/MinGW/include --with-gl-lib=/c/MinGW/lib
<!--* DESTDIR=/blahblah make install  for freetype-->
* or...
mingw32-g++ FTBuffer.cpp FTCharmap.cpp FTCharmap.h FTCharToGlyphIndexMap.h FTContour.cpp FTContour.h FTFace.cpp FTFace.h FTGlyphContainer.cpp FTGlyphContainer.h FTInternals.h FTLibrary.cpp FTLibrary.h FTList.h FTPoint.cpp FTSize.cpp FTSize.h FTVector.h FTVectoriser.cpp FTVectoriser.h FTUnicode.h config.h FTGlyph/FTGlyph.cpp FTGlyph/FTGlyphImpl.h FTGlyph/FTGlyphGlue.cpp FTGlyph/FTBitmapGlyph.cpp FTGlyph/FTBitmapGlyphImpl.h FTGlyph/FTBufferGlyph.cpp FTGlyph/FTBufferGlyphImpl.h FTGlyph/FTExtrudeGlyph.cpp FTGlyph/FTExtrudeGlyphImpl.h FTGlyph/FTOutlineGlyph.cpp FTGlyph/FTOutlineGlyphImpl.h FTGlyph/FTPixmapGlyph.cpp FTGlyph/FTPixmapGlyphImpl.h FTGlyph/FTPolygonGlyph.cpp FTGlyph/FTPolygonGlyphImpl.h FTGlyph/FTTextureGlyph.cpp FTGlyph/FTTextureGlyphImpl.h FTFont/FTFont.cpp FTFont/FTFontImpl.h FTFont/FTFontGlue.cpp FTFont/FTBitmapFont.cpp FTFont/FTBitmapFontImpl.h FTFont/FTBufferFont.cpp FTFont/FTBufferFontImpl.h FTFont/FTExtrudeFont.cpp FTFont/FTExtrudeFontImpl.h FTFont/FTOutlineFont.cpp FTFont/FTOutlineFontImpl.h FTFont/FTPixmapFont.cpp FTFont/FTPixmapFontImpl.h FTFont/FTPolygonFont.cpp FTFont/FTPolygonFontImpl.h FTFont/FTTextureFont.cpp FTFont/FTTextureFontImpl.h FTLayout/FTLayout.cpp FTLayout/FTLayoutImpl.h FTLayout/FTLayoutGlue.cpp FTLayout/FTSimpleLayout.cpp FTLayout/FTSimpleLayoutImpl.h FTGL/ftgl.h -Ix:/ftgl-2.1.3~rc5/src/FTGL/ -Ix:/ftgl-2.1.3~rc5/src  -lopengl32 -lglu32 -Ix:/freetype/include -Ix:/freetype/include/freetype2 -Lx:/freetype/lib -lfreetype -DFTGL_LIBRARY -DFTGL_DLL_EXPORTS -shared -Wl,--out-implib,lib/libftgl.a -o lib/ftgl.dll
---
sed 's/core_/compat_/g' -i *.cpp *.h Makefile
