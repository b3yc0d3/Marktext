#ifndef MARKTEXT_STORAGE_H
#define MARKTEXT_STORAGE_H

#include <map>
#include <string>

/**
 * @brief Class used to Store Registers/Variable created by Users
 * 
 */
class Storage
{
private:
    std::map<std::string, std::string> registers;
    std::map<std::string, std::string> variables;

public:
    Storage();

    /**
     * @brief Sets, Overwrites or Creates a Register
     * 
     * @param key Key Name
     * @param value Value
     */
    void setRegister(std::string key, std::string value);

    /**
     * @brief Sets, Overwrites or Creates a Variable
     *
     * @param key Key Name
     * @param value Value
     */
    void setVariable(std::string key, std::string value);

    /**
     * @brief Get value of a Register
     *
     * @param key
     * @return std::string (null if key does not exist)
     */
    std::string getRegister(std::string key);

    /**
     * @brief Get value of a Variable
     *
     * @param key Key Name
     * @return std::string (null if key does not exist)
     */
    std::string getVariable(std::string key);

    ~Storage();
};
#endif
