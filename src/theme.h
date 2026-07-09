#ifndef THEME_H
#define THEME_H

#include "common.h"

// الثيم الحالي
extern ThemeColors* current_theme;
extern ThemeMode current_mode;

// دوال الثيم
void toggle_theme(void);
void save_theme_config(void);
void load_theme_config(void);
void apply_theme(void);

// دوال الرسم
void draw_gradient_rect(int x, int y, int w, int h, unsigned int color1, unsigned int color2);
void draw_rounded_rect(int x, int y, int w, int h, int radius, unsigned int color);
void draw_card(int x, int y, int w, int h);
void draw_progress_bar(int x, int y, int w, int h, float progress, unsigned int fill_color);
unsigned int get_temp_color(float temp);

#endif
