# Constant-current-load
Constant current load circuit with 0-2A adjustment

## Finding a design and adjusting it
For some time I was looking to make a constant current loads to test some pc power supplies I converted to bench power supplies. I found some designs but had various results and nothing seemed to be stable and reliable enough. The main problem was usually the initial current surge was too high and power supplies considered it a short circuit and switched off. Another obstacle was I didn't have an oscilloscope, but I recently got one [JYETech DSO150 Digital Oscilloscope](https://www.banggood.com/Original-JYETech-Assembled-DSO-SHELL-DSO150-Digital-Oscilloscope-Module-9V-p-1211151.html?cur_warehouse=CN&rmmds=search). Also I came across this thread and this reply on [eevblog.com](https://www.eevblog.com/forum/beginners/a-load-off-my-mnd/msg2151265/#msg2151265), and it seemed promising:
<br> <img src="/images/eevblog_schematic.png" width="60%"> 
<br> So i changed some things on this schematic to adjust to components I already had and got this:
<br> <img src="/images/my_schematic.png" width="60%"> 

## Prototype and testing
After I got the circuit planed out I started to assemble it all on a breadboard <img src="/images/breadboard.jpg" width="60%">
<br> Not much to say here but to show some pictures:
<br> <img src="/images/breadboard_pot.jpg" width="30%"><img src="/images/breadboard_opamp.jpg" width="30%">
<br> Next step was testing, and I tested how much power does the circuit consume, and it was about 20mA at 12V which is 0.24W both while idle and while sinking a 1A load on 5V.
<br> <img src="/images/meter_idle.jpg" width="40%">
<br> Another thing I tested is will the current be same at different voltages, and it was 0.25A both on 5V and on 12V without changing anything else.
<br> <img src="/images/load_5V_0.25A.jpg" width="30%"> <img src="/images/load_12V_0.25A.jpg" width="30%">
<br> Final thing, which I was most worried about was initial current surge. The 1nF capacitor on output of second opamp is to prevent that spike, and after testing with 1nF, 10nf and 100nF caps I found the 1nF worked the best and kept it.
<br> <img src="/images/osc_cap_102.jpg" width="25%"> <img src="/images/osc_cap_103.jpg" width="25%"> <img src="/images/osc_cap_104.jpg" width="25%">
<br> Also I just recorded spikes for different currents, here you can see 0.5A, 1A, 1.5A and 2A:
<br> <img src="/images/osc_0.5A.jpg" width="20%"> <img src="/images/osc_1A.jpg" width="20%"> <img src="/images/osc_1.5A.jpg" width="20%"> <img src="/images/osc_2A.jpg" width="20%">

## Additional components
TODO: I'm still workign on this, but I plan to use a heatsink from an old graphics card and an 80mm fan for cooling, and also adding an Arduino with an OLED display to show current, voltage, power, set current..., and add a BNC connector for external current setting, useful in future for plotting stuff or something. 

## Building it
TODO: Pictures of enclosure and layout, wiring, cooling, front and back panel design...

## Final results
TODO: Final pictures, another testing, overheating testing

