#include <string.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_sta.h"
#include "esp_misc.h"

#include "user_local.h"

void wifi_event_handler_cb(System_Event_t* event);
bool Wifi_init(void);
