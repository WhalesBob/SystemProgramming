# EtcMakeUp

+ 아는 지식인데, 생소한 용어로 정리된 것은 나도 여기에 정리함
+ 아는데 혹시나 모르는거는 다시 정리해서 보자.

#### stack pointer
+ 그냥 스택 부분이 가리키는 포인터

#### Return Address
+ 함수가 불리고 나서, 다 실행 되고 나서 다시 이전 콜스택 맨윗단으로 돌아가야 되는 메모리 주소를 기억해서, return 해서 돌아가는 address
  - 돌아가야할 함수주소 라고 생각하면된다. 

## About GDB

+ list a.c 8 : 8번째줄 주변 10줄을 보여준다
  - gdb 에서 보고싶으면, 그냥 list ~ (n) 이렇게 된다 
  
+ b(break) 13 : 13번째줄 break
  - b add : add 함수 break
  
+ info breakpoint (or info b) : 어디에 브레이크포인트 걸엇는지 보여준다.
+ run :  실행
+ n(next) : 다음 부분 보여주기

+ continue(or c) : 다음 브레이크포인트까지 쭉 가기
+ where :  정확히 함수 호출 스택의 메모리가 어디까지 가있는지? 내가 어디에서 어디로 함수를 어떻게 불렀는지? 알수 있음

+ up : 바로 윗단계의 함수로 갈 수 있음.
+ down : 아래 단계의 함수로 갈 수 있음. 
  - 활용 : up 해서 해당 함수의 x 값을 보고, 다시 down 해서 실행시킬 수 있다. 
  
+ print : 값을 보는것
  - print a(or p a) 하면 값을 볼 수 있을 것이다
  
+ display : 값을 계속적으로 쭈욱 보여주는것

+ delete 2 : 2번 breakpoint 지워진다. 

+ step (s) : 함수 안으로 들어가게 되는 것

+ disable 1 : 1번 breakpoint를 잠시 disable 시키는 것. 지우는것은 아니고 잠시 무력화시킨다. 

+ quit : debugger 가 종료된다.

