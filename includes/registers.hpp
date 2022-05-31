#ifndef MARKTEXT_REGISTERS_H_
#define MARKTEXT_REGISTERS_H_

#include <string>
#include <any>
#include <map>

class Register
{

private:
    std::map<std::string, std::any> register_map;

public:
    Register(){};

    /**
     * @brief Insert Register
     *
     * This function Inserts a new Register.
     * a already existing Identifier will be overwritten
     *
     * @param identifier Register Identifier
     * @param value Any value to store
     */
    void insert(std::string identifier, std::any value)
    {
        // needed, otherwise value won't be inserted
        auto key = this->register_map.find(identifier);
        if(key != this->register_map.end())
        {
            // overwrite the "old" value with 'value'
            key->second = value;

        } else {
            // just inserting 'value' with 'identifier' as key
            this->register_map.insert(std::make_pair(identifier, value));
        }
    }

    /**
     * @brief Get Register Value
     *
     * If given 'identifier' not exists, value of 'fallback' will be retunred
     *
     * @param identifier Identifier Key
     * @param fallback Fallback Value
     * @return std::any Empty String if not Found
     */
    template <typename T>
    T get(std::string identifier, T fallback)
    {
        auto value = this->register_map.find(identifier);
        if(value != this->register_map.end())
        {
            return std::any_cast<T>(value->second);
            
        }

        return fallback;
    }

    /**
     * @brief Get any stored value as a String
     * 
     * Converts and Returns any register value to an string
     * and retuns it as one.
     * 
     * @param identifier Key name
     * @return std::string 
     */
    std::string getStr(std::string identifier)
    {
        auto value = this->register_map.find(identifier);

        if (value != this->register_map.end())
        {
            // checking what type the value is
            if (value->second.type() == typeid(int))
            {
                return std::to_string(std::any_cast<int>(value->second));
            }
            else if (value->second.type() == typeid(std::string))
            {
                return std::any_cast<std::string>(value->second);
            }
        }

        return std::string("");
    }

    ~Register() {}
};

#endif