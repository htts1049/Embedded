
# MX_GPIO_init
* MX_GPIO_Init 함수를 분석해보자
<br></br>
![image_2](https://user-images.githubusercontent.com/130421694/234282537-82c1207b-3f42-435a-9fbe-ca9217f6a6c9.png)

<br></br>
___
## 1. __HAL_RCC_GPIOC_CLK_ENABLE()
* GPIOC의 클럭을 활성화하는 함수   
![image_3](https://user-images.githubusercontent.com/130421694/234289462-a2546838-410a-457a-ac98-d8fab7b75d8a.png)

<br></br>
___
### i. 클럭이란?
![image_1](https://user-images.githubusercontent.com/130421694/234282141-052a18e2-ce46-4303-bef0-fd96851a539e.png)
* 클럭은 모든 동작의 기준점
* 통신한다라고 쳤을때, 어떤 파형을 보낸다면 → HIGH가 길어지면 1이 몇개이고 LOW가 길어지면 0이 몇개일까?
* 이런 것을 구분하는 기준이 바로 클럭
* 클럭은 내부 클럭, 외부 클럭으로 구분 
  → 보통 외부 클럭 많이 사용
<br></br>
<br></br>
___
### ii. SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN)
* 레지스터에 비트를 SET하는 함수   
![image](https://user-images.githubusercontent.com/130421694/234304921-6b4bea77-7371-4977-a3af-5dcaf3c2829e.png)
    * 먼저 RCC->APB2ENR 값을 확인해보자
    * RCC 레지스터의 offset 값은 0x4002 1000
    * APB2ENR 레지스터는 0x18을 더해주면 된다
    * __RCC->APB2ENR = 40021018__
    <br></br>
    <br></br>
    
    * 다음으로 RCC_APB2ENR_IOPCEN 값을 확인해보자
    ![image_6](https://user-images.githubusercontent.com/130421694/234294438-47c95c72-9f41-4a70-8351-feec7ef8b892.png)
    * RCC_APB2ENR_IOPCEN = (1 << 4)
    * __RCC_APB2ENR_IOPCEN = 16__
<br></br>
<br></br>   
___
### iii. SET_BIT 의 의미
  → *(40021018) |= 16
  * 이 SET_BIT 함수의 의미를 데이터 시트를 보며 이해해보자   
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234303169-7a862ee3-5a68-4f41-8b53-864f04bfaf62.png)
* RCC의 APB2ENR 레지스터는 APB2 페리페럴의 클럭을 활성화하는 레지스터라고 한다
* 위 연산의 의미는 __IO 포트 C의 클럭을 활성화__ 하는 것이다
<br></br>
<br></br>
___
### iv. 시스템 버스
![image_7](https://user-images.githubusercontent.com/130421694/234299797-67205ff8-5378-40f9-aebf-1b4688d5038e.png)
* 각 장치마다 필요한 클럭이 다르고 장치마다 전이중 연결 방식을 쓰려다 보니 스타형이 되고 선이 너무 복잡해지는 문제가 발생   
  → 버스형 탄생
* 버스형을 쓰다보니 장치마다 요구되는 클럭 속도가 다르다   
  → 속도가 빠른 장치 전용 버스, 느린 장치 전용 버스를 따로 구분
* AHB = 속도가 빠른 버스
* APB = 속도가 느린 버스
* __사용할 GPIOC 는 APB2에 속해있기 때문에 APB2의 클럭을 활성화 해준 것이다!!__
<br></br>
<br></br>
___
### v. READ_BIT
* 비트를 읽어오는 함수   
![image](https://user-images.githubusercontent.com/130421694/234299360-6c8a0829-78ba-479d-aaa2-ae0aab36fc15.png)
* SET_BIT와 마찬가지
* __tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN)   
  → tmpreg = *(40021018) & 16__
<br></br>
___
### vi. UNUSED
* 현재로써는 아무것도 안함
* 디버깅할때 사용되며 에러메세지를 출력한다는 것만 알아두고 넘어가자
* __UNUSED(tmpreg)__ 는 현재 예제에서는 아무것도 하지 않음
<br></br>
<br></br>
___
### vii. __HAL_RCC_GPIOC_CLK_ENABLE() 함수의 의미
* 사실상 __HAL_RCC_GPIOC_CLK_ENABLE() 의 내부에서 동작하는 구문은 SET_BIT 뿐이다
* SET_BIT 함수는 GPIOC의 클럭을 활성화하는 함수였기 때문에 이 함수는 GPIOC 클럭을 활성화하는 함수이다
<br></br>
<br></br>
___
## 2. HAL_GPIO_WritePin(GPIO_LED_GPIO_Port, GPIO_LED_Pin, GPIO_PIN_SET)
* LED를 제어하는 함수
* GPIO 포트와 핀 번호, 핀 상태의 3개 매개변수를 전달 받음
<br></br>

![image](https://user-images.githubusercontent.com/130421694/234308918-19af5509-297a-4341-abd9-9d225b0e2710.png)   
<br></br>
___
### i. assert_param
![image](https://user-images.githubusercontent.com/130421694/234309829-3feb642d-1301-4da5-b159-2b79aff4423b.png)
* 내부적으로 아무것도 하지 않지만 디버거 메세지 출력용
<br></br>
<br></br>
___
### ii. if 조건문
![image](https://user-images.githubusercontent.com/130421694/234311691-8c1920a3-cac7-4f2e-a838-4f46035b8241.png)
* PinState 값이 1이면 GPIOx->BSRR 가 가리키는 곳에 GPIO_Pin 값을 대입
* PinState 값이 0이면 GPIOx->BSRR 가 가리키는 곳에 GPIO_Pin 값을 왼쪽으로 비트 시프트 16번 해서 대입
<br></br>
* 일단 GPIO_LED_GPIO_Port 는 GPIOC인데, GPIOC의 값은 무엇인지 확인해보자
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234314539-a65a4210-fc0a-4e34-9be4-f0897a3729ee.png)
* __GPIO_LED_GPIO_Port = GPIOC = 0x40011000__   
  GPIO_LED_GPIO_Port 의 값은 0x40011000 이다
  
* __GPIO_LED_Pin = 8192 = *(0x10000000000000) ( 14번째 비트 )__   
  → 1 << 13
* __GPIO_PIN_SET = 1__
<br></br>
* 사실 위의 세 값은 스위치와 LED를 다룰 때 이미 확인했다

<br></br>
<br></br>
___
### iii. HAL_GPIO_WritePin 함수의 의미
* HAL_GPIO_WritePin 함수의 의미를 데이터 시트를 보며 확인해보자
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234320757-7171b163-2b81-4de7-9ebb-363b13a3a8a0.png)
* ODR 비트는 BSRR의 비트 값을 SW적으로 바꾸는 것 외에는 읽기/쓰기가 안됨
<br></br>
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234318070-115f72b7-500b-4b9c-b098-014d79dd0520.png)
* __GPIOC의 BS13을 1로 설정한 것__
  → PC13의 LED가 켜짐
<br></br>

![image](https://user-images.githubusercontent.com/130421694/234319201-0b7d27fa-3c3d-4745-9d3c-64fa61a2b862.png)


* 보통 GPIO 제어할 때 값이 111 ... 111 이면 모든 LED가 켜있는 거고 원하는 비트만 0으로 바꾸는 식으로 제어하지만   
  이 경우는 특이한 경우
* 13번 핀을 키고싶다 → BS13 을 1로
* 13번 핀을 끄고싶다 → BR13 을 1로
<br></br>
<br></br>
___
## 3. Configure GPIO pin

* 사용할 GPIO의 핀값, 모드, 속도 등을 설정하는 부분   
![image](https://user-images.githubusercontent.com/130421694/234326030-2b69fb17-bfa7-47b2-90fc-1c085342fc08.png)
![image](https://user-images.githubusercontent.com/130421694/234325581-67506927-5b94-4905-8c34-bb4ba44b75c1.png)
<br></br>
<br></br>
___
### i. GPIO_LED_Pin
![image](https://user-images.githubusercontent.com/130421694/234329831-293bd8ef-5da3-4a25-ae16-16a110303ff9.png)   
* 0x2000 은 1을 왼쪽으로 13번 비트 시프트한 것과 같다
<br></br>
___
### ii. GPIO_MODE_OUTPUT_PP
![image](https://user-images.githubusercontent.com/130421694/234330569-d80f65be-7f5c-4404-8d64-e8e07f2aab2f.png)
<br></br>
___
### iii. GPIO_PULLDOWN
![image](https://user-images.githubusercontent.com/130421694/234332612-073fd55e-d95b-4ca6-bf66-f9a2df96de74.png)
<br></br>
___
### iv. GPIO_SPEED_FREQ_HIGH
![image](https://user-images.githubusercontent.com/130421694/234332764-7ce777e4-12bd-4120-88de-67a0408af94c.png)
* GPIO_SPEED_FREQ_HIGH = 3 << 0 = 3
* 결과적으로 GPIO_InitTypeDef 구조체 GPIO_InitStruct의 내부 변수 값이 각각 0x2000, 1, 2, 3 이라는 것
<br></br>
<br></br>
___

### v. HAL_GPIO_Init(GPIO_LED_GPIO_Port, &GPIO_InitStruct)
* 코드가 길기 때문에 필요한 부분만 짚고 넘어가자
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234599961-28dee60a-5c16-4223-acbb-ab3dcc04fbd6.png)
<br></br>
* while 문을 보면 조건문에서 Pin 값을 position 만큼 오른쪽으로 비트 시프트하고 그 값이 0이 아니면 반복한다는 것을 알 수 있다   
  이 때 사진에는 보이지 않지만 실행문 가장 아래에서 posoition 값은 1씩 증가한다   
  __따라서 Pin 값은 밑에서 14번째 비트만 1이고 그 아래는 모두 0인 값이기 때문에 position 값이 13일 때 까지만 반복한다__
  <br></br>
* 또한 사진에는 보이지 않지만 while 내부에는 ioposition, iocurrent 값을 설정하는 부분 밑으로는 하나의 if문 만이 존재한다   
  if문 내부로 들어가기 위해 ioposition 과 iocurrent 값이 같으려면 position이 핀 번호 값인 13과 같아야 하고    
  while 문은 positin이 핀 번호 13과 같을 때 까지만 실행한다는 것을 되새기자   
  __따라서 position 값이 핀 번호 값과 일치할 때만 while 조건문과 if 조건문에 충족되어 내부의 switch 문을 실행한다__
  
  ![image](https://user-images.githubusercontent.com/130421694/234340784-ffb58545-01ef-4cc5-8449-9411cb3dd561.png)
* if 조건문 내부로 들어오면 GPIO_InitStruct 의 Mode 값에 따라 config를 설정해준다
![image](https://user-images.githubusercontent.com/130421694/234341280-fe93fa5d-575f-422a-880f-6a9c4fb430e8.png)
* HAL_GPIO_Init 함수에 들어올 때 Speed 값은 3이었다
* __config = 3+0 = 3__

![image](https://user-images.githubusercontent.com/130421694/234343556-d2406e63-6b13-457b-8dcb-a38a1bff80a8.png)
* switch 문을 나오면 iocurrent 값 ( = 핀 번호 )에 따라서 CRL, CRH 레지스터 중 사용할 것을 선택한다   
  → 13번 핀이므로 CRH를 선택한다
* 선택한 레지스터에 따른 offset 값도 구한다
* HAL_GPIO_Init 함수로 들어올 때, GPIOx는 GPIOC ( = 0x4001 0000 )를 전달 받았고   
  사진을 첨부하진 않았지만 GPIO_TypeDef 구조체에서 1,2번째 변수가 각각 CRL, CRH 이다   
  → GPIOx->CRH = *0x4001 0004 가 된다
  __configregister = *0x4001 0004__
<br></br>  
* position == 13 이기에 if 조건문 내부로 들어왔었음을 기억하자   
  __registeroffset = (13-8) << 2 = 20__
<br></br>
<br></br>

  #### MODIFY_REG
  * MODIFY_REG 함수는 위에서 구한 config, configregister, registeroffset 을 가지고 어떤 것을 한다는 것을 볼 수 있다
![image](https://user-images.githubusercontent.com/130421694/234345230-be1f9bf6-86d1-4047-9b54-9d168be3dc28.png)
  * 먼저 결과적으로는 __REG = (REG & ~CLEARMASK) | SETMASK__ 와 같다
  * 이 연산을 이해하려면 비트 마스킹을 알아야 한다
<br></br>
<br></br>
  #### 비트 마스킹
  ![image](https://user-images.githubusercontent.com/130421694/234572058-0f2c29d3-98d4-48c8-b23a-4d583f16ff05.png)
  * 2진수 10011011 를 밑에서 5번째 비트만 0으로 바꾸고 싶다면 어떻게 해야할까?   
  <br></br>
  ![image](https://user-images.githubusercontent.com/130421694/234572713-63bdc3bc-47df-494e-8a02-ee7654013c7b.png)
  <br></br>
  * 먼저 1 << 4 를 준비한다
  * 그리고 1 << 4에 NOT 연산을 취해주면 위와 같이 된다
  <br></br>
  ![image](https://user-images.githubusercontent.com/130421694/234573624-ba7a1d17-b3dd-4950-83b9-f0332fe2f223.png)
  * 위에서 구한 ~(1<<4) 을 기존의 10011011 과 AND 연산을 해주면 위와 같이 5번째 비트만 0으로 바뀌는 것을 볼 수 있다
  * 이것을 __비트 마스킹__ 이라 한다
  <br></br>
  ![image](https://user-images.githubusercontent.com/130421694/234574876-ff9645cb-5a95-4540-8990-99926e2fa8d3.png)
  * 반대로 원하는 비트만 1로 바꾸고 싶다면 OR 연산을 이용하면 된다
  * 이번엔 밑에서 6번째 비트를 바꾸기 위해 1<<5 해주고 10001011 과 OR 연산을 취하면 위와 같이 변한다
  <br></br>
  * 이 개념을 가지고 MODIFY_REG 함수를 다시 보면   
    이 함수는 REG에 들어있는 값의 CLEARMASK에 해당하는 비트를 0으로 바꿔준 뒤   
    다시 SETMASK에 해당하는 비트를 1로 바꿔준 값을 REG가 가리키는 곳에 저장한다는 것을 알 수 있다
  

![image](https://user-images.githubusercontent.com/130421694/234347337-144f9e92-21a2-4ca1-b321-dfd51e828b40.png)
* 비트 마스킹을 알았으니 MODIFY_REG 함수에 집어넣은 인자 중 구하지 않은 것을 따져보자   
<br></br>
  ##### (GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset
  * GPIO_CRL_MODE0 = 3 ( = 0x11 )임을 이미 위에서 확인했다   
    GPIO_CRL_CNF0 = 3 << 2 = 12 ( 0x1100 )   
    → (GPIO_CRL_MODE0 | GPIO_CRL_CNF0) = 0x11 | 0x1100 = 0x1111   
    → 이것을 다시 registeroffset = 20 만큼 왼쪽으로 비트 시프트 한 값이므로    
    → __CLEARMASK = 1111 0000 0000 0000 0000 0000 ( 밑에서 21~24 번째 비트가 1 )__
<br></br>
  ##### config << registeroffset = 11 << 20    
  __→ SETMASK = 11 0000 0000 0000 0000 0000 ( 밑에서 21번째, 22번째 비트가 1 )__
<br></br>
* 따라서 MODIFY_REG 함수는 configregister가 가리키는 값의 21~24번째 비트를 0으로 바꿔준 뒤, 다시 21, 22번째 비트를 1로 바꿔준 것이다
<br></br>
![image](https://user-images.githubusercontent.com/130421694/234582901-f6b0a851-0f85-488d-9bc1-5e6883664f56.png)
* 디버거를 통해 MODIFY_REG 함수를 거치기 전과 후의 값을 비교해보자
* 21~24 번째 값이 0이 된 후 다시 21,22번째 값이 1이 된 것을 확인했다
<br></br>
<br></br>
___
### vi. HAL_GPIO_Init 의 의미
* 함수 밖에서 생성한 GPIO_InitTypeDef 구조체를 하나 받아온다
* 받아온 구조체의 값에 따라서 CRH 레지스터 값을 변경해준다
![image](https://user-images.githubusercontent.com/130421694/234614700-56520978-42f7-4ca7-8700-aab6b30e7b42.png)
<br></br>
<br></br>
___
### vii. Configure GPIO pin 의 의미
* GPIO의 핀, 모드, 풀업/풀다운, 클럭속도를 넣어준다
* 설정한 4가지 값을 가지고 HAL_GPIO_Init 함수를 통해 실제로 CRH 레지스터 값을 변경한다
* 핀 번호가 0~7 사이에 있었다면 CRL 레지스터를 변경한다

  
