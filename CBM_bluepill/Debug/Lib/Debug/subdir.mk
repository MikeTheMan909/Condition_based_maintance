################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Debug/debug.c 

OBJS += \
./Lib/Debug/debug.o 

C_DEPS += \
./Lib/Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Debug/%.o Lib/Debug/%.su: ../Lib/Debug/%.c Lib/Debug/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_bluepill/Drivers/SPIRIT1/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_bluepill/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib-2f-Debug

clean-Lib-2f-Debug:
	-$(RM) ./Lib/Debug/debug.d ./Lib/Debug/debug.o ./Lib/Debug/debug.su

.PHONY: clean-Lib-2f-Debug

