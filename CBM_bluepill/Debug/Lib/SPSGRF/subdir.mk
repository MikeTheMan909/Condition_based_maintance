################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/SPSGRF/SPSGRF.c 

OBJS += \
./Lib/SPSGRF/SPSGRF.o 

C_DEPS += \
./Lib/SPSGRF/SPSGRF.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/SPSGRF/%.o Lib/SPSGRF/%.su: ../Lib/SPSGRF/%.c Lib/SPSGRF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_bluepill/Drivers/SPIRIT1/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_bluepill/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib-2f-SPSGRF

clean-Lib-2f-SPSGRF:
	-$(RM) ./Lib/SPSGRF/SPSGRF.d ./Lib/SPSGRF/SPSGRF.o ./Lib/SPSGRF/SPSGRF.su

.PHONY: clean-Lib-2f-SPSGRF

