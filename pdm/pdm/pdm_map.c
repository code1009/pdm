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
	ctx->first_size =first_size ;
	ctx->second_size=second_size;

	ctx->first_aligned_size  = pdm_allocator_align_size(&core->allocator, first_size );
	ctx->second_aligned_size = pdm_allocator_align_size(&core->allocator, second_size);

	return pdm_set_create(&ctx->set, element_max_count, ctx->first_aligned_size+ctx->second_aligned_size, first_equal, first_less, core);
}

void pdm_map_destroy (pdm_map_t* ctx)
{
	pdm_set_destroy(&ctx->set);
}

//===========================================================================
pdm_size_t pdm_map_count (pdm_map_t* ctx)
{
	return pdm_set_count(&ctx->set);
}

pdm_bool_t pdm_map_full (pdm_map_t* ctx)
{
	return pdm_set_full(&ctx->set);
}

pdm_bool_t pdm_map_empty (pdm_map_t* ctx)
{
	return pdm_set_empty(&ctx->set);
}

void pdm_map_clear (pdm_map_t* ctx)
{
	pdm_set_clear(&ctx->set);
}

//===========================================================================
pdm_pointer_t pdm_map_at (pdm_map_t* ctx, pdm_size_t index)
{
	return pdm_set_at(&ctx->set, index);
}

void pdm_map_erase (pdm_map_t* ctx, pdm_size_t index)
{
	pdm_set_erase(&ctx->set, index);
}

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
		pointer = pdm_container_memory(&ctx->set.container, 0u);
		if (PDM_NULL_POINTER!=pointer)
		{
			e_first_pointer  = pdm_map_first (ctx, pointer);
			e_second_pointer = pdm_map_second(ctx, pointer);

			pdm_copy_memory(e_first_pointer , first_pointer , ctx->first_size );
			pdm_copy_memory(e_second_pointer, second_pointer, ctx->second_size);

			ctx->set.container.element_count++;

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
		pointer = pdm_container_at(&ctx->set.container, index);

		if ( PDM_TRUE==ctx->set.equal(pdm_map_first(ctx, pointer), first_pointer) )
		{
			// already existed
			return PDM_FALSE;
		}
		else
		{
			if ( PDM_TRUE==ctx->set.less(pdm_map_first(ctx, pointer), first_pointer) )
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
	pointer = pdm_container_at(&ctx->set.container, index);

	if ( PDM_TRUE==ctx->set.less(pdm_map_first(ctx, pointer), first_pointer) )
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
		pdm_container_move_down(&ctx->set.container, index);

		pointer = pdm_container_at(&ctx->set.container, index);
	}
	else
	{
		pointer = pdm_container_memory(&ctx->set.container, index);
	}


	e_first_pointer  = pdm_map_first (ctx, pointer);
	e_second_pointer = pdm_map_second(ctx, pointer);

	pdm_copy_memory(e_first_pointer , first_pointer , ctx->first_size );
	pdm_copy_memory(e_second_pointer, second_pointer, ctx->second_size);

	ctx->set.container.element_count++;

	return PDM_TRUE;
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
pdm_pointer_t pdm_map_find (pdm_map_t* ctx, pdm_pointer_t first_pointer)
{
	return pdm_set_find(&ctx->set, first_pointer);
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
	pdm_set_erase_by_element(&ctx->set, first_pointer);
}




