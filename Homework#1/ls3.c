#define MALLOC(p,s){\
	if(!((p) = malloc(s))){\
		fprintf(stderr,"Insufficient Memory \n");\
		exit(EXIT_FAILURE);\
	}\
}\

#define MAX_STORE 100
#define STRING_SIZE 100
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct{
	char modestr[20];
	int hardLink;
	char* uid_to_name;
	char* gid_to_name;
	long st_size;
	char* lastModifyTime;
	char* filename;
	struct stat* infoPointer;
}File_info;

typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}Time;

char* HOW_TO_SET;

File_info* make_FileInfo(void);
void do_ls(char dirname[]);
File_info* dostat(char* filename);
File_info* take_file_info(char* filename, struct stat* info_p);
void mode_to_letters(int mode, char str[]);
char* uid_to_name(uid_t uid);
char* gid_to_name(gid_t gid);
void sortByArg(File_info ** store, int size);
void sortBySize(File_info** store, int size);
void sortByTime(File_info** store, int size);
void printResult(File_info** store, int size);
int compareTime(char* timeA, char* timeB);
Time* getTime(char* time);
int getMonth(char* month);
char* getSubstring(char* string, int start, int end);

int main(int argc, char* argv[]){
	// -t : 시간순 정렬
	// -b : 파일크기 순 정렬
	MALLOC(HOW_TO_SET, STRING_SIZE * sizeof(*HOW_TO_SET));

	strcpy(HOW_TO_SET,argv[1]);
	
	if(argc == 2){
		do_ls("."); // 바로 여기로(상대경로) 들어감! (argc == 1은 최소한 이쪽으로 들어가니까.)
	}else{
		while(argc-- != 1){
			printf("%s:\n", *++argv); // 이쪽으로 가지는 않았음.
			do_ls(*argv); // argv 에 directory가 들어감. 
		}
	}
	
	return 0;
}
File_info* make_FileInfo(void){
	
	File_info* p;
	MALLOC(p, sizeof(*p));
	
	MALLOC(p->uid_to_name, STRING_SIZE * sizeof(*(p->uid_to_name)));
	MALLOC(p->gid_to_name, STRING_SIZE * sizeof(*(p->gid_to_name)));
	MALLOC(p->lastModifyTime, STRING_SIZE * sizeof(*(p->lastModifyTime)));
	MALLOC(p->filename, STRING_SIZE * sizeof(*(p->filename)));
	MALLOC(p->infoPointer, sizeof(*(p->infoPointer)));
	
	return p;
}
void do_ls(char dirname[]){ // 전반적으로 dirname에 있는 애들을 읽어들임
	// dirname (string) 을 읽어서, readdir한 후, NULL 이 아니면 하나하나 
	// dostat(char* filename) 함수에 던짐. do_ls 안에서, 하나하나 파일을 읽어 처리하는 모양.
	
	DIR* dir_ptr;
	struct dirent* direntp;
	File_info* store[MAX_STORE];// 여기서 잘못된 부분이 있다.
	
	for(int i = 0; i < MAX_STORE; i++){
		MALLOC(store[i], sizeof(*store[i]));
	}
	int fileCount = 0;
	
	if((dir_ptr = opendir(dirname)) == NULL){ 
		fprintf(stderr,"ls2: cannot open %s \n",dirname);
	}else{
		while( (direntp = readdir(dir_ptr)) != NULL){ 
			
			store[fileCount] = dostat(direntp->d_name);
			fileCount++;
		}

		sortByArg(store, fileCount);
		printResult(store,fileCount);
		closedir(dir_ptr);
	}
}
File_info* dostat(char* filename){

	struct stat info; 
	File_info* take_file_info(char*, struct stat*);
	if( stat(filename,&info) == -1){

		perror(filename); 
		return NULL;
	}else{
		File_info* result = take_file_info(filename, &info);
		return result; 
	}
}
File_info* take_file_info(char* filename, struct stat* info_p){ 
	
	File_info* fileInfo = make_FileInfo();

	char *uid_to_name(uid_t);
	char *ctime();
	char *gid_to_name(gid_t);
	
	void mode_to_letters();
	char modestr[20];
	
	mode_to_letters(info_p->st_mode, modestr); 
	strcpy(fileInfo->modestr, modestr);
	fileInfo->hardLink = (int)info_p->st_nlink;
	strcpy(fileInfo->uid_to_name,uid_to_name(info_p->st_uid));
	strcpy(fileInfo->gid_to_name,gid_to_name(info_p->st_gid));
	fileInfo->st_size = (long)info_p->st_size;
	strcpy(fileInfo->lastModifyTime,4 + ctime(&info_p->st_mtime));
	strcpy(fileInfo->filename,filename);
	fileInfo->infoPointer = info_p;

	return fileInfo;
}
void mode_to_letters(int mode, char str[]){
	strcpy(str, "--------------"); 
	
	if(S_ISDIR(mode)) str[0] = 'd'; 
	if(S_ISCHR(mode)) str[0] = 'c'; 
	
	if(S_ISBLK(mode)) str[0] = 'b'; 
	
	if(mode & S_IRUSR) str[1] = 'r'; 
	if(mode & S_IWUSR) str[2] = 'w';  
	if(mode & S_IXUSR) str[3] = 'x';  
	
	if(mode & S_IRGRP) str[4] = 'r'; 
	if(mode & S_IWGRP) str[5] = 'w'; 
	if(mode & S_IXGRP) str[6] = 'x'; 
	
	if(mode & S_IROTH) str[7] = 'r';  
	if(mode & S_IWOTH) str[8] = 'w';  
	if(mode & S_IXOTH) str[9] = 'x';  
}

#include <pwd.h> 
char* uid_to_name(uid_t uid){
	
	struct passwd *getpwuid(), *pw_ptr; 
	static char numstr[10];
	
	if( (pw_ptr = getpwuid(uid)) == NULL){ 
		
		sprintf(numstr, "%d", uid); 
		return numstr;
	}else{
		return pw_ptr->pw_name; 
	}
}

#include <grp.h>
char* gid_to_name(gid_t gid){

	struct group *getgrgid(), *grp_ptr;
	static char numstr[10];
	
	if( (grp_ptr = getgrgid(gid)) == NULL){ 
		
		sprintf(numstr, "%d", gid);
		return numstr;
	}else{
		return grp_ptr->gr_name;
	}
}
void sortByArg(File_info ** store, int size){
	if(!strcmp(HOW_TO_SET,"-b")){
		sortBySize(store,size);
	}else{
		sortByTime(store,size);
	}
}
void sortBySize(File_info** store, int size){
	
	for(int i = 0; i < size; i++){
		int min = __INT_MAX__, index = size+1;
		File_info * temp;

		for(int j = i; j < size; j++){
			if(store[j]->st_size < min){
				min = store[j]->st_size;
				index = j;
			}
		}

		SWAP(store[i], store[index], temp);
	}
}
void sortByTime(File_info** store, int size){

	char* min;
	MALLOC(min, STRING_SIZE * sizeof(*min));

	for(int i = 0; i < size; i++){
		int index = size + 1;
		strcpy(min,"Dec 31 23:59:59 9999");
		File_info* temp;

		for(int j = i; j < size; j++){
			if(compareTime(store[j]->lastModifyTime, min) == -1){
				strcpy(min,store[j]->lastModifyTime);
				index = j;
			}
		}

		SWAP(store[i], store[index], temp);
	}
}
void printResult(File_info** store, int size){
	for(int i = 0; i < size; i++){
		printf("%s", store[i]->modestr); 
		printf("%4d ",store[i]->hardLink); 
		printf("%-8s ", store[i]->uid_to_name); 
		printf("%-8s ", store[i]->gid_to_name); 
		printf("%-ld ", store[i]->st_size); 
		printf("%.12s ",store[i]->lastModifyTime); 
		printf("%s \n", store[i]->filename);
	}
}
int compareTime(char* timeA, char* timeB){
	
	Time* A = getTime(timeA);
	Time* B = getTime(timeB);

	if(A->year != B->year) return (A->year > B->year ? 1 : -1);
	if(A->month != B-> month) return (A->month > B->month ? 1 : -1);
	if(A->day != B->day) return (A->day > B->day ? 1 : -1);
	if(A->hour != B->hour) return (A->hour > B->hour ? 1 : -1);
	if(A->minute != B->minute) return (A->minute > B->minute ? 1 : -1);
	if(A->second != B->second) return (A->second > B->second ? 1 : -1);

	return 0;
}
Time* getTime(char* time){

	Time* t;
	MALLOC(t, sizeof(*t));

	t->year = atoi(getSubstring(time,16,19));
	t->month = getMonth(getSubstring(time,0,2));
	t->day = atoi(getSubstring(time,4,5));
	t->hour = atoi(getSubstring(time,7,8));
	t->minute = atoi(getSubstring(time,10,11));
	t->second = atoi(getSubstring(time,13,14));

	return t;
}
int getMonth(char* month){
	char* months[13] = {"Zero","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	for(int i = 0; i < 13; i++){
		if(!strcmp(month,months[i])){
			return i;
		}
	}
}
char* getSubstring(char* string, int start, int end){
	char* str;
	MALLOC(str, (end-start + 1) * sizeof(*str));

	for(int i = start; i <= end; i++){
		str[i-start] = string[i];
	}
	str[end+1] = '\0';

	return str;
}