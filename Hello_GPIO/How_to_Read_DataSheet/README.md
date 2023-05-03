# How to Read DataSheet
* __데이터 시트는 컴퓨터 지식을 많이 알고 영어를 잘해야 읽는 속도가 빨라짐__
* 결국 왕도는 없다 직접 읽어봐야 는다
* 연습으로 7 segment LED Displays 를 제어하는 법을 익혀보자
<br></br>
___
## LED Display Driver IC를 통한 7 세그먼트 LED Displays 제어
<br></br>
___
### 1. 목적을 세우기
* Arm 코어 같은 경우 데이터 시트가 1500장이 되고 이것을 다 읽을 수는 없다
* 개발을 하다보면 많은 시간을 들여서 지식을 습득했는데 굳이 알 필요 없었던 지식도 꽤 많다   
	+ ex) 윈도우 API
* __내가 해야되는 정확한 목표를 세우고 그 목표에 맞는 지식만을 습득하여 시간을 절약한다__
<br></br>
<br></br>
___
### 2. 장치들의 개념을 이해하자
![image](https://user-images.githubusercontent.com/130421694/235921113-286d6740-a530-4b26-87fb-cea8b55126a5.png)
* 일단 데이터 시트 없이 이게 뭐하는 장치인지 대강 파악해보고 상상한다
* 구글에 검색했을 때 사진이나 대략적인 설명을 봐서는 7개의 LED를 제어해서 아라비아 숫자를 출력하는 장치로 보인다
<br></br>
<img src="https://user-images.githubusercontent.com/130421694/235922385-840f8083-9b5e-4cae-844f-8c96d521d5db.png" width="80%" height="80%"/>

* 그런 다음 데이터 시트의 Description을 읽어본다
* 구글에 (장치 이름) Datasheet 라고 검색하면 쉽게 구할 수 있다

* 각 0.56인치 높이를 가진 7개의 LED가 있고 빨강, 주황, 노랑-초록 색을 방출하는 등의 일반적인 정보가 담겨있다
* 그러나 epoxy resin molded라는 것을 검색해보니 어떤 화학 물질이 나온다
* __이런 것은 프로그래머가 알 필요 없는 지식이므로 데이터 시트에 기재된 정보가 프로그래밍에 필요한 정보인지 빠르게 판단하고 넘어가자__
<br></br>
<br></br>
___
### 3. 실제 데이터 시트와 나의 예상 비교
![image](https://user-images.githubusercontent.com/130421694/235924364-b34a117d-c336-4b6b-b2a7-430fefec783f.png)
* Digit 1에 1, 2, 3, 4, 15, 16, 17, 18번 핀이 연결
* Digit 2에 5, 6, 7, 8, 9, 10, 11, 12번 핀이 연결
* A~G, DP LED가 각 8개의 핀에 연결되어 있다
* 7개를 제어할 것으로 예상했지만 .까지 8개 LED를 제어하는 것 외에는 전반적으로 예상이 맞았다고 볼 수 있다
<br></br>
<br></br>
___
### 4. 생각했던 흐름을 그림으로 요약
* 숫자 1개를 표현하기 위해서 8개 핀이 사용되는데, 그럼 숫자 4개를 표현하면 GPIO핀 32개가 필요한가?   
![image](https://user-images.githubusercontent.com/130421694/235927420-aa08f76e-1dfd-4d3a-aacf-3f69c3482180.png)
* FND 모듈에는 4개 선이 있는 것으로 봐서 그렇게 보이지는 않는다
* STM 칩과 FND 모듈 사이에 있는 드라이버를 통해 이 문제를 해결한다
<br></br>
<img src="https://user-images.githubusercontent.com/130421694/235919332-dd5a7b16-fd8d-483d-8bea-bf0410352da4.png" width="80%" height="80%"/>   
<br></br>
* STM 칩과 드라이버는 DI/O, CLK, STB 3개 선으로만 연결되어 있다
* SG1/KS1 에서 나온 선이 DIG1의 A1과, DIG2의 A2에 모두 연결되어 있다
* GR1, GR2는 각각 DIG1, DIG2에 연결되어 있다
* __따라서 A 자리의 LED를 키고 싶으면 SG1/KS1에 전류를 흘리고 원하는 DIG에 따라서 GND를 조절한다__
<br></br>

#### STM 칩에서 핀 3개로 LED IC를 제어하는 법   
![image](https://user-images.githubusercontent.com/130421694/235936329-8bef098e-ec95-458f-8384-3652608470da.png)   

* LED 드라이버인 IK2102DW 의 데이터시트를 보면 Serial Interface 라고 적혀있다
* 이것은 SPI 통신으로 제어한다는 것을 의미한다
  + SPI 통신에 대해 모르면 LED IC를 제어할 수 없게 된다
<br></br>  
#### 임베디드 개발자라면 반드시 알아야할 통신 방법
	1. Uart
	2. Rs232, RS485
	3. SPI
	4. I2C
	5. TCP, UDP
	6. CAN
<br></br>
#### SPI 통신 방법
* STM32 칩에서 어떻게 프로그래밍해야 드라이버에 원하는 정보를 보낼 수 있을까?
![image](https://user-images.githubusercontent.com/130421694/235938678-35390f7f-884f-47c0-a665-42e08d9de9c0.png)   
[SPI 통신 자세히 보기](https://www.hardcopyworld.com/?p=2778)
* 데이터를 보낼 때 데이터가 전달된다고 알려주는 별도의 클럭 라인을 사용하는 동기식 시리얼 통신 방법 중 하나
* 1:N 통신 ( Slave and Master )
* 데이터를 보내려면 STB를 LOW로 설정한다
* 원하는 데이터를 8bit에 맞춰 DI/O로 전송한다
  + 숫자 10을 보내고 싶다면 00001010 전송
* 클럭의 상승 엣지에 데이터가 전송됨
<br></br>
#### 컴퓨터 지식이 중요한 이유
* SPI는 어떻게 보내는지는 정의되어 있지만, 어떤 데이터를 보내야 할지는 정해져있지 않음
* A부분을 키려면 어떤 데이터를 보내야 하지? → FND 데이터 시트, 소스 코드를 읽어야 한다
* 이 부분은 따로 공부를 해야한다
<img src="https://user-images.githubusercontent.com/130421694/235947702-59852455-9605-466a-be9b-2b3b4c42465a.png" width="80%" height="80%"/>   

* 위 Display Mode를 포함해서 4가지 Setting Command가 IK2102DW 데이터 시트에 쓰여있다
* 사진에 나오지 않은 Address나, Grid 개념 등등이 있는데 __결국 필요할 때 스스로 찾아봐야만 한다__
<br></br>
<br></br>
___

### 5. 데이터 시트가 전부는 아니다
* 프로그램을 구현하는 방법을 익히기 위해서는 다음과 같은 방법을 사용할 수 있다   
  i. 소스코드를 구해서 분석해본다 (Best)   
  ii. 회로도를 본다   
  iii. 하드웨어 담당자에게 물어본다
    + 하드웨어 담당자들은 데이터 시트를 보고 한 번씩은 다 이해해보신 분들이다
    + 다만 SW를 어떻게 구현할지 등을 모두 이해하지는 않으신다
