#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <orbis/Sysmodule.h>
#include <orbis/libkernel.h>
#include <orbis/SystemService.h>
#include <orbis/Pigletv2Vsh.h>
#include <orbis/SaveData.h>

#define APP_NAME        "3bodli Tools"
#define APP_VERSION     "v1.0"
#define APP_AUTHOR      "3bodli"

// 🎨 نوع الثيم
typedef enum {
    THEME_DARK = 0,
    THEME_LIGHT = 1
} ThemeMode;

// 📱 هيكل الثيم - بيتغير حسب الاختيار
typedef struct {
    unsigned int bg_primary;      // الخلفية الرئيسية
    unsigned int bg_secondary;    // الخلفية الثانوية
    unsigned int bg_card;         // خلفية الكروت
    unsigned int bg_card_hover;   // خلفية الكروت عند التحويم
    unsigned int accent;          // اللون الرئيسي المميز
    unsigned int accent_light;    // اللون المميز الفاتح
    unsigned int gradient_1;      // لون تدرج 1
    unsigned int gradient_2;      // لون تدرج 2
    unsigned int text_primary;    // النص الأساسي
    unsigned int text_secondary;  // النص الثانوي
    unsigned int success;         // أخضر - نجاح
    unsigned int warning;         // برتقالي - تحذير
    unsigned int danger;          // أحمر - خطر
    unsigned int cpu_color;       // لون CPU
    unsigned int gpu_color;       // لون GPU
    unsigned int ram_color;       // لون RAM
    unsigned int divider;         // لون الفواصل
    unsigned int input_bg;        // خلفية المدخلات
    unsigned int input_border;    // حدود المدخلات
    unsigned int shadow;          // لون الظل
    unsigned int header_bg;       // خلفية الهيدر
    unsigned int sidebar_bg;      // خلفية الشريط الجانبي
} ThemeColors;

// 📐 أبعاد الواجهة
#define CARD_RADIUS         15
#define CARD_PADDING        25
#define CARD_MARGIN         20
#define DASHBOARD_PADDING   60
#define HEADER_HEIGHT       80
#define PROGRESS_BAR_HEIGHT 8
#define FONT_SMALL          18
#define FONT_MEDIUM         24
#define FONT_LARGE          32
#define FONT_XLARGE         48

// 📊 الصفحات
#define PAGE_OVERVIEW       0
#define PAGE_TEMPERATURE    1
#define PAGE_MEMORY         2
#define PAGE_SYSTEM         3
#define PAGE_SETTINGS       4

#endif
