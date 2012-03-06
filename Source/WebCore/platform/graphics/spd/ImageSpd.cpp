#include "config.h"
#include "Image.h"
#include "ImageDecoder.h"

namespace WebCore {

void Image::drawPattern(GraphicsContext* context, const FloatRect& tileRect, const AffineTransform& patternTransform,
                        const FloatPoint& phase, ColorSpace colorSpace, CompositeOperator op, const FloatRect& destRect)
{

}

NativeImagePtr ImageFrame::asNewNativeImage() const
{
}

}//namespace WebCore
