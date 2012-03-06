#include "config.h"
#include "ImageBuffer.h"
#include "ImageBufferDataSpd.h"

#include "Base64.h"
#include "BitmapImage.h"
#include "Color.h"
#include "GraphicsContext.h"
#include "ImageData.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "Pattern.h"
#include "PlatformString.h"
#include <wtf/Vector.h>

using namespace std;

namespace WebCore {

ImageBufferData::ImageBufferData(const IntSize& size)
{

}

ImageBuffer::ImageBuffer(const IntSize& size, ColorSpace, RenderingMode, DeferralMode, bool& success)
    : m_data(size)
    , m_size(size)
{
    success = false;  // Make early return mean error.
    return;
}

ImageBuffer::~ImageBuffer()
{
    return;
}

size_t ImageBuffer::dataSize() const
{
    return m_size.width() * m_size.height() * 4;
}

GraphicsContext* ImageBuffer::context() const
{
    return m_context.get();
}

PassRefPtr<Image> ImageBuffer::copyImage(BackingStoreCopy copyBehavior) const
{
    return NULL;
}

void ImageBuffer::clip(GraphicsContext* context, const FloatRect& maskRect) const
{
    return;
}

void ImageBuffer::draw(GraphicsContext* context, ColorSpace styleColorSpace, const FloatRect& destRect, const FloatRect& srcRect,
                       CompositeOperator op , bool useLowQualityScale)
{
    return;
}

void ImageBuffer::drawPattern(GraphicsContext* context, const FloatRect& srcRect, const AffineTransform& patternTransform,
                              const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator op, const FloatRect& destRect)
{
    return;
}

void ImageBuffer::platformTransformColorSpace(const Vector<int>& lookUpTable)
{
    return;
}

template <Multiply multiplied>
PassRefPtr<ByteArray> getImageData(const IntRect& rect, const ImageBufferData& data, const IntSize& size)
{
    RefPtr<ByteArray> result = ByteArray::create(rect.width() * rect.height() * 4);
    return result.release();
}

PassRefPtr<ByteArray> ImageBuffer::getUnmultipliedImageData(const IntRect& rect) const
{
    return getImageData<Unmultiplied>(rect, m_data, m_size);
}

PassRefPtr<ByteArray> ImageBuffer::getPremultipliedImageData(const IntRect& rect) const
{
    return getImageData<Premultiplied>(rect, m_data, m_size);
}

void ImageBuffer::putByteArray(Multiply multiplied, ByteArray* source, const IntSize& sourceSize, const IntRect& sourceRect, const IntPoint& destPoint)
{
    return;
}


String ImageBuffer::toDataURL(const String& mimeType, const double*) const
{
    return "data:,";
}

} // namespace WebCore
