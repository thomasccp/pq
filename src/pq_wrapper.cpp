/**** pq_wrapper.cpp ****
 * Pre-process data, eliminate one plane
 * Post--process results
 */

#include <cmath>
//#include <yalaa.hpp>
#include "pq_type.hpp"
#include "pq_wrapper.hpp"

// Pre-processing: w_1[j][i], w_2[j][i], max_m[j], phi[j][i], C_1[j], C_2[j]
void pq_wrapper::pre_process(
		const unsigned int &no_C,
		const unsigned int &no_deg,
		unsigned int max_m[],
		double phi[][MAX_NUM_DEGREES],
		double3 s_C[], 
		double3 s_M[], 
		double3 s_W[][MAX_NUM_DEGREES]
		){

	for (unsigned int j=0; j<no_C; j++) {

		// Eliminate one plane, keep two planes
		a = fabs(s_M[j].x);
		b = fabs(s_M[j].y);
		c = fabs(s_M[j].z);
		if (a >= b && a >= c){
			for (unsigned int i=0; i<no_deg; i++){
				W_1[i] = s_W[j][i].y;
				W_2[i] = s_W[j][i].z;
			}
			C_1 = s_C[j].y;
			C_2 = s_C[j].z;
			max_m[j] = 1;
		}
		else if (b > a && b >= c){
			for (unsigned int i=0; i<no_deg; i++){
				W_1[i] = s_W[j][i].x;
				W_2[i] = s_W[j][i].z;
			}
			C_1 = s_C[j].x;
			C_2 = s_C[j].z;
			max_m[j] = 2;
		}
		else{
			for (unsigned int i=0; i<no_deg; i++){
				W_1[i] = s_W[j][i].x;
				W_2[i] = s_W[j][i].y;
			}
			C_1 = s_C[j].x;
			C_2 = s_C[j].y;
			max_m[j] = 3;
		}
		for (unsigned int i=0; i<no_deg; i++){
			// w_d = w - P
			w_d_1 = W_1[i] - C_1;
			w_d_2 = W_2[i] - C_2;
			// phi = atan2(w_d_2, w_d_1)
			phi[j][i] = atan2(w_d_2, w_d_1);
		}
	}

}

// Post-processing
void pq_wrapper::post_process(
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
		){

	if (mode==1){
		// For each segment, find maximum deviation among all points
		for (unsigned int l_idx=0; l_idx<no_link; l_idx++){
			bound = (l_idx == no_link-1) ? no_pt : s_L[l_idx+1];
			s_dev[l_idx] = 0;
			for (unsigned int i=s_L[l_idx]; i<bound; i++){
				if (s_dev[l_idx] < min_dist[i]){
					s_dev[l_idx] = min_dist[i];
					s_link_pt_idx[l_idx] = i;
				}
			}
		}
	}else if (mode==2){
		// Give contour output
		for (unsigned int i=0; i<no_pt; i++){
			if ( (s_pt_contour_dev[out_pt_idx[i]]==0) || (min_dist[i]<s_pt_contour_dev[out_pt_idx[i]]) ) {
				s_pt_contour_dev[out_pt_idx[i]] = min_dist[i];
				s_pt_contour_idx[out_pt_idx[i]] = i;
			}
		}

	}
}
