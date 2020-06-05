/****************************************************************************
**
** File: pdm_allocator.c
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
pdm_bool_t pdm_allocator_create (pdm_allocator_t* ctx)
{
	ctx->aligned_size     = sizeof(void*);
	ctx->allocated_size   = 0u;
	ctx->deallocated_size = 0u;

	if (ctx->memory->size < ctx->aligned_size)
	{
		return PDM_FALSE;
	}

	return PDM_TRUE;
}

void pdm_allocator_destroy (pdm_allocator_t* ctx)
{
}

pdm_size_t pdm_allocator_align_size (pdm_allocator_t* ctx, pdm_size_t size)
{
	pdm_size_t multiple;
	pdm_size_t remain;
	pdm_size_t align;


	multiple = size / ctx->aligned_size;
	remain   = size % ctx->aligned_size;

	if ( 0u!=remain )
	{
		multiple++;
	}

	align = multiple * ctx->aligned_size;

	return align;
}

pdm_bool_t pdm_allocator_allocate (pdm_allocator_t* ctx, pdm_memory_t* memory)
{
	pdm_size_t aligned_size;


	aligned_size = pdm_allocator_align_size(ctx, memory->size);
	if ( ctx->memory->size < (ctx->allocated_size+aligned_size) )
	{
		memory->pointer = PDM_NULL_POINTER;
		return PDM_FALSE;
	}


	memory->pointer = ctx->memory->pointer+ctx->allocated_size;

	ctx->allocated_size += aligned_size;

	return PDM_TRUE;
}

void pdm_allocator_free (pdm_allocator_t* ctx, pdm_memory_t* memory)
{
	pdm_size_t aligned_size;


	aligned_size = pdm_allocator_align_size(ctx, memory->size);


	ctx->deallocated_size += aligned_size;
}




