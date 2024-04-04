#include "../../include/Static/Functions.h"

std::string Functions::convertToUpper(std::string& toConvert)
{
    std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::toupper);
    return toConvert;
}

std::string Functions::convertToLower(std::string toConvert)
{
    std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::tolower);
    return toConvert;
}