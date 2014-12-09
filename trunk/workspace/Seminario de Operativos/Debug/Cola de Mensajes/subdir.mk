################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cola\ de\ Mensajes/Cola_Mensajes.c \
../Cola\ de\ Mensajes/chat_a.c \
../Cola\ de\ Mensajes/escritor.c 

OBJS += \
./Cola\ de\ Mensajes/Cola_Mensajes.o \
./Cola\ de\ Mensajes/chat_a.o \
./Cola\ de\ Mensajes/escritor.o 

C_DEPS += \
./Cola\ de\ Mensajes/Cola_Mensajes.d \
./Cola\ de\ Mensajes/chat_a.d \
./Cola\ de\ Mensajes/escritor.d 


# Each subdirectory must supply rules for building sources it contributes
Cola\ de\ Mensajes/Cola_Mensajes.o: ../Cola\ de\ Mensajes/Cola_Mensajes.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Cola de Mensajes/Cola_Mensajes.d" -MT"Cola\ de\ Mensajes/Cola_Mensajes.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Cola\ de\ Mensajes/chat_a.o: ../Cola\ de\ Mensajes/chat_a.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Cola de Mensajes/chat_a.d" -MT"Cola\ de\ Mensajes/chat_a.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Cola\ de\ Mensajes/escritor.o: ../Cola\ de\ Mensajes/escritor.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Cola de Mensajes/escritor.d" -MT"Cola\ de\ Mensajes/escritor.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


