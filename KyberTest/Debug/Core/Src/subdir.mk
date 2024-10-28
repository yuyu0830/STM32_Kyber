################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/fips202.c \
../Core/Src/indcpa.c \
../Core/Src/main.c \
../Core/Src/ntt.c \
../Core/Src/poly.c \
../Core/Src/polyvec.c \
../Core/Src/reduce.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/fips202.o \
./Core/Src/indcpa.o \
./Core/Src/main.o \
./Core/Src/ntt.o \
./Core/Src/poly.o \
./Core/Src/polyvec.o \
./Core/Src/reduce.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/fips202.d \
./Core/Src/indcpa.d \
./Core/Src/main.d \
./Core/Src/ntt.d \
./Core/Src/poly.d \
./Core/Src/polyvec.d \
./Core/Src/reduce.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/fips202.cyclo ./Core/Src/fips202.d ./Core/Src/fips202.o ./Core/Src/fips202.su ./Core/Src/indcpa.cyclo ./Core/Src/indcpa.d ./Core/Src/indcpa.o ./Core/Src/indcpa.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/ntt.cyclo ./Core/Src/ntt.d ./Core/Src/ntt.o ./Core/Src/ntt.su ./Core/Src/poly.cyclo ./Core/Src/poly.d ./Core/Src/poly.o ./Core/Src/poly.su ./Core/Src/polyvec.cyclo ./Core/Src/polyvec.d ./Core/Src/polyvec.o ./Core/Src/polyvec.su ./Core/Src/reduce.cyclo ./Core/Src/reduce.d ./Core/Src/reduce.o ./Core/Src/reduce.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

