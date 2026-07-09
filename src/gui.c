#include "gui.h"
#include <orbis/Pigletv2Vsh.h>
#include <orbis/SaveData.h>

// متغيرات عامة للواجهة
static int screen_width = 1920;
static int screen_height = 1080;
static int current_page = 0;

int init_gui(void) {
    // تهيئة مكتبة الرسوميات
    scePigletv2VshInitialize();
    
    // مسح الشاشة باللون الخلفي
    scePigletv2VshClear(COLOR_BG);
    
    return 0;
}

int update_gui(SystemInfo* sys_info, TemperatureInfo* temp_info) {
    // رسم الهيدر
    draw_header();
    
    // رسم معلومات النظام
    draw_system_info(sys_info);
    
    // رسم درجات الحرارة
    draw_temperature(temp_info);
    
    // رسم استخدام الذاكرة
    draw_memory_usage(sys_info);
    
    return 0;
}

int draw_header(void) {
    // رسم عنوان التطبيق
    scePigletv2VshDrawText(50, 30, APP_NAME, COLOR_ACCENT, 3);
    scePigletv2VshDrawText(50, 70, APP_VERSION, COLOR_TEXT, 1);
    scePigletv2VshDrawText(1600, 30, "By 3bodli", COLOR_TEXT, 1);
    
    // رسم خط فاصل
    scePigletv2VshDrawRect(50, 100, 1820, 2, COLOR_ACCENT);
    
    return 0;
}

int draw_system_info(SystemInfo* info) {
    int y = 150;
    char buffer[256];
    
    // عنوان القسم
    scePigletv2VshDrawText(50, y, "System Information", COLOR_ACCENT, 2);
    y += 50;
    
    // معلومات النظام
    sprintf(buffer, "Model: %s", info->model);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 35;
    
    sprintf(buffer, "Firmware: %s", info->firmware);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 35;
    
    sprintf(buffer, "CPU: %d MHz (%d Cores)", info->cpu_freq, info->cpu_cores);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 35;
    
    return y;
}

int draw_temperature(TemperatureInfo* temp) {
    int y = 450;
    char buffer[128];
    
    // عنوان القسم
    scePigletv2VshDrawText(50, y, "Temperature Monitor", COLOR_ACCENT, 2);
    y += 50;
    
    // CPU Temperature مع تلوين حسب القيمة
    unsigned int color = COLOR_SUCCESS;
    if (temp->cpu_temp > 70) color = COLOR_DANGER;
    else if (temp->cpu_temp > 60) color = COLOR_WARNING;
    
    sprintf(buffer, "CPU: %.1f°C", temp->cpu_temp);
    scePigletv2VshDrawText(70, y, buffer, color, 2);
    y += 45;
    
    // SOC Temperature
    color = COLOR_SUCCESS;
    if (temp->soc_temp > 65) color = COLOR_DANGER;
    else if (temp->soc_temp > 55) color = COLOR_WARNING;
    
    sprintf(buffer, "SOC: %.1f°C", temp->soc_temp);
    scePigletv2VshDrawText(70, y, buffer, color, 2);
    y += 45;
    
    // GDDR Temperature
    color = COLOR_SUCCESS;
    if (temp->gddr_temp > 60) color = COLOR_DANGER;
    else if (temp->gddr_temp > 50) color = COLOR_WARNING;
    
    sprintf(buffer, "GDDR: %.1f°C", temp->gddr_temp);
    scePigletv2VshDrawText(70, y, buffer, color, 2);
    y += 45;
    
    // Fan Speed
    sprintf(buffer, "Fan: %d%% (%d RPM)", temp->fan_speed, temp->fan_rpm);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 45;
    
    return y;
}

int draw_memory_usage(SystemInfo* info) {
    int y = 750;
    char buffer[128];
    
    // عنوان القسم
    scePigletv2VshDrawText(50, y, "Memory Usage", COLOR_ACCENT, 2);
    y += 50;
    
    // RAM Usage
    sprintf(buffer, "RAM: %dMB / %dMB (%d%% Used)", 
            info->used_ram, info->total_ram,
            (info->used_ram * 100) / info->total_ram);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 35;
    
    // VRAM Usage
    sprintf(buffer, "VRAM: %dMB Available", info->total_vram);
    scePigletv2VshDrawText(70, y, buffer, COLOR_TEXT, 1);
    y += 35;
    
    // شريط استخدام الذاكرة
    int bar_width = 800;
    int bar_height = 30;
    int bar_x = 70;
    int bar_y = y + 20;
    
    // خلفية الشريط
    scePigletv2VshDrawRect(bar_x, bar_y, bar_width, bar_height, 0xFF333333);
    
    // الجزء المستخدم
    int used_width = (info->used_ram * bar_width) / info->total_ram;
    unsigned int bar_color = COLOR_ACCENT;
    if (info->used_ram > info->total_ram * 0.8) bar_color = COLOR_DANGER;
    scePigletv2VshDrawRect(bar_x, bar_y, used_width, bar_height, bar_color);
    
    return y + 60;
}

int handle_input(void) {
    // معالجة أزرار التحكم
    // زر O للخروج
    // زر X للتأكيد
    
    // في الواقع تحتاج لاستخدام مكتبة pad
    return 1; // استمرار التشغيل
}

void close_gui(void) {
    // تنظيف وإغلاق الواجهة
}
