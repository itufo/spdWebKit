#include "config.h"
#include "FontCache.h"

#include "Font.h"
#include "FontData.h"
#include "SimpleFontData.h"
#include "UnicodeRange.h"
#include "wtf/OwnPtr.h"


namespace WebCore {

/*
#if defined(IMLANG_FONT_LINK) && (IMLANG_FONT_LINK == 2)
IMLangFontLink2* FontCache::getFontLinkInterface()
#else
IMLangFontLink* FontCache::getFontLinkInterface()
#endif
{
}
*/

void FontCache::platformInit()
{
}

const SimpleFontData* FontCache::getFontDataForCharacters(const Font& font, const UChar* characters, int length)
{
}

SimpleFontData* FontCache::getSimilarFontPlatformData(const Font& font)
{
    return 0;
}

SimpleFontData* FontCache::getLastResortFallbackFont(const FontDescription& fontDesc, ShouldRetain shouldRetain)
{
}

void FontCache::getTraitsInFamily(const AtomicString& familyName, Vector<unsigned>& traitsMasks)
{
}

FontPlatformData* FontCache::createFontPlatformData(const FontDescription&, const AtomicString& family)
{

}

} // namespace WebCore
