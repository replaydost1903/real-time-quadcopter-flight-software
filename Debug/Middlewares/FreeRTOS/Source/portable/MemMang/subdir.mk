################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.c \
../Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.c \
../Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.c \
../Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.c \
../Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.c 

OBJS += \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.o \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.o \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.o \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.o \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.o 

C_DEPS += \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.d \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.d \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.d \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.d \
./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/Source/portable/MemMang/%.o Middlewares/FreeRTOS/Source/portable/MemMang/%.su Middlewares/FreeRTOS/Source/portable/MemMang/%.cyclo: ../Middlewares/FreeRTOS/Source/portable/MemMang/%.c Middlewares/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/ComplementaryFilter/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/Middlewares/FreeRTOS/Source" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/Middlewares/FreeRTOS/Source/include" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/ControllerDriver/pid/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MadgwickAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorFusionLibrary/MahonyAHRS/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/bmi160_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmi160/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_port/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/bmp388_selftest/Inc" -I"C:/Users/Kubilay/Desktop/quadcopter_project/Software/Real_Time_Fligth_Stabilization/Real_Time_Flight_Stabilization/SensorLibrary/bmp388/Inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.cyclo ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.d ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.o ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_1.su ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.cyclo ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.d ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.o ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_2.su ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.cyclo ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.d ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.o ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_3.su ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.cyclo ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.d ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.o ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_4.su ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.cyclo ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.d ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.o ./Middlewares/FreeRTOS/Source/portable/MemMang/heap_5.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

