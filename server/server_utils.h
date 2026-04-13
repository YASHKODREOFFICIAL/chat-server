#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <pthread.h>

void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);

extern pthread_mutex_t clients_mutex;

#endif