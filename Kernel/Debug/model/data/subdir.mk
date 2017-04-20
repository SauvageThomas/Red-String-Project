################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../model/data/config.c \
../model/data/data_base.c \
../model/data/password.c 

OBJS += \
./model/data/config.o \
./model/data/data_base.o \
./model/data/password.o 

C_DEPS += \
./model/data/config.d \
./model/data/data_base.d \
./model/data/password.d 


# Each subdirectory must supply rules for building sources it contributes
model/data/%.o: ../model/data/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


