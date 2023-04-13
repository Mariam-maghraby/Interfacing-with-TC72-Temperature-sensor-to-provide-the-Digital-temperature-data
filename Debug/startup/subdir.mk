################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"E:/4th_year_Biomedical/firstTerm/AdvancedEmbedded/43_polling/43_polling/inc" -I"E:/4th_year_Biomedical/firstTerm/AdvancedEmbedded/43_polling/43_polling/CMSIS/device" -I"E:/4th_year_Biomedical/firstTerm/AdvancedEmbedded/43_polling/43_polling/CMSIS/core" -I"E:/4th_year_Biomedical/firstTerm/AdvancedEmbedded/43_polling/43_polling/Drivers/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

