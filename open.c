#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int append_file(){
	int fd;
	fd = open("datafile", O_WRONLY | O_APPEND);

	if(fd == -1){
		printf("open() error\n");
		return -1;
	}	

	// append로 덧붙이기 
	dprintf(fd, "hello again!\n");

	close(fd);
	return 0;
}

static int trunc_file(){
	int fd;
	fd = open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	
	if(fd == -1){
		printf("open() error\n");
		return -1;
	}

	// TRUNC로 기존 내용 삭제 후 다시 작성 
	dprintf(fd, "byebye file\n");

	close(fd);
	return 0;
}

static int write_file(){
	// 파일 생성하며 열기 + 쓰기 권한 요청 
	int fd;
	fd = open("datafile", O_WRONLY | O_CREAT, 0644); // RWX/R--/R-- 
							
	if(fd == -1){
		printf("open() error\n");
		return -1;
	}
	
	dprintf(fd, "hello world! %d\n", 123);

	close(fd); // 닫기 
	return 0;
}

int main(int argc, char **argv){
	if(write_file()){
		printf("write_file() error\n");
		return -1;
	}

	if(trunc_file()){
		printf("trunc_file() error\n");
		return -1;
	}

	if(append_file()){
		printf("append_file() error\n");
		return -1;
	}

	return 0;
}
