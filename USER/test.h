//*****************************************************************************
// file		: test.h
// test module
// Copyright (c) 2006-2012 HSAE co. Ltd. All rights reserved
// 
// Change Logs:
// Date				Author        Note	
// 2014/01/21		chc	      
// 
//*****************************************************************************
#ifndef __TEST_H__
#define __TEST_H__

//*****************************************************************************
//
//! \addtogroup 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//extern unsigned char DEBUG_CanInfo;		//CAN print
//extern unsigned char DEBUG_UartRec;		//uart print
//extern unsigned char DEBUG_UartSend;
//extern unsigned char DEBUG_KernelInfo;
//
//extern unsigned char DEBUG_TimeInfo;		//Timer print
//extern unsigned char DEBUG_ResendInfo; 	//Resend Print
//extern unsigned char DEBUG_McuTestInfo;	//test print
//extern unsigned char DEBUG_KeyInfo;
//typedef enum
//{
//	TEST_PRINT_LEVEL_MSG,
//	TEST_PRINT_LEVEL_WARNING,
//	TEST_PRINT_LEVEL_ERROR,
//}
//tPrintLevel;
//
//#define TEST_PRINT_LEVEL_DEFAULT		TEST_PRINT_LEVEL_MSG

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void test_init(void);
//void test_set_printlevel(tPrintLevel level);
//void test_process_per10ms(void);
//void test_print_array(unsigned char *pByte, unsigned char len, tPrintLevel level);
void test_printf(unsigned char printFlags, const char *fmt, ...);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif //  __TEST_H__

