#ifndef CONSTANTS_H
#define CONSTANTS_H

// Server configuration
#define DEFAULT_PORT 9090     // changed from 8080 to avoid conflicts
#define MAX_CLIENTS 100

// Buffer sizes
#define BUFFER_SIZE 1024
#define USERNAME_LEN 32

// Message formatting
#define MAX_MESSAGE_LEN (BUFFER_SIZE + USERNAME_LEN + 10)

// Utility macros
#define EXIT_FAILURE_CODE 1
#define EXIT_SUCCESS_CODE 0

#endif