#ifndef __WEATHER_H__
#define __WEATHER_H__
#include "ui.h"
#include "http.h"
#include "cJSON.h"


#define WEATHER_URL "http://apis.juhe.cn/simpleWeather/query"
#define KEY "修改为你的key" //申请的key

#ifndef __WEATHERVALUE_H__
#define __WEATHERVALUE_H__


extern char cityname[32];
#endif // __WEATHERVALUE_H__

void getWeather(char* city);


#endif // __WEATHER_H__
