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
// Utils
#include "../includes/lexer.h"
#include "../includes/txtutil.h"
#include "../includes/version.h"
// Parser
#include "../includes/parsers/plaintext.h"

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

void print_usage()
{
    std::cout << "Usage: mtt [options] <INPUT_FILE_PATH>\n"
              << "Options:\n"
              << "   -F <pt>           Set the output format.\n"
              << "   --version         Shows this message.\n"
              << "   --help            Shows version of Marktext.\n\n"
              << "Positional Patameter:\n"
              << "   INPUT_FILE_PATH   File path to Input file."
              << "\n";
}

int main(int argc, char **argv)
{
    const char *filePath;
    // TODO: Command line Arguments
    if (DEBUG)
    {
        std::cout << "Marktext v"
                  << VERSION_MAJOR << "."
                  << VERSION_MINOR << "."
                  << VERSION_PATCH << "-"
                  << VERSION_PRE_RELEASE
                  << "\n";
    }

    if (argc <= 1)
    {
        print_usage();
        exit(EXIT_SUCCESS);
    }

    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        std::string tmp = std::string(argv[i]);
        if (tmp.find("=") != std::string::npos)
        {
            std::vector<std::string> parts = txtutil::split_str(tmp, "=");

            for (size_t i = 0; i < parts.size(); i++)
            {
                args.push_back(parts[i]);
            }
        }
        else
        {
            args.push_back(tmp);
        }
    }

    if (txtutil::vector_contains<std::string>(args, "--version"))
    {
        std::cout << "Marktext "
                  << "v"
                  << VERSION_MAJOR
                  << "."
                  << VERSION_MINOR
                  << "."
                  << VERSION_PATCH
                  << "-"
                  << VERSION_PRE_RELEASE
                  << "\n";

        exit(EXIT_SUCCESS);
    }

    if (txtutil::vector_contains<std::string>(args, "--help"))
    {
        print_usage();
        exit(EXIT_SUCCESS);
    }

    if (!txtutil::strswi(args.back().c_str(), "-"), !txtutil::strswi(args.back().c_str(), "--"))
    {
        filePath = args.back().c_str();
    }

    std::fstream in(filePath);
    std::string fContents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    std::vector<Token> tokens;
    std::string document;

    {
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();
        tokens = lexer->run(fContents);
    }

    {
        std::unique_ptr<PlaintextParser> ptParser = std::make_unique<PlaintextParser>();
        document = ptParser->parse(tokens);
        std::cout << txtutil::repeat("#", ptParser->regi->get<int>("LL", 72));
    }

    std::cout << "\n"
              << document << "\n";

    return 0;
}
