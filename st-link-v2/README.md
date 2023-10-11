

 * I have the following ST-LINK V2:

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/03.jpg" width="50%" >


 * I installed the [ST-LINK, ST-LINK/V2, ST-LINK/V2-1, STLINK-V3 USB driver signed for Windows7, Windows8, Windows10](https://www.st.com/en/development-tools/stsw-link009.html)

 * I installed the [ST Visual IDE for developing STM8 applications ](https://www.st.com/en/development-tools/stvd-stm8.html)


 * I'm also using PlatformIO installation with the following platformio.ini settings:

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/04.png" width="50%" >


 * PltaformIO while programming shows some errors. When I execute the **stm8flash** (part of PlatformIO) tool from command line it looks like below. The **red** diode
of the programmer is constantly on. The **blue** diode is off. The process seems to hang and I need to hit Ctrl-C (or remove the programmer USB dongle) to break it 

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/05.png" width="50%" >


 * When using **ST Visual Programmer** (installed together with **ST Visual IDE for developing STM8 applications**) it also shows
some errors and the **red** diode of the programmes is constantly on (while **blue** diode is off). Unfortunately I don't have a screenshot yet.


 * I decided to upgrade the firmware of my ST-LINK V2 programmer. To do this need to install [ST-LINK, ST-LINK/V2, ST-LINK/V2-1, STLINK-V3 firmware upgrade](https://www.st.com/en/development-tools/stsw-link007.html)
and run the Windows/ST-LinkUpgrade.exe program. Current firmaware of my ST-LINK V2 was V2.J29.57, which has been upgraded to V2.J43.57.
The tool just installs a new software to the microcontroller of ST-LINK V2 programmer:

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/10.png" width="50%" >


 * After that flashing with the usage of **stm8flash** shows a different issue and the **red** and **blue** diodes of the programmer blink.
When the command is finished **red** and **blue** diodes are on constantly:

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/15.png" width="50%" >


 * While also the **ST Visual Programmer** shows some different error message. At the beginning the **red** and **blue** diodes of the programmer blink
and later only **blue** is on (while **red** is turned off):

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/20.png" width="50%" >


 * In my opinion it looks a bit better now. I have read that the cause of the issue may be:
   * wrong cable connections
   * lack of capacitor on Vcap pin of the microcontroller
   * battery or power issues
   * to long cbales between ST-LINK V2 and the target microcontroller
   
 The wiring between programmer and target is correct. The capacitor on Vcap is hard to be investigated, but since the HC-12 works correctly when I
 coonnect it to Arduino Nano, I'm assuming that the capacitor is already there. The cables could be a problem here as they are 20cm long. I'ver replaced
 them with a shorter one - 10cm and it seems to help. When reading the FLASH I got the error saying that the device is protected and reading/writing is
 not allowed:
 
<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/25.png" width="50%" >
 
 
 
Almost there to finally fix the programming issue. First need to write OPTION BYTE with disabled protection.

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/30.png" width="50%" >
 
During the process the entire device will be erased, but it will be possible to upload new firmware. Now it reads the FLASH,
however we have all zeros. 

<img src="https://raw.githubusercontent.com/wmarkow/arduino-sandbox/master/st-link-v2/doc/35.png" width="50%" >