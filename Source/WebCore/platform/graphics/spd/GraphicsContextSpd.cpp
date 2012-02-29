#include "config.h"
#include "GraphicsContext.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace WebCore {

void GraphicsContext::platformInit(void* platformContext)
{
}

void GraphicsContext::platformDestroy()
{
    delete m_data;
}

AffineTransform GraphicsContext::getCTM() const
{
    if (paintingDisabled())
        return AffineTransform();

    return AffineTransform(0, 0, 0, 0, 0, 0);
}

PlatformGraphicsContext* GraphicsContext::platformContext() const
{
    return NULL;
}

void GraphicsContext::savePlatformState()
{
    return;
}

void GraphicsContext::restorePlatformState()
{
    return;
}

// Draws a filled rectangle with a stroked border.
void GraphicsContext::drawRect(const IntRect& rect)
{
    return;
}

// This is only used to draw borders, so we should not draw shadows.
void GraphicsContext::drawLine(const IntPoint& point1, const IntPoint& point2)
{
    return;
}

// This method is only used to draw the little circles used in lists.
void GraphicsContext::drawEllipse(const IntRect& rect)
{
    return;
}

void GraphicsContext::strokeArc(const IntRect& rect, int startAngle, int angleSpan)
{
    return;
}

void GraphicsContext::drawConvexPolygon(size_t npoints, const FloatPoint* points, bool shouldAntialias)
{
    return;
}

void GraphicsContext::clipConvexPolygon(size_t numPoints, const FloatPoint* points, bool antialiased)
{
    return;
}

void GraphicsContext::fillPath(const Path& path)
{
    return;
}

void GraphicsContext::strokePath(const Path& path)
{
    return;
}

void GraphicsContext::fillRect(const FloatRect& rect)
{
    return;
}

void GraphicsContext::fillRect(const FloatRect& rect, const Color& color, ColorSpace)
{
    return;
}

void GraphicsContext::clip(const FloatRect& rect)
{
    return;
}

void GraphicsContext::clipPath(const Path& path, WindRule clipRule)
{
    return;
}
/*
IntRect GraphicsContext::clipBounds() const
{
    return enclosingIntRect(FloatRect(0, 0, 0, 0));
}
*/
void GraphicsContext::drawFocusRing(const Path& path, int width, int /* offset */, const Color& color)
{
    return;
}

void GraphicsContext::drawFocusRing(const Vector<IntRect>& rects, int width, int /* offset */, const Color& color)
{
    return;
}

void GraphicsContext::drawLineForText(const FloatPoint& origin, float width, bool printing)
{
    return;
}

void GraphicsContext::drawLineForTextChecking(const FloatPoint& origin, float width, TextCheckingLineStyle style)
{
    return;
}

FloatRect GraphicsContext::roundToDevicePixels(const FloatRect& frect, RoundingMode)
{
    return FloatRect(0, 0, 0, 0);
}

void GraphicsContext::translate(float x, float y)
{
    return;
}

void GraphicsContext::setPlatformFillColor(const Color& col, ColorSpace colorSpace)
{
    // Cairo contexts can't hold separate fill and stroke colors
    // so we set them just before we actually fill or stroke
}

void GraphicsContext::setPlatformStrokeColor(const Color& col, ColorSpace colorSpace)
{
    // Cairo contexts can't hold separate fill and stroke colors
    // so we set them just before we actually fill or stroke
}

void GraphicsContext::setPlatformStrokeThickness(float strokeThickness)
{
    return;
}
/*
void GraphicsContext::setPlatformStrokeStyle(StrokeStyle strokeStyle)
{
    return;
}
*/
void GraphicsContext::setURLForRect(const KURL& link, const IntRect& destRect)
{
    return;
}

void GraphicsContext::concatCTM(const AffineTransform& transform)
{
    return;
}

void GraphicsContext::setCTM(const AffineTransform& transform)
{
    return;
}

void GraphicsContext::addInnerRoundedRectClip(const IntRect& rect, int thickness)
{
    return;
}

void GraphicsContext::setPlatformShadow(FloatSize const& size, float blur, Color const& color, ColorSpace)
{
    return;
}

void GraphicsContext::clearPlatformShadow()
{
    return;
}

void GraphicsContext::beginPlatformTransparencyLayer(float opacity)
{
    return;
}

void GraphicsContext::endPlatformTransparencyLayer()
{
    return;
}

bool GraphicsContext::supportsTransparencyLayers()
{
    return false;
}

void GraphicsContext::clearRect(const FloatRect& rect)
{
    return;
}

void GraphicsContext::strokeRect(const FloatRect& rect, float width)
{
    return;
}

void GraphicsContext::setLineCap(LineCap lineCap)
{
    return;
}

void GraphicsContext::setLineDash(const DashArray& dashes, float dashOffset)
{
    return;
}

void GraphicsContext::setLineJoin(LineJoin lineJoin)
{
    return;
}

void GraphicsContext::setMiterLimit(float miter)
{
    return;
}

void GraphicsContext::setAlpha(float alpha)
{
    return;
}

void GraphicsContext::setPlatformCompositeOperation(CompositeOperator op)
{
    return;
}

void GraphicsContext::clip(const Path& path)
{
    return;
}

void GraphicsContext::canvasClip(const Path& path)
{
    clip(path);
}

void GraphicsContext::clipOut(const Path& path)
{
    return;
}

void GraphicsContext::rotate(float radians)
{
    return;
}

void GraphicsContext::scale(const FloatSize& size)
{
    return;
}

void GraphicsContext::clipOut(const IntRect& r)
{
    return;
}

void GraphicsContext::fillRoundedRect(const IntRect& r, const IntSize& topLeft, const IntSize& topRight, const IntSize& bottomLeft, const IntSize& bottomRight, const Color& color, ColorSpace colorSpace)
{
    return;
}

void GraphicsContext::setPlatformShouldAntialias(bool enable)
{
    return;
}

void GraphicsContext::setImageInterpolationQuality(InterpolationQuality quality)
{
    return;
}

InterpolationQuality GraphicsContext::imageInterpolationQuality() const
{
    return InterpolationQuality();
}

#if ENABLE(3D_RENDERING) && USE(TEXTURE_MAPPER)
TransformationMatrix GraphicsContext::get3DTransform() const
{
    return;
}

void GraphicsContext::concat3DTransform(const TransformationMatrix& transform)
{
    return;
}

void GraphicsContext::set3DTransform(const TransformationMatrix& transform)
{
    return;
}
#endif

} // namespace WebCore
