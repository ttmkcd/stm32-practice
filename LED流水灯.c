#include "stm32f10x.h"      → 工具箱：芯片所有寄存器和库函数的名单。
                               没有它，编译器不认识 GPIOA 是谁。

#include "Delay.h"          → 把江协 1-3 节的延时模块拉进来。
                               Delay_ms 住在这——漏加它，编译能过、链接报错。

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                            → 推电闸：给 GPIOA 房间通电。
                               这行没有，后面全白配。

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    → 填单①：推挽输出
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;         → 填单②：整组口都要
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   → 填单③：翻转速度

GPIO_Init(GPIOA, &GPIO_InitStructure);
                            → 递交：配置单写进硬件寄存器，
                               PA0~PA7 从此是输出口。

while (1)                   → 死循环 = 单片机的主业。
                               一遍干完从头来，断电才算下班。

GPIO_Write(GPIOA, ~(0x0001 << i));
                            → 一口气写整个A组。1 左移 i 位，指到第 i 个口；
                               ~ 取反后那位变 0（低电平）→ 第 i 个灯亮，
                               其余位是 1 → 灭。这是流水的心脏。

Delay_ms(100);              → 卡住 100ms：灯亮着别动。
                               这个数决定流水跑多快。

i++;  if (i >= 8) i = 0;   → 1 跑到头回零，循环流水。
