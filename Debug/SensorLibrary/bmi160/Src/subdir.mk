################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SensorLibrary/bmi160/Src/bmi160.c 

OBJS += \
./SensorLibrary/bmi160/Src/bmi160.o 

C_DEPS += \
./SensorLibrary/bmi160/Src/bmi160.d 


# Each subdirectory must supply rules for building sources it contributes
SensorLibrary/bmi160/Src/%.o SensorLibrary/bmi160/Src/%.su SensorLibrary/bmi160/Src/%.cyclo: ../SensorLibrary/bmi160/Src/%.c SensorLibrary/bmi160/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/HMC5883L/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/QuadcopterModel" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/FlightInterfaceParser/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/FligthControl/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/TaskHandles/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/Config" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/OS" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/SEGGER/SEGGER" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/TaskHandles/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ThirdParty/FreeRTOS/Source/include" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SensorLibrary-2f-bmi160-2f-Src

clean-SensorLibrary-2f-bmi160-2f-Src:
	-$(RM) ./SensorLibrary/bmi160/Src/bmi160.cyclo ./SensorLibrary/bmi160/Src/bmi160.d ./SensorLibrary/bmi160/Src/bmi160.o ./SensorLibrary/bmi160/Src/bmi160.su

.PHONY: clean-SensorLibrary-2f-bmi160-2f-Src

