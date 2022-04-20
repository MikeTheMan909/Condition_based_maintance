################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_General.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Management.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.c \
../Drivers/SPIRIT1_Library/Src/SPIRIT_Types.c 

OBJS += \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_General.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Management.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.o \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Types.o 

C_DEPS += \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_General.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Management.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.d \
./Drivers/SPIRIT1_Library/Src/SPIRIT_Types.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SPIRIT1_Library/Src/%.o Drivers/SPIRIT1_Library/Src/%.su: ../Drivers/SPIRIT1_Library/Src/%.c Drivers/SPIRIT1_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_discboard/lib/comm" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/debug" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/spsgrf" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/cbm" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SPIRIT1_Library-2f-Src

clean-Drivers-2f-SPIRIT1_Library-2f-Src:
	-$(RM) ./Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Aes.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Calibration.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Commands.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Csma.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_DirectRF.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_General.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_General.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_General.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Gpio.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Irq.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_LinearFifo.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Management.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Management.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Management.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktBasic.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktCommon.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktMbus.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_PktStack.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Qi.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Radio.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Timer.su ./Drivers/SPIRIT1_Library/Src/SPIRIT_Types.d ./Drivers/SPIRIT1_Library/Src/SPIRIT_Types.o ./Drivers/SPIRIT1_Library/Src/SPIRIT_Types.su

.PHONY: clean-Drivers-2f-SPIRIT1_Library-2f-Src

