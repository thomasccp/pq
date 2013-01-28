/**** Type definition ****/

#ifndef TYPE_H
#define TYPE_H

#define   	MAX_NUM_POINTS 1500000 // TPB * TB >= MAX_NUM_POINTS
#define 	MAX_NUM_SEGMENTS 32
#define    	MAX_NUM_LINKS 5
#define  	MAX_NUM_DEGREES 28

//typedef yalaa::details::double_iv_t iv_t;
//typedef yalaa::traits::interval_traits<iv_t> iv_traits;
typedef struct { double x, y, z; } double3;

#endif
