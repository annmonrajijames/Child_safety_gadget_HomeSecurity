# Child_safety_gadget_HomeSecurity
Child safety gadget is a home security device which ensures the safety of the child when the child reaches home by providing acknowledgement to the parents who are not at home. There are three versions of this module, 
> child safety gadget 1.0 - The password mechanism module\
> child safety gadget 2.0 - The Camera module\
> child safety gadget 3.0 - The lock module

## Child safety gadget 1.0
Child safety gadget 1.0 is a device, to provide acknowledgement to parents through email to notify that child reached home after the child enters correct password on the keypad, and the led will blink green light and an email will be sent to parents mobile. If the password is wrong, wrong passcode entered email will be sent and red led will blink. The child can enter a pseudo-passcode which is a different password if the child feels threatened and this will send an SOS email to parents but the device will blink green light to fool the criminal to believe that the child entered the correct passcode. 
The components of project are ES8266 microcontroller, Keypad, RGB Led light, Jumper wires. IoT platform Blynk 2.0 is also used. 

## Child safety gadget 2.0
Child safety gadget 2.0, brings camera feature to the device where it will take a picture and sends the picture to Google drive when someone comes near the device. An IR sensor is used for this, as the child enters the password the IR sensor which is placed near the device will get activated and will send the picture to parents Google drive. 
The components used in this project are ESP32CAM, IR sensor, FTDI232 (only while uploading the code), Jumper wires and Breadboard.

## Child safety gadget 3.0
Door lock is added to the existing child safety gadget, which makes part of Home Security. 
Door will be opened if either correct password OR pseudo-password is entered, To lock the door reverse password of correct password can be entered. For wrong password, nothing will happen.

# Development steps for child safety 1.0


### How to Connect wires between Keypad & ESP8266
ROW0-->D0, ROW1-->D1, ROW2-->NOT USED, ROW3-->D2
COL0-->D3, COL1-->D4, COL4-->D5
THE KEYPAD IMAGE
![Keypad](Resources/To_Keypad.jpeg)
THE MICROCONTROLLER IMAGE [ESP8266-NodeMCU]
![ESP8266](Resources/To_ESP8266.jpeg)

### Selection of Board in Arduino IDE
Select the board and then upload the code, once code is written.
![Selected NodeMCU 1.0 in Arduino IDE under board tab](Resources/BoardSelect_IDE.png)

If you completed testing the code for keypad, then NEXT STEP is configuring email using Blynk IoT platform to send emails to parents email id.

### Setting up Blynk (Main things to consider)

Creating a template
![Alt text](Resources/Blynk_IoT.png)

Click on "Click to copy Code", which will copy Template ID, Template Name, and AuthToken, and later you have to paste it in the code file
![Alt text](Resources/CopyIDS_FIRMWARE_CONFIGURATION.png)

Go to "Events & Notification tab", and then click on "Add New Event", Since we are using IoT for sending emails
![Alt text](Resources/EventsandNotification.png)

Enter "Event Name" and then click "Save"
![Alt text](Resources/AddNewEvent.png)

The code snippet that you copied before can be pasted here (Circled Red)
![Alt text](Resources/Code_Blynk_Template.png)

Don't forget to add the automatically generated "Event code" in the code file, This will activate the specific IoT functionality to trigger. (Circled Red)
![Alt text](Resources/Code_BlynkLogEvent-1.png)

References
1. https://github.com/Tech-Trends-Shameer/Esp-8266-Projects/blob/main/Theft-Alert-Notification-Using-Blynk-IOT/theft-alert-notification-using-blynk-iot-and-esp8266.ino To know how the codng part for Blynk IoT works

# Development steps for child safety 2.0

References- 

1. https://www.electroniclinic.com/esp32-cam-send-images-to-google-drive-iot-security-camera/ 
This is the main reference where i got the source code for the camera module. There are two files of source codes, one is without IR sensor(periodically taking pictures) and the other is with IR sensor. (Take picture when IR sensor gets activated)
2. https://randomnerdtutorials.com/program-upload-code-esp32-cam/ If you have doubts regarding connection of ESP32CAM and FTDI232 and on trouble shooting, then refer this
3. https://youtu.be/9BOYOMEJXUg
Watch this YouTube video, which will give the entire procedure 

### Setting up Google App Script

Click on "Start Scripting"
![Alt text](Resources/image-4.png)

Click on "New Project"
![Alt text](Resources/image-5.png)

Copy the JavaScript code and paste it there, you will get the code from "Google_appscript.js" file inside "Photo_ESP32Cam" folder 
![Alt text](Resources/image-6.png)

Name your project by changing "Untitled Project" and then click on Deploy button and select "New deployment"
![Alt text](Resources/image-7.png)

Select Web app
![Alt text](Resources/image-8.png)

Select Anyone and then click Deploy
![Alt text](Resources/New_deployment.png)
Then click Authorize access, again select your Google account, then click Advanced, then click "Go to ESP32CAM (unsafe)".
A new window will come- "ESP32CAM wants to access your Google account" so click Allow
[WARNING!], do not use your personal Google account, because it may access your personal data so use a dedicated Google account for it.

Copy the URL of the web app and paste it in the address bar and search.

Copy a part of the URL of the web app and paste it for the String variable myScript
For example, here the value of myScript after pasting should be:-
myScript= "/macros/s/AKfycbxcnqrleZjKohDYYwADWckLugt1Mr_sh-IAEcWw7TScxDNLexU/exec"
![Alt text](Resources/WebURL.png)
And then upload the code, before uploading you should now how to make connect ESP32CAM to FTDI programmer so learn how to do from below heading "Connection of ESP32CAM and FTDI programmer"

### Connection of ESP32CAM and FTDI programmer
![Alt text](Resources/image.png)

While uploading the code, make sure GND and IO0 pins are connected in the ESP32-CAM microcontroller. After uploading the code, remove the connection between GND and IO0
![Alt text](Resources/image-1.png)
In Arduino IDE, Go to Tools > Board and select ESP32 Wrover Module then upload the code. (After uploading, don't forget to remove that wire)

When you start to see some dots on the debugging window, press the ESP32-CAM on-board RST button.
![Alt text](Resources/image-2.png)

![Alt text](Resources/image-3.png)


After the code is uploaded and pressing reset button, place an object near IR sensor. And it will send images to Google drive. (You may have to wait for some time, there may be some lag and make sure adequate internet speed is there)
The pictures can be viewvew in Google drive's ESP32-CAM folder

![Alt text](Resources/image-10.png)

>Troubleshooting
1. Sometimes, you need to think out of the box, you may think the error can be due to wrong code or setting up hardware improperly, I worked if for a while and finally replaced JUMPER WIRES, then it worked, even small things will have impact on your project. 
2. Use different cable for connecting between FTDI and USB port.
3. The camera in the ESP32-CAM may be loosely attached, so make sure that the camera is working, you may try with basic CameraWebServer code to check only for the camera.
4. Maybe you need to press RST button again, to check whether the ESP32-CAM works properly, in the one i brought, the ESP32-CAM blynks flash light after pressing RST button. (may not be true for all versions). I used ESP32-S version.

# Development steps for child safety 3.0

