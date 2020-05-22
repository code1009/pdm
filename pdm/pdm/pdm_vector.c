/****************************************************************************
**
** File: pdm_vector.c
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
pdm_bool_t pdm_vector_create (pdm_vector_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_core_t* core)
{
	ctx->container.core = core;
	ctx->container.element_size      = element_size;
	ctx->container.element_max_count = element_max_count;

	return pdm_container_create(&ctx->container);
}

void pdm_vector_destroy (pdm_vector_t* ctx)
{
	pdm_container_destroy(&ctx->container);
}

//===========================================================================
pdm_size_t pdm_vector_count (pdm_vector_t* ctx)
{
	return pdm_container_count(&ctx->container);
}

pdm_bool_t pdm_vector_full (pdm_vector_t* ctx)
{
	return pdm_container_full(&ctx->container);
}

pdm_bool_t pdm_vector_empty (pdm_vector_t* ctx)
{
	return pdm_container_empty(&ctx->container);
}

void pdm_vector_clear (pdm_vector_t* ctx)
{
	pdm_container_clear(&ctx->container);
}

//===========================================================================
pdm_pointer_t pdm_vector_at (pdm_vector_t* ctx, pdm_size_t index)
{
	return pdm_container_at(&ctx->container, index);
}

void pdm_vector_erase (pdm_vector_t* ctx, pdm_size_t index)
{
	pdm_container_erase(&ctx->container, index);
}

//===========================================================================
pdm_bool_t pdm_vector_insert (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	return pdm_container_insert(&ctx->container, index, pointer);
}

//===========================================================================
void pdm_vector_set (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	pdm_container_set(&ctx->container, index, pointer);
}

pdm_bool_t pdm_vector_get (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	return pdm_container_get(&ctx->container, index, pointer);
}

//===========================================================================
pdm_bool_t pdm_vector_push_back (pdm_vector_t* ctx, pdm_pointer_t pointer)
{
	return pdm_container_push_back(&ctx->container, pointer);
}

void pdm_vector_pop_back (pdm_vector_t* ctx)
{
	pdm_container_pop_back(&ctx->container);
}

pdm_bool_t pdm_vector_push_front (pdm_vector_t* ctx, pdm_pointer_t pointer)
{
	return pdm_container_push_front(&ctx->container, pointer);
}

void pdm_vector_pop_front (pdm_vector_t* ctx)
{
	pdm_container_pop_front(&ctx->container);
}



