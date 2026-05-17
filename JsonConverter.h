// This is gennerated by AI.
// ChatGPT (GPT-5.5.)

#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "json.hpp"

#include <optional>

template<typename T>
void to_json(nlohmann::json &j, const std::optional<T> &s)
{
    if (s.has_value()){
        j = *s;
    } else {
        j = nlohmann::json(nullptr);
    }
}

template<typename T>
void from_json(const nlohmann::json &j, std::optional<T> &s)
{
    if (j.is_null()){
        s = std::nullopt;
    } else {
        s = j.get<T>();
    }
}

struct Message;
struct Contact;
struct User;

void to_json(nlohmann::json& j, const Message& m);
void from_json(const nlohmann::json& j, Message& m);

void to_json(nlohmann::json& j, const Contact& c);
void from_json(const nlohmann::json& j, Contact& c);

void to_json(nlohmann::json& j, const User& u);
void from_json(const nlohmann::json& j, User& u);

#endif // JSONCONVERTER_H
