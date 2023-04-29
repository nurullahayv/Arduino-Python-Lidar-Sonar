# Arduino-Python-Lidar-Sonar
Arduino(mega) Lidar &amp; Sonar Project with Python(/w matplotlib) | not real time rendering

1- You have to upload .ino code to Arduino.

2- Then use SerialReadSave.py code for collect data from arduino and save to a .csv file. (i am not remember well but probably you need an empty .csv file which is named in the SerialReadSave.py file(names have to be matched). in the code it is "data.csv")

3- Lastly use "processplot.py" file for render data in the .csv file.

!!! need synchronization for servos, need a few(lots of work) upgrade for clean work.
!!! you can change ploting settings for better render
![basic](https://user-images.githubusercontent.com/40025745/235295954-cc5a4215-ac56-45d0-926f-aa1f6fb19c9a.png)
![image](https://user-images.githubusercontent.com/40025745/235296168-4eb66801-52de-45b0-9762-97fec3c5910d.png)


Reference Projects;

https://www.youtube.com/watch?v=fIlklRIuXoY - https://github.com/curiores/ArduinoTutorials 

https://projecthub.arduino.cc/TravisLedo/80136939-97af-4c05-9a1d-ddfd40d00f01


