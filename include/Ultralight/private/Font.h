#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/RefPtr.h>
#include <Ultralight/Geometry.h>

namespace ultralight {

class Bitmap;
class Path;
class TextureInfo;

class UExport Font : public RefCounted {
public:
  virtual bool is_distance_field() const = 0;

  virtual float font_size() const = 0;

  virtual bool HasGlyph(uint32_t index) const = 0;

  virtual void StoreGlyph(uint32_t index, int advance, int width, int height, int bearing, RefPtr<Bitmap> bitmap, const Point& offset) = 0;

  virtual void StoreGlyph(uint32_t index, int advance, int width, int height, int bearing, RefPtr<Path> path) = 0;

  virtual int GetGlyphAdvance(uint32_t index) = 0;

  virtual int GetGlyphWidth(uint32_t index) = 0;

  virtual int GetGlyphHeight(uint32_t index) = 0;

  virtual int GetGlyphBearing(uint32_t index) = 0;

  virtual TextureInfo GetGlyphTexture(uint32_t index) = 0;

  virtual Point GetGlyphOffset(uint32_t index) = 0;

protected:
  static Ref<Font> Create(bool is_distance_field, float font_size);

  Font();
  virtual ~Font();
  Font(const Font&);
  void operator=(const Font&);

  friend class FontCache;
};

} // namespace ultralight
