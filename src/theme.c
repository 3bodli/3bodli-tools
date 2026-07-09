#include "theme.h"
#include <orbis/SaveData.h>

// 📂 ملف حفظ إعدادات الثيم
#define THEME_CONFIG_FILE "/data/3bodli_tools/theme.cfg"

// 🌙 الثيم الغامق (Dark)
const ThemeColors dark_theme = {
    .bg_primary     = 0xFF0A0A1A,  // أسود مزرق عميق
    .bg_secondary   = 0xFF0F0F25,  // أزرق غامق جداً
    .bg_card        = 0xFF1A1A2E,  // كحلي غامق
    .bg_card_hover  = 0xFF252545,  // كحلي فاتح
    .accent         = 0xFF6C63FF,  // بنفسجي مميز
    .accent_light   = 0xFF8B83FF,  // بنفسجي فاتح
    .gradient_1     = 0xFF00D2FF,  // أزرق ساطع
    .gradient_2     = 0xFF6C63FF,  // بنفسجي
    .text_primary   = 0xFFFFFFFF,  // أبيض ناصع
    .text_secondary = 0xFFB0B0CC,  // رمادي فاتح
    .success        = 0xFF00E676,  // أخضر
    .warning        = 0xFFFF9100,  // برتقالي
    .danger         = 0xFFFF1744,  // أحمر
    .cpu_color      = 0xFF00D2FF,  // أزرق
    .gpu_color      = 0xFF6C63FF,  // بنفسجي
    .ram_color      = 0xFFFF9100,  // برتقالي
    .divider        = 0xFF2A2A4A,  // خط فاصل غامق
    .input_bg       = 0xFF1A1A2E,  // خلفية إدخال
    .input_border   = 0xFF3A3A5A,  // حدود إدخال
    .shadow         = 0x60000000,  // ظل أسود شفاف
    .header_bg      = 0xFF0D0D22,  // هيدر غامق
    .sidebar_bg     = 0xFF0D0D20   // شريط جانبي غامق
};

// ☀️ الثيم الفاتح (Light)
const ThemeColors light_theme = {
    .bg_primary     = 0xFFF0F2F5,  // رمادي فاتح جداً
    .bg_secondary   = 0xFFF8F9FA,  // أبيض مائل للرمادي
    .bg_card        = 0xFFFFFFFF,  // أبيض ناصع
    .bg_card_hover  = 0xFFF5F5FF,  // أبيض بنفسجي خفيف
    .accent         = 0xFF6C63FF,  // بنفسجي (نفس اللون للتميز)
    .accent_light   = 0xFF8B83FF,  // بنفسجي فاتح
    .gradient_1     = 0xFF00B4D8,  // أزرق محيطي
    .gradient_2     = 0xFF6C63FF,  // بنفسجي
    .text_primary   = 0xFF1A1A2E,  // أسود مزرق (للقراءة)
    .text_secondary = 0xFF6E6E8A,  // رمادي متوسط
    .success        = 0xFF00C853,  // أخضر غامق
    .warning        = 0xFFFF6D00,  // برتقالي غامق
    .danger         = 0xFFD50000,  // أحمر غامق
    .cpu_color      = 0xFF0091EA,  // أزرق
    .gpu_color      = 0xFF6C63FF,  // بنفسجي
    .ram_color      = 0xFFFF6D00,  // برتقالي
    .divider        = 0xFFE0E0E0,  // خط فاصل فاتح
    .input_bg       = 0xFFF5F5F5,  // خلفية إدخال فاتحة
    .input_border   = 0xFFD0D0E0,  // حدود فاتحة
    .shadow         = 0x10000000,  // ظل خفيف جداً
    .header_bg      = 0xFFFFFFFF,  // هيدر أبيض
    .sidebar_bg     = 0xFFF5F5FA   // شريط جانبي فاتح
};

// 🎨 الثيم الحالي (يبدأ بالغامق افتراضياً)
ThemeColors* current_theme = (ThemeColors*)&dark_theme;
ThemeMode current_mode = THEME_DARK;

// 🌓 تبديل الثيم
void toggle_theme(void) {
    if (current_mode == THEME_DARK) {
        current_theme = (ThemeColors*)&light_theme;
        current_mode = THEME_LIGHT;
    } else {
        current_theme = (ThemeColors*)&dark_theme;
        current_mode = THEME_DARK;
    }
    save_theme_config();
    apply_theme();
}

// 💾 حفظ إعدادات الثيم
void save_theme_config(void) {
    sceSaveDataInitialize();
    
    int fd = sceKernelOpen(THEME_CONFIG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd >= 0) {
        sceKernelWrite(fd, &current_mode, sizeof(ThemeMode));
        sceKernelClose(fd);
    }
}

// 📂 تحميل إعدادات الثيم
void load_theme_config(void) {
    sceSaveDataInitialize();
    
    int fd = sceKernelOpen(THEME_CONFIG_FILE, O_RDONLY, 0);
    if (fd >= 0) {
        ThemeMode saved_mode;
        if (sceKernelRead(fd, &saved_mode, sizeof(ThemeMode)) > 0) {
            if (saved_mode == THEME_LIGHT) {
                current_theme = (ThemeColors*)&light_theme;
                current_mode = THEME_LIGHT;
                return;
            }
        }
        sceKernelClose(fd);
    }
    
    // افتراضي غامق
    current_theme = (ThemeColors*)&dark_theme;
    current_mode = THEME_DARK;
}

// 🎨 تطبيق الثيم على الواجهة
void apply_theme(void) {
    // مسح الشاشة بلون الخلفية الجديد
    scePigletv2VshClear(current_theme->bg_primary);
    
    // إعادة رسم كل العناصر
    // (راح يتم استدعاؤها من dashboard)
}

// 🎨 دوال الرسم المساعدة
void draw_gradient_rect(int x, int y, int w, int h, unsigned int color1, unsigned int color2) {
    for (int i = 0; i < h; i++) {
        float ratio = (float)i / h;
        unsigned int r1 = (color1 >> 16) & 0xFF, g1 = (color1 >> 8) & 0xFF, b1 = color1 & 0xFF;
        unsigned int r2 = (color2 >> 16) & 0xFF, g2 = (color2 >> 8) & 0xFF, b2 = color2 & 0xFF;
        
        unsigned int r = (unsigned int)(r1 * (1 - ratio) + r2 * ratio);
        unsigned int g = (unsigned int)(g1 * (1 - ratio) + g2 * ratio);
        unsigned int b = (unsigned int)(b1 * (1 - ratio) + b2 * ratio);
        
        scePigletv2VshDrawRect(x, y + i, w, 1, (0xFF << 24) | (r << 16) | (g << 8) | b);
    }
}

void draw_rounded_rect(int x, int y, int w, int h, int radius, unsigned int color) {
    scePigletv2VshDrawRect(x + radius, y, w - 2 * radius, h, color);
    scePigletv2VshDrawRect(x, y + radius, w, h - 2 * radius, color);
    
    for (int i = 0; i < radius; i++) {
        int offset = (int)sqrt(radius * radius - (radius - i) * (radius - i));
        scePigletv2VshDrawRect(x + radius - offset, y + i, 2 * offset, 1, color);
        scePigletv2VshDrawRect(x + radius - offset, y + h - i - 1, 2 * offset, 1, color);
    }
}

void draw_card(int x, int y, int w, int h) {
    // ظل
    draw_rounded_rect(x + 3, y + 3, w, h, CARD_RADIUS, current_theme->shadow);
    // الكرت نفسه
    draw_rounded_rect(x, y, w, h, CARD_RADIUS, current_theme->bg_card);
    // حدود خفيفة
    draw_rounded_rect(x, y, w, h, CARD_RADIUS, current_theme->divider);
    // رسم الحدود مرة أخرى بلون شفاف للتأثير
}

void draw_progress_bar(int x, int y, int w, int h, float progress, 
                       unsigned int fill_color) {
    // خلفية شريط التقدم
    draw_rounded_rect(x, y, w, h, h/2, current_theme->input_bg);
    draw_rounded_rect(x, y, w, h, h/2, current_theme->divider);
    
    // الجزء الممتلئ
    int fill_w = (int)(w * progress);
    if (fill_w > 0) {
        draw_rounded_rect(x, y, fill_w, h, h/2, fill_color);
        // لمعان
        draw_rounded_rect(x, y, fill_w, h/2, h/4, 0x30FFFFFF);
    }
}

unsigned int get_temp_color(float temp) {
    if (temp < 50) return current_theme->success;
    if (temp < 65) return current_theme->warning;
    return current_theme->danger;
}
