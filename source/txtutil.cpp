#include <algorithm>
#include "../includes/txtutil.h"

namespace txtutil
{
    bool isNumber(const std::string &iText)
    {
        return !iText.empty() && std::find_if(iText.begin(), iText.end(), [](unsigned char c)
                                              { return !std::isdigit(c); }) == iText.end();
    }
}