################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../model/test/exemple.c \
../model/test/test.c 

OBJS += \
./model/test/exemple.o \
./model/test/test.o 

C_DEPS += \
./model/test/exemple.d \
./model/test/test.d 


# Each subdirectory must supply rules for building sources it contributes
model/test/%.o: ../model/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


