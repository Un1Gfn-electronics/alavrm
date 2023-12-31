ifeq ($(shell uname -s),Darwin)
  $(info loading homebrew compat $$PATH ...)
  include /usr/local/share/make/compat.mk
endif

MAKEFLAGS:=-j1 --no-print-directory

# netlist:
# port[~9] -- switch -- buzzer
# buzzer + 220ohm + gnd
#        |        |
#        + 220ohm +

# http://www.rjhcoding.com/avrc-tutorials-home.php

# https://www.microchip.com/en-us/product/atmega328pb

# https://onlinedocs.microchip.com/?find=42559
# https://onlinedocs.microchip.com/?find=42787

# https://docs.arduino.cc/hardware/uno-rev3
# https://www.arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf # schematic
# https://www.microchip.com/en-us/application-notes/an42559        # 328p vs 328pb
# https://www.microchip.com/en-us/application-notes/an42787        # software user guide
# https://www.microchip.com/en-us/search?searchQuery=40001906      # datasheet
# https://www.microchip.com/en-us/search?searchQuery=40002198      # instruction set

# https://stuvel.eu/post/2021-04-27-atmega328pb-on-gcc/
# https://gist.github.com/goncalor/51e1c8038cc058b4379552477255b4e1

#  1kHz =     1000Hz
#  1MHz =  1000000Hz
# 16MHz = 16000000Hz
C:=avr-gcc
# C+=-H
C+=-mmcu=atmega328p
C+=-std=gnu17 -Wall -Wextra -Wno-array-bounds
# C+=-O0
C+=-Os
C+=-DF_CPU=16000000UL

# .PRECIOUS:

default:
	$(MAKE) clean
	$(MAKE) a.elf
	# $(MAKE) lst
	$(MAKE) a.hex
	$(MAKE) upload

# monitor:
# 	picocom --send-cmd "ascii_xfr -s -v -l10" --nolock /dev/arduino-uno

# tty.usbserial-130
upload:
	avrdude -e -c arduino -p m328p -P /dev/cu.usbserial-130 -b 115200 -U flash:w:a.hex

a.hex:
	avr-objcopy -j .text -j .data -O ihex a.elf $@

lst:
	avr-objdump -h -S a.elf

a.elf: main.c beeper.c song.c beeper.h pitch.py
	python3 ./pitch.py >pitch.tmp.h
	$(C) -o $@ $(filter %.c,$^)

# https://gist.github.com/mhitza/8a4608f4dfdec20d3879
# http://www.rjhcoding.com/avr-asm-light-an-led.php
# blink.hex:
# %.hex: %.asm
# 	avra -fI $<

# tty.usbserial-130
erase:
	avrdude -c arduino -p m328p -P /dev/cu.usbserial-130 -b 115200 -e

clean:
	rm -fv *.elf *.hex *.o *.obj *.out *.tmp.h

info:
	type avr-gcc