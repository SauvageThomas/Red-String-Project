################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../model/descriptor/descriptor_generator.c \
../model/descriptor/image_descriptor_generator.c \
../model/descriptor/image_index_generator.c \
../model/descriptor/index_generator.c \
../model/descriptor/sound_descriptor_generator.c \
../model/descriptor/text_descriptor_generator.c 

OBJS += \
./model/descriptor/descriptor_generator.o \
./model/descriptor/image_descriptor_generator.o \
./model/descriptor/image_index_generator.o \
./model/descriptor/index_generator.o \
./model/descriptor/sound_descriptor_generator.o \
./model/descriptor/text_descriptor_generator.o 

C_DEPS += \
./model/descriptor/descriptor_generator.d \
./model/descriptor/image_descriptor_generator.d \
./model/descriptor/image_index_generator.d \
./model/descriptor/index_generator.d \
./model/descriptor/sound_descriptor_generator.d \
./model/descriptor/text_descriptor_generator.d 


# Each subdirectory must supply rules for building sources it contributes
model/descriptor/%.o: ../model/descriptor/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


