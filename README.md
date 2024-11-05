# Klein Explorer
Repository for KleinExplorer, a Klein Fractal explorer written in C++ with OpenFrameworks.

# Compilation
Assuming you have OpenFrameworks installed:

Go in you openFrameworks directory:
`cd openFrameworks/apps/`

Clone the repo:

`git clone git@github.com:epsln/KleinExplorer.git`

Compile:

`make -j4`

You are now ready to run KleinExplorer.

# Use
Run the program using:
`make runRelease`

You can play with a few parameters of the Grandma Recipe. The default traces (ta = 2, tb = 2) will generate a nice Apolonian Gasket.

A lower epsilon will create more detailled images, but will requires a higher search depth.
