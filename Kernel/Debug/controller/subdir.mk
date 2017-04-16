################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../controller/functions.c \
../controller/functions_wrapper.c 

OBJS += \
./controller/functions.o \
./controller/functions_wrapper.o 

C_DEPS += \
./controller/functions.d \
./controller/functions_wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
controller/%.o: ../controller/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


