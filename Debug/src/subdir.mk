################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CAtomicVoxel.cpp \
../src/CGame.cpp \
../src/CGrid.cpp \
../src/CSprite.cpp \
../src/CTexture.cpp \
../src/IRenderable.cpp \
../src/IUpdateable.cpp \
../src/main.cpp 

OBJS += \
./src/CAtomicVoxel.o \
./src/CGame.o \
./src/CGrid.o \
./src/CSprite.o \
./src/CTexture.o \
./src/IRenderable.o \
./src/IUpdateable.o \
./src/main.o 

CPP_DEPS += \
./src/CAtomicVoxel.d \
./src/CGame.d \
./src/CGrid.d \
./src/CSprite.d \
./src/CTexture.d \
./src/IRenderable.d \
./src/IUpdateable.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Independent-Study/SFML-2.1/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


