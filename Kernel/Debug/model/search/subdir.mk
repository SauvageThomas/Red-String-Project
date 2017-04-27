################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../model/search/data_manager.c \
../model/search/image_finder.c \
../model/search/sound_finder.c \
../model/search/text_finder.c 

OBJS += \
./model/search/data_manager.o \
./model/search/image_finder.o \
./model/search/sound_finder.o \
./model/search/text_finder.o 

C_DEPS += \
./model/search/data_manager.d \
./model/search/image_finder.d \
./model/search/sound_finder.d \
./model/search/text_finder.d 


# Each subdirectory must supply rules for building sources it contributes
model/search/%.o: ../model/search/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


