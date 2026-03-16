#include "cleint.h"

#include "esp_err.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include <string.h>
#include <strings.h>

const char *TAG = "TCP";



esp_err_t connect_tcp_server(void) {

    struct sockaddr_in serverInfo = {0};
    char readBuffer[1024] = {0};

    serverInfo.sin_family = AF_INET;
    // serverInfo.sin_addr.s_addr = 0x0100007f;
    // serverInfo.sin_addr.s_addr = inet_addr("192.168.2.193");
    serverInfo.sin_port = htons(12345);
    inet_pton(AF_INET, "192.168.2.193", &serverInfo.sin_addr.s_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        ESP_LOGE(TAG, "failed to create socket..?");
        return TCP_FAILURE;
    }

    if (connect(sock, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) != 0) {

    ESP_LOGI(TAG, "Failed to connect to %s!", inet_ntoa(serverInfo.sin_addr.s_addr));
        close(sock);
        return TCP_FAILURE;
    }
    ESP_LOGI(TAG, "Connected to TCP server.");
    bzero(readBuffer, sizeof(readBuffer));
    int r = read(sock, readBuffer, sizeof(readBuffer)-1);
    for(int i = 0; i < r; i++) {
        putchar(readBuffer[i]);
    }
        ESP_LOGI(TAG,"we got data: %s", readBuffer);
    if (strcmp(readBuffer, "HELLO") == 0) {
        ESP_LOGI(TAG,"WE DID IT!");
    }

    return TCP_SUCCESS;
}
