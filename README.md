/**** Proximity Queries for medical robotic application ****/
	Input:  
		p[] : set of points in 3D space to be queried
        C[], M[], R[] : sequence of circular contours forming the segments
	Output: 
		d[] : shortest distance of every points to all segment boundaries distance is set to zero if point is inside the segment
================================================================

Brittle April 2012
	pq.c
	- Original contour form version with cpu and gpu definitions

Thomas June 2012
	pq_polar.c
	- Added polar form

Thomas Oct 2012 
	pq_all.c
	- Added three modes
	- Added pq_server and client
	- Original data files need to be modified

Thomas Jan 2013
	pq.cpp
	- Port to C++
	- CPU only
	- Polar form only
	- Range analysis by affine arithmetic using yalaa library
	- Need modified data file
	- MAX_NUM_POINTS 1409232

================================================================
Compile:
	make

Debug:
	make debug

Run test case:
	make run
================================================================
