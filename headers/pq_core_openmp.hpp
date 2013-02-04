/**** pq_core_openmp.hpp ****
 * Core of proximity calculation
 * Optimised for OpenMP
 */

#ifndef PQ_CORE_H
#define PQ_CORE_H

#include <cmath>
#include <iostream>
#include "pq_type.hpp"

class pq_core
{
	private:

	public:
		void pt_dist(
				const unsigned int &no_C,
				const unsigned int &no_deg,
				const unsigned int seg_idx[],
				const unsigned int &pt_idx, 
				const double3 &pt, 
				const unsigned int max_m[],
				const double phi[][MAX_NUM_DEGREES],
				double3 s_C[], 
				double3 s_M[],
				double3 s_W[][MAX_NUM_DEGREES],
				double s_min_dist[],
				double3 s_out_pt[],
				unsigned int s_out_pt_idx[]
				);
};

#endif
