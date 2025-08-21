#pragma once

#ifndef FW_DEFINES_H
#define FW_DEFINES_H

// clang-format off

// Used to find kernel base
#define K505_XFAST_SYSCALL         0x000001C0
#define K507_XFAST_SYSCALL         0x000001C0
#define K550_XFAST_SYSCALL         0x000001C0
#define K553_XFAST_SYSCALL         0x000001C0
#define K555_XFAST_SYSCALL         0x000001C0
#define K556_XFAST_SYSCALL         0x000001C0
#define K600_XFAST_SYSCALL         0x000001C0
#define K602_XFAST_SYSCALL         0x000001C0
#define K620_XFAST_SYSCALL         0x000001C0
#define K650_XFAST_SYSCALL         0x000001C0
#define K651_XFAST_SYSCALL         0x000001C0
#define K670_XFAST_SYSCALL         0x000001C0
#define K671_XFAST_SYSCALL         0x000001C0
#define K672_XFAST_SYSCALL         0x000001C0
#define K700_XFAST_SYSCALL         0x000001C0
#define K701_XFAST_SYSCALL         0x000001C0
#define K702_XFAST_SYSCALL         0x000001C0
#define K750_XFAST_SYSCALL         0x000001C0
#define K751_XFAST_SYSCALL         0x000001C0
#define K755_XFAST_SYSCALL         0x000001C0
#define K800_XFAST_SYSCALL         0x000001C0
#define K801_XFAST_SYSCALL         0x000001C0
#define K803_XFAST_SYSCALL         0x000001C0
#define K850_XFAST_SYSCALL         0x000001C0
#define K852_XFAST_SYSCALL         0x000001C0
#define K900_XFAST_SYSCALL         0x000001C0
#define K903_XFAST_SYSCALL         0x000001C0
#define K904_XFAST_SYSCALL         0x000001C0
#define K950_XFAST_SYSCALL         0x000001C0
#define K951_XFAST_SYSCALL         0x000001C0
#define K960_XFAST_SYSCALL         0x000001C0
#define K1000_XFAST_SYSCALL        0x000001C0
#define K1001_XFAST_SYSCALL        0x000001C0
#define K1050_XFAST_SYSCALL        0x000001C0
#define K1070_XFAST_SYSCALL        0x000001C0
#define K1071_XFAST_SYSCALL        0x000001C0
#define K1100_XFAST_SYSCALL        0x000001C0
#define K1102_XFAST_SYSCALL        0x000001C0
#define K1150_XFAST_SYSCALL        0x000001C0
#define K1152_XFAST_SYSCALL        0x000001C0
#define K1200_XFAST_SYSCALL        0x000001C0
#define K1202_XFAST_SYSCALL        0x000001C0

// Used in every payload that uses jailbreak();
#define K505_PRISON_0              0x010986A0
#define K507_PRISON_0              0x010986A0
#define K550_PRISON_0              0x01134180
#define K553_PRISON_0              0x01134180
#define K555_PRISON_0              0x01139180
#define K556_PRISON_0              0x01139180
#define K600_PRISON_0              0x01139458
#define K602_PRISON_0              0x01139458
#define K620_PRISON_0              0x0113D458
#define K650_PRISON_0              0x0113D4F8
#define K651_PRISON_0              0x0113D4F8
#define K670_PRISON_0              0x0113E518
#define K671_PRISON_0              0x0113E518
#define K672_PRISON_0              0x0113E518
#define K700_PRISON_0              0x0113E398
#define K701_PRISON_0              0x0113E398
#define K702_PRISON_0              0x0113E398
#define K750_PRISON_0              0x0113B728
#define K751_PRISON_0              0x0113B728
#define K755_PRISON_0              0x0113B728
#define K800_PRISON_0              0x0111A7D0
#define K801_PRISON_0              0x0111A7D0
#define K803_PRISON_0              0x0111A7D0
#define K850_PRISON_0              0x0111A8F0
#define K852_PRISON_0              0x0111A8F0
#define K900_PRISON_0              0x0111F870
#define K903_PRISON_0              0x0111B840
#define K904_PRISON_0              0x0111B840
#define K950_PRISON_0              0x011137D0
#define K951_PRISON_0              0x011137D0
#define K960_PRISON_0              0x011137D0
#define K1000_PRISON_0             0x0111B8B0
#define K1001_PRISON_0             0x0111B8B0
#define K1050_PRISON_0             0x0111B910
#define K1070_PRISON_0             0x0111B910
#define K1071_PRISON_0             0x0111B910
#define K1100_PRISON_0             0x0111F830
#define K1102_PRISON_0             0x0111F830
#define K1150_PRISON_0             0x0111FA18
#define K1152_PRISON_0             0x0111FA18
#define K1200_PRISON_0             0x0111FA18
#define K1202_PRISON_0             0x0111FA18

// Used in every payload that uses jailbreak();
#define K505_ROOTVNODE             0x022C1A70
#define K507_ROOTVNODE             0x022C1A70
#define K550_ROOTVNODE             0x022EF570
#define K553_ROOTVNODE             0x022EF570
#define K555_ROOTVNODE             0x022F3570
#define K556_ROOTVNODE             0x022F3570
#define K600_ROOTVNODE             0x021BFAC0
#define K602_ROOTVNODE             0x021BFAC0
#define K620_ROOTVNODE             0x021C3AC0
#define K650_ROOTVNODE             0x02300320
#define K651_ROOTVNODE             0x02300320
#define K670_ROOTVNODE             0x02300320
#define K671_ROOTVNODE             0x02300320
#define K672_ROOTVNODE             0x02300320
#define K700_ROOTVNODE             0x022C5750
#define K701_ROOTVNODE             0x022C5750
#define K702_ROOTVNODE             0x022C5750
#define K750_ROOTVNODE             0x01B463E0
#define K751_ROOTVNODE             0x01B463E0
#define K755_ROOTVNODE             0x01B463E0
#define K800_ROOTVNODE             0x01B8C730
#define K801_ROOTVNODE             0x01B8C730
#define K803_ROOTVNODE             0x01B8C730
#define K850_ROOTVNODE             0x01C66150
#define K852_ROOTVNODE             0x01C66150
#define K900_ROOTVNODE             0x021EFF20
#define K903_ROOTVNODE             0x021EBF20
#define K904_ROOTVNODE             0x021EBF20
#define K950_ROOTVNODE             0x021A6C30
#define K951_ROOTVNODE             0x021A6C30
#define K960_ROOTVNODE             0x021A6C30
#define K1000_ROOTVNODE            0x01B25BD0
#define K1001_ROOTVNODE            0x01B25BD0
#define K1050_ROOTVNODE            0x01BF81F0
#define K1070_ROOTVNODE            0x01BF81F0
#define K1071_ROOTVNODE            0x01BF81F0
#define K1100_ROOTVNODE            0x02116640
#define K1102_ROOTVNODE            0x02116640
#define K1150_ROOTVNODE            0x02136E90
#define K1152_ROOTVNODE            0x02136E90
#define K1200_ROOTVNODE            0x02136E90
#define K1202_ROOTVNODE            0x02136E90

// clang-format on

#endif
