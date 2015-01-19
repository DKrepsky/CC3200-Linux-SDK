################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Provisioning\ SmartConfig.hex \

SECONDARY_SIZE += \
Provisioning\ SmartConfig.siz \


# All Target
all: Provisioning\ SmartConfig.elf secondary-outputs

# Tool invocations
Provisioning\ SmartConfig.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "/home/dkrepsky/App/CC3200SDK-Linux/eclipse//../sdk/other/cc3200.ld" -Xlinker --gc-sections -L"/home/dkrepsky/App/CC3200SDK-Linux/eclipse//../sdk/lib" -Wl,-Map,"Provisioning SmartConfig.map" -eResetISR -o "Provisioning SmartConfig.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Provisioning\ SmartConfig.hex: Provisioning\ SmartConfig.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "Provisioning SmartConfig.elf"  "Provisioning SmartConfig.hex"
	@echo 'Finished building: $@'
	@echo ' '

Provisioning\ SmartConfig.siz: Provisioning\ SmartConfig.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "Provisioning SmartConfig.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "Provisioning SmartConfig.elf"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
