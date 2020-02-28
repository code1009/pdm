#ifndef __pdm_const_string__h__
#define __pdm_const_string__h__

/****************************************************************************
**
** File: pdm_const_string.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _pdm_const_string_t
{
	pdm_container_t container;
	pdm_size_t      c_str_length;
}
pdm_const_string_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_bool_t pdm_const_string_create  (pdm_const_string_t* ctx, pdm_char_t* c_str, pdm_int_t length, pdm_core_t* core);
PDM_API void       pdm_const_string_destroy (pdm_const_string_t* ctx);

PDM_API pdm_bool_t  pdm_const_string_empty (pdm_const_string_t* ctx);

PDM_API pdm_size_t  pdm_const_string_length  (pdm_const_string_t* ctx);
PDM_API pdm_char_t* pdm_const_string_c_str   (pdm_const_string_t* ctx);
PDM_API pdm_int_t   pdm_const_string_compare (pdm_const_string_t* ctx, pdm_const_string_t* s);





#endif




