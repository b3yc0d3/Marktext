#ifndef MARKTEXT_PLAINTEXT_H
#define MARKTEXT_PLAINTEXT_H

#include <vector>
#include <memory>
#include "../storage.h"
#include "../token.h"

class PlaintextParser
{
private:
    std::vector<Token> tokens;
    // Storage for all Registers and Variable that
    // the user can create
    Storage *storage;

    Token cur_token;
    bool isBoL; // True if Begon of Line
    std::string document;
    unsigned int index;

public:
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
    Token preview();

    /**
     * @brief Get value of Current Token
     * 
     * @return std::string 
     */
    std::string cValue()
    {
        if(this->cur_token.value == "NULL")
        {
            return "NULL";
        }

        return this->cur_token.value;
    }

    /**
     * @brief Get Type of Current Token
     *
     * @return Token
     */
    TokenType cType()
    {
        if (this->cur_token.value == "NULL")
        {
            //return "NULL";
        }

        return this->cur_token.type;
    }

    /**
     * @brief Parse given Tokens
     * 
     * @param tokens Token Vector 
     * @return std::string 
     */
    std::string parse(std::vector<Token> &tokens);

    ~PlaintextParser();
};


#endif