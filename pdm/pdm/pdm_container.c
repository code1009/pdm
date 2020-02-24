/****************************************************************************
**
** File: pdm_container.c
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
pdm_bool_t pdm_container_create (pdm_container_t* ctx)
{
	pdm_size_t element_aligned_size;
	pdm_size_t element_max_count;


//	element_aligned_size = pdm_allocator_align_size(&ctx->core->allocator, ctx->element_size);
	element_aligned_size = ctx->element_size;
	element_max_count    = ctx->element_max_count;


	ctx->element_aligned_size = element_aligned_size;
	ctx->element_count        = 0u;


//	ctx->memory.size = pdm_allocator_align_size(&ctx->core->allocator, element_aligned_size * element_max_count);
	ctx->memory.size = element_aligned_size * element_max_count;
	
	return pdm_allocator_allocate(&ctx->core->allocator, &ctx->memory);
}

void pdm_container_destroy (pdm_container_t* ctx)
{
	pdm_container_clear(ctx);
	pdm_allocator_free(&ctx->core->allocator, &ctx->memory);
}

//===========================================================================
pdm_size_t pdm_container_count (pdm_container_t* ctx)
{
	return ctx->element_count;
}

pdm_bool_t pdm_container_full (pdm_container_t* ctx)
{
	if ( ctx->element_max_count==ctx->element_count )
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}

pdm_bool_t pdm_container_empty (pdm_container_t* ctx)
{
	if ( 0u==ctx->element_count )
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}

void pdm_container_clear (pdm_container_t* ctx)
{
	ctx->element_count = 0u;
}

//===========================================================================
pdm_bool_t pdm_container_push_back (pdm_container_t* ctx, pdm_pointer_t pointer)
{
	return pdm_container_insert(ctx, ctx->element_count, pointer);
}

void pdm_container_pop_back (pdm_container_t* ctx)
{
	if (PDM_FALSE==pdm_container_empty(ctx))
	{
		ctx->element_count--;
	}
}

pdm_bool_t pdm_container_push_front (pdm_container_t* ctx, pdm_pointer_t pointer)
{
	return pdm_container_insert(ctx, 0u, pointer);
}

void pdm_container_pop_front (pdm_container_t* ctx)
{
	pdm_container_erase(ctx, 0u);
}

//===========================================================================
void pdm_container_move (pdm_container_t* ctx, pdm_size_t index_to, pdm_size_t index_from)
{
	pdm_byte_t* e_to;
	pdm_byte_t* e_from;


	if (index_to   >= ctx->element_max_count)
	{
		return /*PDM_FALSE*/;
	}
	if (index_from >= ctx->element_max_count)
	{
		return /*PDM_FALSE*/;
	}


	e_to   = ctx->memory.pointer + (index_to  *ctx->element_aligned_size);
	e_from = ctx->memory.pointer + (index_from*ctx->element_aligned_size);

	pdm_copy_memory(e_to, e_from, ctx->element_size);


	/*return PDM_TRUE;*/
}

void pdm_container_move_down (pdm_container_t* ctx, pdm_size_t index)
{
	pdm_size_t count;
	pdm_size_t i;


	if (index > ctx->element_count)
	{
		return /*PDM_FALSE*/;
	}


	count = ctx->element_count - index;
	for (i=0u; i<count; i++)
	{
		pdm_container_move(ctx, ctx->element_count-i, ctx->element_count-i-1u);
	}


	/*return PDM_TRUE;*/
}

void pdm_container_move_up (pdm_container_t* ctx, pdm_size_t index)
{
	pdm_size_t count;
	pdm_size_t i;


	if (index > ctx->element_count)
	{
		return /*PDM_FALSE*/;
	}


	count = ctx->element_count - index;
	for (i=0u; i<count; i++)
	{
		pdm_container_move(ctx, index+i, index+i+1u);
	}


	/*return PDM_TRUE;*/
}

//===========================================================================
pdm_bool_t pdm_container_insert (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_byte_t* e;


	if (ctx->element_count >= ctx->element_max_count)
	{
		return PDM_FALSE;
	}
	if (index > ctx->element_count)
	{
		return PDM_FALSE;
	}


	if (ctx->element_count>0u)
	{
		pdm_container_move_down(ctx, index);
	}


	e = ctx->memory.pointer + (index*ctx->element_aligned_size);
	pdm_copy_memory(e, pointer, ctx->element_size);
	ctx->element_count++;


	return PDM_TRUE;
}

void pdm_container_erase (pdm_container_t* ctx, pdm_size_t index)
{
	if (ctx->element_count == 0u)
	{
		return /*PDM_FALSE*/;
	}
	if (index>=ctx->element_count)
	{
		return /*PDM_FALSE*/;
	}


	pdm_container_move_up(ctx, index);


	ctx->element_count--;


	/*return PDM_TRUE;*/
}

//===========================================================================
void pdm_container_set (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_byte_t* e;


	if (ctx->element_count >= ctx->element_max_count)
	{
		return /*PDM_FALSE*/;
	}
	if (index >= ctx->element_count)
	{
		return /*PDM_FALSE*/;
	}


	e = ctx->memory.pointer + (index*ctx->element_aligned_size);
	pdm_copy_memory(e, pointer, ctx->element_size);


	/*return PDM_TRUE;*/
}

pdm_bool_t pdm_container_get (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_byte_t* e;


	if (ctx->element_count >= ctx->element_max_count)
	{
		return PDM_FALSE;
	}
	if (index >= ctx->element_count)
	{
		return PDM_FALSE;
	}


	e = ctx->memory.pointer + (index*ctx->element_aligned_size);
	pdm_copy_memory(pointer, e, ctx->element_size);


	return PDM_TRUE;
}

//===========================================================================
pdm_pointer_t pdm_container_at (pdm_container_t* ctx, pdm_size_t index)
{
	pdm_byte_t* e;


	e = PDM_NULL_POINTER;
	if (index < ctx->element_count)
	{
		e = ctx->memory.pointer + (index*ctx->element_aligned_size);
	}


	return e;
}

//===========================================================================
pdm_pointer_t pdm_container_memory (pdm_container_t* ctx, pdm_size_t index)
{
	pdm_byte_t* e;


	e = PDM_NULL_POINTER;
	if (index < ctx->element_max_count)
	{
		e = ctx->memory.pointer + (index*ctx->element_aligned_size);
	}


	return e;
}




