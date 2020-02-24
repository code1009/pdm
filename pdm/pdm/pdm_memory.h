#ifndef __pdm_memory__h__
#define __pdm_memory__h__

/****************************************************************************
**
** File: pdm_memory.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_memory_t
{
	pdm_byte_t* pointer;
	pdm_size_t  size;
}
pdm_memory_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API void pdm_memory_copy (pdm_memory_t* destination, pdm_memory_t* source);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API void pdm_copy_memory (pdm_pointer_t destination, pdm_pointer_t source, pdm_size_t size);
PDM_API void pdm_fill_memory (pdm_pointer_t destination, pdm_byte_t ch, pdm_size_t size);
PDM_API void pdm_zero_memory (pdm_pointer_t destination, pdm_size_t size);





#endif




