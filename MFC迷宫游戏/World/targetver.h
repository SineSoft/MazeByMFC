#pragma once

//下面两个头文件和一个常量定义用于使编译器特别为指定平台进行编译，顺序不可变更
//WIN32_WINNT指定了应用程序最低支持的操作系统版本,依据NT内核版本号定义
//0x0500---Windows 2000
//0x0501---Windows XP
//0x0502---Windows 2003(Server)
//0x0600---Windows Vista
//      ---Windows 2008(Server)
//0x0601---Windows 7
//      ---Windows 2008 R2(Server)
//以上定义被Visual Studio 2010支持
//0x0602---Windows 8
//      ---Windows 2012(Server)
//以上定义被Visual Studio 2012支持
#include <WinSDKVer.h>
#define WIN32_WINNT 0x0501 //系统要求：至少WinXP
#include <SDKDDKVer.h>
//特别说明：这两个头文件在VC6中不存在。
