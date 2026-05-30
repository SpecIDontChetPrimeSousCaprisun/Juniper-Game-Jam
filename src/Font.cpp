#include "Font.h"
#include "FileLoader.h"

Font::Font(const std::string& path, float pixelHeight) {
  ttfBuffer = FileLoader::loadFontFile(path);

  const int BITMAP_W = 512;
  const int BITMAP_H = 512;

  unsigned char* bitmap = new unsigned char[BITMAP_W * BITMAP_H];

  stbtt_BakeFontBitmap(
      ttfBuffer.data(),
      0,
      pixelHeight,
      bitmap,
      BITMAP_W,
      BITMAP_H,
      32,
      96,
      cdata
  );

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_ALPHA,
      BITMAP_W,
      BITMAP_H,
      0,
      GL_ALPHA,
      GL_UNSIGNED_BYTE,
      bitmap
  );

  delete[] bitmap;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

  if (!stbtt_InitFont(
        &fontInfo,
        ttfBuffer.data(),
        stbtt_GetFontOffsetForIndex(
            ttfBuffer.data(),
            0
        )))
  {
      std::cout << "Failed to init font\n";
  }

  stbtt_GetFontVMetrics(
    &fontInfo,
    &ascent,
    &descent,
    &lineGap
  );

  scale = stbtt_ScaleForPixelHeight(&fontInfo, pixelHeight); 
  height = (ascent - descent) * scale;

  glBindTexture(GL_TEXTURE_2D, 0);
}
