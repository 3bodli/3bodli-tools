#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "common.h"
#include "theme.h"
#include "sysinfo.h"
#include "temperature.h"

void init_dashboard(void);
void draw_modern_header(void);
void draw_overview_page(SystemInfo* sys, TemperatureInfo* temp);
void draw_settings_page(void);

#endif
