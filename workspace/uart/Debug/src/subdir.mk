################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/main.c \
../src/uart.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/main.o \
./src/uart.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/main.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\CMSISv1p30_LPC17xx\inc" -I"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\uart\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


