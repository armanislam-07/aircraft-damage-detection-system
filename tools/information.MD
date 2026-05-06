The NiceNano uses a .uf2 pipline to flash code. Below is the command you put it so we can flash our code


python uf2conv.py tx_new.ino.hex -o firmware.uf2 -f 0xADA52840

uf2conv.py is the tool we use to convert our compiled .hex file into a .uf2

tx_new.ino.hex is our compiled .hex file

firmware.uf2 is the name of our output.uf2 file we will use to flash

-f 0xADA52840 basically tells the tool, using our .uf2 we created to flash the specific address (review over the correct wording and phrase)
