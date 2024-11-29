# Klein Explorer
Repository for KleinExplorer, a Klein Fractal explorer written in C++ with [OpenFrameworks](https://openframeworks.cc/) and [ofxDatGUI](https://braitsch.github.io/ofxDatGui/index.html).

# Compilation
Assuming you have OpenFrameworks and ofxDatGUI installed:

Go in your openFrameworks directory:
`cd openFrameworks/apps/`

Clone the repo:

`git clone git@github.com:epsln/KleinExplorer.git`

Compile:

`make -j4`

You are now ready to run KleinExplorer.

# Use
Run the program using:
`make runRelease`

## Recipes
The 4 main recipes are implemented:
	- Grandma Recipe
	- Grandma Special Recipe
	- Maskit Recipe
	- Jorgensen Recipe

You can play around with the parameters, and create some sick looking Klein Fractals. 

A lower epsilon will create more detailled images, but will requires a higher search depth. By default, the Real Time Mode is deactivated, as a high search depth with Real Time Mode will make the app unresponsive. 

## Special Fraction and Special Words
The last recipe requires you to input the Special Fraction. This fraction is used to determine the special word, which when computed will give out a Parabolic Mobius transform. Special Fraction allows you to finely follow the Maskit boundary, and always create good looking gaskets. It does so by hopping along Farey Neighbors until it reaches the input fraction, each time solving for the root of the associated polynom. The root of the previous Farey Neighbor is used as a good starting guess. The root of this polynom is then used as an input for the Grandma Recipe. 
