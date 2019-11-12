#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/Geometry.h>

namespace ultralight {

// 32-bit RGBA, Not Premultiplied
typedef uint32_t Color;

#define UltralightRGBA(r, g, b, a) \
    static_cast<uint32_t>( \
        (static_cast<uint8_t>(r) << 24) | \
        (static_cast<uint8_t>(g) << 16) | \
        (static_cast<uint8_t>(b) << 8) | \
        (static_cast<uint8_t>(a) << 0))

#define UltralightRGB(r, g, b) \
    static_cast<uint32_t>( \
        (static_cast<uint8_t>(r) << 24) | \
        (static_cast<uint8_t>(g) << 16) | \
        (static_cast<uint8_t>(b) << 8) | \
        (255 << 0))

#define UltralightColorGetR(color)      (((color) >> 24) & 0xFF)
#define UltralightColorGetG(color)      (((color) >> 16) & 0xFF)
#define UltralightColorGetB(color)      (((color) >>  8) & 0xFF)
#define UltralightColorGetA(color)      (((color) >>  0) & 0xFF)
#define UltralightColorGetFloat4(color) { UltralightColorGetR(color) / 255.0f, \
                                          UltralightColorGetG(color) / 255.0f, \
                                          UltralightColorGetB(color) / 255.0f, \
                                          UltralightColorGetA(color) / 255.0f }
#define UltralightColorGetRaw(color) { (float)UltralightColorGetR(color), \
                                       (float)UltralightColorGetG(color), \
                                       (float)UltralightColorGetB(color), \
                                       (float)UltralightColorGetA(color) }

#define UltralightColorTRANSPARENT  0x00000000
#define UltralightColorBLACK        0x000000FF
#define UltralightColorWHITE        0xFFFFFFFF
#define UltralightColorRED          0xFF0000FF
#define UltralightColorGREEN        0x00FF00FF
#define UltralightColorBLUE         0x0000FFFF
#define UltralightColorYELLOW       0xFFFF00FF

struct UExport GradientStop {
  float stop;
  float color[4];
};

struct UExport Gradient {
  uint32_t num_stops;
  GradientStop stops[12];
  Point p0;
  Point p1;
  float r0;
  float r1;
  bool is_radial;
};

struct Pattern;

enum FillRule {
  kFillRule_NonZero,
  kFillRule_EvenOdd,
};

enum CompositeOp {
  kCompositeOp_Clear,
  kCompositeOp_Copy,
  kCompositeOp_SourceOver,
  kCompositeOp_SourceIn,
  kCompositeOp_SourceOut,
  kCompositeOp_SourceAtop,
  kCompositeOp_DestinationOver,
  kCompositeOp_DestinationIn,
  kCompositeOp_DestinationOut,
  kCompositeOp_DestinationAtop,
  kCompositeOp_XOR,
  kCompositeOp_PlusDarker,
  kCompositeOp_PlusLighter,
  kCompositeOp_Difference
};

enum BlendMode {
  kBlendMode_Normal = 1, // Start with 1 to match SVG's blendmode enumeration.
  kBlendMode_Multiply,
  kBlendMode_Screen,
  kBlendMode_Darken,
  kBlendMode_Lighten,
  kBlendMode_Overlay,
  kBlendMode_ColorDodge,
  kBlendMode_ColorBurn,
  kBlendMode_HardLight,
  kBlendMode_SoftLight,
  kBlendMode_Difference,
  kBlendMode_Exclusion,
  kBlendMode_Hue,
  kBlendMode_Saturation,
  kBlendMode_Color,
  kBlendMode_Luminosity,
  kBlendMode_PlusDarker,
  kBlendMode_PlusLighter
};

struct UExport Paint {
  Color color;
};

enum BorderStyle {
  kBorderStyle_None,
  kBorderStyle_Dotted,
  kBorderStyle_Dashed,
  kBorderStyle_Solid,
  kBorderStyle_Double,
  kBorderStyle_Groove,
  kBorderStyle_Ridge,
  kBorderStyle_Inset,
  kBorderStyle_Outset
};

struct UExport BorderPaint {
  Color color;
  BorderStyle style;
};

}  // namespace ultralight
