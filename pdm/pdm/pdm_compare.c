/****************************************************************************
**
** File: pdm_compare.c
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
#define PDM_EQUAL(T,a,b) \
	T* ap;                  \
	T* bp;                  \
	T  av;                  \
	T  bv;                  \
	                        \
	                        \
	ap = (T*)a;             \
	bp = (T*)b;             \
	av = *ap;               \
	bv = *bp;               \
	                        \
	                        \
	if (av == bv)           \
	{                       \
		return PDM_TRUE;    \
	}                       \
	                        \
	return PDM_FALSE


#define PDM_LESS(T,a,b) \
	T* ap;                  \
	T* bp;                  \
	T  av;                  \
	T  bv;                  \
	                        \
	                        \
	ap = (T*)a;             \
	bp = (T*)b;             \
	av = *ap;               \
	bv = *bp;               \
	                        \
	                        \
	if (av < bv)            \
	{                       \
		return PDM_TRUE;    \
	}                       \
	                        \
	return PDM_FALSE






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
pdm_bool_t pdm_equal_int    (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_int_t   , left, right); }
pdm_bool_t pdm_equal_int32  (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_int32_t , left, right); }
pdm_bool_t pdm_equal_int16  (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_int16_t , left, right); }
pdm_bool_t pdm_equal_int8   (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_int8_t  , left, right); }

pdm_bool_t pdm_equal_uint   (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_uint_t  , left, right); }
pdm_bool_t pdm_equal_uint32 (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_uint32_t, left, right); }
pdm_bool_t pdm_equal_uint16 (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_uint16_t, left, right); }
pdm_bool_t pdm_equal_uint8  (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_uint8_t , left, right); }

pdm_bool_t pdm_equal_char   (pdm_pointer_t left, pdm_pointer_t right) { PDM_EQUAL(pdm_char_t  , left, right); }

pdm_bool_t pdm_equal_const_string (pdm_pointer_t left, pdm_pointer_t right)
{
	pdm_const_string_t* ap;
	pdm_const_string_t* bp;


	ap = (pdm_const_string_t*)left;
	bp = (pdm_const_string_t*)right;

	if (0==pdm_const_string_compare(ap, bp))
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
pdm_bool_t pdm_less_int    (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_int_t   , left, right); }
pdm_bool_t pdm_less_int32  (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_int32_t , left, right); }
pdm_bool_t pdm_less_int16  (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_int16_t , left, right); }
pdm_bool_t pdm_less_int8   (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_int8_t  , left, right); }

pdm_bool_t pdm_less_uint   (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_uint_t  , left, right); }
pdm_bool_t pdm_less_uint32 (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_uint32_t, left, right); }
pdm_bool_t pdm_less_uint16 (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_uint16_t, left, right); }
pdm_bool_t pdm_less_uint8  (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_uint8_t , left, right); }

pdm_bool_t pdm_less_char   (pdm_pointer_t left, pdm_pointer_t right) { PDM_LESS(pdm_char_t  , left, right); }

pdm_bool_t pdm_less_const_string (pdm_pointer_t left, pdm_pointer_t right)
{
	pdm_const_string_t* ap;
	pdm_const_string_t* bp;


	ap = (pdm_const_string_t*)left;
	bp = (pdm_const_string_t*)right;

	if (0>pdm_const_string_compare(ap, bp))
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}




