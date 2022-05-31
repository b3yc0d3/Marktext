#include <algorithm>
#include <cctype>
#include "../includes/txtutil.h"

namespace txtutil
{
    bool isNumeric(const std::string &iText)
    {
        return !iText.empty() && std::find_if(iText.begin(), iText.end(), [](unsigned char c)
                                              { return !std::isdigit(c); }) == iText.end();
    }

    std::string str2lower(std::string iText)
    {
        for (char &c : iText)
        {
            c = tolower(c);
        }

        return iText;
    }

    std::string str2upper(std::string text)
    {
        for(char &c : text)
        {
            c = toupper(c);
        }

        return text;
    }

    std::string repeat(const std::string &input, unsigned int num)
    {
        std::string ret;
        ret.reserve(input.size() * num);
        while (num--)
            ret += input;
        return ret;
    }

    std::string center(std::string text, const std::string &fChar, unsigned int length)
    {

        if (text.length() == 0)
        {
            return repeat(" ", length);
        }

        std::string retStr = "";

        // implemented cause if line is longer then 'length', it get wrapped
        std::vector<std::string> parts = split_str(word_wrap(text.c_str(), length), "\n");

        for (std::string &part : parts)
        {
            std::string buffer = "";
            unsigned int pLength = part.length();
            unsigned int padding = (length - pLength) / 2;

            buffer.append(repeat(fChar, padding));
            buffer.append(part);
            // buffer.append(repeat(fChar, padding));

            if (buffer.length() > length)
            {
                buffer.resize(length);
            }

            retStr.append(buffer);
            buffer.clear();
        }

        return retStr;
    }

    std::string title3Part(const std::vector<std::string> parts, unsigned int length)
    {
        std::string buffer = center(parts[1], " ", length);

        buffer.append(repeat(" ", (length - buffer.length())));

        int leftTitleLength = parts[0].size();
        int rightTitleLength = parts[2].size();

        buffer = parts[0] + buffer.substr(leftTitleLength, buffer.size());
        buffer = buffer.substr(0, (buffer.length() - rightTitleLength)) + parts[2];

        return buffer;
    }

    std::string word_wrap(std::string text, int line_length)
    {
        unsigned line_begin = 0;

        while (line_begin < text.size())
        {
            const unsigned ideal_end = line_begin + line_length;
            unsigned line_end = ideal_end <= text.size() ? ideal_end : text.size() - 1;

            if (line_end == text.size() - 1)
                ++line_end;
            else if (std::isspace(text[line_end]))
            {
                text[line_end] = '\n';
                ++line_end;
            }
            else // backtrack
            {
                unsigned end = line_end;
                while (end > line_begin && !std::isspace(text[end]))
                    --end;

                if (end != line_begin)
                {
                    line_end = end;
                    text[line_end++] = '\n';
                }
                else
                    text.insert(line_end++, 1, '\n');
            }

            line_begin = line_end;
        }

        return text;
    }

    std::vector<std::string> split_str(const std::string &str, const std::string &delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
        {
            token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(str.substr(pos_start));
        return res;
    }

    bool strswi(const std::string &var, const std::string &text)
    {
        return (var.rfind(text, 0) == 0);
    }

    std::string placeholderInsertValue(std::string text, Register *reg)
    {
        std::regex regexPlaceholder("\\$\\(([A-Z_]+)\\)");
        std::smatch matches;
        std::string buffer = text;

        while (std::regex_search(text, matches, regexPlaceholder))
        {
            std::regex exp1("\\$\\(" + matches[1].str() + "\\)");

            buffer = std::regex_replace(buffer, exp1, reg->getStr(matches[1].str()));

            text = matches.suffix();
        }

        return buffer;
    }
}