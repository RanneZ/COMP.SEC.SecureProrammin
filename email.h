#ifndef EMAIL_H
#define EMAIL_H

#include <QSslSocket>
#include <string>
#include <QString>

class email{
public:
    email();

    bool sendEmail( const std::string& from,
                    const std::string& pass,
                    const std::string& to,
                    const std::string& subject,
                    const std::string& message);

private:
    void sendCommand(QSslSocket& socket, const std::string& command);
};

#endif // EMAIL_H
