# hardware control

ieb_dot.ko
ieb_dipsw.ko
ieb_tactsw.ko
ieb_led.ko
ieb_fnd.ko

위의 모듈이 보드에 삽입되어있어야만 작동한다.

dip 스위치를 97에 두고, tact 스위치를 795에 두면 dot matrix에 WELCOME이 출력된다.

입력을 용이하게 하기 위해 키보드 오른쪽의 자판 형식으로 출력되도록 하였다.(ex. 795 입력 시 135로 출력)
