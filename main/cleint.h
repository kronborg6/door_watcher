#ifndef CLIENT_H
#define CLIENT_H

#include "esp_err.h"

#define TCP_SUCCESS 1 << 0
#define TCP_FAILURE 1 << 1

esp_err_t connect_tcp_server(void);

#endif /* end of include guard: CLIENT_H */
