/**** pq_wrapper.hpp ****
 * Pre-process data, eliminate one plane
 * Post--process results
 */
#ifndef PQ_WRAPPER_H
#define PQ_WRAPPER_H

#include <cmath>
//#include <yalaa.hpp>
#include "pq_type.hpp"

class pq_wrapper
{
	private:
		double	a, b, c;
		double 	W_1[MAX_NUM_DEGREES], W_2[MAX_NUM_DEGREES];
		double 	C_1, C_2;
		double 	w_d_1, w_d_2;
		unsigned int bound;

	public:
		void pre_process(
				const unsigned int &no_C,
				const unsigned int &no_deg,
				unsigned int max_m[],
				double phi[][MAX_NUM_DEGREES],
				double3 s_C[], 
				double3 s_M[], 
				double3 s_W[][MAX_NUM_DEGREES]
				);
		void post_process(
				const unsigned int &mode,
				const unsigned int &no_link,
				const unsigned int &no_pt,
				const unsigned int s_L[],
				const unsigned int out_pt_idx[],
				const double min_dist[],
				double s_dev[],
				unsigned int s_link_pt_idx[],
				double s_pt_contour_dev[],
				unsigned int s_pt_contour_idx[]
				);
};

#endif
