/**** pq_core_openmp.hpp ****
 * Core of proximity calculation
 * Optimised for OpenMP
 */

#ifndef PQ_CORE_H
#define PQ_CORE_H

#include <cmath>
#include "pq_type.hpp"

class pq_core
{
	private:
		double3 		d1, d2;
		double3 		n;
		double3 		rhol1, rhol2;
		double			rhol_1, rhol_2;
		double			theta;
		double			u;
		double3 		v32, w;
		unsigned int	idx_1, idx_2;
		double3 		wa, wb;
		double			pa, pb, pc, pd;
		double 			t1, t2, t;
		double3			v2, v3;
		double3 vd;
		double3 vb1, vb2, vb3, vb4;
		double 	lamda1, lamda2, lamda3, lamda4;
		double			delta[MAX_NUM_SEGMENTS];
		double			px[MAX_NUM_SEGMENTS];
		double			py[MAX_NUM_SEGMENTS];
		double			pz[MAX_NUM_SEGMENTS];

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
