#ifndef TEMPERATURE_H
#define TEMPERATURE_H

typedef struct {
    float cpu_temp;
    float soc_temp;
    float gddr_temp;
    int fan_speed;
    int fan_rpm;
} TemperatureInfo;

int init_temperature_monitor(void);
int get_temperature_info(TemperatureInfo* temp);
int set_fan_speed(int percentage);

#endif
