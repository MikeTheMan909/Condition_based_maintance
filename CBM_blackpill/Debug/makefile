################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Lib/sensor/subdir.mk
-include Lib/SPSGRF/subdir.mk
-include Lib/Mesh/subdir.mk
-include Lib/Debug/subdir.mk
-include Lib/Comm/subdir.mk
-include Lib/Cbm/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/SPIRIT1/SPIRIT1_Library/Src/subdir.mk
-include Drivers/SPIRIT1/SPIRIT1_Library/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := CBM_blackpill
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CBM_blackpill.elf \

MAP_FILES += \
CBM_blackpill.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CBM_blackpill.list \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: CBM_blackpill.elf secondary-outputs

# Tool invocations
CBM_blackpill.elf CBM_blackpill.map: $(OBJS) $(USER_OBJS) D:\Quest_workspace\CBM\CBM_blackpill\STM32F411CEUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CBM_blackpill.elf" @"objects.list" $(USER_OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group -mcpu=cortex-m4 -T"D:\Quest_workspace\CBM\CBM_blackpill\STM32F411CEUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CBM_blackpill.map" -Wl,--gc-sections -static -L"D:\Quest_workspace\CBM\CBM_blackpill\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CBM_blackpill.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CBM_blackpill.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CBM_blackpill.elf CBM_blackpill.list CBM_blackpill.map default.size.stdout
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex CBM_blackpill.elf CBM_blackpill.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
