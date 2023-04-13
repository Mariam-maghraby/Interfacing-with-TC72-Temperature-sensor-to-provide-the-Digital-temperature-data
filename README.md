# Interfacing-with-TC72-Temperature-sensor-to-provide-the-Digital-temperature-data
Implementation of a device that interfaces to a TC72 Temperature sensor to provide the Digital temperature data with Polling client as Cooling Controller.

Cooling controller implements a PID controller to generate a PWM signal based on the
deviation between the read temperature from the sensor and the set temperature point.

The Cooling controller works based on the following parameters:
- Temperature sampling period: 500ms.
- PWM duty cycle range: 0 to 0.73
- Set temperature is 30.
- Values of the PID controller arguments are Kp = 0.1, Ki = 0.01 and Kd = 0

![image](https://user-images.githubusercontent.com/61349498/231752257-d46ac114-d37f-4176-9bef-c3369ca351fd.png)




https://user-images.githubusercontent.com/61349498/231751922-f70aeda9-912c-4a1c-86ae-edf76ba7772b.mp4

