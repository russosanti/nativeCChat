################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Memoria\ Compartida/Mem_Compartida.c \
../Memoria\ Compartida/Productor.c 

OBJS += \
./Memoria\ Compartida/Mem_Compartida.o \
./Memoria\ Compartida/Productor.o 

C_DEPS += \
./Memoria\ Compartida/Mem_Compartida.d \
./Memoria\ Compartida/Productor.d 


# Each subdirectory must supply rules for building sources it contributes
Memoria\ Compartida/Mem_Compartida.o: ../Memoria\ Compartida/Mem_Compartida.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Memoria Compartida/Mem_Compartida.d" -MT"Memoria\ Compartida/Mem_Compartida.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Memoria\ Compartida/Productor.o: ../Memoria\ Compartida/Productor.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Memoria Compartida/Productor.d" -MT"Memoria\ Compartida/Productor.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


