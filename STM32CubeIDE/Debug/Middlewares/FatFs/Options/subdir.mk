################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/Third_Party/FatFs/src/option/syscall.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/Third_Party/FatFs/src/option/unicode.c 

OBJS += \
./Middlewares/FatFs/Options/syscall.o \
./Middlewares/FatFs/Options/unicode.o 

C_DEPS += \
./Middlewares/FatFs/Options/syscall.d \
./Middlewares/FatFs/Options/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Options/syscall.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/Third_Party/FatFs/src/option/syscall.c Middlewares/FatFs/Options/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I"../../Display/" -I"../../AppLogic/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/Options/unicode.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/Third_Party/FatFs/src/option/unicode.c Middlewares/FatFs/Options/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I"../../Display/" -I"../../AppLogic/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-Options

clean-Middlewares-2f-FatFs-2f-Options:
	-$(RM) ./Middlewares/FatFs/Options/syscall.cyclo ./Middlewares/FatFs/Options/syscall.d ./Middlewares/FatFs/Options/syscall.o ./Middlewares/FatFs/Options/syscall.su ./Middlewares/FatFs/Options/unicode.cyclo ./Middlewares/FatFs/Options/unicode.d ./Middlewares/FatFs/Options/unicode.o ./Middlewares/FatFs/Options/unicode.su

.PHONY: clean-Middlewares-2f-FatFs-2f-Options

