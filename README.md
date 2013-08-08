# Proximity Queries for medical robotic application 
Proximity Query (PQ) is a process to calculate the relative placement of objects. 
It is a critical task for many applications such as robot motion planning, particularly those involving human-robot collaborative control. 
This program computes a PQ formulation which can support non-convex objects represented by meshes or cloud points. 

## How to use

Compile:
'make'

Debug:
'make debug'

Run test case:
'make run'

## Change log

Thomas Feb 2013
	- Master: v0.2 that is able to run smoothly on CPU
	- Branch cpu_run: for running real cases
	- Branch yalaa: for range analysis using yalaa library

Thomas Jan 2013
	pq.cpp
	- Port to C++
	- CPU only
	- Polar form only
	- Need modified data file
	- MAX_NUM_POINTS 1409232

Thomas Oct 2012 
	pq_all.c
	- Added three modes
	- Added pq_server and client
	- Original data files need to be modified

Thomas June 2012
	pq_polar.c
	- Added polar form

Brittle April 2012
	pq.c
	- Original contour form version with cpu and gpu definitions

================================================================
