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
	ctx->container.core = core;
	ctx->container.element_size      = element_size;
	ctx->container.element_max_count = element_max_count;

	return pdm_container_create(&ctx->container);
}

void pdm_stack_destroy (pdm_stack_t* ctx)
{
	pdm_container_destroy(&ctx->container);
}

//===========================================================================
pdm_size_t pdm_stack_count (pdm_stack_t* ctx)
{
	return pdm_container_count(&ctx->container);
}

pdm_bool_t pdm_stack_full (pdm_stack_t* ctx)
{
	return pdm_container_full(&ctx->container);
}

pdm_bool_t pdm_stack_empty (pdm_stack_t* ctx)
{
	return pdm_container_empty(&ctx->container);
}

void pdm_stack_clear (pdm_stack_t* ctx)
{
	pdm_container_clear(&ctx->container);
}

//===========================================================================
pdm_bool_t pdm_stack_push (pdm_stack_t* ctx, pdm_pointer_t pointer)
{
	return pdm_container_push_back(&ctx->container, pointer);
}

void pdm_stack_pop (pdm_stack_t* ctx)
{
	pdm_container_pop_back(&ctx->container);
}

//===========================================================================
void pdm_stack_set (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_container_set(&ctx->container, index, pointer);
}

pdm_bool_t pdm_stack_get (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	return pdm_container_get(&ctx->container, index, pointer);
}

//===========================================================================
pdm_pointer_t pdm_stack_at (pdm_stack_t* ctx, pdm_size_t index)
{
	return pdm_container_at(&ctx->container, index);
}

//===========================================================================
pdm_pointer_t pdm_stack_top (pdm_stack_t* ctx)
{
	if ( pdm_container_empty(&ctx->container) )
	{
		return PDM_NULL_POINTER;
	}

	return pdm_container_at(&ctx->container, pdm_container_count(&ctx->container)-1u);
}

pdm_size_t pdm_stack_top_index (pdm_stack_t* ctx)
{
	pdm_size_t top_index;


	top_index = (pdm_size_t)-1;
	if ( pdm_container_empty(&ctx->container) )
	{
		return top_index;
	}

	top_index = pdm_container_count(&ctx->container)-1u;

	return top_index;
}

pdm_bool_t pdm_stack_top_get (pdm_stack_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t index;


	if ( pdm_container_empty(&ctx->container) )
	{
		return PDM_FALSE;
	}


	index = pdm_stack_top_index(ctx);

	return pdm_container_get(&ctx->container, index, pointer);
}




