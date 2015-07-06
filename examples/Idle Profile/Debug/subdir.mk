################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lp3p0_board.c \
../lp3p0_plat_ops.c \
../main.c \
../pinmux.c \
../startup_gcc.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/utils_if.c \
/opt/cc3200/CC3200-Linux-SDK/examples/common/wdt_if.c 

OBJS += \
./lp3p0_board.o \
./lp3p0_plat_ops.o \
./main.o \
./pinmux.o \
./startup_gcc.o \
./utils_if.o \
./wdt_if.o 

C_DEPS += \
./lp3p0_board.d \
./lp3p0_plat_ops.d \
./main.d \
./pinmux.d \
./startup_gcc.d \
./utils_if.d \
./wdt_if.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver/hal" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/pm" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/timer" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/soc" -I"/opt/cc3200/CC3200-Linux-SDK/examples/Idle Profile" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utils_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/utils_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver/hal" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/pm" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/timer" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/soc" -I"/opt/cc3200/CC3200-Linux-SDK/examples/Idle Profile" -std=c99 -MMD -MP -MF"utils_if.d" -MT"utils_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

wdt_if.o: /opt/cc3200/CC3200-Linux-SDK/examples/common/wdt_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Dgcc -DUSE_FREERTOS -DSL_PLATFORM_MULTI_THREADED -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/portable/GCC/ARM_CM4" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS/Source/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/other/FreeRTOS" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/simplelink/include" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/examples/common" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/driverlib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/oslib" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/inc" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/driver/hal" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/pm" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/framework/timer" -I"/opt/cc3200/eclipse/../CC3200-Linux-SDK/src/middleware/soc" -I"/opt/cc3200/CC3200-Linux-SDK/examples/Idle Profile" -std=c99 -MMD -MP -MF"wdt_if.d" -MT"wdt_if.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


