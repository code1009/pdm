/****************************************************************************
**
** File: pdm_map.c
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
pdm_bool_t pdm_set_create (pdm_set_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_equal_t equal, pdm_less_t less, pdm_core_t* core)
{
	ctx->equal=equal;
	ctx->less =less ;

	ctx->container.core = core;
	ctx->container.element_size      = element_size;
	ctx->container.element_max_count = element_max_count;

	return pdm_container_create(&ctx->container);
}

void pdm_set_destroy (pdm_set_t* ctx)
{
	pdm_container_destroy(&ctx->container);
}

//===========================================================================
pdm_size_t pdm_set_count (pdm_set_t* ctx)
{
	return pdm_container_count(&ctx->container);
}

pdm_bool_t pdm_set_full (pdm_set_t* ctx)
{
	return pdm_container_full(&ctx->container);
}

pdm_bool_t pdm_set_empty (pdm_set_t* ctx)
{
	return pdm_container_empty(&ctx->container);
}

void pdm_set_clear (pdm_set_t* ctx)
{
	pdm_container_clear(&ctx->container);
}

//===========================================================================
pdm_pointer_t pdm_set_at (pdm_set_t* ctx, pdm_size_t index)
{
	return pdm_container_at(&ctx->container, index);
}

void pdm_set_erase (pdm_set_t* ctx, pdm_size_t index)
{
	pdm_container_erase(&ctx->container, index);
}

pdm_bool_t pdm_set_insert (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;
	pdm_int_t pos  ;

	pdm_uint_t    index;
	pdm_pointer_t e;


	if (PDM_TRUE==pdm_set_full(ctx))
	{
		return PDM_FALSE;
	}
	if (PDM_TRUE==pdm_set_empty(ctx))
	{
		e = pdm_container_memory(&ctx->container, 0u);
		if (PDM_NULL_POINTER!=e)
		{
			pdm_copy_memory(e, pointer , ctx->container.element_size);

			ctx->container.element_count++;

			return PDM_TRUE;
		}

		return PDM_FALSE;
	}


	count = (pdm_int_t)pdm_set_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index = mid;
		e     = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->equal(e, pointer) )
		{
			// already existed
			return PDM_FALSE;
		}
		else
		{
			if ( PDM_TRUE==ctx->less(e, pointer) )
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
	}


	index = mid;
	e     = pdm_container_at(&ctx->container, index);

	if ( PDM_TRUE==ctx->less(e, pointer) )
	{
		pos = mid + 1;
	}
	else
	{
		pos = mid;
	}


	index = pos;
	if (pos<count)
	{
		pdm_container_move_down(&ctx->container, index);

		e = pdm_container_at(&ctx->container, index);
	}
	else
	{
		e = pdm_container_memory(&ctx->container, index);
	}

	pdm_copy_memory(e, pointer , ctx->container.element_size );

	ctx->container.element_count++;

	return PDM_TRUE;
}

//===========================================================================
pdm_pointer_t pdm_set_find (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;

	pdm_size_t    index;
	pdm_pointer_t e;


	if (PDM_TRUE==pdm_set_empty(ctx))
	{
		return PDM_NULL_POINTER;
	}


	count = (pdm_int_t)pdm_set_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index = mid;
		e     = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->equal(e, pointer) )
		{
			return e;
		}
		else
		{
			if ( PDM_TRUE==ctx->less(e, pointer) )
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
	}

	return PDM_NULL_POINTER;
}

void pdm_set_erase_by_element (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;

	pdm_size_t    index;
	pdm_pointer_t e;


	if (PDM_TRUE==pdm_set_empty(ctx))
	{
		return /*PDM_FALSE*/;
	}


	count = (pdm_int_t)pdm_set_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index   = mid;
		e = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->equal(e, pointer) )
		{
			pdm_set_erase(ctx, index);
			return /*PDM_TRUE*/;
		}
		else
		{
			if ( PDM_TRUE==ctx->less(e, pointer) )
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
	}


	/*return PDM_FALSE;*/
}




