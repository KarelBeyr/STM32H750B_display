################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c 

OBJS += \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.o \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.o \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.o 

C_DEPS += \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.d \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.d \
./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c Middlewares/STM32_USBH_Library/Class/MSC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c Middlewares/STM32_USBH_Library/Class/MSC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c Middlewares/STM32_USBH_Library/Class/MSC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32_USBH_Library-2f-Class-2f-MSC

clean-Middlewares-2f-STM32_USBH_Library-2f-Class-2f-MSC:
	-$(RM) ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.cyclo ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.d ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.o ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc.su ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.cyclo ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.d ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.o ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_bot.su ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.cyclo ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.d ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.o ./Middlewares/STM32_USBH_Library/Class/MSC/usbh_msc_scsi.su

.PHONY: clean-Middlewares-2f-STM32_USBH_Library-2f-Class-2f-MSC

