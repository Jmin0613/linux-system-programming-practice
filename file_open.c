#include <stdio.h>
#include <string.h>

int write_to_file(){
	FILE *fp; //파일 포인터 
	
	fp = fopen("data", "w"); //쓰기 모드 
	if(fp == NULL){ //실패시 
		perror("fopen error\n");
		return -1;
	}

	//파일 열기 성공시 
	fputs("hello world", fp); //파일 작성 
	fclose(fp);

	return 0;
}

int read_from_file(){
	FILE *fp;
	char buf[1024];

	fp = fopen("data", "r"); // 읽기 모드
	if(fp == NULL){
		perror("fopen error\n");
		return -1;
	}

	memset(buf, 0, sizeof(buf)); // 버퍼 초기화 
	fgets(buf, sizeof(buf), fp); // 파일 읽어오기 
	fclose(fp);

	printf("%s\n", buf);

	return 0;

}

int main(int argc, char **argv){
	if (write_to_file()){
		perror("write_to_file\n");
		return -1;
	}

	if (read_from_file()){
		perror("read to file\n");
		return -1;
	}

	return 0;
}


