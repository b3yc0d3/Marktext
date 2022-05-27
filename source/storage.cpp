#include "../includes/storage.h"

Storage::Storage() {}

/**
 * Setter
 */
void Storage::setRegister(std::string key, std::string value)
{
    this->registers.insert(std::make_pair(key, value));
}

/**
 * Getter
 */

std::string Storage::getRegister(std::string key)
{
    if (this->registers.count(key))
    {
        return this->registers[key];
    }
    else
    {
        return NULL;
    }
}


Storage::~Storage() {}