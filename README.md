# ADNS3080
This is an Arduino library for ADNS3080 mouse sensor. It provides a simple interface to retrieve motion and frame data from the sensor. See the following schematic on how to connect a comercial module to an arduino uno. It is the same for other boards except the SPI spins change. 

<img src = "ADNS3080_arduino_wiring.jpg" width = "40%" height = "40%"> 

#### IMPORTANT
The camera must be focused for the sensor to work properly. See the following repo to focus the lens: [ADNS3080_frame_capture](https://github.com/RCmags/ADNS3080_frame_capture). It contains an arduino sketch and a python script that work in conjunction with this library.  

# References:
- Credit goes to [Lauszus](https://github.com/Lauszus/ADNS3080) and [Neumi](https://github.com/Neumi/OpticalFlowA3080ArduinoProcessing) for getting the sensor to work with arduino. This library is essentially a repackaging of their code into a neater form.  

- For more information on the sensor, see the [datasheet](https://people.ece.cornell.edu/land/courses/ece4760/FinalProjects/s2009/ncr6_wjw27/ncr6_wjw27/docs/adns_3080.pdf)  

- The schematic can be found [here](http://forum.arduino.ir/8/21/391.html), along with another another library for the ADNS3080.  
