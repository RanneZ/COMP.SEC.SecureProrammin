// This is gennerated by AI.
// ChatGPT (GPT-5.5.)

#include "JsonConverter.h"
#include "Actions.h"

void to_json(nlohmann::json& j, const Contact& c) {
    j = nlohmann::json{
        {"username", c.username},
        {"email", c.email}
    };
}

void from_json(const nlohmann::json& j, Contact& c) {
    c.username = j.value("username", "");
    c.email = j.value("email", "");
}

void to_json(nlohmann::json& j, const User& u) {
    j = nlohmann::json{
        {"username", u.username},
        {"email", u.email},
        {"passwordHash", u.passwordHash},
        {"passwordSalt", u.passwordSalt},
        {"contacts", u.contacts}
    };
}

void from_json(const nlohmann::json& j, User& u) {
    u.username = j.value("username", "");
    u.email = j.value("email", "");
    u.passwordHash = j.value("passwordHash", "");
    u.passwordSalt = j.value("passwordSalt", "");
    u.contacts = j.value("contacts", std::vector<Contact>{});
}
