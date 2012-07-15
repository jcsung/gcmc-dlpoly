gcmc-dlpoly
===========

Grand Canonical Movie Creator for DL_POLY

Creates a working DCD trajectory file for systems simulated in the Grand 
Canonical ensemble - i.e., with changing numbers of atoms.

Takes DL_POLY HISTORY files as input

Just make to compile, and then run

./moviemaker HIS1 [HIS2] [HIS3] ....

Output DCD is named traj.dcd

To view the movie, load the XYZ frame with the highest number of atoms
(probably the last or one of the last) frames.  Delete that frame, then 
load traj.dcd into that frame.

Requires the following:

-hisxyz.f from DL_POLY

-catdcd

File input has the following structure:

Number of frames in each HISTORY file (must be the same for all HISTORY files)

Executable name for compiled form of hisxyz.f (make sure it is in your path)

r_min

r_max

-----
r_min and r_max are large ints such that a dummy atom can be placed there and 
not show up in the frame of the movie.
