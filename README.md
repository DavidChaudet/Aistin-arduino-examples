# Aistin Arduino examples  
These are Arduino examples for iProtoXi Aistin family. Arduino IDE (1.5.0-) required.  
## How to use  
1. Download the repository & extract it to Arduino's *Sketchbook* folder.<br>
Trouble finding sketchbook location check FAQ "Where is my Arduino Sketchbook folder?"  
2. Merge the included *hardware* folder with Arduino's *hardware* folder.  
3. Navigate into Arduino's *\hardware\arduino\avr* folder.  
4. On windows: you can run addboard.bat file to automatically add board. <br>
If you have installed Arduino you need to run batch file as administrator(mouse right click and *Run as administrator*).  
4. On other systems: you need to manually copy text from aistinboard.txt into the end of boards.txt.  
5. If using windows. Install driver at windows-driver -folder(*dpinst.exe* mouse right click and *Run as administrator*).<br>
Windows 8 and newer users check FAQ "My windows says drivers are not signed."  
6. Connect sensor board(s) to Aistin CPU.  
7. Connect CPU to computer.  
8. Launch Arduino IDE and open one of the examples.  
9. Select *Aistin CPU 2* at *Tools - Board*.  
10. Upload code.  

##FAQ
###Where is my Arduino Sketchbook folder?  
You can find your Sketchbook location at the Arduino IDE preferences. Launch Arduino IDE, select File-Preferences.  
Default location in Mac & Windows: Documents\Arduino. In Linux: /home/username/Sketchbook  
###My board is not working.  
Detach and retach usb cable.  
If you are using Windows make sure you have installed the Windows drivers.  
Make sure your board is powered by pressing power switch (next to the usb connector).  
###My windows says drivers are not signed.  
Windows 8 and newer require you to enable installing unsigned drivers. Look link below for how-to-tutorial:  
http://www.addictivetips.com/windows-tips/how-to-install-any-digitally-unsigned-drivers-on-windows-8/  
###Green led keeps blinking and board is not responsive  
Reboot the device by pressing power switch two times.  
###Problems with uploading code:  
After pressing upload at Arduino IDE green led should start blinking in few seconds.  
When led stops blinking immediately force Micro to bootloader mode by launching avrdude with following settings:  
avrdude -C"[avrdude.conf location]" -patmega32u4 -cavr109 -P[communication port] -b1200  
Replace the [avrdude.conf location] with actual location of the file (default: [Arduino-installation-folder]\hardware\tools\avr\etc\avrdude.conf).  
Replace the [communication port] with the port of the iProtoXi Micro (eg. Windows: COM4, Linux: /dev/ttyACM0, Mac: /dev/tty.usbmodem262471).  
###iProtoXi Micro is not showing in my Arduino IDE board menu.  
If you are using Windows make sure you have installed the drivers.  
Make sure you have Classic Arduino IDE (versions 1.0.4 to 1.0.6 should work).  
Merge the included hardware -folder with the Arduino's hardware folder (\Arduino-installation-folder\hardware\).  
###Arduino can not find libraries.  
Copy the libraries-folder and merge it with the [Arduino-installation-folder]\libraries  