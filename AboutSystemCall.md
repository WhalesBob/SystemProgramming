# About System Call

+ System Call 이란?
  -  User 가 원래는 자기 혼자 다 할수 있는것 이 아니다
  -  LDE(Limited Direct Execution) 체제 하에서 오직 System Call로 OS와 상호작용할 수 있다. 
  -  반대로, OS는 사용자가 클릭하는 것을 일일이 하나하나 감시하고 기다리고 있는 것이 아니다. 
    - 만약 사용자가 더블클릭이라는 행동을 하게 된다면, 이것은 System Call 이 되어 OS 에게 나아가는 것이다. 
    - OS 는 이런 System Call 을 받고, 사용자에게 적절한 응답을 줄 것이다. 

+ Directory 개념 
  - 안에 있는 File 정보들을 담고 있는 특별한 파일.
  - 

+ dirent 
  - dirent.h 에 관련정보가 있다. 
    - __Dir__ ectory 와 __ent__ ry 의 합친것을 줄인것이라고 한다. 
  
  - opendir(char* dirname) 해서 넘어오는 struct dirent{ } 정보
    - ino_t d_ino : 그 엔트리의 파일 번호
    - __uint16_t d_reclen :  그 레코드의 길이 
    - __uint8_t d_type :  파일타입
    - __uint8_t d_namlen : 파일이름 문자열의 길이 
    - char d_name[255+1] : 파일이름. 256를 넘어서는 안된다. 
  
  - 만약에 dirent* 주소값이 NULL 이면, 끝까지 간 것이다. 

+ DIR
  - 파일 읽을 때도 관련 struct 포인터를 쓰듯이, Directory 도 마찬가지로, 그 위치를 넘겨주는 포인터가 있다. 
  - DIR struct를 통해서 Directory 관련 포인터를 하나씩 넘기면서 할 수 있다. 
  - 디렉토리를 컨트롤할 때 쓰는것.

+ stat
  - 해당 파일의 상태를 얻어오는 System Call
  - 각 정보들이 의미하는 것 : 접근권한/파일소유 아이디/파일소유 그룹/마지막 실행시간/파일이름
  - About stat
    - 1번째 인자 : 파일이름(ex: argv[1]
    - 2번째 인자 : 정보를 받을 것의 포인터. (&info) . 여기서 info는 struct stat info 이다.
    - 리턴값이 -1 일때는 비정상. 0일 때는 정상리턴.
 
+ 허가 관련 bit 관리하는 방법 : bit masking
  - 유저,그룹,다른사람들에 대한 read,write,execute 권한을 관리함. 
