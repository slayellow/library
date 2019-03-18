################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/CFilefHigh.cpp 

OBJS += \
./Core/CFilefHigh.o 

CPP_DEPS += \
./Core/CFilefHigh.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


