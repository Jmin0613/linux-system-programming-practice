#include <stdio.h>
#include <string.h>

static int create_file(){
	FILE *fp;

	if(!(fp = fopen("datafile", "w"))){
		printf("fopen() fail\n");
		return -1;
	}

	// 파일 열었을 때의 포지션 값 확인 
	printf("after fopen(). offset =  %ld\n", ftell(fp));

	// 파일 내용 작성 
	fputs("hello world\n", fp);
	fputs("hello world!\n", fp);
	fputs("hello world!!\n", fp);
	fputs("hello world!!!\n", fp);

	// 파일 작성 후 포지션 값 확인  
	printf("before fclose. offset = %ld\n", ftell(fp));

	printf("----------------------------------------\n");

	fclose(fp);

	return 0;
}

static int read_file(){
	FILE *fp;
	char buf[1024];

	if(!(fp = fopen("datafile","r+"))){
		printf("fopen() fail\n");
		return -1;
	}

	// 파일 열었을 때 포지션 값 확인
	printf("after fopen(). offset = %ld\n", ftell(fp));

	// 한줄 읽기 
	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), fp);
	printf("after fgets(). offset = %ld\n", ftell(fp));

	// 파일 끝으로 이동 
	fseek(fp, 0, SEEK_END);
	printf("after fseek(). offset = %ld\n", ftell(fp));
	fputs("final\n", fp); // 파일 작성 
	printf("before fclose(). offset = %ld\n", ftell(fp));

	printf("----------------------------------------\n");

	fclose(fp);

	return 0;
}


int main(int argc, char **argv){
	create_file();

	read_file();

	return 0;
}
