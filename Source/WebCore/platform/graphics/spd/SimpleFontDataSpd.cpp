#include "config.h"
#include "SimpleFontData.h"

#include "FloatRect.h"
#include "Font.h"
#include "FontCache.h"
#include "FontDescription.h"
#include <wtf/MathExtras.h>

namespace WebCore {


void SimpleFontData::platformInit()
{
}

void SimpleFontData::platformDestroy()
{
}

PassOwnPtr<SimpleFontData> SimpleFontData::createScaledFontData(const FontDescription& fontDescription, float scaleFactor) const
{
}

SimpleFontData* SimpleFontData::smallCapsFontData(const FontDescription& fontDescription) const
{
}

SimpleFontData* SimpleFontData::emphasisMarkFontData(const FontDescription& fontDescription) const
{
}

bool SimpleFontData::containsCharacters(const UChar* characters, int length) const
{
}

void SimpleFontData::determinePitch()
{
}

FloatRect SimpleFontData::platformBoundsForGlyph(Glyph) const
{
}
    
float SimpleFontData::platformWidthForGlyph(Glyph glyph) const
{
}


void SimpleFontData::platformCharWidthInit()
{
}

} // namespace WebCore
