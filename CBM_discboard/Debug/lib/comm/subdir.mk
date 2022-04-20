################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/comm/comm.c 

OBJS += \
./lib/comm/comm.o 

C_DEPS += \
./lib/comm/comm.d 


# Each subdirectory must supply rules for building sources it contributes
lib/comm/%.o lib/comm/%.su: ../lib/comm/%.c lib/comm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"D:/Quest_workspace/CBM/CBM_discboard/lib/comm" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/debug" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/spsgrf" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library/Inc" -I"D:/Quest_workspace/CBM/CBM_discboard/Drivers/SPIRIT1_Library" -I"D:/Quest_workspace/CBM/CBM_discboard/lib" -I"D:/Quest_workspace/CBM/CBM_discboard/lib/cbm" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-comm

clean-lib-2f-comm:
	-$(RM) ./lib/comm/comm.d ./lib/comm/comm.o ./lib/comm/comm.su

.PHONY: clean-lib-2f-comm

