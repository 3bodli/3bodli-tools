#include "dashboard.h"

void init_dashboard(void) {
    load_theme_config();
    apply_theme();
}

void draw_modern_header(void) {
    // خلفية الهيدر
    draw_gradient_rect(0, 0, 1920, HEADER_HEIGHT, 
                       current_theme->header_bg, current_theme->bg_secondary);
    
    // خط توهج أسفل الهيدر
    draw_gradient_rect(0, HEADER_HEIGHT - 2, 1920, 2,
                       current_theme->accent, current_theme->gradient_1);
    
    // الشعار
    scePigletv2VshDrawText(40, 18, "⚡", FONT_XLARGE, current_theme->accent);
    scePigletv2VshDrawText(100, 15, "3BODLI TOOLS", FONT_LARGE, current_theme->text_primary);
    scePigletv2VshDrawText(100, 52, "System Monitor Dashboard", FONT_SMALL, current_theme->text_secondary);
    
    // الساعة
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm);
    scePigletv2VshDrawText(1750, 20, time_str, FONT_LARGE, current_theme->text_primary);
    
    // زر تبديل الثيم 🌓
    int btn_x = 1550;
    int btn_y = 50;
    draw_rounded_rect(btn_x, btn_y, 60, 30, 15, current_theme->bg_card);
    draw_rounded_rect(btn_x, btn_y, 60, 30, 15, current_theme->divider);
    
    if (current_mode == THEME_DARK) {
        scePigletv2VshDrawText(btn_x + 8, btn_y + 3, "🌙", FONT_SMALL, current_theme->text_primary);
    } else {
        scePigletv2VshDrawText(btn_x + 8, btn_y + 3, "☀️", FONT_SMALL, current_theme->text_primary);
    }
}

void draw_overview_page(SystemInfo* sys, TemperatureInfo* temp) {
    int start_x = 60;
    int start_y = 120;
    int card_w = 430;
    int card_h = 220;
    int gap = 20;
    
    // كرت 1: CPU
    draw_card(start_x, start_y, card_w, card_h);
    scePigletv2VshDrawText(start_x + 25, start_y + 20, "🧠 CPU", FONT_MEDIUM, current_theme->cpu_color);
    
    char buf[64];
    sprintf(buf, "%.1f°C", temp->cpu_temp);
    scePigletv2VshDrawText(start_x + 25, start_y + 65, buf, FONT_XLARGE, get_temp_color(temp->cpu_temp));
    
    sprintf(buf, "%d MHz", sys->cpu_freq);
    scePigletv2VshDrawText(start_x + 25, start_y + 130, buf, FONT_SMALL, current_theme->text_secondary);
    
    draw_progress_bar(start_x + 25, start_y + 170, card_w - 50, PROGRESS_BAR_HEIGHT,
                     temp->cpu_temp / 100.0f, get_temp_color(temp->cpu_temp));
    
    // كرت 2: SOC/GPU
    int card2_x = start_x + card_w + gap;
    draw_card(card2_x, start_y, card_w, card_h);
    scePigletv2VshDrawText(card2_x + 25, start_y + 20, "🎮 SOC/GPU", FONT_MEDIUM, current_theme->gpu_color);
    
    sprintf(buf, "%.1f°C", temp->soc_temp);
    scePigletv2VshDrawText(card2_x + 25, start_y + 65, buf, FONT_XLARGE, get_temp_color(temp->soc_temp));
    
    scePigletv2VshDrawText(card2_x + 25, start_y + 130, "System on Chip", FONT_SMALL, current_theme->text_secondary);
    draw_progress_bar(card2_x + 25, start_y + 170, card_w - 50, PROGRESS_BAR_HEIGHT,
                     temp->soc_temp / 100.0f, get_temp_color(temp->soc_temp));
    
    // كرت 3: RAM
    int row2_y = start_y + card_h + gap;
    draw_card(start_x, row2_y, card_w, card_h);
    scePigletv2VshDrawText(start_x + 25, row2_y + 20, "💾 RAM", FONT_MEDIUM, current_theme->ram_color);
    
    float ram_percent = (float)sys->used_ram / sys->total_ram * 100;
    sprintf(buf, "%.1f%%", ram_percent);
    scePigletv2VshDrawText(start_x + 25, row2_y + 65, buf, FONT_XLARGE, current_theme->text_primary);
    
    sprintf(buf, "%dMB / %dMB", sys->used_ram, sys->total_ram);
    scePigletv2VshDrawText(start_x + 25, row2_y + 130, buf, FONT_SMALL, current_theme->text_secondary);
    
    draw_progress_bar(start_x + 25, row2_y + 170, card_w - 50, PROGRESS_BAR_HEIGHT,
                     ram_percent / 100.0f, current_theme->ram_color);
    
    // كرت 4: FAN
    draw_card(card2_x, row2_y, card_w, card_h);
    scePigletv2VshDrawText(card2_x + 25, row2_y + 20, "🌀 FAN", FONT_MEDIUM, current_theme->accent);
    
    sprintf(buf, "%d%%", temp->fan_speed);
    scePigletv2VshDrawText(card2_x + 25, row2_y + 65, buf, FONT_XLARGE, current_theme->text_primary);
    
    sprintf(buf, "%d RPM", temp->fan_rpm);
    scePigletv2VshDrawText(card2_x + 25, row2_y + 130, buf, FONT_SMALL, current_theme->text_secondary);
    
    draw_progress_bar(card2_x + 25, row2_y + 170, card_w - 50, PROGRESS_BAR_HEIGHT,
                     temp->fan_speed / 100.0f, current_theme->accent);
    
    // كرت 5: GDDR Temperature
    int row3_y = row2_y + card_h + gap;
    draw_card(start_x, row3_y, card_w, card_h);
    scePigletv2VshDrawText(start_x + 25, row3_y + 20, "🔥 GDDR Memory", FONT_MEDIUM, current_theme->warning);
    
    sprintf(buf, "%.1f°C", temp->gddr_temp);
    scePigletv2VshDrawText(start_x + 25, row3_y + 65, buf, FONT_XLARGE, get_temp_color(temp->gddr_temp));
    
    scePigletv2VshDrawText(start_x + 25, row3_y + 130, "Graphics Memory", FONT_SMALL, current_theme->text_secondary);
    draw_progress_bar(start_x + 25, row3_y + 170, card_w - 50, PROGRESS_BAR_HEIGHT,
                     temp->gddr_temp / 100.0f, get_temp_color(temp->gddr_temp));
}

void draw_settings_page(void) {
    int start_x = 60;
    int start_y = 120;
    int card_w = 880;
    int card_h = 500;
    
    draw_card(start_x, start_y, card_w, card_h);
    scePigletv2VshDrawText(start_x + 30, start_y + 25, "⚙️ Settings", FONT_LARGE, current_theme->text_primary);
    
    // خط فاصل
    scePigletv2VshDrawRect(start_x + 30, start_y + 70, card_w - 60, 1, current_theme->divider);
    
    // اختيار الثيم
    scePigletv2VshDrawText(start_x + 30, start_y + 100, "Appearance", FONT_MEDIUM, current_theme->text_primary);
    
    int y = start_y + 145;
    
    // زر الثيم الغامق
    int dark_btn_x = start_x + 30;
    int btn_w = 350;
    int btn_h = 120;
    
    draw_rounded_rect(dark_btn_x, y, btn_w, btn_h, 12, 
                     current_mode == THEME_DARK ? current_theme->accent : current_theme->bg_card);
    draw_rounded_rect(dark_btn_x, y, btn_w, btn_h, 12, current_theme->divider);
    
    scePigletv2VshDrawText(dark_btn_x + 100, y + 25, "🌙", FONT_XLARGE, 
                          current_mode == THEME_DARK ? 0xFFFFFFFF : current_theme->text_primary);
    scePigletv2VshDrawText(dark_btn_x + 35, y + 70, "Dark Mode", FONT_MEDIUM,
                          current_mode == THEME_DARK ? 0xFFFFFFFF : current_theme->text_primary);
    
    // زر الثيم الفاتح
    int light_btn_x = dark_btn_x + btn_w + 30;
    
    draw_rounded_rect(light_btn_x, y, btn_w, btn_h, 12,
                     current_mode == THEME_LIGHT ? current_theme->accent : current_theme->bg_card);
    draw_rounded_rect(light_btn_x, y, btn_w, btn_h, 12, current_theme->divider);
    
    scePigletv2VshDrawText(light_btn_x + 100, y + 25, "☀️", FONT_XLARGE,
                          current_mode == THEME_LIGHT ? 0xFF1A1A2E : current_theme->text_primary);
    scePigletv2VshDrawText(light_btn_x + 35, y + 70, "Light Mode", FONT_MEDIUM,
                          current_mode == THEME_LIGHT ? 0xFF1A1A2E : current_theme->text_primary);
    
    // معلومات التطبيق
    y += 160;
    scePigletv2VshDrawText(start_x + 30, y, "About", FONT_MEDIUM, current_theme->text_primary);
    y += 40;
    
    char info[128];
    sprintf(info, "App: %s %s", APP_NAME, APP_VERSION);
    scePigletv2VshDrawText(start_x + 50, y, info, FONT_SMALL, current_theme->text_secondary);
    y += 30;
    
    sprintf(info, "Author: %s", APP_AUTHOR);
    scePigletv2VshDrawText(start_x + 50, y, info, FONT_SMALL, current_theme->text_secondary);
}
