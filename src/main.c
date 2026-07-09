#include "common.h"
#include "gui.h"
#include "sysinfo.h"
#include "temperature.h"

int main(void) {
    SystemInfo sys_info;
    TemperatureInfo temp_info;
    int running = 1;
    
    // تهيئة النظام
    sceSysmoduleLoadModule(SCE_SYSMODULE_INTERNAL_SYS_CORE);
    
    // تهيئة الواجهة
    if (init_gui() < 0) {
        return -1;
    }
    
    // الحلقة الرئيسية
    while (running) {
        // تحديث معلومات النظام
        get_system_info(&sys_info);
        get_temperature_info(&temp_info);
        
        // تحديث الواجهة
        update_gui(&sys_info, &temp_info);
        
        // معالجة المدخلات
        if (handle_input() == 0) {
            running = 0;
        }
        
        // انتظار 500 مللي ثانية
        sceKernelUsleep(500000);
    }
    
    close_gui();
    return 0;
}
