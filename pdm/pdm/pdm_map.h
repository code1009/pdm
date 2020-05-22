#ifndef __pdm_map__h__
#define __pdm_map__h__

/****************************************************************************
**
** File: pdm_map.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_map_t
{
	pdm_set_t set;

	pdm_size_t first_size;
	pdm_size_t second_size;

	pdm_size_t first_aligned_size;
	pdm_size_t second_aligned_size;
}
pdm_map_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_map_create  (pdm_map_t* ctx, pdm_size_t element_max_count, 
                                    pdm_size_t first_size, pdm_size_t second_size, 
                                    pdm_equal_t first_equal, pdm_less_t first_less, 
                                    pdm_core_t* core);
PDM_API void       pdm_map_destroy (pdm_map_t* ctx);

PDM_API pdm_size_t pdm_map_count (pdm_map_t* ctx);
PDM_API pdm_bool_t pdm_map_full  (pdm_map_t* ctx);
PDM_API pdm_bool_t pdm_map_empty (pdm_map_t* ctx);
PDM_API void       pdm_map_clear (pdm_map_t* ctx);

PDM_API pdm_pointer_t pdm_map_at(pdm_map_t* ctx, pdm_size_t index); // return pair pointer
PDM_API void          pdm_map_erase(pdm_map_t* ctx, pdm_size_t index);

PDM_API pdm_size_t pdm_map_lower_bound(pdm_map_t* ctx, pdm_pointer_t first_pointer);
PDM_API pdm_size_t pdm_map_upper_bound(pdm_map_t* ctx, pdm_pointer_t first_pointer);

PDM_API pdm_bool_t pdm_map_insert(pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer);

PDM_API pdm_pointer_t pdm_map_find           (pdm_map_t* ctx, pdm_pointer_t first_pointer); // return pair pointer
PDM_API void          pdm_map_erase_by_first (pdm_map_t* ctx, pdm_pointer_t first_pointer);

PDM_API pdm_bool_t pdm_map_set (pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer);
PDM_API pdm_bool_t pdm_map_get (pdm_map_t* ctx, pdm_pointer_t first_pointer, pdm_pointer_t second_pointer);

PDM_API pdm_pointer_t pdm_map_first  (pdm_map_t* ctx, pdm_pointer_t pointer); // return first pointer
PDM_API pdm_pointer_t pdm_map_second (pdm_map_t* ctx, pdm_pointer_t pointer); // return second pointer





#endif




