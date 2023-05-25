# MX_USART1_UART_Init 함수 분석
⬇ [huart1.Instance](#huart1instance)   
⬇ [huart1.Init](#huart1init)   

* STM32F103C8T6 칩이 제공하는 UART 통신 중 하나인 __USART1을 사용하기 위해 원하는 값을 설정하는 초기화 함수__

![image](https://github.com/htts1049/Embedded/assets/130421694/58d71f8d-0760-4098-8f9e-df7cc1f5f15e)

* MX_USART1_UART_Init 함수에서는 내부 변수인 Instance와 Init의 값을 원하는 대로 설정
* huart1을 HAL_UART_Init 함수에 전달하며 __실제 설정은 HAL_UART_Init 함수 내부에서 실행__
* HAL_UART_Init 함수에서 반환된 값이 HAL_OK (정상 작동)이 아니면 Error_Handler 실행
<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/d5001011-9c06-406c-83fb-0e6bacd4833a)

* huart1 의 자료형은 Uart_HandleTypeDef 구조체로 내부 변수는 위와 같다   
* HAL_UART_Init 함수 안에서는 Lock, gState, RxState, ErrorCode 로 4개 변수를 사용하지만 이는 아래에서 다루도록 한다

* 주석의 설명에 의하면 USART1 초기화에 사용되는 6개 변수의 쓰임새는 다음과 같다
  + Instance　:　UART 레지스터의 주소
  + Init　　　:　UART 통신에 사용되는 매개변수
  + Lock　　 :　UART 통신에 사용되는 객체가 현재 Lock 된 상태인지 알려주는 값
  + gState　　:　전반적인 Handle 관리에 연관된 UART 상태 정보이며, Tx 작동에도 연관됨
  + RxState　 :　Rx 작동에 연관된 UART 상태 정보
  + ErrorCode :　UART 에러 상태에 대한 코드

<br></br>
<br></br>
___
## huart1.Instance
* Instance 의 자료형은 USART_TypeDef 구조체로 내부 변수는 다음과 같다

![image](https://github.com/htts1049/Embedded/assets/130421694/b4726de1-c189-4ff3-9e70-cb08344397ec)

      huart1.Instance = USART1;

* huart1.Instance 에 대입되는 __USART1__ 의 값을 추적하면 다음과 같다

![image](https://github.com/htts1049/Embedded/assets/130421694/282408fd-5db0-4a7c-9970-49621f0b565f)

* USART1 = 0x40000000 + 0x00010000 + 0x00003800   

* 따라서 위는 다음과도 같다   

      huart1.Instance = 0x40013800;

<br></br>

![image](https://github.com/htts1049/Embedded/assets/130421694/e3fd582d-71fa-4f3e-b878-5d17d4e59ac2)

* USART1 은 APB2 에 속해있고 레지스터 메모리 주소가 0x4001 3800 부터 시작하는 것을 확인할 수 있다
<br></br>

⬆ [TOP](#mx_usart1_uart_init-함수-분석)

<br></br>
___
## huart1.Init
* Init 의 자료형은 UART_InitTypeDef 구조체로 내부 변수는 다음과 같다

![image](https://github.com/htts1049/Embedded/assets/130421694/1cb660c9-eaef-43b8-9da8-404bd9ab3009)

```C
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
```

huart1.Init의 7개 매개 변수를 하나씩 분석해보도록 한다

<br></br>
___
### huart1.Init.BaudRate
      huart1.Init.BaudRate = 115200;
* 보드(Baud)는 초당 펄스 수 또는 초당 심볼 수를 뜻하며 보드 레이트는 1초에 몇개의 비트가 오고가는지를 의미
* 초당 115200 개의 비트를 주고 받게 된다
* 보드 레이트는 아래 공식에 의해 계산된다
  + IntegerDivider = ((PCLKx) / (16 * (huart->Init.BaudRate)))
  + FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5

<br></br>
___
### huart1.Init.WordLength
      huart1.Init.WordLength = UART_WORDLENGTH_8B;
* 1개 프레임에 사용되는 데이터 비트의 개수를 지정한다

![image](https://github.com/htts1049/Embedded/assets/130421694/f8250044-1f16-4d11-8a07-416880d382a1)

* UART_WORDLENGTH_8B = 0 이므로 위는 다음과도 같다

      huart1.Init.WordLength = 0;

* 9개의 데이터 비트를 사용하려면 어떻게 해야할까?

![image](https://github.com/htts1049/Embedded/assets/130421694/ed2329c9-95ef-4607-8f55-04bb7ae4ea98)

* 정의된 UART_WORDLENGTH_9B 의 값은 USART_CR1_M 이다
* 이는 1 << 12 이며, 정의된 이름이 USART_CR1 으로 시작하는 것으로 보아 USART_CR1 레지스터의 12번 비트로 추측된다

![image](https://github.com/htts1049/Embedded/assets/130421694/b562ff2f-0a82-4084-afc3-7fd201df50f7)

* 추측이 맞았다
* M 비트는 데이터가 오고 가는 중에는 변경되어선 안된다고 하니 주의가 필요하다

<br></br>
___
### huart1.Init.StopBits
      huart1.Init.StopBits = UART_STOPBITS_1;
* 데이터 전송할 때 프레임이 끝난다는 신호인 정지 비트의 개수를 지정한다

![image](https://github.com/htts1049/Embedded/assets/130421694/63c39fb5-27bc-499c-b8e7-69965fe727ce)

* UART_STOPBITS_1 = 0 이므로 위는 다음과도 같다

      huart1.Init.StopBits = 0;
     
![image](https://github.com/htts1049/Embedded/assets/130421694/298a5aee-940e-4a7c-9b29-e7aa15e5e0ac)

* 정지 비트를 2개 사용하려면 위에서 했던 것과 같이 USART_CR2 레지스터 값의 의미를 찾아본다

![image](https://github.com/htts1049/Embedded/assets/130421694/9156e9d8-b90a-4d01-a220-cc43a0dad9ba)

* UART_STOPBITS_2 는 0x10을 왼쪽으로 12번 비트 시프트한 값이었고 이는 레퍼런스 매뉴얼과 일치한다

<br></br>
___
### huart1.Init.Parity
      huart1.Init.Parity = UART_PARITY_NONE;
* 전송 과정에서 1의 개수가 짝수 혹은 홀수인지를 판단함으로써 비트 오류를 검출하는 __패리티 비트__ 방식을 어떻게 사용할 것인지 지정한다

![image](https://github.com/htts1049/Embedded/assets/130421694/31130b58-5cee-42e9-8271-f71a972013b7)

* UART_PARITY_NONE = 0 이므로 위는 다음과도 같다

      huart1.Init.Parity = 0;
      
![image](https://github.com/htts1049/Embedded/assets/130421694/c31d2a12-0781-4e89-a7ed-fbaa26c479dc)

* USART_CR1_PCE = 1 << 10
* USART_CR1_PS = 1 << 9

![image](https://github.com/htts1049/Embedded/assets/130421694/7a121d31-e55d-4ff7-b7a4-87ce1455a19b)

* PCE비트가 1이면 패리티 비트를 사용한다.
  + 데이터 전송시 계산된 패리티 비트가 위치에 맞게 삽입
  + 데이터 수신시 패리티 비트를 체크
  + M비트 ( WordLength 담당 ) 가 1이면 MSB에서 9번째, 0이면 MSB에서 8번째 위치에서 수행
* PS비트는 PCE비트가 1일 때 동작하고 패리티 비트의 짝수/홀수를 결정한다
* UART_PARITY_NONE = 0 으로 설정했으므로 패리티 비트를 사용하지 않는다

<br></br>
___
### huart1.Init.Mode
      huart1.Init.Mode = UART_MODE_TX_RX;
* UART 통신을 사용함에 있어 송수신 여부를 결정한다

![image](https://github.com/htts1049/Embedded/assets/130421694/8ee92a80-7ca3-412f-8875-d6a303674e8f)

* UART_MODE_TX_RX = (1 << 3) | (1 << 2) 이므로 위는 다음과도 같다

      huart1.Init.Mode = 0b1100;

![image](https://github.com/htts1049/Embedded/assets/130421694/dc55a870-5160-4e0d-9c88-0107bdbf8c47)

* TE, RE비트는 각각 송신, 수신을 담당하며 0이면 비활성화 1이면 활성화된다
* UART_MODE_TX_RX 의 값은 TE, RE 비트를 모두 1로 설정한 것이므로 송신과 수신 모두 사용한다는 의미이다

<br></br>
___
### huart1.Init.HwFlowCtl
      huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
* 하드웨어의 흐름제어 사용 여부를 결정한다

![image](https://github.com/htts1049/Embedded/assets/130421694/b33f2e02-324b-43e2-a168-815f0e5b623f)

* UART_HWCONTROL_NONE = 0 이므로 위는 다음과도 같다

      huart1.Init.HwFlowCtl = 0;

* USART_HWCONTROL_RTS = 1 << 8
* USART_HWCONTROL_CTS = 1 << 9
* USART_HWCONTROL_RTS_CTS = (1 << 8) | (1 << 9)

![image](https://github.com/htts1049/Embedded/assets/130421694/167a0563-1f19-43f2-904d-099fec3b050e)

* CTSE비트가 1이면 CTS 모드 활성화
  + 데이터는 CTS 입력이 활성화될 때 (0으로 연결될 때)에만 전송됨
  + 데이터 전송 중 CTS 입력이 비활성화되면 전송이 완료된 후 CTS 입력이 멈춤
  + CTS 입력이 비활성화된 상태에서 데이터 레지스터에 데이터가 쓰여지면 CTS 입력이 활성화될 때까지 전송이 지연됨

* RTSE비트가 1이면 RTS 모드 활성화
  + 수신 버퍼에 공간이 있을 때에만 데이터가 요청됨
  + 전송 중인 문자가 전송이 완료되면 중지될 것으로 예상됨
  + 데이터를 받을 수 있을 때 RTS 출력이 활성화 (0으로 연결)

![image](https://github.com/htts1049/Embedded/assets/130421694/66cf4017-7474-461c-a802-3fe3b515b864)

* RTS/CTS 신호는 원래 반이중 통신 방법을 위해 사용되었다
  + FTDI 모듈에 RTS는 없고 CTS만 있는 것이 이런 이유로 생각된다
* 송수신측은 RTS/CTS를 서로 교차하여 연결한다
* 주로 송신측에서 RTS, 수신측에서 CTS를 보낸다

<br></br>
___
### huart1.Init.OverSampling
      huart1.Init.OverSampling = UART_OVERSAMPLING_16;
* 8배 오버 샘플링의 활성화 여부를 결정
* 더 높은 속도(최대 fPCLK/8)를 달성하기 위해 사용
* STM32F100xx 시리즈에서만 사용 가능하므로 OverSampling은 항상 16으로 설정
  + 현재 사용 중인 칩은 STM32F103C8T6 이다

![image](https://github.com/htts1049/Embedded/assets/130421694/6b7995f9-fb96-4c2e-abe0-795cd44e9b6e)

* UART_OVERSAMPLING_16 = 0 이므로 위는 다음과도 같다

      huart1.Init.OverSampling = 0;

* 사용 중인 칩이 STM32F100xx 시리즈가 아니므로 8배 샘플링은 사실상 사용되지 않는다

<br></br>

⬆ [TOP](#mx_usart1_uart_init-함수-분석)
___
