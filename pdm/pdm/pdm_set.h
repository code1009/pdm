#ifndef __pdm_set__h__
#define __pdm_set__h__

/****************************************************************************
**
** File: pdm_set.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_set_t
{
	pdm_container_t container;

	pdm_equal_t equal;
	pdm_less_t  less;
}
pdm_set_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_set_create  (pdm_set_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_equal_t equal, pdm_less_t less, pdm_core_t* core);
PDM_API void       pdm_set_destroy (pdm_set_t* ctx);

PDM_API pdm_size_t pdm_set_count (pdm_set_t* ctx);
PDM_API pdm_bool_t pdm_set_full  (pdm_set_t* ctx);
PDM_API pdm_bool_t pdm_set_empty (pdm_set_t* ctx);
PDM_API void       pdm_set_clear (pdm_set_t* ctx);

PDM_API pdm_pointer_t pdm_set_at     (pdm_set_t* ctx, pdm_size_t index);
PDM_API void          pdm_set_erase  (pdm_set_t* ctx, pdm_size_t index);
PDM_API pdm_bool_t    pdm_set_insert (pdm_set_t* ctx, pdm_pointer_t pointer);

PDM_API pdm_pointer_t pdm_set_find             (pdm_set_t* ctx, pdm_pointer_t pointer);
PDM_API void          pdm_set_erase_by_element (pdm_set_t* ctx, pdm_pointer_t pointer);





#endif




