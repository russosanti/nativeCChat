################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TextConScroll.c \
../TextViewWindow.c \
../TextViewWindowPane.c \
../TextWindow.c \
../ejemploventana.c \
../paneles.c \
../paneles2.c \
../text.c 

OBJS += \
./TextConScroll.o \
./TextViewWindow.o \
./TextViewWindowPane.o \
./TextWindow.o \
./ejemploventana.o \
./paneles.o \
./paneles2.o \
./text.o 

C_DEPS += \
./TextConScroll.d \
./TextViewWindow.d \
./TextViewWindowPane.d \
./TextWindow.d \
./ejemploventana.d \
./paneles.d \
./paneles2.d \
./text.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc `pkg-config --cflags --libs gtk+-2.0` -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


