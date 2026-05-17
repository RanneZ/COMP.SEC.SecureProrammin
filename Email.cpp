// AI assistance was used extensively during the development of the SMTP workflow,
// particularly for understanding protocol structure.
// ChatGPT (GPT-5.5.)

#include "Email.h"

#include <iostream>

bool sendEmail(const emailContent& content){

    QSslSocket socket;
    std::string responseStr;

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

    // login to the email
    responseStr = sendCommand(socket, "AUTH LOGIN");
    if (responseStr.substr(0, 3) != "334") {
        std::cout << "AUTH LOGIN rejected" << std::endl;;
        return false;
    }
    responseStr = sendCommand(socket, QByteArray::fromStdString(content.from).toBase64().toStdString());
    if (responseStr.substr(0, 3) != "334") {
        std::cout << "Username rejected\n";
        return false;
    }
    responseStr = sendCommand(socket, QByteArray::fromStdString(content.pass).toBase64().toStdString());
    if (responseStr.substr(0, 3) == "235") {
        std::cout << "Login successful\n";
    }
    else {
        std::cout << "Login failed\n";
        return false;
    }

    // Email setup
    sendCommand(socket, "MAIL FROM:<" + content.from + ">");
    for (const auto& recipient : content.to) {
        sendCommand(socket, "RCPT TO:<" + recipient + ">");
    }
    sendCommand(socket, "DATA");

    // Message
    std::string data = "Subject: "+ content.subject +"\r\n""\r\n"+ content.message + "\r\n.";

    sendCommand(socket, data);

    sendCommand(socket, "QUIT");

    socket.close();

    return true;
}

std::string sendCommand(QSslSocket& socket, const std::string& command){
    QString qCommand = QString::fromStdString(command);

    socket.write(qCommand.toUtf8() + "\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    QByteArray response = socket.readAll();
    std::string responseStr = response.toStdString();
    return responseStr;
}
