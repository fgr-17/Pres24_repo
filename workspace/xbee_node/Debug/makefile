################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: xbee_node.axf

# Tool invocations
xbee_node.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_CMSISv2p00_LPC17xx\Debug" -L"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_Board\Debug" -L"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_MCU\Debug" -Xlinker --gc-sections -Xlinker -Map=xbee_node.map -mcpu=cortex-m3 -mthumb -T "ea_test_Debug.ld" -o"xbee_node.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) xbee_node.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size xbee_node.axf; # arm-none-eabi-objdump -h -S xbee_node.axf >xbee_node.lss
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
