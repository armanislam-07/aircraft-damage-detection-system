MCU=atmega328p
F_CPU=16000000UL
CC=avr-gcc
CFLAGS=-mmcu=$(MCU) -Os -DF_CPU=$(F_CPU)
OBJ=main



all:
	$(CC) $(CFLAGS) -o $(OBJ).elf $(OBJ).c
	avr-objcopy -O ihex -R .eeprom $(OBJ).elf $(OBJ).hex


flash: 
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -D -U flash:w:$(OBJ).hex:i


clean:
	rm -f *.elf *.hex 

#change depending on station you are flashing from 
monitor:
	screen /dev/ttyUSB0 9600
