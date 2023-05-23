# Uart 프레임

* Uart는 8bit에 정보를 담아 전송하는 직렬(Serial)통신 방법
* 0의 시작(start)비트와 1의 정지(stop)비트로 데이터의 시작과 끝을 알림
* 보내는 쪽(Tx)과 받는 쪽(Rx)이 데이터를 원활하게 주고 받으려면 __데이터를 보내는 속도에 대한 약속(Protocol)__ 이 정해져야 함
  + 보드 레이트 (Baud Rate)
<br></br>
<br></br>
___
## Uart 프레임 구조
<br></br>
![image](https://github.com/htts1049/Embedded/assets/130421694/1c8de536-1f9e-4ea5-a16c-4b71782ca3ea)

* 정지비트를 1개 사용하고 패리티 비트를 사용하지 않을 때, Uart 프레임의 구조는 위와 같다
* 프레임이 시작된다는 신호로 1비트로 0을 보냄
* 프레임이 끝난다는 신호로 1비트로 1을 보냄
<br></br>
<br></br>
___
## Uart 코드

![image](https://github.com/htts1049/Embedded/assets/130421694/00281a86-4ae8-4d27-9f9b-8c5867249090)

* printf 함수를 구현할 때 했던 대로 hello world 라는 문장을 전송해보자
<br></br>
<br></br>
___
## 오실로스코프 측정

* hello world 의 첫 글자는 h 이므로 오실로스코프로 트리거를 걸었을 때 잡히는 첫 문자는 h가 될 것이다

![image](https://github.com/htts1049/Embedded/assets/130421694/7d43148c-06d8-425f-8995-710bc264908a)

* h는 16진수로 0x68, 2진수로는 0110 1000 이 된다
* 오실로스코프에서 0110 1000이 전송되는지 확인해보자

<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/73677367-cd8b-41f1-952f-4de965c573f5)

* 설정한 보드레이트 값은 115200 으로 이는 1초에 115200 개의 비트를 주고 받는다는 의미
* 1bit 전송 시간 = 1sec / 115200 baudrate = 8.7us
* 오실로스코프의 T커서가 0.2 단위로 움직이기에 8.6us 정도의 간격으로 비트 값 확인
* 비트 값은 0110 1000 이 아니라 __0001 0110__ 을 보내고 있다
* 이것은 STM 칩이 __최하위 비트(Least Significant Bit, LSB)부터 전송했기 때문__
<br></br>
<br></br>
___
## 리틀 엔디안 vs 빅 엔디안

http://www.tcpschool.com/c/c_refer_endian
https://jhnyang.tistory.com/226

![image](https://github.com/htts1049/Embedded/assets/130421694/d3ffd477-1a9e-44d2-8b8c-c5e524a39da8)

* 리틀 엔디안은 낮은 메모리 주소에 최하위 비트부터 채운다
* 빅 엔디안은 낮은 메모리 주소에 최상위 비트부터 채운다
* 리틀 엔디안과 빅 엔디안은 각각의 장단점이 있다
	+ 수학적 연산, 자료형 변환에는 리틀 엔디안이 유리
	+ 크기 비교 연산, 편리한 디버깅에는 빅 엔디안이 유리