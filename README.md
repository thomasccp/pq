/**** Proximity Queries for medical robotic application ****/
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
	- Need modified data file
	- MAX_NUM_POINTS 1409232

Thomas Feb 2013
	- Master: v0.2 that is able to run smoothly on CPU
	- Branch cpu_run: for running real cases
	- Branch yalaa: for range analysis using yalaa library

================================================================
Compile:
	make

Debug:
	make debug

Run test case:
	make run
================================================================
