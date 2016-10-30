################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../punto-montaje/fuseLib.c 

OBJS += \
./punto-montaje/fuseLib.o 

C_DEPS += \
./punto-montaje/fuseLib.d 


# Each subdirectory must supply rules for building sources it contributes
punto-montaje/%.o: ../punto-montaje/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -D_FILE_OFFSET_BITS=64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


