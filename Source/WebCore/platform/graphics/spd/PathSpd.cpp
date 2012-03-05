#include "config.h"
#include "Path.h"

#include "AffineTransform.h"
#include "FloatRect.h"
#include "GraphicsContext.h"
#include "PlatformString.h"
#include "StrokeStyleApplier.h"
#include <math.h>
#include <wtf/MathExtras.h>

namespace WebCore {

Path::Path()
{

}

Path::~Path()
{
    delete m_path;
}

Path::Path(const Path& other)
{

}

Path& Path::operator=(const Path& other)
{

}

void Path::clear()
{

}

bool Path::isEmpty() const
{

}

bool Path::hasCurrentPoint() const
{

}

FloatPoint Path::currentPoint() const 
{

}

void Path::translate(const FloatSize& p)
{

}

void Path::moveTo(const FloatPoint& p)
{

}

void Path::addLineTo(const FloatPoint& p)
{

}

void Path::addRect(const FloatRect& rect)
{

}

void Path::addQuadCurveTo(const FloatPoint& controlPoint, const FloatPoint& point)
{

}

void Path::addBezierCurveTo(const FloatPoint& controlPoint1, const FloatPoint& controlPoint2, const FloatPoint& controlPoint3)
{

}

void Path::addArc(const FloatPoint& p, float r, float startAngle, float endAngle, bool anticlockwise)
{

}

void Path::addArcTo(const FloatPoint& p1, const FloatPoint& p2, float radius)
{

}

void Path::addEllipse(const FloatRect& rect)
{

}

void Path::closeSubpath()
{

}

FloatRect Path::boundingRect() const
{

}

FloatRect Path::strokeBoundingRect(StrokeStyleApplier* applier) const
{

}

bool Path::contains(const FloatPoint& point, WindRule rule) const
{

}

bool Path::strokeContains(StrokeStyleApplier* applier, const FloatPoint& point) const
{

}

void Path::apply(void* info, PathApplierFunction function) const
{

}

void Path::transform(const AffineTransform& trans)
{

}

} // namespace WebCore
