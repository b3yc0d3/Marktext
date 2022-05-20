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

#include "../includes/lexer.h"
#include "../includes/txtutil.h"

/**
 * @brief Converts Token Type to String
 *
 * @param tType
 * @return const std::string&
 */
const std::string &tType2Str(const TokenType &tType)
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
}

int main()
{
    std::vector<Token> tokens;
    std::string text =
        ".ll 72"
        ".ti"
        "This is a Title"
        ""
        ".ce 2 Text center 1 text Center 2";

    /*{
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();
        tokens = lexer->run(text);
    }*/

    std::cout << "D";
    Lexer *lexer = new Lexer();
    tokens = lexer->run(text);

    delete lexer;

    for (Token &i : tokens)
    {
        std::cout << "D] " << "S" << " :: " << i.value  << "\n";
    }

    return 0;
}