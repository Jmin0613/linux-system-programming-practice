#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct person{
	char name[16];
	int age;
};

static int write_info(struct person *p){
	int fd;
	ssize_t ret;
	
	// 파일 열기 
	fd = open("person_info", O_CREAT | O_WRONLY | O_APPEND, 0644);

	if(fd == -1){
		printf("open() fail\n");
		return -1;
	}

	// 파일 작성 
	ret = write(fd, p, sizeof(struct person));

	if(ret == -1){ // 실패 시 
		printf("write() fail\n");
		close(fd);
		return -1;
	} else if(ret != sizeof(struct person)){ // 일부분만 write된 경우 
		printf("write() fail(partial write)\n");
		close(fd);
		return -1;
	}

	close(fd);

	return 0;
}

static int dump_info(){
	int fd;
	ssize_t ret;
	struct person p;

	fd = open("person_info", O_RDONLY);

	if(fd == -1){
		printf("open() fail\n");
		return -1;
	}

	// 파일 읽기 
	do{
		ret = read(fd, &p, sizeof(struct person));

		if(ret == -1){
			printf("read() fail\n");
			close(fd);
			return -1;
		} else if(ret == 0 ){ // EOF 
			// fdopen() 호출하여 fd -> ptr 변환 
			FILE *fp;
			fp = fdopen(fd, "r");

			if(fp == NULL){
				printf("fdopen() fail\n");
				close(fd);
				return -1;
			}

			printf("file postion = %ld\n", ftell(fp));
			fclose(fp);
			break;
		} else if(ret != sizeof(struct person)){
			printf("read() fail(partial read)\n");
			close(fd);
			return -1;
		}

		printf("name: %s, age: %d\n", p.name, p.age);

	} while(1);

	close(fd);
	return 0;
}

int main(int argc, char **argv){
	struct person persons[] = {
		{"kim", 32},
		{"oh", 31}
	};

	write_info(&persons[0]);
	write_info(&persons[1]);

	dump_info();

	return 0;
}
