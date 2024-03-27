#include "../../include/Static/Functions.h"

std::string Functions::convertToUpper(std::string& toConvert)
{
    std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::toupper);
    return toConvert;
}