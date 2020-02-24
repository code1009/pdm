/****************************************************************************
**
** File: pdm_const_string.c
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pdm.h"
#include <string.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
pdm_bool_t pdm_const_string_create (pdm_const_string_t* ctx, pdm_char_t* c_str, pdm_int_t length, pdm_core_t* core)
{
	pdm_bool_t result;

	pdm_char_t* pointer;


	if (length<0)
	{
		ctx->c_str_length = strlen(c_str);
	}
	else
	{
		ctx->c_str_length = length;
	}

	ctx->container.core = core;
	ctx->container.element_size      = sizeof(pdm_char_t);
	ctx->container.element_max_count = ctx->c_str_length+1u;

	result = pdm_container_create(&ctx->container);
	if (PDM_TRUE==result)
	{
		pointer = pdm_const_string_c_str(ctx);

		pdm_copy_memory(pointer, c_str, ctx->c_str_length);

		*(pointer+ctx->c_str_length) = 0;
	}

	return result;
}

void pdm_const_string_destroy (pdm_const_string_t* ctx)
{
	pdm_container_destroy(&ctx->container);
}

//===========================================================================
pdm_size_t pdm_const_string_length (pdm_const_string_t* ctx)
{
	return ctx->c_str_length;
}

pdm_char_t* pdm_const_string_c_str (pdm_const_string_t* ctx)
{
	pdm_char_t* pointer;


	pointer = (pdm_char_t*)ctx->container.memory.pointer;

	return pointer;
}

pdm_bool_t pdm_const_string_empty (pdm_const_string_t* ctx)
{
	if (0u==ctx->c_str_length)
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}

pdm_int_t pdm_const_string_compare (pdm_const_string_t* ctx, pdm_const_string_t* s)
{
	return strcmp( pdm_const_string_c_str(ctx), pdm_const_string_c_str(s) );
}




