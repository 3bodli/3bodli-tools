#ifndef GUI_H
#define GUI_H

#include "common.h"
#include "sysinfo.h"
#include "temperature.h"

int init_gui(void);
int update_gui(SystemInfo* sys_info, TemperatureInfo* temp_info);
int draw_header(void);
int draw_system_info(SystemInfo* info);
int draw_temperature(TemperatureInfo* temp);
int draw_memory_usage(SystemInfo* info);
int handle_input(void);
void close_gui(void);

#endif
