################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CGame.cpp \
../src/CMap.cpp \
../src/CSprite.cpp \
../src/CTexture.cpp \
../src/CTile.cpp \
../src/CUnit.cpp \
../src/main.cpp 

OBJS += \
./src/CGame.o \
./src/CMap.o \
./src/CSprite.o \
./src/CTexture.o \
./src/CTile.o \
./src/CUnit.o \
./src/main.o 

CPP_DEPS += \
./src/CGame.d \
./src/CMap.d \
./src/CSprite.d \
./src/CTexture.d \
./src/CTile.d \
./src/CUnit.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/1 Programing/C++/Independent-Study/SFML-2.1/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


