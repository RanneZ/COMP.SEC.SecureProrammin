// AI assistance was used extensively during the development of the SMTP workflow,
// particularly for understanding protocol structure.
// ChatGPT (GPT-5.5.)

#ifndef EMAIL_H
#define EMAIL_H

#include <QSslSocket>
#include <string>
#include <vector>
#include <QString>

struct emailContent{
    std::string from; // sender
    std::string pass; // email app password
    std::vector<std::string> to; // recipient(s)
    std::string subject;
    std::string message;
};

// try to send email content
// and return true if success
bool sendEmail(const emailContent& items);

// send command to the socket and returns responce
std::string sendCommand(QSslSocket& socket, const std::string& command);

#endif // EMAIL_H
