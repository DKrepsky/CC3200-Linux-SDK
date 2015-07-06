################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../startup_gcc.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/uart_if.c 

OBJS += \
./main.o \
./startup_gcc.o \
./uart_if.o 

C_DEPS += \
./main.d \
./startup_gcc.d \
./uart_if.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/CC3200-Linux-SDK/examples/Provisioning AP" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/uart_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/CC3200-Linux-SDK/examples/Provisioning AP" -std=gnu11 -MMD -MP -MF"uart_if.d" -MT"uart_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


