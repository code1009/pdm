/****************************************************************************
**
** File: pdm_memory.c
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pdm.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void pdm_memory_copy (pdm_memory_t* destination, pdm_memory_t* source)
{
	pdm_size_t copy_size;


	copy_size = source->size;
	if (copy_size>destination->size)
	{
		copy_size = destination->size;
	}

	pdm_copy_memory(destination->pointer, source->pointer, copy_size);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void pdm_copy_memory (pdm_pointer_t destination, pdm_pointer_t source, pdm_size_t size)
{
	pdm_byte_t* s;
	pdm_byte_t* d;

	pdm_size_t count;


	s     = (pdm_byte_t*)source;
	d     = (pdm_byte_t*)destination;
	count = size;
	while (count--)
	{
		*d++ = *s++;
	}
}

void pdm_fill_memory (pdm_pointer_t destination, pdm_byte_t ch, pdm_size_t size)
{
	pdm_byte_t* d;

	pdm_size_t count;


	d     = (pdm_byte_t*)destination;
	count = size;
	while (count--)
	{
		*d++ = ch;
	}
}

void pdm_zero_memory (pdm_pointer_t destination, pdm_size_t size)
{
	pdm_fill_memory(destination, 0u, size);
}

