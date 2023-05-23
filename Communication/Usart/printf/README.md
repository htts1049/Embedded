# USART로 printf() 구현
* printf() 함수는 일반 PC에서 비주얼 스튜디오로 실행하면 콘솔창에 출력
	+ 리눅스에서는 콘솔창이 아니라 파일에 기록되게 할 수 있다   
= 표준 출력을 바꿀 수 있다
* 디버깅 과정에서 printf()를 구현하면 쓰레드 실행과 같이 여러 가지를 실시간으로 볼 때 유용
	+ 디버거로 일일히 확인할 수도 있지만 printf를 사용하면 __디버깅이 더욱 편리__
* 사용자 UI로도 쓰임
<br></br>
<br></br>
___
## UART vs USART
* UART : 동기 방식, 클럭 있는 통신 방식
	+ 클럭이 있으면 CLK 라는 핀이 더있다
	+ 클럭 선, 데이터 선이 따로 연결
	+ 클럭 HIGH & 데이터 HIGH 면 1
	+ 클럭 HIGH & 데이터 LOW 면 0
<br></br>
* USART : 비동기 방식, 클럭 없는 통신 방식
	+ 클럭을 안쓰는 대신 시간을 동기화
	+ 시간을 정확하게 쪼갬
	+ 기준 시간 = 보드 레이트
<br></br>
<br></br>
___
## FTDI 모듈 구성
* UART 신호를 받아서 USB 형태로 전환
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/880e8d7e-3240-4d72-8c65-a8c7a9b0af4f)


* DTR : 출력
* RX  : 수신부 ( 보드의 송신부와 연결 )
* TX  : 송신부 ( 보드의 수신부와 연결 )
* VCC : 입력 전원
* CTS : 흐름 제어 목적 ( 송신측 전송 속도 > 수신측 처리 속도 → 문제가 발생하므로 수신측에서 송신측 속도 제어 )
	+ 공유 매체 사용하는 무선 LAN 등의 경우 : 데이터 수신 준비 완료 신호를 송신측에 보냄
	+ 별도 송수신제어 선이 있는 RS-232 등의 경우 : DCE측이 CTS 선을 통해 데이터를 더 받을 수 있음을 알림
* GND : 그라운드


* 최소한 입력 전원, RX, TX 핀이 연결되어 있으면 통신 가능

<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/4352af1c-461b-48c2-9ea1-39dcb4b52f80)

* PC에 FTDI 모듈을 연결
* 제어판 - 장치 관리자에서 확인 가능
<br></br>
<br></br>
___
## IDE 설정

![image](https://github.com/htts1049/Embedded/assets/130421694/64c9dbc4-d5db-4989-baa7-3bc703c11538)

* 좌측 Connectivity 에서 USART1 선택
* PA9, PA10 이 자동으로 선택 ( IDE의 장점 )
* 그 외 설정은 건드리지 않음
	+ 보드레이트 : 1초당 보내는 비트 수
	+ Word Length : 한 글자에 담긴 비트 수
	+ Parity : 짝수/홀수 패리티 선택
	+ Stop Bits : 전송이 끝났다는 의미를 담는 비트 수가 1개인지 혹은 2개인지
	+ Data Direction : 송신 혹은 수신만 할 것인지, 둘 다 할 것인지

* PA9 = Tx
	+ 보드의 송신부
* PA10 = Rx
	+ 보드의 수신부
<br></br>
<br></br>
___
## Usart 기능 시험
* Usart가 제대로 동작하는지 확인하는 코드를 작성해보자

![image](https://github.com/htts1049/Embedded/assets/130421694/e3e04b9d-ef3e-4f6f-bc19-9791871e65fe)

* Usart 설정을 마치면 main 함수에는 IDE가 설정값을 토대로 초기화 함수를 작성해줌
* 전송할 데이터를 설정
* 1초 간격으로 데이터 송신
* 코드 작성 후 PC와 보드를 연결하여 실행
<br></br>
<br></br>
___
## 핀 연결

<img src="https://github.com/htts1049/Embedded/assets/130421694/641d68ac-54ff-4a9d-85e7-9b1be51442a9" width="60%" height="60%"/>   

* A, B 라는 두 사람이 있고 서로 소통을 하려고 한다
* 둘이 소통하기 위해서는 A가 입으로 낸 소리가 B의 귀에 닿고, B가 낸 소리가 A의 귀에 닿아야 한다
* FTDI와 STM이 통신하려면 2개의 선이 연결되어야 한다
* FTDI의 Rx는 STM 칩의 Tx에 연결
* FTDI의 Tx는 STM 칩의 Rx에 연결
* 각각의 Rx는 사람의 귀, Tx는 사람의 입인 셈

<br></br>

<img src="https://github.com/htts1049/Embedded/assets/130421694/af15e3cd-2942-4481-9a37-e4a79004a36c" width="60%" height="60%"/>   

* 가시성을 위해 브레드 보드로 핀을 연결해주었다
* 브레드 보드 없이 직접적으로 연결해도 통신에는 무방
* FTDI Rx ㅡ 갈색 선 ㅡ STM Tx
* FTDI Tx ㅡ 흰색 선 ㅡ STM Rx
* FTDI GND ㅡ 검은색 선 ㅡ STM GND
<br></br>
<br></br>
___
## Xshell5 로 출력 메세지 확인
* Window 운영체제에서 SSH 접속을 수월하게 하기 위한 프로그램
	+ SSH ( Secure Shell ) : 원격 호스트에 접속하기 위해 사용되는 보안 프로토콜, 커널과 사용자 간 다리 역할
* Shell 프로그램은 binary 코드를 출력하지 않고 오직 string 만 출력
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/b535d46f-d459-4bcb-b12d-a78e69ac5dd4)

* 새로 만들기
* 이름 설정
* 프로토콜 Serial로 설정
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/c5d090a4-98c2-4f57-be47-5d77e977f01c)

* 장치 관리자에서 포트 번호 확인 후 FTDI가 연결된 포트로 설정
* STM에서 설정한 값과 같은 값의 보드 레이트로 설정
<br></br>

![bandicam 2023-05-23 15-55-41-824](https://github.com/htts1049/Embedded/assets/130421694/5546a103-15cc-4ceb-bd65-a48b9399ac58)

* 데이터 전송 확인
<br></br>
<br></br>
___
### \r의 의미

![bandicam 2023-05-23 16-04-56-967](https://github.com/htts1049/Embedded/assets/130421694/bbe5afe7-572b-4551-b957-73759b9f2873)

* \r 없이 보내면 계단 형태로 출력
* \r은 캐리지 리턴으로 패럿을 줄 맨앞으로 보냄
* 현재는 컴파일러가 \n만 써도 개행과 캐리지 리턴을 둘다하지만 옛날엔 구분하여 사용
<br></br>
<br></br>
___
### 개인적 궁금증

![image](https://github.com/htts1049/Embedded/assets/130421694/2e8c2b99-171f-43eb-b6c5-5f86c0d1c046)

* FTDI는 수신부가 최대 28 바이트 까지 담는다는데 그 이상 보내면 어떻게 될까

<br></br>
![bandicam 2023-05-23 16-13-43-735](https://github.com/htts1049/Embedded/assets/130421694/d377edc9-2796-475c-864b-b4397bcdcc58)

* 문제 없이 출력됨
* 설명이 잘못된건지, 무언가 프로그램적으로 버퍼 크기를 넘어서는 메세지를 받아도 처리할 수 있게 한건지 모르겠음
<br></br>
<br></br>
___
## printf 구현

* 고정된 상수나 문자열이 아닌 변수 값을 출력하려면 printf 함수가 필요
* stdio.h 헤더파일을 include 하고 printf 함수를 사용해도 출력이 안됨
* _write 함수를 수정하여 이를 해결
	+ _write 함수는 printf 함수 내부에서 실행되는 함수라는 것 까지만 알고 넘어가자
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/64763ee3-8ed2-49bd-84c1-eb18dfcbd2ae)

* _write 함수를 위와 같이 재정의
* 출력을 기존에 있던 부분에서 huart1 으로 바꿔준 것
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/68288441-1a86-41ae-ac34-4f9580c10d29)

* 매 초마다 i값을 출력하고 1씩 증가하는 코드를 작성
<br></br>

![bandicam 2023-05-23 16-44-00-562](https://github.com/htts1049/Embedded/assets/130421694/17e0b139-555e-4cb5-8a44-ee3e2d6f1f63)

* 출력 확인
<br></br>
<br></br>
___
### 실수 출력

![image](https://github.com/htts1049/Embedded/assets/130421694/8eda3c8e-1145-4814-ac1b-3fb5b2ddc678)

* 프로젝트 설정 → C/C++ Build → Settings → MCU GCC Linker → Miscellaneous → Other flags → -u _printf_float 입력 → Apply
* 링킹할 때 옵션을 넣는 것

![bandicam 2023-05-23 17-10-51-828](https://github.com/htts1049/Embedded/assets/130421694/e1eb714e-ac90-4eac-b136-322f67e14ed2)

* i를 float로 바꾸고 실행하면 실수로 출력

<br></br>
<br></br>
___
### Live Expressions 로도 실시간 확인 가능

![image](https://github.com/htts1049/Embedded/assets/130421694/517382ec-a251-4410-aa41-fe89eae3176f)

* 전역 변수로 선언해야함
	+ 코드 영역
* main 함수에서 하면 스택영역이라 디버그할 때 걸림

![bandicam 2023-05-23 17-16-31-024](https://github.com/htts1049/Embedded/assets/130421694/e49950d1-5c4a-4f41-8a79-e2e866da7cce)

* 우측 Live Expressions 에서 i 값 증가 확인