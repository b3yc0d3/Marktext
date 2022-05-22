#ifndef MARKTEXT_TXTUTIL_H
#define MARKTEXT_TXTUTIL_H

#include <string>

namespace txtutil
{
    /**
     * @brief Checks if String only contains Numbers
     *
     * @param iText Text that should be checked
     * @return true
     * @return false
     *
     * @see https://stackoverflow.com/a/4654718
     */
    bool isNumber(const std::string &iText);

    /**
     * @brief Converts Token Type to String
     * 
     * @param tType 
     * @return const std::string& 
     */
    /*const std::string &tType2Str(const TokenType &tType)
    {
        std::string retStr;

        switch (tType)
        {
        case TokenType::Apostrophe:
        {
            retStr = "Apostrophe";
        }
        break;

        case TokenType::CRLF:
        {
            retStr = "CRLF";
        }
        break;

        case TokenType::DollarSign:
        {
            retStr = "DollarSign";
        }
        break;

        case TokenType::FullStop:
        {
            retStr = "FullStop";
        }
        break;

        case TokenType::LeftCurlyBracket:
        {
            retStr = "LeftCurlyBracket";
        }
        break;

        case TokenType::Number:
        {
            retStr = "Number";
        }
        break;

        case TokenType::QuotationMark:
        {
            retStr = "QuotationMark";
        }
        break;

        case TokenType::ReverseSolidus:
        {
            retStr = "ReverseSolidus";
        }
        break;

        case TokenType::RightCurlyBracket:
        {
            retStr = "RightCurlyBracket";
        }
        break;

        case TokenType::Text:
        {
            retStr = "Text";
        }
        break;

        case TokenType::Tilde:
        {
            retStr = "Tilde";
        }
        break;

        case TokenType::Whitespace:
        {
            retStr = "Whitespace";
        }
        break;

        default:
            {
                retStr = "Unkown";
            }
            break;
        }

        return retStr;
    }*/

    /**
     * @brief Converts String to Integer
     *
     * @param str
     * @param h
     * @return constexpr unsigned int
     */
    /*constexpr unsigned int str2int(const char *str, int h = 0)
    {
        return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
    }*/
}

#endif