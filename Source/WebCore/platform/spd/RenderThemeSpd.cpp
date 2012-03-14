#include "config.h"
#include "RenderThemeSpd.h"

#include "CSSValueKeywords.h"
#include "FileSystem.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "HTMLInputElement.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PaintInfo.h"
//#include "PlatformContextCairo.h"
#include "RenderBox.h"
#include "RenderObject.h"
#include "RenderProgress.h"
#include "RenderSlider.h"
#include "UserAgentStyleSheets.h"

#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>


namespace WebCore {
RenderThemeSpd::RenderThemeSpd()
{
}

PassRefPtr<RenderTheme> RenderTheme::themeForPage(Page* page)
{
    return adoptRef(new RenderThemeSpd());
}

void RenderThemeSpd::systemFont(int propId, FontDescription& fontDescription) const
{

}

}//namespace WebCore
