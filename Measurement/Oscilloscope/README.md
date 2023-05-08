# 오실로스코프
* 제품명 : FNIRSI-1013D
* 멀티미터기와 달리 시간에 따른 전압 파형을 측정
* 복잡한 신호를 시각적으로 확인하기 위해 사용
* __임베디드 개발에서는 데이터가 제대로 통신하는지 확인하기 위해 사용__
<br></br>
<br></br>
___
## SPI 신호를 측정하며 오실로스코프 사용법 익히기
* SPI 통신에 대해 자세히 모르기 때문에 우선 강의를 보며 따라했다
<br></br>
### 1. SPI 신호 전송
* 먼저 오실로스코프로 측정할 SPI 신호를 생성

![image](https://user-images.githubusercontent.com/130421694/236734247-841d3bf3-0785-42a3-b3ac-5c9770a24f60.png)

* PA5 : SPI1_SCK  ( 클럭 )
* PA6 : SPI1_MISO ( Master Input Slave Out = STM 입력 )
* PA7 : SPI1_MOSI ( Master Output Slave input = STM 출력 )   

<br></br>
<br></br>   
![image](https://user-images.githubusercontent.com/130421694/236734668-875b7204-f40c-431c-8f8e-854d71b08dc9.png)   
* 좌측 Connectivity 에서 SPI1 선택
* Mode를 Full-Duplex Master 로 설정 후 저장
* 그 외 하단의 Parameter 등은 건들지 않아도 무방


<br></br>
<br></br>

![image](https://user-images.githubusercontent.com/130421694/236736436-974d4890-a3b0-4aa1-b673-faf78197067a.png)   
* 전송할 데이터 설정
* 일정한 시간 간격마다 데이터 전송하는 코드 작성 후 STM에 연결하여 실행


<br></br>
<br></br>
### 2. 오실로스코프 활용
#### 프로브 관련 기능
<img src="https://user-images.githubusercontent.com/130421694/236739306-42b620c5-032d-4c38-a570-867d4b4350ce.png" width="60%" height="60%"/>   

* open CH : 프로브 사용/미사용
* oepn FFT : 주파수 변환해 화면에 출력 ( 고속 푸리에 변환 )
* coupling : DC/AC로 화면에 출력   
  + 완전한 DC는 없다. DC 전류도 결국 미세하게 AC 전류가 있는 것이다.
* probe mode : 측정한 전압을 1, 10, 100 배수로 변환
<br></br>
<br></br>

![image](https://user-images.githubusercontent.com/130421694/236742067-05cce5e5-8df0-4fce-80fc-ee37ec55b50f.png)

* 클럭 출력하는 PA5에 CH1 프로브 연결 ( 적색 선 )
* STM 출력하는 PA7에 CH2 프로브 연결  ( 갈색 선 )
* GND에 CH1, CH2 프로브 연결  ( 흰색 선 )
<br></br>
<br></br>
#### 오토셋
<img src="https://user-images.githubusercontent.com/130421694/236742677-ded7ba22-dd7a-4be3-a531-6cf5d6e2ca10.png" width="60%" height="60%"/>   

* 화면 우측 AUTO SET을 터치하면 파형을 적절하게 변환

<br></br>
<br></br>
#### 트리거

<img src="https://user-images.githubusercontent.com/130421694/236743380-34939fb7-e7e8-48bc-9530-ab1e6f8cd77b.png" width="40%" height="40%"/>   

* 화면 우측 상단에 위치
* 일정 전압 이상에 도달했을 때를 기준으로 전압 파형 측정
* __굉장히 빠른 속도로 오고 가는 신호를 잡아내기 위해서 사용__
* trig mode : 트리거 모드 변환
  + auto : 파형이 정지되지 않고 게속 업데이트
  + single : 트리거 조건에 맞는 첫 번째 파형에서 트리거하고 멈춤
  + normal : 트리거 조건에 맞는 파형에서만 트리거하고 화면은 게속 업데이트
* trig edge : 상승/하강 엣지에서 트리거 검출 선택
* trig CH : 트리거할 프로브 선택

<br></br>
<br></br>

#### 전압, 시간 단위 조절

* 전압 단위 조절
  + 화면 우측 상단 CRTL을 누르면 각 프로브 마다 단위를 조절할 수 있는 탭이 표시됨
  + V+ : 한 칸의 전압 단위가 작아짐 = 파형이 커짐
  + V- : 한 칸의 전압 단위가 커짐 = 파형이 작아짐
* 시간 단위 조절
  + 화면 가운데를 기준으로 좌/우측을 터치하면 시간 단위가 커지거나 작아짐

<br></br>
<br></br>

#### 전송 데이터 확인

<img src="https://user-images.githubusercontent.com/130421694/236752077-ef21ea69-37b1-49db-a711-db000674cea3.png" width="100%" height="100%"/>   

* 트리거 조건을 다음과 같이 설정
  + 전압 단위 : 1V
  + 시간 단위 : 1uS
  + 트리거 조건 : single 모드, 3V

* 클럭이 1일 때 STM 출력이 1이면 1, STM 출력이 0이면 0을 전송한 것
* 첫 번째 데이터는 0110 0001, 두 번째 데이터는 0110 0010 을 의미

<br></br>
<br></br>

<img src="https://user-images.githubusercontent.com/130421694/236752807-23fbd73f-f988-4d06-b5a4-276e9c8da0d8.png" width="40%" height="40%"/>   

* __0110 0001 (2) = 61 (16) 이고, 0110 0010 (2) = 62 (16) 이므로 a, b가 모두 제대로 전송된 것을 확인__
* __이런 식으로 오실로스코프는 주로 시간 간격이 제대로 되는지, 전압이 제대로 출력되는지 등을 확인할 때 쓰임__

<br></br>
<br></br>

#### T커서, V커서

<img src="https://user-images.githubusercontent.com/130421694/236755380-3e83137f-588e-4d0f-b2cf-e34ac9fbedc4.png" width="100%" height="100%"/>   

* 화면 우측에 위치
* 시간 간격, 전압 간격을 표시하기 위한 용도
* 좌측 상단에 점선 사이 구간 만큼의 시간/전압 간격이 표시
  + 사진에서는 2.36us, 3.48V 의 차이
