################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Comm/comm.c 

OBJS += \
./Lib/Comm/comm.o 

C_DEPS += \
./Lib/Comm/comm.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Comm/%.o Lib/Comm/%.su: ../Lib/Comm/%.c Lib/Comm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_bluepill/Drivers/SPIRIT1/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_bluepill/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib-2f-Comm

clean-Lib-2f-Comm:
	-$(RM) ./Lib/Comm/comm.d ./Lib/Comm/comm.o ./Lib/Comm/comm.su

.PHONY: clean-Lib-2f-Comm

