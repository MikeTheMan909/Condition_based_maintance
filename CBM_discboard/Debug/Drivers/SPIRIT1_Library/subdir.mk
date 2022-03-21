################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SPIRIT1_Library/radio_target.c 

OBJS += \
./Drivers/SPIRIT1_Library/radio_target.o 

C_DEPS += \
./Drivers/SPIRIT1_Library/radio_target.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SPIRIT1_Library/%.o: ../Drivers/SPIRIT1_Library/%.c Drivers/SPIRIT1_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_discboard/lib/comm" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/debug" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/spsgrf" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SPIRIT1_Library

clean-Drivers-2f-SPIRIT1_Library:
	-$(RM) ./Drivers/SPIRIT1_Library/radio_target.d ./Drivers/SPIRIT1_Library/radio_target.o

.PHONY: clean-Drivers-2f-SPIRIT1_Library

