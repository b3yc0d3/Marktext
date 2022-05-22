#include <iostream>
#include "../includes/lexer.h"
#include "../includes/txtutil.h"

constexpr unsigned int str2int(const char *str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Lexer::Lexer()
{
}

void Lexer::add(TokenType type, const std::string &value)
{
    Token tmpToken;
    tmpToken.type = type;
    tmpToken.value = value;

    this->tokens.push_back(tmpToken);
}

void Lexer::dumpTmpStr()
{
    if (this->tmpStr != "")
    {
        // check if Temporeral String is only Numbers
        if (txtutil::isNumber(this->tmpStr))
        {
            this->add(TokenType::Number, this->tmpStr);
            // IMPORTANT! clear Temporeral String
            this->tmpStr = "";
        }
        else
        {
            this->add(TokenType::Text, this->tmpStr);
            // IMPORTANT! clear Temporeral String
            this->tmpStr = "";
        }
    }
}

std::vector<Token> Lexer::run(const std::string &rText)
{
    for (const char c : rText)
    {
        switch (str2int(&c))
        {
        case str2int("'"): // Apostrophe
        {
            this->dumpTmpStr();
            this->add(TokenType::Apostrophe, &c);
        }
        break;

        case str2int("\n"):
        case str2int("\r"): // CRLF
        case str2int("\r\n"):
        {
            this->dumpTmpStr();
            this->add(TokenType::CRLF, "\n");
        }
        break;

        case str2int("$"): // DollarSign
        {
            this->dumpTmpStr();
            this->add(TokenType::DollarSign, &c);
        }
        break;

        case str2int("."): // FullStop
        {
            this->dumpTmpStr();
            this->add(TokenType::FullStop, &c);
        }
        break;

        case str2int("{"): // LeftCurlyBracket
        {
            this->dumpTmpStr();
            this->add(TokenType::LeftCurlyBracket, &c);
        }
        break;

        case str2int("\""): // QuotationMark
        {
            this->dumpTmpStr();
            this->add(TokenType::QuotationMark, &c);
        }
        break;

        case str2int("\\"): // ReverseSolidus
        {
            this->dumpTmpStr();
            this->add(TokenType::ReverseSolidus, &c);
        }
        break;

        case str2int("}"): // RightCurlyBracket
        {
            this->dumpTmpStr();
            this->add(TokenType::RightCurlyBracket, &c);
        }
        break;

        case str2int("~"): // Tilde
        {
            this->dumpTmpStr();
            this->add(TokenType::Tilde, &c);
        }
        break;

        case str2int(" "): // Whitespace
        {
            this->dumpTmpStr();
            this->add(TokenType::Whitespace, &c);
        }
        break;

        default:
        {
            this->tmpStr.append(&c);
        }
        break;
        }
    }

    // just in case if it is not empty
    this->dumpTmpStr();

    return this->tokens;
}

Lexer::~Lexer()
{
}