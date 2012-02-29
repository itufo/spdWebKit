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

static PassRefPtr<SharedBuffer> loadResourceSharedBufferFallback()
{
    return SharedBuffer::create(); // TODO: fallback image?
}

static PassRefPtr<SharedBuffer> loadResourceSharedBuffer(const char* name)
{
    RefPtr<SharedBuffer> buffer = SharedBuffer::createWithContentsOfFile(makeString(DATA_DIR "/webkit-1.0/images/", name, ".png"));    
    if (buffer)
        return buffer.release();
    return loadResourceSharedBufferFallback();
}

PassRefPtr<Image> Image::loadPlatformResource(const char* name)
{
    RefPtr<BitmapImage> img = BitmapImage::create();
    RefPtr<SharedBuffer> buffer = loadResourceSharedBuffer(name);
    img->setData(buffer.release(), true);
    return img.release();
}

}
