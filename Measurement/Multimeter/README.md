# 멀티미터기 사용법
* 제품명 : SK-4201
* 주의사항 : __DC 60V, AC 25V 이상의 전압은 감전 위험이 있으니 장갑을 끼도록 하자__
* 임베디드 개발을 하다보면 하드웨어에서 문제가 생길 때도 많고,   
  하드웨어 담당자에게 __어떤 부분이 문제인지를 말하기 위해__ 최소한의 멀티미터기 사용법은 알아야 한다
<br></br>
<br></br>
## 교류 전압 측정
<img src="https://user-images.githubusercontent.com/130421694/236671303-cfb8d8b1-6fde-4e23-8bd6-b55e172da304.jpg" width="60%" height="60%"/>   

* 스위치를 AC에 놓고 측정
* 가정용 교류 전압 220V 로 시험 측정
* 양 극단에 테스트 리드를 접촉하면 교류 전압 표시
<br></br>
<br></br>
## 직류 전압 측정
<img src="https://user-images.githubusercontent.com/130421694/236671362-144165d5-2f0a-422a-8e53-63d9536c1a19.jpg" width="60%" height="60%"/>   

* 스위치를 DC에 놓고 측정
* AA 배터리로 시험 측정
* 테스트리드는 적색/흑색이 있으며 각각 (+)극, (-)극을 측정
* 양 극단에 테스트 리드를 접촉하면 직류 전압 표시
* __DC 전원을 반대로 넣으면 기계가 망가질 수 있으니 전원을 넣을 때는 전류 방향이 맞는지 확인해주고 넣는 게 안정적__
<br></br>
<br></br>
## 저항 측정

<img src="https://user-images.githubusercontent.com/130421694/236671375-dc336c03-fa74-483b-8a8e-d2f3bdc98a7d.jpg" width="60%" height="60%"/>   

* 스위치를 Ω(Ohm)에 놓고 측정
* 220Ω 저항으로 시험 측정
* 양 극단에 테스트 리드 접촉하면 저항 값 표시
* __반드시 회로의 전원을 끊고, 콘덴서를 방전시킨 후 측정__
<br></br>
<br></br>

## 도통 측정

<img src="https://user-images.githubusercontent.com/130421694/236671395-b4531839-e3d7-40d1-ae50-a767a7257613.jpg" width="80%" height="80%"/>   

* 스위치를 와이파이 기호와 비슷한 곳에 놓고 측정
* 양 극단에 테스트 리드를 접촉했을 때, 전기가 통하면 부저음 발생과 함께 저항 값 표시
* __반드시 회로의 전원을 끊고, 콘덴서를 방전시킨 후 측정__

<br></br>
<br></br>
___
# 멀티미터기를 통해 GPIO 출력 측정

<img src="https://user-images.githubusercontent.com/130421694/236672685-239ed695-d06d-40f1-8600-2bfe77581635.png" width="80%" height="80%"/>   

* GPIO를 임의로 선택하고 초기 값을 설정
<br></br>
<br></br>

<img src="https://user-images.githubusercontent.com/130421694/236672722-92c8143a-b247-4b7b-924d-508a889feace.png" width="80%" height="80%"/>   

* 1초 간격으로 선택한 GPIO의 출력을 HIGH, LOW로 바꾸는 코드 작성 후 실행
<br></br>
<br></br>
<img src="https://user-images.githubusercontent.com/130421694/236672548-1d8664fa-31f3-47ed-a1b7-a7016b1c4f1c.gif" width="80%" height="80%"/>   

* 테스트 리드의 (+) 극을 GPIO 핀에, (-) 극을 GND에 연결
* 1초 간격으로 출력 전압 값이 3.3V, 0V 로 변경 확인
