/**** pq_io.hpp ****
 * Process input and output of data
 */

#ifndef IO_H
#define IO_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "pq_type.hpp"

class pq_io
{
	private:
		FILE	*f;
		double	dummy1, dummy2, dummy3;

	public:
		int data_in(
				const int &no_params,
				const char **params,
				unsigned int &mode,
				unsigned int &no_pt,
				double3 pt[],
				unsigned int &no_link,
				unsigned int L[],
				unsigned int &no_C,
				unsigned int &no_deg,
				double3 C[],
				double3 M[],
				double3 W[][MAX_NUM_DEGREES],
				unsigned int seg_idx[]
				);

		int data_out(
				const unsigned int &mode,
				const unsigned int &no_link,
				const unsigned int &no_pt,
				const unsigned int seg_idx[],
				const double min_dist[],
				const double3 out_pt[],
				const unsigned int out_pt_idx[],
				const unsigned int link_pt_idx[],
				const double dev[],
				const double pt_contour_dev[],
				const unsigned int pt_contour_idx[]
				);

};

#endif
