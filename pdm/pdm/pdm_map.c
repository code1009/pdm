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
pdm_bool_t pdm_map_create (pdm_map_t* ctx, pdm_size_t element_max_count, pdm_size_t first_size, pdm_size_t second_size, pdm_equal_t first_equal, pdm_less_t first_less, pdm_core_t* core)
{
	ctx->first_equal=first_equal;
	ctx->first_less =first_less ;

	ctx->first_size =first_size ;
	ctx->second_size=second_size;

	ctx->first_aligned_size  = pdm_allocator_align_size(&core->allocator, first_size );
	ctx->second_aligned_size = pdm_allocator_align_size(&core->allocator, second_size);

	ctx->container.core = core;
	ctx->container.element_size      = ctx->first_aligned_size + ctx->second_aligned_size;
	ctx->container.element_max_count = element_max_count;

	return pdm_container_create(&ctx->container);
}

void pdm_map_destroy (pdm_map_t* ctx)
{
	pdm_container_destroy(&ctx->container);
}

//===========================================================================
pdm_size_t pdm_map_count (pdm_map_t* ctx)
{
	return pdm_container_count(&ctx->container);
}

pdm_bool_t pdm_map_full (pdm_map_t* ctx)
{
	return pdm_container_full(&ctx->container);
}

pdm_bool_t pdm_map_empty (pdm_map_t* ctx)
{
	return pdm_container_empty(&ctx->container);
}

void pdm_map_clear (pdm_map_t* ctx)
{
	pdm_container_clear(&ctx->container);
}

//===========================================================================
pdm_bool_t pdm_map_insert (pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;
	pdm_int_t pos  ;

	pdm_uint_t    index;
	pdm_pointer_t pointer;

	pdm_pointer_t e_first_pointer;
	pdm_pointer_t e_second_pointer;



	if (PDM_TRUE==pdm_map_full(ctx))
	{
		return PDM_FALSE;
	}
	if (PDM_TRUE==pdm_map_empty(ctx))
	{
		pointer = pdm_container_memory(&ctx->container, 0u);
		if (PDM_NULL_POINTER!=pointer)
		{
			e_first_pointer  = pdm_map_first (ctx, pointer);
			e_second_pointer = pdm_map_second(ctx, pointer);

			pdm_copy_memory(e_first_pointer , first_pointer , ctx->first_size );
			pdm_copy_memory(e_second_pointer, second_pointer, ctx->second_size);

			ctx->container.element_count++;

			return PDM_TRUE;
		}

		return PDM_FALSE;
	}


	count = (pdm_int_t)pdm_map_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index   = mid;
		pointer = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->first_equal(pdm_map_first(ctx, pointer), first_pointer) )
		{
			// already existed
			return PDM_FALSE;
		}
		else
		{
			if ( PDM_TRUE==ctx->first_less(pdm_map_first(ctx, pointer), first_pointer) )
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
	}


	index   = mid;
	pointer = pdm_container_at(&ctx->container, index);

	if ( PDM_TRUE==ctx->first_less(pdm_map_first(ctx, pointer), first_pointer) )
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

		pointer = pdm_container_at(&ctx->container, index);
	}
	else
	{
		pointer = pdm_container_memory(&ctx->container, index);
	}


	e_first_pointer  = pdm_map_first (ctx, pointer);
	e_second_pointer = pdm_map_second(ctx, pointer);

	pdm_copy_memory(e_first_pointer , first_pointer , ctx->first_size );
	pdm_copy_memory(e_second_pointer, second_pointer, ctx->second_size);

	ctx->container.element_count++;

	return PDM_TRUE;
}

void pdm_map_erase (pdm_map_t* ctx, pdm_size_t index)
{
	pdm_container_erase(&ctx->container, index);
}

//===========================================================================
pdm_bool_t pdm_map_set (pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer)
{
	pdm_pointer_t pointer;
	
	pdm_pointer_t e_second_pointer;

	
	pointer = pdm_map_find (ctx,first_pointer);
	if (PDM_NULL_POINTER==pointer)
	{
		if (PDM_TRUE==pdm_map_full(ctx))
		{
			return PDM_FALSE;
		}

		return pdm_map_insert(ctx, first_pointer, second_pointer);
	}


	e_second_pointer = pdm_map_second(ctx, pointer);

	pdm_copy_memory(e_second_pointer, second_pointer, ctx->second_size);


	return PDM_TRUE;
}

pdm_bool_t pdm_map_get (pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer)
{
	pdm_pointer_t pointer;
	
	pdm_pointer_t e_second_pointer;

	
	pointer = pdm_map_find (ctx,first_pointer);
	if (PDM_NULL_POINTER==pointer)
	{
		return PDM_FALSE;
	}


	e_second_pointer = pdm_map_second(ctx, pointer);

	pdm_copy_memory(second_pointer, e_second_pointer, ctx->second_size);


	return PDM_TRUE;
}

//===========================================================================
pdm_pointer_t pdm_map_at (pdm_map_t* ctx, pdm_size_t index)
{
	return pdm_container_at(&ctx->container, index);
}

//===========================================================================
pdm_pointer_t pdm_map_find (pdm_map_t* ctx, pdm_pointer_t first_pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;

	pdm_size_t    index;
	pdm_pointer_t pointer;


	if (PDM_TRUE==pdm_map_empty(ctx))
	{
		return PDM_NULL_POINTER;
	}


	count = (pdm_int_t)pdm_map_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index   = mid;
		pointer = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->first_equal(pdm_map_first(ctx, pointer), first_pointer) )
		{
			return pointer;
		}
		else
		{
			if ( PDM_TRUE==ctx->first_less(pdm_map_first(ctx, pointer), first_pointer) )
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

pdm_pointer_t pdm_map_first (pdm_map_t* ctx, pdm_pointer_t pointer)
{
	return pointer;
}

pdm_pointer_t pdm_map_second (pdm_map_t* ctx, pdm_pointer_t pointer)
{
	pdm_byte_t* first_pointer;
	pdm_byte_t* second_pointer;
	

	first_pointer  = pointer;
	second_pointer = first_pointer + ctx->first_aligned_size;

	return second_pointer;
}

void pdm_map_erase_by_first (pdm_map_t* ctx, pdm_pointer_t first_pointer)
{
	pdm_int_t count;
	pdm_int_t low  ;
	pdm_int_t high ;
	pdm_int_t mid  ;

	pdm_size_t    index;
	pdm_pointer_t pointer;


	if (PDM_TRUE==pdm_map_empty(ctx))
	{
		return /*PDM_FALSE*/;
	}


	count = (pdm_int_t)pdm_map_count(ctx);
	low   = 0;
	high  = count - 1;
	mid   = 0;
	while ( low<=high )
	{
		mid = (low + high) / 2;

		index   = mid;
		pointer = pdm_container_at(&ctx->container, index);

		if ( PDM_TRUE==ctx->first_equal(pdm_map_first(ctx, pointer), first_pointer) )
		{
			pdm_map_erase(ctx, index);
			return /*PDM_TRUE*/;
		}
		else
		{
			if ( PDM_TRUE==ctx->first_less(pdm_map_first(ctx, pointer), first_pointer) )
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




