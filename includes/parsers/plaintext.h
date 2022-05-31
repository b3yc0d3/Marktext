#ifndef MARKTEXT_PLAINTEXT_H
#define MARKTEXT_PLAINTEXT_H

#include <vector>
#include <memory>
#include "../token.h"
#include "../registers.hpp"

class PlaintextParser
{
private:
    std::vector<Token> tokens;

    Token cur_token;
    bool isBoL; // True if Begon of Line
    std::string document;
    unsigned int index;
    std::string tmpParagraph;

public:
    // Storage for all Registers and Variable that
    // the user can create
    Register *regi;

    PlaintextParser();

    /**
     * @brief Go to next Token
     * 
     */
    void next();

    /**
     * @brief Get Next token without iterate
     * 
     * @return Token 
     */
    Token peek();

    /**
     * @brief Get value of Current Token
     * 
     * @return std::string 
     */
    std::string cValue();

    /**
     * @brief Get Type of Current Token
     *
     * @return Token
     */
    TokenType cType();

    /**
     * @brief Get the Complete Line object
     *
     * @return std::string
     */
    std::string getCompleteLine();

    /**
     * @brief Go to Next line
     * 
     */
    void nextLine();

    /**
     * @brief Skip text untill given Token Type
     * 
     * @param token 
     */
    void skipTill(TokenType token);

    /**
     * @brief Parse given Tokens
     * 
     * @param tokens Token Vector 
     * @return std::string 
     */
    std::string parse(std::vector<Token> &tokens);

    /**
     * @brief Get text untill certain Char or Token Type
     * 
     * @param token 
     * @return std::vector<std::string> 
     */
    std::string getTill(TokenType token);

    /**
     * @brief Append Temporeral Paragraph
     * 
     * @param value Value to Append
     */
    void appendTmpParagraph(const std::string &value);

    /**
     * @brief Dump Temporeral Paragraph
     *
     * This functions adds the temporeral Paragraph to the Document
     */
    void dumpTmpParagraph();

    ~PlaintextParser();
};


#endif