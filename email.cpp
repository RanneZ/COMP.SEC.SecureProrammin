#include "email.h"
#include <iostream>

email::email() {}

bool email::sendEmail(const std::string &from,
                      const std::string &pass,
                      const std::string &to,
                      const std::string &subject,
                      const std::string &message){

    QSslSocket socket;

    // connect to the smtp servise
    socket.connectToHost("smtp.gmail.com", 587);

    if(!socket.waitForConnected(5000)){
        std::cout << "Connection failed" << std::endl;
        return false;
    }

    socket.waitForReadyRead();

    QByteArray response = socket.readAll();
    std::cout << response.toStdString() << std::endl;

    // smtp servise commands

    sendCommand(socket, "EHLO localhost");
    sendCommand(socket, "STARTTLS");

    socket.startClientEncryption();

    if(!socket.waitForEncrypted(5000)){
        std::cout << "STARTTLS failed" << std::endl;
        return false;
    }

    sendCommand(socket, "EHLO localhost");

    // login to the ms outlook?
    sendCommand(socket, "AUTH LOGIN");
    sendCommand(socket, QByteArray::fromStdString(from).toBase64().toStdString());
    sendCommand(socket, QByteArray::fromStdString(pass).toBase64().toStdString());

    // Email setup
    sendCommand(socket, "MAIL FROM:<" + from + ">");
    sendCommand(socket, "RCPT TO:<" + to + ">");
    sendCommand(socket, "DATA");

    // Message
    std::string data = "Subject: "+ subject +"\r\n""\r\n"+ message + "\r\n.";

    sendCommand(socket, data);

    sendCommand(socket, "QUIT");

    socket.close();

    return true;

}

void email::sendCommand(QSslSocket& socket, const std::string& command){
    std::cout << "CLIENT: " << command << std::endl;
    QString qCommand = QString::fromStdString(command);

    socket.write(qCommand.toUtf8() + "\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    QByteArray response = socket.readAll();
    std::cout << "SERVER: " << response.toStdString() << std::endl;
}
