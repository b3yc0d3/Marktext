/*
 * @file lexer.h
 * @author b3yc0d3
 * @brief Contains the lexer for Marktext Typeset
 * @date Sun May 15 2022
 *
 * @copyright See LICENSE file in the source tree.
*/

#ifndef MARKTEXT_LEXER_H
#define MARKTEXT_LEXER_H

#include <string>
#include <vector>

#include "../includes/token.h"

class Lexer
{
private:
    std::vector<Token> tokens;
    std::string tmpStr = "";

    /**
     * @brief Dump current Temporeral String in to Token Vector
     *
     */
    void dumpTmpStr();
    
    /**
     * @brief Add Token to Token Vector
     * 
     * @param type Type of Token
     * @param value Value of Token
     */
    void add(TokenType type, const std::string &value);

public:
    /**
     * @brief Create new Instance of Lexer
     * 
     */
    Lexer(/* args */);

    /**
     * @brief Lexical Analyze given text
     *
     * @param rText Text that should be Analyzed
     * @return std::vector<Token>
     */
    std::vector<Token> run(const std::string &rText);
    
    ~Lexer();
};

#endif