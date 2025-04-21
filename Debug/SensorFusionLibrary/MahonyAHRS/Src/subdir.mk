################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.c 

OBJS += \
./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.o 

C_DEPS += \
./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.d 


# Each subdirectory must supply rules for building sources it contributes
SensorFusionLibrary/MahonyAHRS/Src/%.o SensorFusionLibrary/MahonyAHRS/Src/%.su SensorFusionLibrary/MahonyAHRS/Src/%.cyclo: ../SensorFusionLibrary/MahonyAHRS/Src/%.c SensorFusionLibrary/MahonyAHRS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SensorFusionLibrary-2f-MahonyAHRS-2f-Src

clean-SensorFusionLibrary-2f-MahonyAHRS-2f-Src:
	-$(RM) ./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.cyclo ./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.d ./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.o ./SensorFusionLibrary/MahonyAHRS/Src/MahonyAHRS.su

.PHONY: clean-SensorFusionLibrary-2f-MahonyAHRS-2f-Src

