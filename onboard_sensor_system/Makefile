MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU)
OBJ = main spi nrf24l01      
OBJ_FILES = $(OBJ:=.o)

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o main.elf $(OBJ_FILES)
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: all
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -D -U flash:w:main.hex:i

clean:
	rm -f *.o *.elf *.hex

monitor:
	screen /dev/ttyUSB0 9600