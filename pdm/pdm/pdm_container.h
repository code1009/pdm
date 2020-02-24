#ifndef __pdm_container__h__
#define __pdm_container__h__

/****************************************************************************
**
** File: pdm_container.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_container_t
{
	pdm_core_t*   core;
	pdm_memory_t  memory;

	pdm_size_t    element_size;
	pdm_size_t    element_max_count;

	pdm_size_t    element_aligned_size;
	pdm_size_t    element_count;
}
pdm_container_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_container_create  (pdm_container_t* ctx);
PDM_API void       pdm_container_destroy (pdm_container_t* ctx);

PDM_API pdm_size_t    pdm_container_count     (pdm_container_t* ctx);
PDM_API pdm_bool_t    pdm_container_full      (pdm_container_t* ctx);
PDM_API pdm_bool_t    pdm_container_empty     (pdm_container_t* ctx);
PDM_API void          pdm_container_clear     (pdm_container_t* ctx);
PDM_API pdm_bool_t    pdm_container_push_back (pdm_container_t* ctx, pdm_pointer_t pointer);
PDM_API void          pdm_container_pop_back  (pdm_container_t* ctx);
PDM_API pdm_bool_t    pdm_container_push_front(pdm_container_t* ctx, pdm_pointer_t pointer);
PDM_API void          pdm_container_pop_front (pdm_container_t* ctx);
PDM_API pdm_bool_t    pdm_container_insert    (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API void          pdm_container_erase     (pdm_container_t* ctx, pdm_size_t index);
PDM_API void          pdm_container_set       (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API pdm_bool_t    pdm_container_get       (pdm_container_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API pdm_pointer_t pdm_container_at        (pdm_container_t* ctx, pdm_size_t index);

PDM_API void pdm_container_move      (pdm_container_t* ctx, pdm_size_t index_to, pdm_size_t index_from);
PDM_API void pdm_container_move_down (pdm_container_t* ctx, pdm_size_t index);
PDM_API void pdm_container_move_up   (pdm_container_t* ctx, pdm_size_t index);

PDM_API pdm_pointer_t pdm_container_memory (pdm_container_t* ctx, pdm_size_t index);



#endif




