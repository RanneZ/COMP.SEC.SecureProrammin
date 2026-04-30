#include "jsonconverter.h"
#include "datastructures.h"

void to_json(nlohmann::json& j, const Message& m) {
    j = nlohmann::json{
        {"sender", m.sender},
        {"recipients", m.recipients},
        {"subject", m.subject},
        {"body", m.body},
        {"timestamp", m.timestamp}
    };
}

void from_json(const nlohmann::json& j, Message& m) {
    m.sender = j.value("sender", "");
    m.recipients = j.value("recipients", std::vector<std::string>{});
    m.subject = j.value("subject", "");
    m.body = j.value("body", "");
    m.timestamp = j.value("timestamp", 0);
}

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
        {"inbox", u.inbox},
        {"sent", u.sent},
        {"contacts", u.contacts}
    };
}

void from_json(const nlohmann::json& j, User& u) {
    u.username = j.value("username", "");
    u.email = j.value("email", "");
    u.passwordHash = j.value("passwordHash", "");
    u.passwordSalt = j.value("passwordSalt", "");
    u.inbox = j.value("inbox", std::vector<Message>{});
    u.sent = j.value("sent", std::vector<Message>{});
    u.contacts = j.value("contacts", std::vector<Contact>{});
}
