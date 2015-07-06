################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../camera_app.c \
../httpserverapp.c \
../i2cconfig.c \
../main.c \
../mt9d111.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/network_if.c \
../pinmux.c \
../startup_gcc.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/uart_if.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/udma_if.c 

OBJS += \
./camera_app.o \
./httpserverapp.o \
./i2cconfig.o \
./main.o \
./mt9d111.o \
./network_if.o \
./pinmux.o \
./startup_gcc.o \
./uart_if.o \
./udma_if.o 

C_DEPS += \
./camera_app.d \
./httpserverapp.d \
./i2cconfig.d \
./main.d \
./mt9d111.d \
./network_if.d \
./pinmux.d \
./startup_gcc.d \
./uart_if.d \
./udma_if.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -DENABLE_JPEG -DXGA_FRAME -I"/opt/cc3200/CC3200-Linux-SDK/examples/Websock Camera" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/netapps/http/server" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

network_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/network_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -DENABLE_JPEG -DXGA_FRAME -I"/opt/cc3200/CC3200-Linux-SDK/examples/Websock Camera" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/netapps/http/server" -std=gnu11 -MMD -MP -MF"network_if.d" -MT"network_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/uart_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -DENABLE_JPEG -DXGA_FRAME -I"/opt/cc3200/CC3200-Linux-SDK/examples/Websock Camera" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/netapps/http/server" -std=gnu11 -MMD -MP -MF"uart_if.d" -MT"uart_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

udma_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/udma_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -Dcc3200 -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -DENABLE_JPEG -DXGA_FRAME -I"/opt/cc3200/CC3200-Linux-SDK/examples/Websock Camera" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse//../CC3200-Linux-SDK/src/netapps/http/server" -std=gnu11 -MMD -MP -MF"udma_if.d" -MT"udma_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


