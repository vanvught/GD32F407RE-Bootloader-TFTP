![GitHub](https://img.shields.io/github/license/vanvught/GD32F407RE-Bootloader-TFTP)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://img.shields.io/badge/C%2B%2B-11%-blue.svg)
![GitHub issues](https://img.shields.io/github/issues-raw/vanvught/GD32F407RE-Bootloader-TFTP)
![GitHub contributors](https://img.shields.io/github/contributors/vanvught/GD32F407RE-Bootloader-TFTP)
![GitHub Sponsors](https://img.shields.io/github/sponsors/vanvught)
![Main](https://github.com/vanvught/GD32F407RE-Bootloader-TFTP/actions/workflows/c-cpp.yml/badge.svg?branch=main)

[PayPal.Me Donate](https://paypal.me/AvanVught?locale.x=nl_NL)
# GD32F407RE Bootloader TFTP

This bootloader will install your application by means of the TFTP protocol. There is no need to change your application code. 
Per default DHCP is used for obtaining the ip-address.

The bootloader is active during reset of the board:

* When the `KEY_BOOTLOADER_TFTP_GPIO_PINx` is pressed. Which is defined in file:
	* lib-gd32/include/board/bw_opidmx4.h
	* lib-gd32/include/board/dmx4.h
	* lib-gd32/include/board/gd32f407r.h
 

* When `bkp_data_read(BKP_DATA_1) == 0xA5A5`. This is set in your application by means of human readable UDP messages. See for more information: [https://www.gd32-dmx.org/bootloader.html](https://www.gd32-dmx.org/bootloader.html). There is also a sample Java UI application available for working with the UDP messages: [https://github.com/vanvught/GD32F-Firmware-Update-UI](https://github.com/vanvught/GD32F-Firmware-Update-UI)

Otherwise the bootloader will directly jump to your application. With the snippet: 

	    	// 8. Call the reset handler
	    	const uint32_t* reset_p = (uint32_t *)(FLASH_BASE + OFFSET_UIMAGE + 4);
	    	asm volatile ("bx %0;" : : "r"(*reset_p));

The bootloader can be installed with the tools supplied by GigaDevice -> [http://www.gd32mcu.com/en/download/7?kw=GD32F4](http://www.gd32mcu.com/en/download/7?kw=GD32F4)

The limitation for the firmware file to be uploaded is given by the RAM available. For example, the MCU on [https://github.com/vanvught/GD32FxxR-dev-board](https://github.com/vanvught/GD32FxxxR-dev-board) is the [GD32F407RE](https://www.gigadevice.com/microcontroller/gd32f407re6/). With the 128K RAM we have the firmware file size limit of 106K.

There are 2 places for this configuration:

File: `gd32f407_flash.ld`

	  __heap_size = DEFINED(__heap_size) ? __heap_size : 107K;
	  __stack_size = DEFINED(__stack_size) ? __stack_size : 1K;

File: `flashcodeinstall.h`

	# elif defined (BOARD_GD32F407RE)
	#  define OFFSET_UIMAGE		0x008000		// 32K
	#  define FIRMWARE_MAX_SIZE (106 * 1024)	// 106K
	# elif defined (BOARD_BW_OPIDMX4)
	#  define OFFSET_UIMAGE		0x008000		// 32K
	#  define FIRMWARE_MAX_SIZE (106 * 1024)	// 106K
	# elif defined (BOARD_DMX4)
	#  define OFFSET_UIMAGE		0x008000		// 32K
	#  define FIRMWARE_MAX_SIZE (106 * 1024)	// 106K
The 1K difference is needed for other `new` (`malloc`) within the bootloader.

The change to be made in your build configuration is in the file `gd32f407_flash.ld `. 

	MEMORY
	{
	  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 32K
	  TCMSRAM (rw)    : ORIGIN = 0x10000000, LENGTH = 64K
	  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
	  RAMADD (xrw)    : ORIGIN = 0x20030000, LENGTH = 0
	  BKPSRAM (rw)    : ORIGIN = 0x40024000, LENGTH = 4K
	}

The `FLASH ORIGIN` must match the `OFFSET_UIMAGE` from the bootloader file `flashcodeinstall.h`

The code for the bootloader is a fork from [https://github.com/vanvught/rpidmx512](https://github.com/vanvught/rpidmx512). In order to reduce the memory footprint, some functions are not available.