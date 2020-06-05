/****************************************************************************
**
** File: pdm_core.c
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
pdm_bool_t pdm_core_create (pdm_core_t* ctx)
{
	pdm_fill_memory(ctx->memory.pointer, 0x00, ctx->memory.size);

	ctx->allocator.memory = &ctx->memory;

	return pdm_allocator_create(&ctx->allocator);
}

void pdm_core_destroy (pdm_core_t* ctx)
{
	pdm_allocator_destroy(&ctx->allocator);
}


