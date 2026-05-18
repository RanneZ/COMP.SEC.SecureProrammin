#ifndef UI_H
#define UI_H

#include <string>

    // print separator line
    void separator();

    // print space
    void space();

    // print page header and some mesage if have one
    void pageHeader(const std::string& pageTitle, const std::string& username, const std::string& message);

#endif // UI_H
