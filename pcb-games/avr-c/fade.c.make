MCU=atmega328p
TARGET_ARCH=-mmcu=$(MCU)
TARGET=fade
CC=avr-gcc
CPPFLAGS=-mmcu=$(MCU)
CFLAGS=-Os -g -Wall -I. -DF_CPU=16000000
LDFLAGS=-g -mmcu=$(MCU) -lm -Wl,--gc-sections -Os
PGMER=-c arduino -p m328p -b 115200 -P /dev/cu.usbmodem14301
PGMERISP=-c avrispv2 -P /dev/cu.usbmodem14301
DUDE=/usr/local/bin/avrdude -V -p $(MCU)

C_SRCS= $(TARGET).c
OBJ_FILES= $(C_SRCS:.c=.out)

all:
	$(TARGET).hex

clean:
	rm -f $(TARGET).elf *.o *.hex

%.out: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $(TARGET).elf eeprom.hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:$(TARGET).hex

size: $(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf
