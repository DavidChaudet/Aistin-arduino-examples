# Aistin Arduino examples  
<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/Aistin-CPU2.png" align="right" />
These are Arduino examples for iProtoXi Aistin family. [Arduino IDE](https://www.arduino.cc/en/Main/Software) (1.5.0-) required. For Arduino Classic IDE support see FAQ [I want to use Arduino Classic IDE](#I-want-to-use-Arduino-Classic-IDE).  

In this readme
* [Support for Arduino IDE](#Support-for-Arduino-IDE)
* [Attaching the boards](#Attaching-the-boards)
* [FAQ](#FAQ)


##	Support for Arduino IDE
1.	Detach Aistin CPU 2 from your PC.
2.	Check you have Arduino IDE version 1.5.0 or newer. 
	*	Launch Arduino IDE and check your version from title bar (Version 1.6.5 in figure).  
		<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/arduino-version.png "/>
	*	If you don’t have Arduino IDE installed or have an older version install newer version from 
		https://www.arduino.cc/en/Main/Software
3.	Check location of your Arduino Sketchbook-directory.
	*	On Arduino IDE open File-menu and open Preferences.  
  		<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/file-menu.png "/>
	*	Write down location of your Sketchbook and exit Arduino IDE.  
		<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/sketchbook-location.png "/>
4.	Download repository with <img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/download-button.png "/>-button on the right.
5.	Open the Zip-file and open Aistin-arduino-examples-master-folder inside.
6.	Extract the package to Arduino Sketchbook-folder.
7.	Go to Arduino Sketchbook folder and copy the hardware folder.
8.	Head to Arduino installation folder and paste hardware folder.
This will not overwrite but merge the Arduino’s hardware-folder with Aistin hardware-folder.
9.	Open the hardware-folder and inside it the arduino-folder and inside it the avr-folder.
10.	Execute addboard.bat file. If Arduino IDE is installed with installer this step requires running the batch-file as administrator. Select the file with second mouse button and select Run as administrator.
	*	Alternatively you can manually copy the text from aistinboard.txt-file to boards.txt. This requires using text editor with administrator privileges.
11.	Head back to Arduino Sketchbook-directory and open folder windows-driver.
12.	Run file dpinst.exe as administrator.
	*	Windows 8.1 64bit and newer users need to allow installation of unsigned drivers. Check this tutorial: http://www.howtogeek.com/167723/how-to-disable-driver-signature-verification-on-64-bit-windows-8.1-so-that-you-can-install-unsigned-drivers/
13.	Now connect Aistin CPU 2 to your PC. Windows will now recognize the device and install drivers.
14.	Launch Arduino IDE.
15.	On Arduino IDE open Tools-menu and from both Board- and Port-submenu select Aistin CPU 2. 
16.	Next open File-menu and from Sketchbook-submenu select example code to try out.
17.	Press Upload-button <img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/upload-button.png "/> to upload code into Aistin CPU 2. 

## Attaching the boards
Connect the addon boards to CPU board by connecting the female and male [Aistin BUS24](https://iprotoxi.fi/index.php/aistin-bus24) connectors. Push gently on the Aistin BUS24 connectors pointed by the blue arrows on the first figure. Make sure the addon boards are aligned with the CPU board like in the first figure. DO NOT connect the addon boards as in the crossed figure.  
<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/Addonboards-correct.png "/>  
<img src="https://raw.github.com/iProtoXi/Aistin-arduino-examples/master/img/Addonboards-incorrect.png "/>  

##	FAQ  
###	Where is my Arduino Sketchbook folder?  
You can find your Sketchbook location at the Arduino IDE preferences. Launch Arduino IDE, select File-Preferences.  
Default location in Mac & Windows: *Documents\Arduino*. In Linux: */home/username/Sketchbook*  
###	My board is not working.  
Make sure your board is powered by pressing power switch (next to the usb connector).  
Try to detach, wait 30sec and reattach the usb cable.  
If you are using Windows make sure you have installed the Windows drivers.  
###	My windows says drivers are not signed and does not allow me to install them.  
Windows 8 and newer require you to enable installing unsigned drivers. Look link below for how-to-tutorial:  
http://www.addictivetips.com/windows-tips/how-to-install-any-digitally-unsigned-drivers-on-windows-8/  
###	Green led keeps blinking and board is not responsive  
Reboot the device by pressing power switch two times.  
###	Problems with uploading code:  
After pressing upload at Arduino IDE green led should start blinking in few seconds.  
When led stops blinking immediately force microcontroller to bootloader mode by launching avrdude with following settings:  
*avrdude -C"[avrdude.conf location]" -patmega32u4 -cavr109 -P[communication port] -b1200*  
Replace the *[avrdude.conf location]* with actual location of the file (default: *[Arduino-installation-folder]\hardware\tools\avr\etc\avrdude.conf*).  
Replace the [communication port] with the port of the Aistin CPU (eg. Windows: COM4, Linux: */dev/ttyACM0*, Mac: */dev/tty.usbmodem262471*).  
###	Aistin CPU is not showing in my Arduino IDE board menu.  
If you are using Windows make sure you have installed the drivers.  
Merge the included hardware -folder with the Arduino's hardware folder (*\Arduino-installation-folder\hardware\*).  
Navigate into Arduino's *\hardware\arduino\avr* folder. Copy text from *aistinboard.txt* into the end of *boards.txt*.  
###	Arduino can not find libraries.  
Copy the libraries-folder and merge it with the *[Arduino-installation-folder]\libraries*  
###	I want to use Arduino Classic IDE
Support for Arduino IDE v1.0.x is found in *Arduino 1.0.x support* folder. See readme in there for more information.