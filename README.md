# arduino_projects
standalone projects with arduino

## get_humidity_temperature_soil

Get the soil Humidity and temperature using DHT11 on surface and deep sensor and print on LCD with I2C.

This project could be done as self power (or using a batery).


## scarecrow

This project is a scarecrow.

If something will interrupt the doppler sensor the processor will wake and start a motor.

## utils

This holds utils to read components.

### ledDigitalAngalogSensor

This will read different components with the following commands:

- o# turn on

- f# turn off

- d# read digital data

- axxx# read xxx time analogic sensor with an average of 100 reads and delay of 1000

- i# disable isr

- Ix# enable isr 0=RISING, 1=FALLING

Tested components: Hall sensor, pthotorezistor, photodiode, phototransistor, termistor 10k.

### readAnalogicComponents

This is a stripdown version of ledDigitalAngalogSensor but only for analogic components.

### rfid

Those are some examples to read  mifare ultraligh using RFID-RC522.

## wheater_with_DHC11_on_lcd

Wheather (Humidity and temperature using DHT11) and print the LCD without I2C.
 
