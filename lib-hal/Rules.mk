$(info $$MAKE_FLAGS [${MAKE_FLAGS}])

ifneq ($(MAKE_FLAGS),)
	ifneq (,$(findstring CONSOLE_I2C,$(MAKE_FLAGS)))
		EXTRA_SRCDIR+=console/i2c
	else
		ifneq (,$(findstring CONSOLE_FB,$(MAKE_FLAGS)))
			EXTRA_SRCDIR+=console console/h3
		else
			ifneq (,$(findstring CONSOLE_NULL,$(MAKE_FLAGS)))
				EXTRA_SRCDIR+=console/null
			else
				EXTRA_SRCDIR+=console/uart0
			endif
		endif
	endif
	
	FATFS=
	ifeq ($(findstring CONFIG_USB_HOST_MSC,$(MAKE_FLAGS)), CONFIG_USB_HOST_MSC)
		FATFS=1
 	endif
 	
 	ifeq (,$(findstring DISABLE_FS,$(MAKE_FLAGS)))
 			FATFS=1
 	endif
 	
 	ifdef FATFS
 		EXTRA_SRCDIR+=ff12c ff12c/option
 		EXTRA_SRCDIR+=posix
 	endif
	
	ifeq (,$(findstring DISABLE_RTC,$(MAKE_FLAGS)))
		EXTRA_SRCDIR+=rtc
		ifneq (,$(findstring DISABLE_INTERNAL_RTC,$(MAKE_FLAGS)))
			EXTRA_SRCDIR+=rtc/i2c
		endif
	endif
	
	ifneq (,$(findstring DEBUG_I2C,$(MAKE_FLAGS)))
		EXTRA_SRCDIR+=debug/i2c
		EXTRA_INCLUDES+=debug/i2c
	endif
	
	ifneq (,$(findstring DEBUG_STACK,$(MAKE_FLAGS)))
		EXTRA_SRCDIR+=debug/stack
	endif
else
	DEFINES+=DEBUG_I2C DEBUG_STACK
	EXTRA_INCLUDES+=debug/i2c debug/stack
	EXTRA_SRCDIR+=console/i2c console/null console/uart0 rtc 
	EXTRA_SRCDIR+=posix
endif
