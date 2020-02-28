#ifndef __pdm_compare__h__
#define __pdm_compare__h__

/****************************************************************************
**
** File: pdm_compare.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef pdm_bool_t (*pdm_equal_t)(pdm_pointer_t left, pdm_pointer_t right);
typedef pdm_bool_t (*pdm_less_t )(pdm_pointer_t left, pdm_pointer_t right);


//===========================================================================
PDM_API pdm_bool_t pdm_equal_int     (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_int32   (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_int16   (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_int8    (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_equal_uint    (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_uint32  (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_uint16  (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_equal_uint8   (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_equal_char    (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_equal_const_string (pdm_pointer_t left, pdm_pointer_t right);


//===========================================================================
PDM_API pdm_bool_t pdm_less_int     (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_int32   (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_int16   (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_int8    (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_less_uint    (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_uint32  (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_uint16  (pdm_pointer_t left, pdm_pointer_t right);
PDM_API pdm_bool_t pdm_less_uint8   (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_less_char    (pdm_pointer_t left, pdm_pointer_t right);

PDM_API pdm_bool_t pdm_less_const_string (pdm_pointer_t left, pdm_pointer_t right);






#endif




