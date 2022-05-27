#ifndef MARKTEXT_TXTUTIL_H
#define MARKTEXT_TXTUTIL_H

#include <string>
#include <vector>
#include <algorithm>

namespace txtutil
{
    /**
     * @brief Checks if String only contains Numbers
     *
     * @param iText Text that should be checked
     * @return true
     * @return false
     *
     * @see https://stackoverflow.com/a/4654718
     */
    bool isNumber(const std::string &iText);

    /**
     * @brief Text to lower case
     *
     * @param iText Input Text
     * @return std::string
     */
    std::string str2lower(std::string iText);

    // ##########################################

    /**
     * @brief Repeat string
     *
     * Repeat X char(s) Y given times
     *
     * @param input String to repeat
     * @param num How often to repeat
     * @return std::string
     */
    std::string repeat(const std::string &input, unsigned int num);

    /**
     * @brief Centers Text
     *
     * Centers given text X in length of Y, and fills the space with fille Z
     *
     * @param text Text to Center
     * @param fChar Filler char
     * @param length Length to center in
     * @return std::string
     */
    std::string center(std::string text, const std::string &fChar, unsigned int length);

    /**
     * @brief Create Title
     * 
     * e.g.: "Left text                     Center text                     Right Text"
     * 
     * @param parts Parts
     * @param length Line Length
     * @return std::string 
     */
    std::string title3Part(const std::string parts[3], unsigned int length);

    // ##########################################

    /**
     * @brief Wraps word to specifc length
     *
     * @param text Input text
     * @param line_length Length to wrap in
     * @return std::string
     *
     * @see https://www.cplusplus.com/forum/beginner/132223/#msg714543
     * @see https://ideone.com/wai9da
     */
    std::string word_wrap(std::string text, int line_length);

    /**
     * @brief Splits string at specific char(s)
     *
     * @param str Input string
     * @param delimiter Delimiter Char(s)
     * @return std::vector<std::string>
     *
     * @see https://stackoverflow.com/a/46931770
     */
    std::vector<std::string> split_str(const std::string &str, const std::string &delimiter);

    template <typename T>
    bool vector_contains(const std::vector<T> &vec, const T &val)
    {
        return std::count(vec.begin(), vec.end(), val);
    }

    /**
     * @brief Check if String starts with specific Char
     *
     * @param var Variable to check
     * @param text Text to check
     * @return true
     * @return false
     */
    bool strswi(const std::string &var, const std::string &text);
}

#endif