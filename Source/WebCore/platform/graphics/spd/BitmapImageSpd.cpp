#include "config.h"
#include "Image.h"

#include "BitmapImage.h"
#include "SharedBuffer.h"

#include <wtf/text/StringConcatenate.h>

namespace WebCore {

void BitmapImage::initPlatformData()
{
}

void BitmapImage::invalidatePlatformData()
{
}

void BitmapImage::checkForSolidColor()
{
}

void BitmapImage::draw(GraphicsContext*, const FloatRect& dstRect, const FloatRect& srcRect, ColorSpace styleColorSpace, CompositeOperator)
{
}

}
