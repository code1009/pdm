#include "pdm.h"
#include <stdio.h>

typedef struct _element_value_t
{
	unsigned short int value1;
	unsigned short int value2;
	unsigned short int value3;
} element_value_t;

//pdm_byte_t buffer[sizeof(element_value_t)*10];
//pdm_byte_t buffer[4*10];
element_value_t buffer[10]; // sizeof(element_value_t)==6

static void test_pdm_container_element_dump (pdm_uint_t index, pdm_pointer_t pointer)
{
	element_value_t* e;


	e = (element_value_t*)pointer;

	printf ("[%d]=%d\r\n",index,e->value1);
}

static void test_pdm_container_dump (pdm_container_t* container)
{
	pdm_uint_t i;
	pdm_uint_t count;


	count = pdm_container_count(container); // container->element_count;
	printf ("count=%d\r\n",count);
	for (i=0u; i<count; i++)
	{
		test_pdm_container_element_dump(i, pdm_container_at(container, i));
	}
	printf ("\r\n");
}

static void test_pdm_container (void)
{
	//==========================================================================
	//--------------------------------------------------------------------------
	pdm_core_t      core;
	pdm_container_t container;
	element_value_t element_value;

	pdm_uint_t i;
	pdm_uint_t count;


	//==========================================================================
	//--------------------------------------------------------------------------
	pdm_fill_memory(&element_value, 0xFFu, sizeof(element_value));



	//==========================================================================
	//--------------------------------------------------------------------------
	core.memory.pointer = (pdm_byte_t*)buffer;
	core.memory.size    = sizeof(buffer);
	if (PDM_FALSE==pdm_core_create (&core))
	{
		return;
	}


	container.core = &core; // 중요
	container.element_max_count = 10u;
	container.element_size      = sizeof(element_value_t);
	if (PDM_FALSE==pdm_container_create(&container))
	{
		pdm_core_destroy(&core);
		return;
	}


	//==========================================================================
	//--------------------------------------------------------------------------
	count = 9;
	for (i=0u; i<count; i++)
	{
		element_value.value1 = i;
		pdm_container_push_back(&container, &element_value);
	}


	//==========================================================================
	//--------------------------------------------------------------------------
	pdm_container_pop_back(&container);
	pdm_container_erase(&container, 0u);

	pdm_container_erase(&container, 7u);
	test_pdm_container_dump(&container);

	pdm_container_erase(&container, 5u);
	test_pdm_container_dump(&container);


	//--------------------------------------------------------------------------
	element_value.value1 = 99;
	pdm_container_insert(&container, 0u, &element_value);

	element_value.value1 = 88;
	pdm_container_insert(&container, 1u, &element_value);

	element_value.value1 = 77;
	pdm_container_insert(&container, 7u, &element_value);
	test_pdm_container_dump(&container);


	//--------------------------------------------------------------------------
	element_value.value1 = 66;
	pdm_container_set(&container, 8u, &element_value);
	test_pdm_container_dump(&container);


	//--------------------------------------------------------------------------
	element_value.value1 = 0;
	pdm_container_get(&container, 2u, &element_value);
	test_pdm_container_element_dump(22, &element_value);


	//==========================================================================
	//--------------------------------------------------------------------------
	pdm_container_destroy(&container);

	pdm_core_destroy(&core);
}

void pdm_test (void)
{
	test_pdm_container();
}
