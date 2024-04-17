

<div class="copyspace">
<h3>Java Controlled LED Matrix via an MAX7219 SPI Controller</h3>

<div class="featuredProject">
<h3>Overview</h3>

<p>
<helper:RandomGreeting /> &nbsp;
</p>
</div>

<div class="featuredProject">
<h3>Hardware</h3>

<ul>
<li>
Raspberry Pi 2 Model B V1.1 -

<a href="https://pi4j.com/1.2/pins/model-2b-rev1.html" >
Pin out</a>
</li>

<li>
<a href="https://www.amazon.com/gp/product/B07VM6HXN5" >
Max7219 SPI 8x8 LED Matrix Driver</a>

</li>
</ul>
</div>

<div class="featuredProject">
<h3>Software Prerequisites</h3>

<ul>
<li>
Pi4J version 1.2
<ul>
<li>
$ curl -sSL https://pi4j.com/install | sudo bash
</li>

<li>
<pre>
Pi4J version 3.2 was tried but SPI did not seem to work with a Model B

and gave the following error with version 3.2

UnsatisfiedLinkError = libpi4j-pigpio.so
</pre>
</li>
</ul>
</li>

<li>
Update WiringPi

<pre>
$ wget https://project-downloads.drogon.net/wiringpi-latest.deb
$ sudo dpkg -i wiringpi-latest.deb
$ gpio -v
gpio version: 2.52
gpio version: 2.52
Copyright (c) 2012-2018 Gordon Henderson
This is free software with ABSOLUTELY NO WARRANTY.
For details type: gpio -warranty


Raspberry Pi Details:
Type: Pi 2, Revision: 01, Memory: 1024MB, Maker: Embest
* Device tree is enabled.
*--> Raspberry Pi 2 Model B Rev 1.1
* This Raspberry Pi supports user-level GPIO access.

</pre>
</li>

<li>
Java 11

<pre>
sudo apt update
sudo apt upgrade
sudo apt install openjdk-11-jdk
java -version
javac -version
</pre>
</li>

<li>
Run the Application

<pre>
pi@raspberrypi:~ $ /opt/pi4j/bin/pi4j -jar pi4j-spi-1.0-SNAPSHOT-jar-with-dependencies.jar
</pre>
</li>
</ul>
</div>

<div class="featuredProject">
<h3>Wiring and Connections</h3>

<p>
These are the connection details:
</p>

<pre>
MAX7219 LED
matrix driver -> Raspberry Pi 2 Model B v1.1


DIN -> blue   -> MOSI -> header 19

CS -> purple -> CE0  -> header 24

CLK -> white  -> SCLK -> header 23

VCC -> 5V ->  header 2

GND -> ground -> header 9

</pre>

Wiring Diagram
<br/>
<img src="documentation/wiring-diagram.png"
alt="Wiring Diagram"
width="50%"
height="50%"/>
![Wiring Diagram](documentation/wiring-diagram.png "Wiring Diagram")

<br/>
<br/>


<img src="j8header-2b.png" alt="Labeled Raspberry Pi Header"/>
![Labeled Raspberry Pi Header](j8header-2b.png "Labeled Raspberry Pi Header")

<br/>

Image Credit:

<a href="https://pi4j.com/">
Pi4J</a>

<p>
See the
<a href="https://pi4j.com/1.2/pins/model-2b-rev1.html">
Pi4J site's</a
for more pin details.
</p>
</div>

<div class="featuredProject">
<h3>Debugging with the Netbeans IDE</h3>

<p>
<a href="https://stackoverflow.com/a/41633184/803890">This Stackoverflow answer</a>
helped a bunch to configure debug mode in Netbeans, for this project.
</p>

<p>
Be sure to use the instructions values for Spring Boot version 2.x (again, specifically for this project/Pi B)
&nbsp;

<br/><br/>

Project -> Settings -> Actions -> Debug project

<pre>
Execute Goals:
spring-boot:run


Set Properties:
spring-boot.run.jvmArguments=-Xdebug -Xrunjdwp:transport=dt_socket,server=n,address=
jpda.listen=true
</pre>
</p>
</div>

<div class="featuredProject">
<h3>Run Integrations Tests</h3>

<pre>
$ mvn integration-test
</pre>
</div>

<div class="featuredProject">
<h3>other</h3>

<p>

</p>

<ul>
<li>
<a href="" >
</a>
</li>
</ul>
</div>

<div class="featuredProject">
<h3>Going Further</h3>

<ul>
<li>
Add an I2C controlled

<a href="https://www.adafruit.com/product/2651">
Adafruit BMP280 Temperature Sensor
</a>

(just bought 3 of them)

<ul>
<li>
<a href="https://pi4j.com/examples/jbang/bme280_temperature_humidity_pressure/" >
Pi4J I2C Support</a>
</li>
</ul>

<a href="" >
</a>
</li>

<li>
<a href="" >
</a>
</li>
</ul>
</div>

<div class="featuredProject">
<h3>Resources</h3>

<p>
&nbsp;
</p>

<ul>
<li>
<a href="https://www.hackerspacetech.com/raspberry-pi-and-spi-8x8-led-matrix-example-with-java-and-pi4j/" >
SPI 8x8 LED Matrix Pi4J Example</a>
</li>

<li>
<a href="https://github.com/FDelporte/JavaOnRaspberryPi/tree/master/Chapter_09_Pi4J/java-pi4j-spi" >
Raspberry Pi and Pi4J SPI</a>
</li>

<li>
<a href="" >
</a>
</li>
</ul>
</div>
