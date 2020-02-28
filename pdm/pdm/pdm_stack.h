#ifndef __pdm_stack__h__
#define __pdm_stack__h__

/****************************************************************************
**
** File: pdm_stack.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
** Sequence container
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_stack_t
{
	pdm_vector_t vector;
}
pdm_stack_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_stack_create  (pdm_stack_t* ctx, pdm_size_t element_max_count, pdm_size_t element_size, pdm_core_t* core);
PDM_API void       pdm_stack_destroy (pdm_stack_t* ctx);

PDM_API pdm_size_t pdm_stack_count (pdm_stack_t* ctx);
PDM_API pdm_bool_t pdm_stack_full  (pdm_stack_t* ctx);
PDM_API pdm_bool_t pdm_stack_empty (pdm_stack_t* ctx);
PDM_API void       pdm_stack_clear (pdm_stack_t* ctx);

PDM_API pdm_pointer_t pdm_stack_at (pdm_stack_t* ctx, pdm_size_t index);

PDM_API void       pdm_stack_set (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer);
PDM_API pdm_bool_t pdm_stack_get (pdm_stack_t* ctx, pdm_size_t index, pdm_pointer_t pointer);

PDM_API pdm_bool_t pdm_stack_push (pdm_stack_t* ctx, pdm_pointer_t pointer);
PDM_API void       pdm_stack_pop  (pdm_stack_t* ctx);

PDM_API pdm_pointer_t pdm_stack_top       (pdm_stack_t* ctx);
PDM_API pdm_size_t    pdm_stack_top_index (pdm_stack_t* ctx);
PDM_API pdm_bool_t    pdm_stack_top_get   (pdm_stack_t* ctx, pdm_pointer_t pointer);




#endif




