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
    this->regi = new Register();
    this->isBoL = true;

    this->regi->insert("LL", 72);
    this->regi->insert("INDENT", 3);
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

Token PlaintextParser::peek(int l = 1)
{
    if ((this->index + l) < this->tokens.size())
    {
        return this->tokens[this->index + l];
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

    return txtutil::placeholderInsertValue(buffer, this->regi);
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

    return txtutil::placeholderInsertValue(buffer, this->regi);
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
    if (this->tmpParagraph != "")
    {
        int lineLengthIndented = this->regi->get<int>("LL", 72) - this->regi->get<int>("INDENT", 3);
        std::vector<std::string> lines = txtutil::split_str(txtutil::word_wrap(txtutil::placeholderInsertValue(this->tmpParagraph, this->regi), lineLengthIndented), "\n");

        // this->document.append("\n");

        for (std::string &line : lines)
        {
            // printf(std::string(line).c_str());
            this->document.append(txtutil::repeat(" ", this->regi->get<int>("INDENT", 3)) + line + "\n");
        }

        // clear 'tmpParagraph'
        this->tmpParagraph.clear();
    }
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

    while (this->cur_token.value != "NULL")
    {

        // check if it is a comment
        switch (this->cType())
        {
        case Solidus:
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
            }
            break;

            default:
            {
                this->document.append(this->cValue());
            }
            break;
            }
        }
        break;

            // TODO: variable use aka. $(NAME)
            // https://coliru.stacked-crooked.com/a/3902146ee704c4fe

        default:
            break;
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
                this->dumpTmpParagraph();

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
                std::string vValue;

                if (this->cType() == TokenType::QuotationMark)
                {
                    this->next();
                    vValue = this->getTill(TokenType::QuotationMark);
                }
                else
                {
                    vValue = this->getCompleteLine();
                }

                if (txtutil::isNumeric(vValue))
                {
                    this->regi->insert(txtutil::str2upper(vIdentifier), std::stoi(vValue));
                }
                else
                {
                    this->regi->insert(txtutil::str2upper(vIdentifier), vValue);
                }
            }
            break;

            // title [.tl 'LEFT'CENTER'RIGHT']
            case str2int("tl"):
            {
                this->dumpTmpParagraph();
                std::vector<std::string> parts;

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
                parts.push_back(this->getTill(TokenType::Apostrophe));

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                // GET "CENTER" PART
                this->next();
                parts.push_back(this->getTill(TokenType::Apostrophe));

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                // GET "RIGHT" PART
                this->next();
                parts.push_back(this->getTill(TokenType::Apostrophe));

                if (this->cType() != TokenType::Apostrophe)
                {
                    // TODO: output error message
                    exit(EXIT_FAILURE);
                }

                this->document.append(txtutil::title3Part(parts, this->regi->get<int>("LL", 72)));
                this->document.append("\n");
            }
            break;

            // center [.ce <NUMBER>]
            case str2int("ce"):
            {
                this->dumpTmpParagraph();
                this->next();

                unsigned int lineCount = 1;
                if (this->cType() == TokenType::Whitespace)
                {
                    this->next();
                    if (this->cType() == TokenType::Number)
                    {
                        lineCount = std::stoi(this->cValue());
                    }
                }

                this->nextLine();
                for (unsigned int i = 0; i < lineCount; i++)
                {
                    this->document.append(txtutil::center(this->getCompleteLine(), " ", this->regi->get<int>("LL", 72)) + "\n");
                    this->next();
                }
            }
            break;

            // empty lines [.el <?NUMBER>]
            case str2int("el"):
            {
                this->dumpTmpParagraph();
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

                for (unsigned int i = 0; i < eLines; i++)
                {
                    this->document.append("\n");
                }
            }
            break;

            // paragraph [.ph CRLF <VALUE>]
            case str2int("ph"):
            {
                this->nextLine();
                this->dumpTmpParagraph();
                bool doIt = true;
                std::string tmpLine = "";

                while (doIt)
                {
                    // check if the Paragraph end is reached (or end of file aka cValue == NULL)
                    //if (this->cValue() == "NULL" || (this->isBoL && this->peek().type == TokenType::FullStop))
                    if ((this->cType() == TokenType::CRLF && this->peek().type == TokenType::CRLF) || this->cValue() == "NULL")
                    {
                        doIt = false;
                    }
                    else if (!(this->cType() == TokenType::FullStop && this->isBoL))
                    {
                        this->appendTmpParagraph(this->cValue());
                    }

                    this->next();
                }
            }
            break;

            // header [.hr <?NUMBER>]
            case str2int("hr"):
            {
                this->dumpTmpParagraph();
                this->next();

                unsigned int level = 1;
                if (this->cType() == TokenType::Whitespace)
                {
                    this->next();
                    if (this->cType() == TokenType::Number)
                    {
                        level = std::stoi(this->cValue());
                    }
                }

                this->nextLine();
                std::string text = this->getCompleteLine();

                this->document.append("\n" + text + "\n");

                switch (level)
                {
                case 0:
                case 1:
                {
                    this->document.append(txtutil::repeat("=", text.size()) + "\n\n");
                }
                break;

                case 2:
                {
                    this->document.append(txtutil::repeat("-", text.size()) + "\n\n");
                }
                break;

                default:
                {
                    this->document.append("\n");
                }
                break;
                }
            }
            break;

            // not formatted [.nf CRLF <VALUE>]
            case str2int("nf"):
            {
                this->nextLine();
                this->dumpTmpParagraph();
                bool doIt = true;
                std::string tmp = "";

                while (doIt)
                {
                    // check if the end is reached (or end of file aka cValue == NULL)
                    if (this->cValue() == "NULL" || (this->isBoL && this->peek().type == TokenType::FullStop))
                    {
                        doIt = false;
                    }
                    else
                    {
                        tmp.append(this->cValue());
                    }

                    this->next();
                }

                int lineLengthIndented = this->regi->get<int>("LL", 72) - this->regi->get<int>("INDENT", 3);
                // replace all value placeholder contained in text
                std::vector<std::string> lines = txtutil::split_str(txtutil::placeholderInsertValue(tmp, this->regi), "\n");

                for (std::string &line : lines)
                {
                    if (line.length() > lineLengthIndented)
                    {
                        std::vector<std::string> lines2 = txtutil::split_str(txtutil::word_wrap(line, lineLengthIndented), "\n");

                        for (std::string &line2 : lines2)
                        {
                            this->document.append(txtutil::repeat(" ", this->regi->get<int>("INDENT", 3)) + line2 + "\n");
                        }
                    }
                    else
                    {
                        this->document.append(txtutil::repeat(" ", this->regi->get<int>("INDENT", 3)) + line + "\n");
                    }
                }

                tmp.clear();
            }
            break;

            default:
            {
            }
            break;
            }
        }

        this->next();
    }

    // just in cas if it isn't empty
    this->dumpTmpParagraph();

    return this->document;
}

PlaintextParser::~PlaintextParser()
{
    delete this->regi;
}