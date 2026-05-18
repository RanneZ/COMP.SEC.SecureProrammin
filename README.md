# COMP.SEC.SecureProrammin Email system

This app is a command-line email client and contact manager built in C++ (not very practical one, and conteins lots of typos here and there).

## Quick Start

You can download the fully compiled, ready-to-run application directly from the **[Releases](../../releases)** tab. 

1. Download the latest `.zip` archive for your windows.
2. Extract the contents to a local folder.
3. Run the executable in your terminal.

## Prerequisites
*   **Email sytem app:** This app.
*   **Valid Gmail Account:** A working Gmail address used as the primary sender for the user.
*   **Valid Gmail App Password:** A dedicated 16-character security token generated from your Google Account settings. The App Password is never written, cached, or serialized to the local disk (such as the `users.txt` file). It only exists as a temporary string variable during runtime.
    
    >**Security Note:** Because Google blocks less secure apps from using your primary account password, you **must** generate an **App Password** under your Google Account's *2-Step Verification* settings. The application transmits this token securely over an encrypted TLS connection (`STARTTLS`) to authenticate against `smtp.gmail.com`.

---

## Supported Platforms & Email
*   **Windows:** Main target platform. Developed and tested using MinGW (x64) and Qt.
*   **Linux:** Built with cross-platform frameworks (Qt & Crypto++), but currently untested.
*   **Gmail:** Currently is only supported email.

---

## Application Commands & Features

The application operates as a command-line state machine.

### Unauthenticated Commands (Public Access)
These commands are available to anyone when the application starts:
*   `help` - Displays all available commands.
*   `sign_in` - Launches the registration wizard to create a new user.
*   `log_in <username>` - Prompts for password verification to log in using a unique username.
*   `log_in <email>` - Prompts for password verification to log in using a registered email address.

### Authenticated Commands (Login Required)
The following operations are strictly guarded unless a user has successfully logged in:

*   **Email Management:**
    *   `send_email` - Launches the create email wizard to create a new email and sends it.
*   **Contact Management:**
    *   `create_contact` - Adds a new contact name and email to the current user contacts list.
    *   `print_contacts` - Lists all contacts saved under the current user.
    *   `update_contact <contact_name>` - Modifies details for an existing contact.
    *   `remove_contact <contact_name>` - Deletes a contact from the current users contacts list.
*   **Account & Profile Security:**
    *   `print_user` - Displays user profile for the currently logged-in user.
    *   `change_password` - Updates and re-hashes the user's account password.
    *   `change_email_address` - Updates the users email address.
    *   `log_out` - Clears the current user profile, uses zero-overwrite memory scrubbing on the email password, and resets the console to unauthenticated state.

---

## Prerequisites & Dependencies

*   **Compiler:** GCC, Clang, or MinGW supporting **C++17**.
*   **Framework:** Qt 5 or Qt 6 (`core` and `network` modules).
*   **Package Manager (Windows):** `vcpkg` configured with `x64-mingw-static`.
*   **Libraries:** 
    *   [Crypto++](https://www.cryptopp.com/) (Must be installed via system package manager vcpkg on Windows).
    *   [nlohmann/json](https://github.com/nlohmann/json) (Included locally in `/libs`).