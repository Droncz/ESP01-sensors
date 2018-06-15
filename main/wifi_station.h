#include <string.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_sta.h"
#include "esp_misc.h"


#define SSID "svika"
#define PASSWORD "Karla Viky 1130"


void wifi_event_handler_cb(System_Event_t* event);
bool Wifi_init(void);
