# ADNS3080
This is an Arduino library for ADNS3080 mouse sensor. It provides a simple interface to retrieve motion and frame data from the sensor. It is generally sold as a module with a lens attached. This code was written for such a module. The following schematic shows how to connect the module to an arduino uno. It's the same for other boards except the SPI spins change. 

<img src = "extras/ADNS3080_arduino_wiring.jpg" width = "40%" height = "40%"> 

To focus the camera see the following repo: [ADNS3080_frame_capture](https://github.com/RCmags/ADNS3080_frame_capture). It contains an arduino sketch and a python script that work in conjunction with this library.  

### References:
Credit goes to Lauszus and Neumi for on their code to get the sensor to work with arduino. This library is essentially a repackaging of their code into a neater form.  
https://github.com/Lauszus/ADNS3080  
https://github.com/Neumi/OpticalFlowA3080ArduinoProcessing

For more information on this sensor see the datasheet:  
https://people.ece.cornell.edu/land/courses/ece4760/FinalProjects/s2009/ncr6_wjw27/ncr6_wjw27/docs/adns_3080.pdf

The schematic was found here: (the page also contains another library)  
http://forum.arduino.ir/8/21/391.html
