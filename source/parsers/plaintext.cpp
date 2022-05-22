#include <iostream>
#include "../../includes/parsers/plaintext.h"

// copied in here because i'm so dumb
constexpr unsigned int str2int(const char *str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

PlaintextParser::PlaintextParser()
{
    this->storage = new Storage();
    this->isBoL = true;
}

void PlaintextParser::next()
{
    // check for Line Begin
    if (this->cType() == TokenType::CRLF)
    {
        this->isBoL = true;
    }
    else
    {
        this->isBoL = false;
    }

    if ((this->index + 1) < this->tokens.size())
    {
        this->index++;
        this->cur_token = this->tokens[this->index];
    }
    else
    {
        Token tmp;
        tmp.value = "NULL";
        this->cur_token = tmp;
    }
}

Token PlaintextParser::preview()
{
    if ((this->index + 1) > this->tokens.size())
    {
        return this->tokens[this->index + 1];
    }
    else
    {
        Token tmp;
        tmp.value = "NULL";
        return tmp;
    }
}

std::string PlaintextParser::parse(std::vector<Token> &tokens)
{
    this->tokens = tokens;
    // Set first Token
    this->index = 0;
    this->cur_token = this->tokens[this->index];

    while (this->cur_token.value != "NULL")
    {
    
        if (this->isBoL)
        {
            std::cout << "D] pt_66 :: " << this->cValue() << "\n";
        }

        this->next();
    }

    return this->document;
}

PlaintextParser::~PlaintextParser()
{
    delete this->storage;
}