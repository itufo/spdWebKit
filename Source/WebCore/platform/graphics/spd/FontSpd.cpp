#include "config.h"
#include "Font.h"

#include "AffineTransform.h"
#include "FloatRect.h"
#include "FontCache.h"
#include "FontData.h"
#include "FontFallbackList.h"
#include "GlyphBuffer.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "NotImplemented.h"
#include "TextRun.h"
#include "WidthIterator.h"
#include <wtf/MathExtras.h>
#include <wtf/OwnPtr.h>
#include <wtf/unicode/Unicode.h>


using namespace WTF::Unicode;

namespace WebCore {

void Font::drawGlyphs(GraphicsContext* graphicsContext, const SimpleFontData* fontData, const GlyphBuffer& glyphBuffer,
                      int from, int numGlyphs, const FloatPoint& point) const
{

}

void Font::drawComplexText(GraphicsContext* context, const TextRun& run, const FloatPoint& point,
                           int from, int to) const
{

}

void Font::drawEmphasisMarksForComplexText(GraphicsContext* /* context */, const TextRun& /* run */, const AtomicString& /* mark */, const FloatPoint& /* point */, int /* from */, int /* to */) const
{

}

float Font::floatWidthForComplexText(const TextRun& run, HashSet<const SimpleFontData*>* fallbackFonts, GlyphOverflow* glyphOverflow) const
{

}

int Font::offsetForPositionForComplexText(const TextRun& run, float xFloat, bool includePartialGlyphs) const
{

}

FloatRect Font::selectionRectForComplexText(const TextRun& run, const FloatPoint& pt,
                                     int h, int from, int to) const
{

}

bool Font::canReturnFallbackFontsForComplexText()
{
    return false;
}

bool Font::canExpandAroundIdeographsInComplexText()
{
    return false;
}

} // namespace WebCore
