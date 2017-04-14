################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../view/console_IO.c \
../view/functions_view.c \
../view/main.c \
../view/menus.c 

OBJS += \
./view/console_IO.o \
./view/functions_view.o \
./view/main.o \
./view/menus.o 

C_DEPS += \
./view/console_IO.d \
./view/functions_view.d \
./view/main.d \
./view/menus.d 


# Each subdirectory must supply rules for building sources it contributes
view/%.o: ../view/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


