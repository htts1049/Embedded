# Analyze HAL_init()

<br></br>
* 먼저, PREFETCH_ENABLE 이 0이 아니라면 조건문을 실행한다

  + 조건문 안으로 들어가면 다시 여러 개의 defined() 함수로 이루어진 조건문이 기다린다
  + 다양한 칩에 따라서 속성을 바꾸려고 앞에 defined로 확인하는 것
  
    - define이 안 돼 있으면 IDE가 회색 처리하여 접근 안함을 표시
    - IDE의 장점 중 하나 → 이게 없으면 소스 분석하는데 굉장히 애먹는다
<br></br>
![image_1](https://user-images.githubusercontent.com/130421694/232226111-f83b2b63-0cb4-4f63-aa57-b48c89e8243d.png)

* 이 칩은 STM32F103xB에 해당하는 것 같다
![image_2](https://user-images.githubusercontent.com/130421694/232226112-9268c7d0-93eb-4c9a-bc55-8fa5846d3364.png)
<br></br><br></br>
---

## __HAL_FLASH_PREFETCH_BUFFER_ENABLE()
<br></br>
* defined 조건문에 해당되니 이 함수를 실행한다

![image_3](https://user-images.githubusercontent.com/130421694/232227621-55f94cbb-381d-4e83-aca9-351c980dd098.png)
* 정의를 찾아보니, 다음과 같다
* FLASH->ACR = 0x40000000 + 0x00020000 + 0x00002000 = 0x40022000
  + ACR은 FLASH_Typedef 구조체에서 첫 번째 변수이므로 +0이다
  + 다른 변수라면 자료형 크기에 따라 값을 더했을 것
 
  + volatile 은 최적화 방지용, 이것을 쓰지 않으면 다음과 같은 문제가 발생할 수 있다
    - GPIO 제어시 원하는 동작이 일어나지 않음
    - CPU가 변수를 자기 레지스터에 넣어서 변하지 않음
  <br></br>
  
* FLASH_ACR_PRFTBE = 1 << 4 = 16
* 따라서 위 구문은 이렇다
  <br></br>

* __*(0x40022000) |= 16__

<br></br>
___
## So Why?
<br></br>
* 이 작업을 하는 이유에 대한 답은 데이터시트에 있다
<br></br>
![image_4](https://user-images.githubusercontent.com/130421694/232229011-73fb6afd-fbac-47f0-b044-5326d236bf57.png)
* 위 FLASH_TypeDef 구조체와 같은 구조를 가진다

<br></br>
![image_5](https://user-images.githubusercontent.com/130421694/232229013-5e12eba7-9f33-403e-947f-884bf2a4d8da.png)
* ACR 레지스터의 쓰임새
  1. Prefetch 와 Half cycle access 의 활성화/비활성화
  2. CPU 속도에 따른 Flash 메모리 접근 시간 제어
<br></br>

![image_6](https://user-images.githubusercontent.com/130421694/232229016-d63c41d3-6b59-45c5-8ab7-09e8bc3d5575.png)
* 그리고 우리는 위에서 5번째 비트의 값을 1로 바꿔주었다
* __따라서 PRFTBE 비트 값을 1로 바꾸면서 Prefetch를 활성화 해준 것이다!!__

<br></br>
___
## Prefetch?
<br></br>
* Prefetch가 뭘까? 우리에겐 구글이 있다!
* 참고) http://portable-forensics.blogspot.com/2014/11/prefetch-and-superfetch.html
<br></br>
* SSD가 보급되기 이전, HDD가 주로 쓰일 때 사용됨
* 윈도우는 프리패치 파일에 실행 파일이 사용하는 시스템 자원을 미리 저장하였다가 부팅 시 프리패치 파일을 모두 메모리에 로드
* __실제 사용시 메모리 매핑만을 수행하여 사용함으로써 실행 속도 향상__
* 실행파일을 메모리로 로딩할 때의 효율을 최대한 끌어올리기 위한 목적   
<br></br>

* 요약하자면, 접근 속도가 느린 HDD와 주기억장치의 속도 차이를 극복하기 위해 사용된 방법이라는 것이다   
<br></br>
* HDD의 Read, Write 속도 : 30-150MB/s, 평균 약 80MB/s
* SSD의 Read, Write 속도 : 최대 3.5GB/s
<br></br>
___
