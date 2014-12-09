################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../abc.c \
../abc_senales.c \
../escritor.c \
../fifoEscritor.c \
../fifoLector.c \
../fifos.c \
../mkPipe.c \
../pipesHijoPadre.c \
../senales.c 

OBJS += \
./abc.o \
./abc_senales.o \
./escritor.o \
./fifoEscritor.o \
./fifoLector.o \
./fifos.o \
./mkPipe.o \
./pipesHijoPadre.o \
./senales.o 

C_DEPS += \
./abc.d \
./abc_senales.d \
./escritor.d \
./fifoEscritor.d \
./fifoLector.d \
./fifos.d \
./mkPipe.d \
./pipesHijoPadre.d \
./senales.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


