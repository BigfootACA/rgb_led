/*
 *
 * Copyright (C) 2023 BigfootACA <bigfoot@classfun.cn>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 *
 * Path process functions
 *
 */

#ifndef CONDASH_PATH_CPP
#define CONDASH_PATH_CPP
#ifndef __cplusplus
#include<stddef.h>
#else
#include<cstddef>
#include<string>
#include<climits>
extern "C"{
#endif
extern size_t path_resolve(char*buff,size_t size,char sep,const char*path);
extern size_t path_merge(char*buff,size_t size,char sep,const char*path1,const char*path2);
extern const char*path_basename(char*buff,size_t size,const char*path,size_t len);
extern const char*path_dirname(char*buff,size_t size,const char*path,size_t len);
extern const char*path_get_self(char*buff,size_t size);
extern const char*path_get_self_folder(char*buff,size_t size);
#ifdef __cplusplus
};
static inline std::string path_resolve(char sep,std::string path){
	char buff[PATH_MAX];
	size_t r=::path_resolve(
		buff,sizeof(buff),
		sep,path.c_str()
	);
	return std::string(buff,r);
}
static inline std::string path_merge(char sep,std::string path1,std::string path2){
	char buff[PATH_MAX];
	size_t r=::path_merge(
		buff,sizeof(buff),sep,
		path1.c_str(),path2.c_str()
	);
	return std::string(buff,r);
}
static inline std::string path_basename(std::string path){
	char buff[PATH_MAX];
	return std::string(::path_basename(
		buff,sizeof(buff),
		path.c_str(),path.length()
	));
}
static inline std::string path_dirname(std::string path){
	char buff[PATH_MAX];
	return std::string(::path_dirname(
		buff,sizeof(buff),
		path.c_str(),path.length()
	));
}
static inline std::string path_get_self(void){
	char buff[PATH_MAX];
	return std::string(::path_get_self(buff,sizeof(buff)));
}
static inline std::string path_get_self_folder(void){
	char buff[PATH_MAX];
	return std::string(::path_get_self_folder(buff,sizeof(buff)));
}
#endif
#endif
