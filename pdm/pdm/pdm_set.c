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

//===========================================================================
pdm_size_t pdm_set_lower_bound (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t low;
	pdm_size_t high;
	pdm_size_t mid;

	pdm_pointer_t e;


	low  = 0u;
	high = pdm_set_count(ctx);
	while (low < high)
	{
		// mid = (low + high) / 2u;
		// (x+y)/2 => x&y + (x^y)/2
		mid = (low & high) + ((low ^ high) / 2u);

		e = pdm_container_at(&ctx->container, mid);
		if (PDM_TRUE == ctx->less(e, pointer))
		{
			low  = mid + 1u;
		}
		else
		{
			high = mid;
		}
	}

	return low;
}

pdm_size_t pdm_set_upper_bound (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t low;
	pdm_size_t high;
	pdm_size_t mid;

	pdm_pointer_t e;


	low  = 0u;
	high = pdm_set_count(ctx);
	while (low < high)
	{
		//mid = (low + high) / 2u;
		mid = (low & high) + ((low ^ high) / 2u);

		e = pdm_container_at(&ctx->container, mid);
		if (PDM_TRUE == ctx->less(pointer, e))
		{
			high = mid;
		}
		else
		{
			low  = mid + 1u;
		}
	}

	return low;
}

//===========================================================================
pdm_bool_t pdm_set_insert (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t    count;
	pdm_size_t    lbound;
	pdm_pointer_t e;


	count  = pdm_set_count(ctx);
	lbound = pdm_set_lower_bound(ctx, pointer);
	if (lbound < count)
	{
		e = pdm_container_at(&ctx->container, lbound);
		if (PDM_TRUE == ctx->equal(e, pointer))
		{
			// already existed
			return PDM_FALSE;
		}
		else
		{
			return pdm_container_insert(&ctx->container, lbound, pointer);
		}
	}

	return pdm_container_push_back(&ctx->container, pointer);
}

//===========================================================================
pdm_bool_t pdm_set_get(pdm_set_t* ctx, pdm_size_t index, pdm_pointer_t pointer)
{
	return pdm_container_insert(&ctx->container, index, pointer);
}

//===========================================================================
pdm_pointer_t pdm_set_find (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t    count;
	pdm_size_t    lbound;
	pdm_pointer_t e;


	count  = pdm_set_count(ctx);
	lbound = pdm_set_lower_bound(ctx, pointer);
	if (lbound < count)
	{
		e = pdm_container_at(&ctx->container, lbound);
		if (PDM_TRUE == ctx->equal(e, pointer))
		{
			return e;
		}
	}

	return PDM_NULL_POINTER;
}

void pdm_set_erase_by_element (pdm_set_t* ctx, pdm_pointer_t pointer)
{
	pdm_size_t    count;
	pdm_size_t    lbound;
	pdm_pointer_t e;


	count  = pdm_set_count(ctx);
	lbound = pdm_set_lower_bound(ctx, pointer);
	if (lbound < count)
	{
		e = pdm_container_at(&ctx->container, lbound);
		if (PDM_TRUE == ctx->equal(e, pointer))
		{
			pdm_set_erase(ctx, lbound);
		}
	}
}




