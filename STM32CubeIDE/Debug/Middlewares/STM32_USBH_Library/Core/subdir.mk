################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.o 

C_DEPS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBH_Library/Core/usbh_core.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_pipes.o: C:/projects/STM32-H750B-DK/LTDC_Paint/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DAPPLICATION_ADDRESS=0x90000000 -DSTM32H750xx -DUSE_HAL_DRIVER -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_LDO_SUPPLY -c -I../../Inc -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H750B-DK -I../../Utilities/Fonts -I../../Drivers/BSP/Components/Common -I../../Utilities -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Utilities/lcd -I../../Utilities/Lcd_Trace -I"../../FK/" -I../../Display/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32_USBH_Library-2f-Core

clean-Middlewares-2f-STM32_USBH_Library-2f-Core:
	-$(RM) ./Middlewares/STM32_USBH_Library/Core/usbh_core.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_core.d ./Middlewares/STM32_USBH_Library/Core/usbh_core.o ./Middlewares/STM32_USBH_Library/Core/usbh_core.su ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.su ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.su ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.d ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.o ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.su

.PHONY: clean-Middlewares-2f-STM32_USBH_Library-2f-Core

