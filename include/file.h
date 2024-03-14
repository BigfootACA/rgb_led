//
// Created by bigfoot on 2024/3/14.
//

#ifndef RGB_LED_FILE_H
#define RGB_LED_FILE_H
#ifdef __cplusplus
extern "C"{
#endif
#include<stdarg.h>
#include<stdint.h>
#include<stdlib.h>
extern ssize_t file_read_buff(char*buff,size_t len,const char*file);
extern ssize_t file_read_buff_v(char*buff,size_t len,const char*file,va_list va);
extern ssize_t file_read_buff_f(char*buff,size_t len,const char*file,...);
extern int file_read_uint64_v(uint64_t*out,const char*file,va_list va);
extern int file_read_uint64_f(uint64_t*out,const char*file,...);
extern ssize_t file_write_buff(const char*buff,size_t len,const char*file);
extern ssize_t file_write_buff_v(const char*buff,size_t len,const char*file,va_list va);
extern ssize_t file_write_buff_f(const char*buff,size_t len,const char*file,...);
extern int file_write_uint64_v(uint64_t out,const char*file,va_list va);
extern int file_write_uint64_f(uint64_t out,const char*file,...);
#ifdef __cplusplus
};
#endif
#endif
