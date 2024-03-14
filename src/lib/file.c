//
// Created by bigfoot on 2024/3/14.
//

#include<err.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<inttypes.h>

ssize_t file_read_buff(char*buff,size_t len,const char*file){
	int fd;
	ssize_t s;
	memset(buff,0,len);
	if((fd=open(file,O_RDONLY))<0){
		warn("open %s failed",file);
		return -1;
	}
	if((s=read(fd,buff,len))<0)
		warn("read %s failed",file);
	close(fd);
	return s;
}

ssize_t file_read_buff_v(char*buff,size_t len,const char*file,va_list va){
	char path[4096];
	memset(path,0,sizeof(path));
	vsnprintf(path,sizeof(path)-1,file,va);
	return file_read_buff(buff,len,path);
}

ssize_t file_read_buff_f(char*buff,size_t len,const char*file,...){
	va_list va;
	va_start(va,file);
	ssize_t r=file_read_buff_v(buff,len,file,va);
	va_end(va);
	return r;
}

int file_read_uint64_v(uint64_t*out,const char*file,va_list va){
	char buff[256],*end=NULL;
	if(!out)return -1;
	*out=0,errno=ERANGE;
	ssize_t r=file_read_buff_v(buff,sizeof(buff),file,va);
	if(r<=0)return -1;
	errno=0,*out=strtoull(buff,&end,0);
	if(!end||*end||end==buff||errno!=0){
		warnx("parse %s failed",file);
		return -1;
	}
	return 0;
}

int file_read_uint64_f(uint64_t*out,const char*file,...){
	va_list va;
	va_start(va,file);
	int r=file_read_uint64_v(out,file,va);
	va_end(va);
	return r;
}

ssize_t file_write_buff(const char*buff,size_t len,const char*file){
	int fd;
	ssize_t s;
	if((fd=open(file,O_WRONLY))<0){
		warn("open %s failed",file);
		return -1;
	}
	if((s=write(fd,buff,len))<0)
		warn("write %s failed",file);
	close(fd);
	return s;
}

ssize_t file_write_buff_v(const char*buff,size_t len,const char*file,va_list va){
	char path[4096];
	memset(path,0,sizeof(path));
	vsnprintf(path,sizeof(path)-1,file,va);
	return file_write_buff(buff,len,path);
}

ssize_t file_write_buff_f(const char*buff,size_t len,const char*file,...){
	va_list va;
	va_start(va,file);
	ssize_t r=file_write_buff_v(buff,len,file,va);
	va_end(va);
	return r;
}

int file_write_uint64_v(uint64_t out,const char*file,va_list va){
	char buff[256];
	memset(buff,0,sizeof(buff));
	snprintf(buff,sizeof(buff)-1,"%"PRIu64,out);
	return file_write_buff_v(buff,strlen(buff),file,va);
}

int file_write_uint64_f(uint64_t out,const char*file,...){
	va_list va;
	va_start(va,file);
	int r=file_write_uint64_v(out,file,va);
	va_end(va);
	return r;
}
