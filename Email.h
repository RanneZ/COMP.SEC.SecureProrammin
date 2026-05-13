#ifndef EMAIL_H
#define EMAIL_H

#include <QSslSocket>
#include <string>
#include <QString>

struct emailContent{
    std::string from;
    std::string pass;
    std::string to;
    std::string subject;
    std::string message;
};

bool sendEmail(const emailContent& items);
void sendCommand(QSslSocket& socket, const std::string& command);

#endif // EMAIL_H
