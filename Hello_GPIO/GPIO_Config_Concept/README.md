# GPIO Configuration 
* GPIO 설정에 필요한 개념 설명   
<br></br>
## GPIO output
![image_4](https://user-images.githubusercontent.com/130421694/233956709-ce00457a-9fb5-4884-bdd2-7fad2a236953.png)
<br></br>
## 1. GPIO output level
* GPIO 출력 초기값을 3.3V, 0V 중에서 선택   
![image_5](https://user-images.githubusercontent.com/130421694/233958053-5e6490e1-5e3d-4e34-aca9-a587ae68d265.png)
* MX_GPIO_Init() 함수 내부에서 위 부분에 해당
* GPIO_PIN_SET = 1 ( HIGH )
* LOW로 설정하면 GPIO_PIN_RESET 으로 설정됨
<br></br>
## 2. GPIO mode

### PushPull 회로   
![image_1](https://user-images.githubusercontent.com/130421694/233959292-9f7c428c-e2b8-4a7f-a484-9d75a2982a1a.png)
* sw1가 닫히면 출력단으로 전류 흐름 → HIGH
* sw2가 닫히면 GND에 연결, 전류 안 흐름 → LOW   

<br></br>
### Open Drain 회로   
![image_2](https://user-images.githubusercontent.com/130421694/233959403-1b28f286-9de9-4aef-8b56-e262e5b1963e.png)
* 스위치 열리면 floating
* 닫혀있으면 GND 연결 -> LOW level 출력
	+ LED 키려면 전류가 흘러야 되니까 Push Pull 을 써야함

#### 오픈 드레인을 사용하는 경우   
![image_3](https://user-images.githubusercontent.com/130421694/233959418-1a65dbdc-9bcf-419c-90ec-940c9bc118ba.png)

* SW2가 5V를 필요로 하지만 MCU 전압은 3.3V
* 스위치 닫히면 외부전압 5V 흐르고, 열리면 5V 안흐름
<br></br>
## 3. Pull-up/Pull-down
* Floating 현상을 해결하기 위한 방법
	+ Pull up : 위로 끌어당긴다
	+ Pull down : 아래로 잡아내린다
<br></br>
### Floating
![image_6](https://user-images.githubusercontent.com/130421694/233963309-46e4e77e-52e7-4ea2-87c1-effd2728dfbb.png)

* 입력 전압이랑 GND가 연결되어있지 않아서 Input 핀에 들어오는 전압이 HIGH 인지 LOW인지 모름
<br></br>
### Pull up 저항
![image_7](https://user-images.githubusercontent.com/130421694/233967088-5f5bf546-08be-49b7-ab44-b902243d5673.png)


* 입력 전압 쪽에 적당한 저항을 달아줌
* 스위치가 닫히면 GND로 전류가 흐름 → Input 은 0이 됨
* 저항 안달고 스위치 닫으면 short 돼서 전선이 타버림 → MCU도 타격을 받음
<br></br>
### Pull down 저항
![image_8](https://user-images.githubusercontent.com/130421694/233967113-5679b962-6ebe-4a68-bff9-c70f2d67bfed.png)
* Pull up과 반대
* GND 쪽에 저항을 달아줌
* 스위치 닫히면 HIGH 열리면 LOW
* 저항이 없을때 스위치 열리면 Open
* 일반적으로 풀다운보다 풀업이 노이즈나 충격에 강해서 풀업을 많이 사용
* 풀업 풀다운은 일반적으로 크게 의미가 없지만 오픈 드레인이나 입력에서는 유효
<br></br>
### 회로도를 보고 풀업, 풀다운 판단하기
![image_9](https://user-images.githubusercontent.com/130421694/233968335-c830bdb8-382c-4989-a663-ffaa03228d65.png)
* GND 쪽에 저항이 없다 → 저항이 없으면 회로가 탄다
* PA0 내부에 풀업 회로가 구성되어있다는 의미
* PA0이 풀다운이었다면 GND 쪽에 저항이 있었을 것
<br></br>
## 4. Maximum output speed
* HIGH ↔ LOW 바뀔 때 필요한 시간
