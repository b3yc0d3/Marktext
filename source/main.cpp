/*
 * @file main.cpp
 * @author b3yc0d3
 * @brief Main file of Maketext
 * @date Sun May 15 2022
 *
 * @copyright See LICENSE file in the source tree.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#include "../includes/lexer.h"
#include "../includes/txtutil.h"
#include "../includes/version.h"

#define DEBUG false

/**
 * @brief Converts Token Type to String
 *
 * @param tType
 * @return const std::string&
 */
const std::string tType2Str(const TokenType &tType)
{
    std::string retStr;

    switch (tType)
    {
    case TokenType::Apostrophe:
    {
        return "Apostrophe";
    }
    break;

    case TokenType::CRLF:
    {
        return "CRLF";
    }
    break;

    case TokenType::DollarSign:
    {
        return "DollarSign";
    }
    break;

    case TokenType::FullStop:
    {
        return "FullStop";
    }
    break;

    case TokenType::LeftCurlyBracket:
    {
        return "LeftCurlyBracket";
    }
    break;

    case TokenType::Number:
    {
        return "Number";
    }
    break;

    case TokenType::QuotationMark:
    {
        return "QuotationMark";
    }
    break;

    case TokenType::ReverseSolidus:
    {
        return "ReverseSolidus";
    }
    break;

    case TokenType::RightCurlyBracket:
    {
        return "RightCurlyBracket";
    }
    break;

    case TokenType::Text:
    {
        return "Text";
    }
    break;

    case TokenType::Tilde:
    {
        return "Tilde";
    }
    break;

    case TokenType::Whitespace:
    {
        return "Whitespace";
    }
    break;

    default:
    {
        return "Unkown";
    }
    break;
    }
}

int main()
{
    // TODO: Command line Arguments
    if (DEBUG)
    {
        std::cout << "Marktext v"
                  << VERSION_MAJOR << "."
                  << VERSION_MINOR << "."
                  << VERSION_PATCH << "\n";
    }

    std::vector<Token> tokens;

    std::fstream in("./data/example.mt");
    std::string fContents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    {
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();
        tokens = lexer->run(fContents);
    }

    // just for testing
    for (Token &i : tokens)
    {
        std::cout << "D] " << tType2Str(i.type) << " :: " << i.value << "\n";
    }

    return 0;
}