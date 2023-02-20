#include "CppUTest/TestHarness.h"

#include "pp_const_ports_masks_list.h"
#include "stdio.h"

	GPIO_TypeDef GPIOAbase;
	GPIO_TypeDef GPIOCbase;
	GPIO_TypeDef GPIODbase;
	GPIO_TypeDef GPIOEbase;

	GPIO_TypeDef* GPIOA=&GPIOAbase;
	GPIO_TypeDef* GPIOC=&GPIOCbase;
	GPIO_TypeDef* GPIOD=&GPIODbase;
	GPIO_TypeDef* GPIOE=&GPIOEbase;


TEST_GROUP(PConstPortsListTestGroup)
{
	PConstPortsList list;
	uPortMask lcdPortsTab[5];																	

  void setup() {
		
		PConstPortsListConstruct(&list, lcdPortsTab, sizeof(lcdPortsTab)/sizeof(uPortMask));
	
	
	}
  void teardown() {}
};


TEST(PConstPortsListTestGroup, createTest)
{
	uPin ioPins[13]={{GPIOD, Pin2}, {GPIOD, Pin4}, {GPIOD, Pin5}, {GPIOE, Pin2}, {GPIOE, Pin3}, {GPIOE, Pin4}, {GPIOA, Pin5}, {GPIOE, Pin6},
																			{GPIOC, Pin3}, {GPIOC, Pin8}, {GPIOC, Pin11}, {GPIOC, Pin12}, {GPIOC, Pin13}};
	
	list.create(&list.data, ioPins, 13);	
	
	LONGS_EQUAL(4, list.data.size);
	POINTERS_EQUAL(GPIOD, list.data.portsMasks[0].port);
	LONGS_EQUAL(0x34, list.data.portsMasks[0].clrMask);
	POINTERS_EQUAL(GPIOE, list.data.portsMasks[1].port);
	LONGS_EQUAL(0b01011100, list.data.portsMasks[1].clrMask);
	POINTERS_EQUAL(GPIOA, list.data.portsMasks[2].port);
	POINTERS_EQUAL(GPIOC, list.data.portsMasks[3].port);
}


