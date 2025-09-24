
<div class="copyspace">
<h3>Adafruit TPS61169 LED Driver - Name Sign</h3>

<div class="featuredProject">
<h3>Overview</h3>

<p>
<helper:RandomGreeting /> &nbsp;This project uses the Adafruit
TPS61169 LED driver to light up a name sign for family member's
graduation gift.
</p>
</div>

<div class="featuredProject">
<h3>Order of Operations/Objectives</h3>

<p>
&nbsp;
</p>

<ul>
<li>
Prototype
<ul>
<li>
Get all lights lit
</li>

<li>
Take photos
</li>
</ul>
</li>

<li>
Design enclosure

</li>

<li>
<a href="" >
</a>
[] Ask if he wants the lightning bolt


</li>

<li>
<a href="" >
</a>
[] Assemble the electronics and enclosure -

<p>
Prototype the enclosure around the faceplate and electronics
</p>
</li>

<li>
<a href="" >
</a>
Figure out layout (LED count)


<ul>
<li>
<a href="" >
</a>
Make images

</li>
<li>
<a href="" >
</a>
Ask Family Mmembver which they like
</li>
<li>
<a href="" >
</a>
</li>
</ul>
</li>

<li>
<a href="" >
</a>

</li>

</ul>
</div>


<div class="featuredProject">
<h3>Hardware</h3>

<p>
&nbsp;
</p>

<ul>
<li>
<a href="https://www.adafruit.com/product/6354" >
LED Driver</a>
</li>

<li>
<a href="https://www.adafruit.com/product/6194" >
Letters</a>
</li>

<li>
<a href="https://www.adafruit.com/product/6096" >
Lightning Bolt</a>
</li>

<li>
<a href="https://www.adafruit.com/product/1152" >
Connector</a> - The product page mentions that these
connector fit the letters, but I only used them to prototype.
The main reasons are that not all letters fit the connector
(some don't have separate connectors ('I') and this connector is not
connected at the JST ends.

<p>
I ended up soldering silicone wires directly to the letter
pads, as seen on the 'ADAFRUIT' photo main product
page.
</p>
</li>

<li>
<a href="https://www.adafruit.com/product/2010" >
Adafruit Pro Trinket - 3V 12MHz</a>
</li>

<li>
<a href="https://www.adafruit.com/product/2124" >
Pro Trinket and Lipo Backpack</a>
</li>





<li>
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
<h3>Fritzing Diagram</h3>

<p>
&nbsp;Here is a wiring diagram done in Fritzing
</p>

<img src="tps61169-with-pro-trinket.png"
alt="Fritzing diagram of the TPS61169 and a Pro Trinket"
width="50%"
height="50%">

<ul>
<li>
<a href="" >
</a>
</li>
</ul>

<p>
Here is a decent-to-nice explanation that Google provided on how
to make the connection between the electronic components used in
this project.
</p>
</div>

<div class="featuredProject">
<h3>Faceplate</h3>

<p>
&nbsp;The faceplate for this project has cutouts for the letters
in the name 'Diego' and the lightning bolt emoji.

</p>

<p>
The faceplate idea for this project was inspired by John Park's
show on the TPS61169.  Click the image for the video.
</p>

<a href="https://youtu.be/g2GlgnLWvW8?t=774" >
<img src="john-park-faceplate.png">
</a>


<p>
Using OpenSCAD's
text features, I was hoping find the font of the LED letters.  But
alas, I could not find the font.
</p>

<p>
I did try this prompt in Google AI:

<br/>
<b>
What font is used in iPixel LED Light Co  LED Rigid Bar M0010 ?
</b>
<br/>
But the response was something like: 'if iPixel didn't realease the font,
then you ain't getting no font name, sucka'.



So, no font metrics for me.
</p>

<p>
I ended up using the letter/lightning bolt PDF datasheets directly in
GIMP to get the SVG path of each letter.  See the link in the
'Resources' section for the datasheets.
</p>

<p>
Then with the SVG path, I used an Inscape plugin to get a OpenSCAD
code to model the letters in 3D.  The faceplate uses the difference()
module to cutout the individual LED letters. See the 'Resources'
section for a link to the OpenSCAD code.
</p>

<ul>
<li>
<a href="" >
</a>
</li>
</ul>
</div>

<div class="featuredProject">
<h3>Control Panel Side Plate</h3>

<p>
&nbsp;The 'control panel' has cutouts for the following items:
</p>

<ul>
<li>
Charging Port - This is where the Pro Trinket's USB port is
accessed. See the resources section for the model used for this cutout.
</li>

<li>
Switch

<ul>
<li>
9mm horizontal
</li>

<li>
13mm vertical
</li>
</ul>



<br/>
!!!!!!!!ADD AND IMAGE!!!!!!!!
</li>

<li>
Potentiometer - 9.5mm x 9.5mm

<br/>
!!!!!!!!ADD AND IMAGE!!!!!!!!
</li>

</ul>

<ul>
<li>
<a href="" >
</a>
</li>
</ul>
</div>

<div class="featuredProject">
<h3>3rd Party Mounting Hardware</h3>

<p>
&nbsp;This project used the following mounting hardware to attach
the driver and microcontroller PCBs to the platform.
</p>

<ul>
<li>
<a href="https://www.thingiverse.com/thing:729459" >
jimlee - T-Bracket</a> this one was increased in the Z-axis
to a height of 8mm. I modified this one to be flat, see
the Github link for the STL named 'flat-trinket-mount.stl'.

<p>
I also had to chop off part of the USB port area, so that
it would fit into the 'control panel' cutout.  Thank you,
flush cutters!
</p>

<br/>
!!!!!!!!ADD AND IMAGE!!!!!!!!
</li>

<li>
<a href="https://www.adafruit.com/product/6402" >
enclosure for the driver</a>
- This enclosure is available for purchase but for this
project I used the
<a href="https://cdn-shop.adafruit.com/product-files/6402/TPS61169+Enclosure+Files.zip" >
3D printable models</a>
provided by Adafruit on the product page. Only the
bottom part of the model is used in this project.

<br/>
!!!!!!!!ADD AND IMAGE!!!!!!!!
</li>

<li>
<a href="" >
</a>
</li>
<li>
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
<h3>Retrospective</h3>

<p>
&nbsp;I would have gone with an all-in-one solution for the
battery charging (no LiPo backpack), like the following
non-WiFi/radio Feathers.
</p>

<ul>
<li>
<a href="https://www.adafruit.com/product/4884" >
Adafruit Feather RP2040</a>
</li>

<li>
<a href="https://www.adafruit.com/product/6000" >
Adafruit Feather RP2350 with HSTX Port</a>
</li>
</ul>

<p>
But I did not have one handy.
</p>
</div>

<div class="featuredProject">
<h3>Resources</h3>

<p>
&nbsp;
</p>

<ul>
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
<a href="https://github.com/adafruit/Adafruit_CAD_Parts/tree/main/2010%20ProTrinket%203V" >
3D model for the Adafruit Pro Trinket 3V</a>
- This was used to make the 'charging port' cutout on the
control panel plate.
</li>

<li>
<a href="https://cdn-shop.adafruit.com/product-files/6210/M0010-A_Z%2825%29.pdf" >
LED Letters Datasheet</a>
</li>

<li>
<a href="https://cdn-shop.adafruit.com/product-files/6096/M0010331LZ-C21532-001_-_A.pdf" >
Lightning Bolt Datasheet</a>
</li>

<li>
<a href="" >
</a>
</li>

<li>
<a href="" >
</a>
</li>
</ul>
</div>

<br class="clearingBreak">
</div>
