/****************************************************************************
**
** File: pdm_stack.c
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
pdm_bool_t pdm_stack_create (pdm_stack_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_core_t* core)
{
	return pdm_vector_create(&ctx->vector, element_max_count, element_size, core);
}

void pdm_stack_destroy (pdm_stack_t* ctx)
{
	pdm_vector_destroy(&ctx->vector);
}

//===========================================================================
pdm_size_t pdm_stack_count (pdm_stack_t* ctx)
{
	return pdm_vector_count(&ctx->vector);
}

pdm_bool_t pdm_stack_full (pdm_stack_t* ctx)
{
	return pdm_vector_full(&ctx->vector);
}

pdm_bool_t pdm_stack_empty (pdm_stack_t* ctx)
{
	return pdm_vector_empty(&ctx->vector);
}

void pdm_stack_clear (pdm_stack_t* ctx)
{
	pdm_vector_clear(&ctx->vector);
}

//===========================================================================
pdm_pointer_t pdm_stack_at(pdm_stack_t* ctx, pdm_size_t index)
{
	return pdm_vector_at(&ctx->vector, index);
}

void pdm_stack_erase(pdm_stack_t* ctx, pdm_size_t index)
{
	pdm_vector_erase(&ctx->vector, index);
}

//===========================================================================
void pdm_stack_set (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_vector_set(&ctx->vector, index, pointer);
}

pdm_bool_t pdm_stack_get (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	return pdm_vector_get(&ctx->vector, index, pointer);
}

//===========================================================================
pdm_bool_t pdm_stack_push (pdm_stack_t* ctx, pdm_pointer_t pointer)
{
	return pdm_vector_push_back(&ctx->vector, pointer);
}

void pdm_stack_pop (pdm_stack_t* ctx)
{
	pdm_vector_pop_back(&ctx->vector);
}

//===========================================================================
pdm_pointer_t pdm_stack_top (pdm_stack_t* ctx)
{
	if ( pdm_vector_empty(&ctx->vector) )
	{
		return PDM_NULL_POINTER;
	}

	return pdm_vector_at(&ctx->vector, pdm_vector_count(&ctx->vector)-1u);
}

pdm_size_t pdm_stack_top_index (pdm_stack_t* ctx)
{
	pdm_size_t top_index;


	top_index = (pdm_size_t)-1;
	if ( pdm_vector_empty(&ctx->vector) )
	{
		return top_index;
	}

	top_index = pdm_vector_count(&ctx->vector)-1u;

	return top_index;
}

pdm_bool_t pdm_stack_top_get (pdm_stack_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t index;


	if ( pdm_vector_empty(&ctx->vector) )
	{
		return PDM_FALSE;
	}


	index = pdm_stack_top_index(ctx);

	return pdm_vector_get(&ctx->vector, index, pointer);
}




