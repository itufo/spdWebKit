#ifndef FontCustomPlatformData_h
#define FontCustomPlatformData_h

#include "FontOrientation.h"
#include "FontRenderingMode.h"
#include "FontWidthVariant.h"
#include "TextOrientation.h"
#include <wtf/Forward.h>
#include <wtf/Noncopyable.h>


namespace WebCore {


struct FontCustomPlatformData {
public:
    //FontCustomPlatformData(FT_Face, SharedBuffer*);
    //~FontCustomPlatformData();
    //FontPlatformData fontPlatformData(int size, bool bold, bool italic, FontOrientation = Horizontal, TextOrientation = TextOrientationVerticalRight, FontWidthVariant = RegularWidth, FontRenderingMode = NormalRenderingMode);
    static bool supportsFormat(const String&);

private:
};

}

#endif
