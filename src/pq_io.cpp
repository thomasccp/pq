/**** pq_io.cpp ****
 * Process input and output of data
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "pq_type.hpp"
#include "pq_io.hpp"

int pq_io::data_in(
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
		){

	// Process CLI arguments
	if (no_params != 6) {
		std::cout << "usage: " << params[0] << "<mode> <point file> <contour file> <start seg_idx> <end seg_idx>" << std::endl;
		std::cout << "mode: point[0] link[1] contour[2]" << std::endl;
		return -1;
	}

	mode = atoi(params[1]);
	if (mode>2){
		std::cout << "Err: point-0 link-1 contour-2" << std::endl;
		return -1;
	}

	// Read point input file
	f = fopen(params[2], "r");
	if (f!=NULL) {
		fscanf(f, "%d", &(no_pt));
		for (unsigned int i=0; i<no_pt; i++)
			fscanf(f, "%lf %lf %lf", &(pt[i].x), &(pt[i].y), &(pt[i].z));
		fscanf(f, "%d", &(no_link));
		for (unsigned int i=0; i<no_link; i++)
			fscanf(f, "%d", &(L[i]));
		fclose(f);
	}else{
		std::cout << "Unable to open point file" << std::endl;
		return -1;
	}

	// Read polar contours file
	f = fopen(params[3], "r");
	if (f!=NULL) {
		fscanf(f, "%d %d", &(no_C), &(no_deg));
		for (unsigned int i=0; i<no_C; i++){
			fscanf(f, "%lf %lf %lf", &(C[i].x), &(C[i].y), &(C[i].z));
			fscanf(f, "%lf %lf %lf", &(M[i].x), &(M[i].y), &(M[i].z));
			fscanf(f, "%lf %lf %lf", &dummy1, &dummy2, &dummy3);
			for (unsigned int j=0; j<no_deg; j++){
				fscanf(f, "%lf %lf %lf %lf %lf", &(W[i][j].x), &(W[i][j].y), &(W[i][j].z), &dummy1, &dummy2);
			}
		}
		fclose(f);
	}else{
		std::cout << "Unable to open contour file" << std::endl;
		return -1;
	}

	// Read segment indices
	seg_idx[0] = atoi(params[4]);
	seg_idx[1] = atoi(params[5]);

	return 0;

}

int pq_io::data_out(
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
		){

	// Output of the deviation distances corresponding to every point
	if (mode==0){
		f = fopen("./run/polar_point_cpu_result.txt", "w");
		for (unsigned int i=0; i<no_pt; i++) {
			fprintf(f, "%.15lf %.15lf %.15lf %.15lf %d\n", min_dist[i], out_pt[i].x, out_pt[i].y, out_pt[i].z, out_pt_idx[i]);
		}
		fclose(f);

		// Output of the deviation distances corresponding to points grouped in every link
	}else if (mode==1){
		f = fopen("./run/polar_link_cpu_result.txt", "w");
		for (unsigned int i=0; i<no_link; i++) {
			fprintf(f, "%.15lf %.15lf %.15lf %.15lf %d\n", dev[i], out_pt[link_pt_idx[i]].x, out_pt[link_pt_idx[i]].y, out_pt[link_pt_idx[i]].z, out_pt_idx[link_pt_idx[i]]);
		}
		fclose(f);
	}else{
		// Output of the deviation distances corresponding to every contour
		f = fopen("./run/polar_contour_cpu_result.txt", "w");
		for (unsigned int i=seg_idx[0]; i<seg_idx[1]; i++) {
			fprintf(f, "%.15lf %d\n", pt_contour_dev[i], pt_contour_idx[i]);
		}
		fclose(f);
	}

	return 0;

}
