#include <iostream>
#include "../../includes/parsers/plaintext.h"
#include "../../includes/txtutil.h"

// copied in here because i'm so dumb
constexpr unsigned int str2int(const char *str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

PlaintextParser::PlaintextParser()
{
    this->storage = new Storage();
    this->isBoL = true;

    this->storage->lineLength = 72;
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

Token PlaintextParser::peek()
{
    if ((this->index + 1) < this->tokens.size())
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

std::string PlaintextParser::cValue()
{
    if (this->cur_token.value == "NULL")
    {
        return "NULL";
    }

    return this->cur_token.value;
}

TokenType PlaintextParser::cType()
{
    if (this->cur_token.value == "NULL")
    {
        // return "NULL";
    }

    return this->cur_token.type;
}

std::string PlaintextParser::getCompleteLine()
{
    bool doIt = true;
    std::string buffer;

    while (doIt)
    {
        if (this->cType() != TokenType::CRLF && this->cValue() != "NULL")
        {
            buffer.append(this->cValue());
            this->next();
        }
        else
        {
            doIt = false;
        }
    }

    return buffer;
}

void PlaintextParser::nextLine()
{
    bool doIt = true;

    while (doIt)
    {
        if (this->cType() == TokenType::CRLF)
        {
            doIt = false;
        }
        else
        {
            this->next();
        }
    }

    this->next();
}

void PlaintextParser::skipTill(TokenType token)
{
    bool doIt = true;

    while (doIt)
    {
        if (this->cType() == token)
        {
            doIt = false;
        }
        else
        {
            this->next();
        }
    }
}

std::string PlaintextParser::getTill(TokenType token)
{
    bool doIt = true;
    std::string buffer = "";

    while (doIt)
    {
        if (this->cValue() != "NULL" && this->cType() != token)
        {
            buffer.append(this->cValue());
            this->next();
        }
        else
        {
            doIt = false;
        }
    }

    return buffer;
}

void PlaintextParser::appendTmpParagraph(const std::string &value)
{
    if (value != "")
    {
        this->tmpParagraph.append(value);
    }
    else if (value == "\n")
    {
        this->tmpParagraph.append(" ");
    }
}

void PlaintextParser::dumpTmpParagraph()
{
    unsigned int lineLengthIndented = this->storage->lineLength - this->storage->indent;
    std::vector<std::string> lines = txtutil::split_str(txtutil::word_wrap(this->tmpParagraph, lineLengthIndented), "\n");

    for (std::string &line : lines)
    {
        this->document.append(txtutil::repeat(" ", this->storage->indent) + line + "\n");
    }

    // clear 'tmpParagraph'
    this->tmpParagraph.clear();
}

/**
 * PARSER
 */

std::string PlaintextParser::parse(std::vector<Token> &tokens)
{
    this->tokens = tokens;
    // Set first Token
    this->index = 0;
    this->cur_token = this->tokens[this->index];
    unsigned int lineBreaks = 0;

    while (this->cur_token.value != "NULL")
    {

        if (this->cType() == TokenType::Solidus)
        {
            switch (this->peek().type)
            {
            case Solidus:
            {
                this->nextLine();
                this->next();
            }
            break;

            case Asterisk:
            {
                int doIt = true;
                while (doIt)
                {
                    if (this->cType() == TokenType::Asterisk && this->peek().type == TokenType::Solidus)
                    {
                        doIt = false;
                        this->next();
                        this->next();
                    }
                    else
                    {
                        this->next();
                    }
                }
                printf("D] COMMENT BLOCK\n");
            }
            break;

            default:
            {
                this->document.append(this->cValue());
            }
            break;
            }
        }

        // Check if it's Begin of Line and if it's a FullStop ('.')
        if (this->isBoL && this->cType() == TokenType::FullStop)
        {
            this->next();

            switch (str2int(txtutil::str2lower(this->cValue()).c_str()))
            {
            // declare and set register value [.dv <IDENTIFIER> <VALUE>]
            case str2int("nr"):
            {
                // dump 'tmpParagraph'
                // this->dumpTmpParagraph();

                this->next();
                if (this->cType() != TokenType::Whitespace)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                this->next();
                if (this->cType() != TokenType::Text)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }
                std::string vIdentifier = this->cValue();

                this->next();
                if (this->cType() != TokenType::Whitespace)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                this->next();
                std::string vValue = this->getCompleteLine();

                if (vIdentifier == "LL")
                {
                    this->storage->lineLength = atoi(vValue.c_str());
                }
                else
                {
                    // Add variable to storage
                    this->storage->setRegister(vIdentifier, vValue);
                }
            }
            break;

            // title [.tl 'LEFT'CENTER'RIGHT']
            case str2int("tl"):
            {
                // dump 'tmpParagraph'
                // this->dumpTmpParagraph();

                this->next();
                if (this->cType() != TokenType::Whitespace)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                this->next();
                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                // GET "LEFT" PART
                this->next();
                std::string part0 = this->getTill(TokenType::Apostrophe);

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                // GET "CENTER" PART
                this->next();
                std::string part1 = this->getTill(TokenType::Apostrophe);

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                // GET "RIGHT" PART
                this->next();
                std::string part2 = this->getTill(TokenType::Apostrophe);

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                std::string parts[3] = {part0, part1, part2};

                this->document.append(txtutil::title3Part(parts, this->storage->lineLength));
                this->document.append("\n");
            }
            break;

            // center [.ce <NUMBER>]
            case str2int("ce"):
            {
                unsigned int lineCount = 1;
                this->next();
                if (this->cType() == TokenType::Whitespace)
                {
                    this->next();
                    if (this->cType() == TokenType::Number)
                    {
                        lineCount = std::stoi(this->cValue());
                    }
                }

                this->nextLine();
                for (int i = 0; i < lineCount; i++)
                {
                    this->document.append(txtutil::center(this->getCompleteLine(), " ", this->storage->lineLength) + "\n");
                    this->next();
                }
            }
            break;

            // empty lines [.el <?NUMBER>]
            case str2int("el"):
            {
                this->next();

                unsigned int eLines = 1;
                if (this->cType() == TokenType::Whitespace)
                {
                    this->next();
                    if (this->cType() == TokenType::Number)
                    {
                        eLines = std::stoi(this->cValue());
                    }
                }

                for (int i = 0; i < eLines; i++)
                {
                    this->document.append("\n");
                }
            }
            break;

            default:
            {
                // this->appendTmpParagraph(this->cValue());
            }
            break;
            }
        }

        this->next();
    }

    return this->document;
}

PlaintextParser::~PlaintextParser()
{
    delete this->storage;
}