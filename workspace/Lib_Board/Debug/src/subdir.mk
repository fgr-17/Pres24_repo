################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/btn.c \
../src/debug.c \
../src/eeprom.c \
../src/font5x7.c \
../src/light.c \
../src/oled.c \
../src/pca9532.c \
../src/rgb.c \
../src/temp.c \
../src/time.c \
../src/trimpot.c 

OBJS += \
./src/board.o \
./src/btn.o \
./src/debug.o \
./src/eeprom.o \
./src/font5x7.o \
./src/light.o \
./src/oled.o \
./src/pca9532.o \
./src/rgb.o \
./src/temp.o \
./src/time.o \
./src/trimpot.o 

C_DEPS += \
./src/board.d \
./src/btn.d \
./src/debug.d \
./src/eeprom.d \
./src/font5x7.d \
./src/light.d \
./src/oled.d \
./src/pca9532.d \
./src/rgb.d \
./src/temp.d \
./src/time.d \
./src/trimpot.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -I"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_CMSISv2p00_LPC17xx\inc" -I"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_Board\inc" -I"C:\Documents and Settings\fede\My Documents\lpcxpresso_3.6.3_317\workspace\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


