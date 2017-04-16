################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../model/tools/data_handler.c \
../model/tools/hash_map.c \
../model/tools/map_of_map.c 

OBJS += \
./model/tools/data_handler.o \
./model/tools/hash_map.o \
./model/tools/map_of_map.o 

C_DEPS += \
./model/tools/data_handler.d \
./model/tools/hash_map.d \
./model/tools/map_of_map.d 


# Each subdirectory must supply rules for building sources it contributes
model/tools/%.o: ../model/tools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


