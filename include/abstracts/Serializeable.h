// Serializable.h
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <nlohmann/json.hpp>

class Serializable
{
public:
    virtual nlohmann::json serialize() const = 0;
    virtual void deserialize(const nlohmann::json &json) = 0;
};

#endif // SERIALIZABLE_H