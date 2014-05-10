Simple port of  [Sparkfun TMP006][1] Sensor for Spark Core.
------------------------------------------------
----------
This is a simple port of Sparkfun TMP006 library for Spark Core.

###Connection###
 1. TMP006 Vcc to 3.3V
 2. TMP006 GND to GND 
 3. TMP006 SCL to D1 (with pullup resistor)
 4. TMP006 SDA to D0 (with pullup resistor)

###Sample Application###
The sample application is based on the [Sparkfun TMP006 Hookup Guide][2]. The application reads the Object Temperature and Sensor Temperature form the sensor and publish an event with name ***tmp006info***.

###Web Page###
I took [@bko][3]'s HTML page and modified it to include the sensor values.

###How to run the application###
Load the sample application into the Spark Core. Open the Web Page in an editor and replace the tokens *deviceid* and *access token* with actual values. Open the web page in a browser and press ***Connect*** Button.


  [1]: https://www.sparkfun.com/products/11859
  [2]: https://learn.sparkfun.com/tutorials/tmp006-hookup-guide
  [3]: https://community.spark.io/t/tutorial-getting-started-with-spark-publish/3422