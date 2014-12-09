################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Semaforos/ejercicios_sem.c \
../Semaforos/procA_sem.c \
../Semaforos/semaforos.c 

OBJS += \
./Semaforos/ejercicios_sem.o \
./Semaforos/procA_sem.o \
./Semaforos/semaforos.o 

C_DEPS += \
./Semaforos/ejercicios_sem.d \
./Semaforos/procA_sem.d \
./Semaforos/semaforos.d 


# Each subdirectory must supply rules for building sources it contributes
Semaforos/%.o: ../Semaforos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


