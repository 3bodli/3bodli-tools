#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <orbis/Sysmodule.h>
#include <orbis/libkernel.h>
#include <orbis/SystemService.h>

#define APP_NAME        "3bodli Tools"
#define APP_VERSION     "1.0.0"
#define APP_AUTHOR      "3bodli"

// ألوان الواجهة
#define COLOR_BG        0xFF1A1A2E
#define COLOR_TEXT      0xFFE0E0E0
#define COLOR_ACCENT    0xFF00D2FF
#define COLOR_WARNING   0xFFFF6B35
#define COLOR_DANGER    0xFFFF4444
#define COLOR_SUCCESS   0xFF00C853

// تعريفات النظام
#define TEMP_CPU        0
#define TEMP_SOC        1
#define TEMP_GDDR       2

#endif
