#include "sysinfo.h"
#include "common.h"
#include <sys/sysctl.h>

int get_system_info(SystemInfo* info) {
    if (!info) return -1;
    
    // جلب اسم الموديل
    size_t len = sizeof(info->model);
    sysctlbyname("machdep.model", info->model, &len, NULL, 0);
    
    // جلب إصدار النظام
    len = sizeof(info->firmware);
    sysctlbyname("kern.osrelease", info->firmware, &len, NULL, 0);
    
    // معلومات المعالج
    info->cpu_cores = 8; // PS4 دائماً 8 أنوية
    info->cpu_freq = get_cpu_frequency();
    
    // معلومات الذاكرة
    get_memory_info(&info->total_ram, &info->used_ram, &info->free_ram);
    
    // معلومات الذاكرة الرسومية (عادة 8GB للنظام كامل)
    info->total_vram = 5500; // حوالي 5.5GB متاحة للألعاب
    
    return 0;
}

int get_cpu_frequency(void) {
    unsigned int freq = 0;
    size_t len = sizeof(freq);
    
    // محاولة قراءة تردد المعالج
    if (sysctlbyname("machdep.xo.cpu_freq", &freq, &len, NULL, 0) < 0) {
        freq = 1600; // القيمة الافتراضية للـ PS4
    }
    
    return freq;
}

int get_memory_info(unsigned int* total, unsigned int* used, unsigned int* free) {
    if (!total || !used || !free) return -1;
    
    // PS4 يحتوي على 8GB GDDR5
    *total = 8192;
    
    // قراءة الذاكرة المستخدمة عبر sysctl
    unsigned int pages_free = 0;
    size_t len = sizeof(pages_free);
    
    if (sysctlbyname("vm.stats.vm.v_free_count", &pages_free, &len, NULL, 0) < 0) {
        // قيمة تقديرية إذا فشلت القراءة
        *free = 2048;
        *used = *total - *free;
        return -1;
    }
    
    // تحويل الصفحات إلى ميجابايت (الصفحة = 16KB في PS4)
    *free = (pages_free * 16) / 1024;
    *used = *total - *free;
    
    return 0;
}
