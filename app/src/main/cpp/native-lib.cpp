#include <jni.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <android/log.h>

#define LOG_TAG "C++ TAG"

uint64_t test(){
    uint32_t a,d;
    asm volatile ("mfence");
    asm volatile ("rdtsc" : "=a" (a), "=d" (d));
    uint64_t time;
    time = (d<<32) | a;
    asm volatile ("mfence");
    return time;
}

uint64_t min(uint64_t a, uint64_t b){
    return (a<=b)?a:b;
}

void maccess(void *p)
{
    asm volatile ("movl (%0), %%eax\n"
        :
        : "c" (p)
        : "eax");
}

void flush(void* p) {
    asm volatile ("clflush 0(%0)\n"
        :
        : "c" (p)
        : "eax");
}

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_prakhar_cppapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    char hello[5] = "yoyo";
//    hello = (char *)malloc(10000);
//    size_t array[5*1024];
//    uint64_t hit_hist[200] = {0};
//    uint64_t xx[201] = {0};
//    memset(array, -1, 5*1024* sizeof(size_t));
//    printf("%d", a);
//    maccess(array+2*1024);
//    sched_yield();

    int fd = open("/sdcard/Download/test.txt", O_RDONLY);
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "fd is %d\n", fd);
    unsigned char* addr = (unsigned char*)mmap(0, 64*1024, PROT_READ, MAP_SHARED, fd, 0);

    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "TESTING LOG TAG. IS IT REALLY WORKING. WHERE IS IT?");
    for (int i = 0; i < 1024*1024*0; ++i) {
        uint64_t start = test();
//        maccess(array+2*1024);
        maccess(addr+8);
        uint64_t end = test();
        uint64_t d = end - start;
        flush(addr+8);
//        hit_hist[min((uint64_t)199, d/5)]++;
        if (d < 205 && d > 0)
        {
            __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%lu,%lu: Cache Hit (%lu cycles)\n",start, start, d);
        }
        for (int j = 0; j < 3; ++j) {
            sched_yield();
        }
    }
//    flush(array + 2*1024);
    sched_yield();
//    for (int i = 0; i < 1024; ++i) {
//        uint64_t start = test();
//        maccess(array + 2*1024);
//        uint64_t end = test();
//        flush(array + 2*1024);
//        uint64_t d = end - start;
//        xx[min((uint64_t)199, d/5)]=1;
//        sched_yield();
//    }
//    int dist = 0;
//    for (int i = 0; i < 200; ++i) {
//        dist = sprintf(hello+dist, "%d\t%lu,",i*5, hit_hist[i]);
//        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%d\t%lu\t%lu",i*5, hit_hist[i], xx[i]);
//    }
//    hello[0] = 's';
    return env->NewStringUTF(hello);
}

