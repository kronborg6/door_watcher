#ifndef WIFI_H
#define WIFI_H


#include "esp_err.h"

/** DEFINES **/
#define WIFI_SUCCESS 1 << 0
#define WIFI_FAILURE 1 << 1
#define MAX_FAILURES 10

esp_err_t connect_wifi();

#endif /* WIFI_H */
