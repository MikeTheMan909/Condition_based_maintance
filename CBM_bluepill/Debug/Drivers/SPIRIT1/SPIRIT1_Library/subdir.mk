################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SPIRIT1/SPIRIT1_Library/radio_target.c 

OBJS += \
./Drivers/SPIRIT1/SPIRIT1_Library/radio_target.o 

C_DEPS += \
./Drivers/SPIRIT1/SPIRIT1_Library/radio_target.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SPIRIT1/SPIRIT1_Library/%.o Drivers/SPIRIT1/SPIRIT1_Library/%.su: ../Drivers/SPIRIT1/SPIRIT1_Library/%.c Drivers/SPIRIT1/SPIRIT1_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_bluepill/Drivers/SPIRIT1/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_bluepill/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SPIRIT1-2f-SPIRIT1_Library

clean-Drivers-2f-SPIRIT1-2f-SPIRIT1_Library:
	-$(RM) ./Drivers/SPIRIT1/SPIRIT1_Library/radio_target.d ./Drivers/SPIRIT1/SPIRIT1_Library/radio_target.o ./Drivers/SPIRIT1/SPIRIT1_Library/radio_target.su

.PHONY: clean-Drivers-2f-SPIRIT1-2f-SPIRIT1_Library

