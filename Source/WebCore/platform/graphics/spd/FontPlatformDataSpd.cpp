#include "config.h"
#include "FontPlatformData.h"

#include "Font.h"
#include "FontCache.h"
#include "FontData.h"
#include "PlatformString.h"
#include "SimpleFontData.h"
#include "UnicodeRange.h"
#include "wtf/OwnPtr.h"
#include <wtf/StdLibExtras.h>
#include <wtf/text/StringHash.h>


namespace WebCore {

FontPlatformData::FontPlatformData(const FontDescription& fontDescription, const AtomicString& desiredFamily)
{
}

FontPlatformData::FontPlatformData(const FontPlatformData& o)
{
}

FontPlatformData::~FontPlatformData()
{
}

bool FontPlatformData::platformIsEqual(const FontPlatformData&) const
{
}

void FontPlatformData::platformDataInit(const FontPlatformData&)
{
}

const FontPlatformData& FontPlatformData::platformDataAssign(const FontPlatformData&)
{
}

}
