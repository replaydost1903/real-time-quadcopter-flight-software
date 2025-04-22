################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ThirdParty/FreeRTOS/Source/portable/MemMang/subdir.mk
-include ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include ThirdParty/FreeRTOS/Source/subdir.mk
-include SensorLibrary/bmp388/bmp388_selftest/Src/subdir.mk
-include SensorLibrary/bmp388/bmp388_port/Src/subdir.mk
-include SensorLibrary/bmp388/Src/subdir.mk
-include SensorLibrary/bmi160/bmi160_port/Src/subdir.mk
-include SensorLibrary/bmi160/Src/subdir.mk
-include SensorFusionLibrary/ComplementaryFilter/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include ControllerDriver/pid/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := Real_Time_Flight_Stabilization
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Real_Time_Flight_Stabilization.elf \

MAP_FILES += \
Real_Time_Flight_Stabilization.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Real_Time_Flight_Stabilization.list \


# All Target
all: main-build

# Main-build Target
main-build: Real_Time_Flight_Stabilization.elf secondary-outputs

# Tool invocations
Real_Time_Flight_Stabilization.elf Real_Time_Flight_Stabilization.map: $(OBJS) $(USER_OBJS) C:\Users\Kubilay\Desktop\quadcopter_project\Software\Real_Time_Fligth_Stabilization\Real_Time_Flight_Stabilization\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Real_Time_Flight_Stabilization.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Kubilay\Desktop\quadcopter_project\Software\Real_Time_Fligth_Stabilization\Real_Time_Flight_Stabilization\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Real_Time_Flight_Stabilization.map" -Wl,--gc-sections -static -L"C:\Users\Kubilay\Desktop\quadcopter_project\Software\Real_Time_Fligth_Stabilization\Real_Time_Flight_Stabilization\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Real_Time_Flight_Stabilization.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Real_Time_Flight_Stabilization.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Real_Time_Flight_Stabilization.elf Real_Time_Flight_Stabilization.list Real_Time_Flight_Stabilization.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
