//*****************************************************************************
// file		: ringbuf.h
// 
// Copyright (c) 2006-2012 HSAE co. Ltd. All rights reserved
// 
// Change Logs:
// Date				Author        Note	
// 2015/04/02		chc	      
// 
//*****************************************************************************
#ifndef __RINGBUF_H__
#define __RINGBUF_H__

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

typedef struct 
{
    unsigned char head;
    unsigned char tail;
    unsigned char size;
    unsigned char *pBuf;
}tRingBuf;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void ringbuf_init(tRingBuf *pRingBuf, unsigned char *pBuf, unsigned char size);
unsigned char ringbuf_empty(tRingBuf *pRingBuf);
unsigned char ringbuf_full(tRingBuf *pRingBuf);
unsigned char ringbuf_avail(tRingBuf *pRingBuf);
unsigned char ringbuf_size(tRingBuf *pRingBuf);
unsigned char ringbuf_used(tRingBuf *pRingBuf);
unsigned char ringbuf_free(tRingBuf *pRingBuf);
void ringbuf_write_one(tRingBuf *pRingBuf, unsigned char data);
void ringbuf_write(tRingBuf *pRingBuf, unsigned char *pData, unsigned char len);
unsigned char ringbuf_read_one(tRingBuf *pRingBuf);
void ringbuf_read(tRingBuf *pRingBuf, unsigned char *pData, unsigned char len);

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

#endif //  __RINGBUF_H__

