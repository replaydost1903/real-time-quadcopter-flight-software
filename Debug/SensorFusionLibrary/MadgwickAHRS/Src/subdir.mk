################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.c 

OBJS += \
./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.o 

C_DEPS += \
./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.d 


# Each subdirectory must supply rules for building sources it contributes
SensorFusionLibrary/MadgwickAHRS/Src/%.o SensorFusionLibrary/MadgwickAHRS/Src/%.su SensorFusionLibrary/MadgwickAHRS/Src/%.cyclo: ../SensorFusionLibrary/MadgwickAHRS/Src/%.c SensorFusionLibrary/MadgwickAHRS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SensorFusionLibrary-2f-MadgwickAHRS-2f-Src

clean-SensorFusionLibrary-2f-MadgwickAHRS-2f-Src:
	-$(RM) ./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.cyclo ./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.d ./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.o ./SensorFusionLibrary/MadgwickAHRS/Src/MadgwickAHRS.su

.PHONY: clean-SensorFusionLibrary-2f-MadgwickAHRS-2f-Src

