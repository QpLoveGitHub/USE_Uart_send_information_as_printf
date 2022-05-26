
//*******************************************************************************************************
//
//                                      ��������Ⱥ������
//                              (c) Copyright 2011.08-2011.10 
//                                     All Rights Reserved
//                                           V 1.00
//
//  
//  ����  :     �����
//  �ļ���:     type.h
//  �ļ�����:   �����������͵Ķ���
//
//*******************************************************************************************************

#ifndef _TYPE_H
#define _TYPE_H

#include "stdio.h"
//#include "dPrintf.h"

#if defined(_DEBUG)
#define DEBUG_FATAL(fmt, arg...)        dPrintf(fmt, ##arg)
#define DEBUG_ERROR(fmt, arg...)        dPrintf(fmt, ##arg)
#define DEBUG_WARNING(fmt, arg...)      dPrintf(fmt, ##arg)
#define DEBUG_INFO(fmt, arg...)         dPrintf(fmt, ##arg)
#define DEBUG_TRACE(fmt, arg...)      //dPrintf(fmt, ##arg)
#else
#define DEBUG_FATAL(format, ...)
#define DEBUG_ERROR(format, ...)
#define DEBUG_WARNING(format, ...)
#define DEBUG_INFO(format, ...)
#define DEBUG_TRACE(format, ...)
#endif

#define CHAR        char
#define UCHAR       unsigned char       
#define USHORT      unsigned short
#define ULONG       unsigned long
#define LONG        long
#define FLOAT       float
#define UFLOAT      unsigned float

#ifndef _STATUS 
#define _STATUS     char
#endif

#ifndef _VOID
#define _VOID       void
#endif

#ifndef _BOOL
#define _BOOL       unsigned char
#endif

#ifndef _STATIC
#define _STATIC     static
#endif

#ifndef U8
#define U8      unsigned char
#endif

#ifndef S8
#define S8      signed char
#endif

#ifndef U16
#define U16     unsigned short
#endif

#ifndef S16
#define S16     signed short
#endif

#ifndef U32
#define U32     unsigned long
#endif

#ifndef S32
#define S32     signed long
#endif

#ifndef NULL
#define NULL    (void *)0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef OK
#define OK      0
#endif

#ifndef ERROR
#define ERROR  (U8)(-1)
#endif

#ifndef ALARM
#define ALARM   1
#endif

#ifndef ALARM_NONE
#define ALARM_NONE  0
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OK_NO_RELEASE
#define OK_NO_RELEASE   2
#endif

// �������ش���ֵ����
#define ERR_WAITING     1
#define ERR_FATAL       2

#define CONNECT_NONE    0
#define CONNECT_L2      1
#define CONNECT_APP     2

#define HANDLE_ERROR    NULL

/* 
 ** ����ĸ���״̬Ϊ��״̬ ��ϵͳ�����л���ֵĸ��ִ�������, ÿ����״̬���ٸ��������������״̬�������ϸ�ڵĹ��� */
#define STATE_END                           255
#define STATE_INIT                          0

/*
 ** ����MESSAGE���̵����״̬ */
#define STATE_MSG_SEND                      1   /* ����һ�����ݰ� */
#define STATE_MSG_WAIT_ACK                  2
#define STATE_MSG_END                       3


#endif

