#ifndef __pdm__h__
#define __pdm__h__

/****************************************************************************
**
** File: pdm.h
**
** Created by MOON, Eui-kwon.
** Created on Jan-10th, 2020.
**
** -------------------------------------------------------------------------
** - Date: Jan-22nd, 2020.
** - Version: 1.0.0.0
** - First release
**
** -------------------------------------------------------------------------
** container:                  pdm_container_t
**     sequence container
**         string:             pdm_const_string_t
**         vector:             pdm_vector_t
**         stack :             pdm_stack_t
**     associative container
**         map:                pdm_map_t
**
****************************************************************************/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef signed int         pdm_int_t    ;
typedef signed int         pdm_int32_t  ;
typedef signed short int   pdm_int16_t  ;
typedef signed char        pdm_int8_t   ;

typedef unsigned int       pdm_uint_t   ;
typedef unsigned int       pdm_uint32_t ;
typedef unsigned short int pdm_uint16_t ;
typedef unsigned char      pdm_uint8_t  ;

typedef unsigned int  pdm_bool_t   ;
typedef unsigned char pdm_byte_t   ;

typedef char          pdm_char_t   ;

typedef void*         pdm_pointer_t;
typedef unsigned int  pdm_size_t   ;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define PDM_TRUE  1u
#define PDM_FALSE 0u

#define PDM_NULL_POINTER 0u





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if defined ( __cplusplus )
#	define PDM_API extern "C"
#else
#	define PDM_API extern
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pdm_memory.h"
#include "pdm_allocator.h"
#include "pdm_core.h"
#include "pdm_container.h"
#include "pdm_compare.h"
#include "pdm_const_string.h"
#include "pdm_vector.h"
#include "pdm_stack.h"
#include "pdm_map.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PDM_API pdm_uint_t pdm_get_version (void);





#endif




