#ifndef CLIENT_H
#define CLIENT_H

#include "esp_err.h"
#include <stdint.h>

/*
 *                      bytes
 *    [1]     [1]      [1]       [1]     [2]     [x]
 * [ 0xAA ][ 0x55 ][ version ][ type ][ len ][ payload ]
 *
 */


typedef enum {
    CONNECTED = 0x01,
} message_type_t;

#define TCP_SUCCESS 1 << 0
#define TCP_FAILURE 1 << 1

esp_err_t connect_tcp_server(void);

int send_data(int fd, message_type_t type, size_t len, const void *payload);

#endif /* end of include guard: CLIENT_H */
