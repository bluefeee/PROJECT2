#ifndef __MQTT_C_DEMO_H__
#define __MQTT_C_DEMO_H__
#include <pthread.h>

extern int LEDSTATE[4];
void * MQTTinit(void);
extern pthread_t g_mqtt_tid ;



#endif // __MQTT_C_DEMO_H__