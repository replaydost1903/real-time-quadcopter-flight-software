################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TaskHandles/Src/task_handles.c 

OBJS += \
./TaskHandles/Src/task_handles.o 

C_DEPS += \
./TaskHandles/Src/task_handles.d 


# Each subdirectory must supply rules for building sources it contributes
TaskHandles/Src/%.o TaskHandles/Src/%.su TaskHandles/Src/%.cyclo: ../TaskHandles/Src/%.c TaskHandles/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/FlightInterfaceParser/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/FligthControl/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/TaskHandles/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/Config" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/OS" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/SEGGER" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/TaskHandles/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source/include" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TaskHandles-2f-Src

clean-TaskHandles-2f-Src:
	-$(RM) ./TaskHandles/Src/task_handles.cyclo ./TaskHandles/Src/task_handles.d ./TaskHandles/Src/task_handles.o ./TaskHandles/Src/task_handles.su

.PHONY: clean-TaskHandles-2f-Src

