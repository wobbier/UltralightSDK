#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/Geometry.h>
#include <Ultralight/private/Paint.h>
#include <Ultralight/private/Path.h>
#include <Ultralight/RefPtr.h>
#include <Ultralight/Bitmap.h>
#include <Ultralight/RenderTarget.h>
#include <Ultralight/private/Font.h>

namespace ultralight {

class Painter;
class Surface;
class Texture;
class Image;
class RenderTexture;

struct UExport Glyph {
  uint32_t index;
  Point origin;
};

/**
 * Canvas is used for drawing geometry to the screen.
 */
//
// Canvas will cache Surfaces as each layer is pushed/popped to avoid creating
// a billion render-textures while drawing. Each Surface will be compiled to a
// DrawList and then appended to the parent Canvas's DrawList each time the layer
// is popped (eg, applied).
//
class UExport Canvas : public RefCounted {
public:
  static Ref<Canvas> Create(int width, int height, BitmapFormat format);
  static Ref<Canvas> CreateRecorder(int width, int height, BitmapFormat format);

  virtual bool IsRecorder() const = 0;
  virtual void Replay(Canvas* canvas) const = 0;
  virtual void ClearCommands() = 0;

  virtual int width() const = 0;
  virtual int height() const = 0;
  virtual BitmapFormat format() const = 0;

  // Save and Restore Drawing State
  virtual void Save() = 0;
  virtual void Restore() = 0;

  virtual void SetCompositeOp(CompositeOp op) = 0;
  virtual CompositeOp composite_op() const = 0;

  virtual void SetBlendMode(BlendMode mode) = 0;
  virtual BlendMode blend_mode() const = 0;

  // Clip Methods
  virtual void SetClip(const Rect& rect, bool inverse) = 0;
  virtual void SetClip(const RoundedRect& rrect, bool inverse) = 0;
  virtual void SetClip(RefPtr<Path> path, FillRule rule, bool inverse) = 0;
  virtual void SetClipEmpty() = 0;
  virtual Rect GetClipBounds() const = 0;

  // Transform Methods
  virtual void Transform(const Matrix& matrix) = 0;
  virtual void SetMatrix(const Matrix& matrix) = 0;
  virtual Matrix GetMatrix() const = 0;
  virtual void SetRootMatrix(const Matrix& matrix) = 0;

  virtual void BeginTransparencyLayer(float opacity) = 0;
  virtual void EndTransparencyLayer() = 0;

  virtual void BeginMaskLayer(RefPtr<Path> path) = 0;
  virtual void EndMaskLayer() = 0;

  virtual void Clear() = 0;
  virtual void Clear(const Rect& rect) = 0;

  virtual RenderTarget render_target() const = 0;
  virtual RefPtr<RenderTexture> render_texture() const = 0;

  // Drawing
  virtual void DrawRect(const Rect& rect, const Paint& paint) = 0;
  virtual void DrawLine(const Point& p0, const Point& p1, const Paint& paint) = 0;
  virtual void DrawEllipse(const Rect& rect, const Paint& paint) = 0;
  virtual void DrawRoundedRect(const RoundedRect& rrect, const Paint& paint,
    float stroke_width, Color stroke_color) = 0;
  virtual void DrawBoxShadow(const Rect& paint_rect, const RoundedRect& rrect, const RoundedRect& clip_rrect,
    bool inset, const Point& offset, float radius, const Paint& paint) = 0;
  virtual void DrawPath(Ref<Path> path, const Paint& paint, bool should_fill, bool should_stroke,
    float stroke_width) = 0;
  virtual void DrawImage(RefPtr<Image> image, uint32_t cur_frame,
    const Rect& src, const Rect& dest, const Paint& paint) = 0;
  virtual void DrawPattern(RefPtr<Image> image, uint32_t cur_frame,
    const Rect& src, const Rect& dest, const Matrix& transform) = 0;
  virtual void DrawGlyphs(Ref<Font> font, const Paint& paint, Glyph* glyphs, size_t num_glyphs, float glyph_scale, bool fake_blur, const Point& offset) = 0;
  virtual void DrawGradient(Gradient* gradient, const Rect& dest) = 0;

  // this method forms a draw dependency between 'canvas' and this Surface's parent canvas.
  // the painter will sort canvases by draw dependencies and draw them in correct order.
  virtual void DrawCanvas(Ref<Canvas> canvas, const Rect& src_uv, const Rect& dest, const Paint& paint) = 0;
  virtual void DrawCanvasPattern(Ref<Canvas> canvas, const Rect& src_uv, const Rect& src, const Rect& dest, const Matrix& transform) = 0;

  virtual void DrawBoxDecorations(const Rect& layout_rect, const RoundedRect& outer_rrect,
    const RoundedRect& inner_rrect, BorderPaint border_top, BorderPaint border_right,
    BorderPaint border_bottom, BorderPaint border_left, Color fill_color) = 0;

protected:
  virtual void Draw() = 0;

  Canvas();
  virtual ~Canvas();
  Canvas(const Canvas&);
  void operator=(const Canvas&);

  friend class GPUContext;
};

}  // namespace ultralight
