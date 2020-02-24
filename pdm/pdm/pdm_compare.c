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
pdm_bool_t pdm_equal_int (pdm_pointer_t left, pdm_pointer_t right)
{
	pdm_int_t* ap;
	pdm_int_t* bp;
	pdm_int_t  av;
	pdm_int_t  bv;


	ap = (pdm_int_t*)left;
	bp = (pdm_int_t*)right;
	av = *ap;
	bv = *bp;


	if (av == bv)
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
pdm_bool_t pdm_less_int (pdm_pointer_t left, pdm_pointer_t right)
{
	pdm_int_t* ap;
	pdm_int_t* bp;
	pdm_int_t  av;
	pdm_int_t  bv;


	ap = (pdm_int_t*)left;
	bp = (pdm_int_t*)right;
	av = *ap;
	bv = *bp;


	if (av < bv)
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}


