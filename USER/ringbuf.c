//*****************************************************************************
// file		: ringbuf.c
// 
// Copyright (c) 2011-2014 HSAE co. Ltd. All rights reserved
// 
// Change Logs:
// Date				Author		Note	
// 2015/04/02    	chc			
// 
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup 
//! @{
//
//*****************************************************************************
#include "ringbuf.h"

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void ringbuf_init(tRingBuf *pRingBuf, unsigned char *pBuf, unsigned char size)
{
    pRingBuf->head = pRingBuf->tail = 0;
    pRingBuf->pBuf = pBuf;
    pRingBuf->size = size;
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_empty(tRingBuf *pRingBuf)
{
    return (pRingBuf->head == pRingBuf->tail);
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_full(tRingBuf *pRingBuf)
{
    return (((pRingBuf->tail + 1) % pRingBuf->size) == pRingBuf->head);
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_avail(tRingBuf *pRingBuf)
{
    return pRingBuf->size - pRingBuf->head + pRingBuf->tail;
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_size(tRingBuf *pRingBuf)
{
    return pRingBuf->size;
}

/**
  * \brief Returns number of bytes stored in ring buffer.
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_used(tRingBuf *pRingBuf)
{
    unsigned char tail, head;

    tail = pRingBuf->tail;
    head = pRingBuf->head;

    return((head >= tail) ? (head - tail) :
        (pRingBuf->size - (tail - head))); 
}

/**
  * \brief Returns number of bytes available in a ring buffer.
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_free(tRingBuf *pRingBuf)
{
    return((pRingBuf->size - 1) - ringbuf_used(pRingBuf));
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void ringbuf_write_one(tRingBuf *pRingBuf, unsigned char data)
{
    if (ringbuf_avail(pRingBuf) != 0)
    {
        pRingBuf->pBuf[pRingBuf->head] = data;
        pRingBuf->head++;

        if (pRingBuf->head >= pRingBuf->size)
        {
            pRingBuf->head = 0;
        }
    }
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void ringbuf_write(tRingBuf *pRingBuf, unsigned char *pData, unsigned char len)
{
    unsigned char i;

    for (i = 0; i < len; i++)
    {
        ringbuf_write_one(pRingBuf, pData[i]);
    }
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
unsigned char ringbuf_read_one(tRingBuf *pRingBuf)
{
    unsigned char data;

    data = pRingBuf->pBuf[pRingBuf->tail++];

    if (pRingBuf->tail >= pRingBuf->size)
    {
        pRingBuf->tail = 0;
    }

    return data;
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void ringbuf_read(tRingBuf *pRingBuf, unsigned char *pData, unsigned char len)
{
    unsigned char i;

    for (i = 0; i < len; i++)
    {
        pData[i] = ringbuf_read_one(pRingBuf);
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

