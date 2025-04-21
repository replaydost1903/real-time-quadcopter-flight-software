################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.c 

OBJS += \
./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.o 

C_DEPS += \
./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
SensorLibrary/bmp388/bmp388_selftest/Src/%.o SensorLibrary/bmp388/bmp388_selftest/Src/%.su SensorLibrary/bmp388/bmp388_selftest/Src/%.cyclo: ../SensorLibrary/bmp388/bmp388_selftest/Src/%.c SensorLibrary/bmp388/bmp388_selftest/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SensorLibrary-2f-bmp388-2f-bmp388_selftest-2f-Src

clean-SensorLibrary-2f-bmp388-2f-bmp388_selftest-2f-Src:
	-$(RM) ./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.cyclo ./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.d ./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.o ./SensorLibrary/bmp388/bmp388_selftest/Src/bmp3_selftest.su

.PHONY: clean-SensorLibrary-2f-bmp388-2f-bmp388_selftest-2f-Src

