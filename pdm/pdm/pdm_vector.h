#ifndef __pdm_vector__h__
#define __pdm_vector__h__

/****************************************************************************
**
** File: pdm_vector.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_vector_t
{
	pdm_container_t container;
}
pdm_vector_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_vector_create  (pdm_vector_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_core_t* core);
PDM_API void       pdm_vector_destroy (pdm_vector_t* ctx);

PDM_API pdm_size_t    pdm_vector_count     (pdm_vector_t* ctx);
PDM_API pdm_bool_t    pdm_vector_fulll     (pdm_vector_t* ctx);
PDM_API pdm_bool_t    pdm_vector_empty     (pdm_vector_t* ctx);
PDM_API void          pdm_vector_clear     (pdm_vector_t* ctx);
PDM_API pdm_bool_t    pdm_vector_push_back (pdm_vector_t* ctx, pdm_pointer_t pointer);
PDM_API void          pdm_vector_pop_back  (pdm_vector_t* ctx);
PDM_API pdm_bool_t    pdm_vector_push_front(pdm_vector_t* ctx, pdm_pointer_t pointer);
PDM_API void          pdm_vector_pop_front (pdm_vector_t* ctx);
PDM_API pdm_bool_t    pdm_vector_insert    (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API void          pdm_vector_erase     (pdm_vector_t* ctx, pdm_size_t index);
PDM_API void          pdm_vector_set       (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API pdm_bool_t    pdm_vector_get       (pdm_vector_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API pdm_pointer_t pdm_vector_at        (pdm_vector_t* ctx, pdm_size_t index);





#endif




