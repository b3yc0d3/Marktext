#ifndef MARKTEXT_STORAGE_H
#define MARKTEXT_STORAGE_H

#include <map>
#include <string>
#include <any>

/**
 * @brief Class used to Store Registers/Variable created by Users
 * 
 */
class Storage
{
private:
    std::map<std::string, std::string> registers;

public:
    unsigned int lineLength = 72;
    unsigned int indent =  3;
    Storage();

    /**
     * @brief Sets, Overwrites or Creates a Register
     * 
     * @param key Key Name
     * @param value Value
     */
    void setRegister(std::string key, std::string value);

    /**
     * @brief Get value of a Register
     *
     * @param key
     * @return std::string (null if key does not exist)
     */
    std::string getRegister(std::string key);

    ~Storage();
};
#endif
