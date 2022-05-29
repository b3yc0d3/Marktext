#ifndef MARKTEXT_TOKEN_H
#define MARKTEXT_TOKEN_H

#include <string>

/**
 * @brief Token Types
 * 
 */
enum TokenType
{
    Apostrophe,         // '
    Asterisk,           // *
    CRLF,               // \r \n or \r\n
    DollarSign,         // $
    FullStop,           // .
    LeftCurlyBracket,   // {    [not used yet]
    Number,             // 0-9
    QuotationMark,      // "
    ReverseSolidus,     // "\"
    Solidus,            // /
    RightCurlyBracket,  // }    [not used yet]
    Text,               // Everything thats not listed here
    Tilde,              // ~
    Whitespace,         //
};

/**
 * @brief Token Struct
 * 
 */
struct Token
{
    TokenType type;
    std::string value;
};


#endif