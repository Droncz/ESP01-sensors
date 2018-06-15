#include "wifi_station.h"


void wifi_event_handler_cb(System_Event_t* event)
{
    if (event == NULL) {
        return;
    }

    switch (event->event_id) {
        case EVENT_STAMODE_GOT_IP:
            printf("sta got ip ,create task and free heap size is %d\n", system_get_free_heap_size());
            // user_conn_init();  // Do something (i.e. start task inside) when we have connectivity
            break;

        case EVENT_STAMODE_CONNECTED:
            printf("sta connected\n");
            break;

        case EVENT_STAMODE_DISCONNECTED:
            wifi_station_connect();
            break;

        default:
            break;
    }
}

bool Wifi_init(void) {
    wifi_set_opmode(STATION_MODE);

    struct station_config config;
    memset((void*)&config, 0, sizeof(struct station_config));
    strcpy((char*)config.ssid, SSID);
    strcpy((char*)config.password, PASSWORD);
 
    if (!wifi_station_set_config(&config)) {
        printf("Failed to set Station config!\n");
        return false;
    }

    if (!wifi_station_dhcpc_status()) {
        printf("DHCP is not started. Starting it...\n");

        if (!wifi_station_dhcpc_start()) {
            printf("DHCP start failed!\n");
            return false;
        }
    }

    wifi_set_event_handler_cb(wifi_event_handler_cb);
    return true;
}