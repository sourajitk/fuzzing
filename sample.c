#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Function to validate an email address
bool IsValidEmail(const char *email) {
    // Basic email validation
    size_t length = strlen(email);
    if (length < 5 || length > 320) {
        return false;
    }

    // Check for '@' symbol
    const char *at_symbol = strchr(email, '@');
    if (!at_symbol || at_symbol == email || at_symbol == email + length - 1) {
        return false;
    }

    // Check for '.' after '@'
    const char *dot = strchr(at_symbol, '.');
    if (!dot || dot == at_symbol + 1 || dot == email + length - 1) {
        return false;
    }

    return true;
}

// Fuzzer target function
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Convert the input data to a null-terminated C string
    char input[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the email validation function
    bool isValid = IsValidEmail(input);

    // Do something with the result to prevent optimization
    if (isValid) {
        return 0;  // Valid email
    } else {
        return 1;  // Invalid email
    }
}
