#ifndef __pdm_allocator__h__
#define __pdm_allocator__h__

/****************************************************************************
**
** File: pdm_allocator.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





//===========================================================================
typedef struct _pdm_allocator_t
{
	pdm_memory_t* memory;
	pdm_size_t    aligned_size;
	pdm_size_t    allocated_size;
	pdm_size_t    deallocated_size;
}
pdm_allocator_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t  pdm_allocator_create     (pdm_allocator_t* ctx);
PDM_API void        pdm_allocator_destroy    (pdm_allocator_t* ctx);
PDM_API pdm_size_t  pdm_allocator_align_size (pdm_allocator_t* ctx, pdm_size_t size);
PDM_API pdm_bool_t  pdm_allocator_allocate   (pdm_allocator_t* ctx, pdm_memory_t* memory);
PDM_API void        pdm_allocator_free       (pdm_allocator_t* ctx, pdm_memory_t* memory);





#endif




