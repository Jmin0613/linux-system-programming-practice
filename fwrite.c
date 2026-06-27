#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person{
	char name[20];
	int age;
};

static int  write_to_file(){
	FILE *fp = NULL;

	// 구조체 
	struct person kim = {
		.name = "kim", .age = 20
	};
	struct person lee = {
		.name = "lee", .age = 26
	};

	if(!(fp = fopen("persons", "w"))){
		return -1; // NULL
	}

	// 파일에 구조체 저장 
	if(fwrite(&kim, sizeof(struct person), 1, fp) != 1){
		goto err;
	}
	if(fwrite(&lee, sizeof(struct person), 1, fp) != 1){
		goto err;
	}

	fclose(fp);

	return 0;

err :
	if(fp){
		fclose(fp);
	}
}

static int read_from_file(){
	FILE *fp;
	int i;
	struct person persons[2];

	if(!(fp = fopen("persons", "r"))){
		return -1;
	}

	//파일 읽어오기 
	if(fread(persons, sizeof(struct person), 2, fp) != 2){
		fclose(fp);
		return -1;
	}

	fclose(fp);

	// 읽어온 구조체 정보 출력 
	for(i = 0; i < 2; i++){
		printf("name: %s, age: %d\n", persons[i].name, persons[i].age);
	}

	return 0;
}

int main(int argc, char **argv){
	// 작성 
	if(write_to_file()){
		printf("write fail\n");
		return -1;
	}

	// 읽기 
	if(read_from_file()){
		printf("read fail\n");
		return -1;
	}

	return 0;
}
