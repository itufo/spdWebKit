#include "config.h"
#include "Language.h"

#include "PlatformString.h"
#include <wtf/Vector.h>
#include <locale.h>

namespace WebCore {

static String platformLanguage()
{
    char* localeDefault = setlocale(LC_CTYPE, 0);

    if (!localeDefault)
        return String("c");

    return String(localeDefault).replace('_', '-');
}

Vector<String> platformUserPreferredLanguages()
{
    Vector<String> userPreferredLanguages;
    userPreferredLanguages.append(platformLanguage());
    return userPreferredLanguages;
}

}
