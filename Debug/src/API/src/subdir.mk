################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/API/src/AbstractAPI.cpp \
../src/API/src/GAPI.cpp \
../src/API/src/ServerHandler.cpp 

OBJS += \
./src/API/src/AbstractAPI.o \
./src/API/src/GAPI.o \
./src/API/src/ServerHandler.o 

CPP_DEPS += \
./src/API/src/AbstractAPI.d \
./src/API/src/GAPI.d \
./src/API/src/ServerHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/API/src/%.o: ../src/API/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/eclipse_ws_eliav/lab32/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


