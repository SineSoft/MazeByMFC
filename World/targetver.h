#pragma once

//��������ͷ�ļ���һ��������������ʹ�������ر�Ϊָ��ƽ̨���б��룬˳�򲻿ɱ��
//WIN32_WINNTָ����Ӧ�ó������֧�ֵĲ���ϵͳ�汾,����NT�ں˰汾�Ŷ���
//0x0500---Windows 2000
//0x0501---Windows XP
//0x0502---Windows 2003(Server)
//0x0600---Windows Vista
//      ---Windows 2008(Server)
//0x0601---Windows 7
//      ---Windows 2008 R2(Server)
//���϶��屻Visual Studio 2010֧��
//0x0602---Windows 8
//      ---Windows 2012(Server)
//���϶��屻Visual Studio 2012֧��
#include <WinSDKVer.h>
#define WIN32_WINNT 0x0501 //ϵͳҪ������WinXP
#include <SDKDDKVer.h>
//�ر�˵����������ͷ�ļ���VC6�в����ڡ�
