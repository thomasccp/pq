/**** pq_core.cpp ****
 * Core of proximity calculation
 */

#include <cmath>
#include <iostream>
#include "pq_type.hpp"
#include "pq_core_openmp.hpp"

/**** pt_dist ****
 * For each point, find the penetration, i.e. distance between the point and the closest link
 */
void pq_core::pt_dist(
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
		){

	double			delta[MAX_NUM_SEGMENTS];
	double			px[MAX_NUM_SEGMENTS];
	double			py[MAX_NUM_SEGMENTS];
	double			pz[MAX_NUM_SEGMENTS];
	double3 		d1, d2;
	double3 		n;
	double3 		rhol1, rhol2;
	double			rhol_a, rhol_b;
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

	d2.x = s_C[seg_idx[0]].x - pt.x;
	d2.y = s_C[seg_idx[0]].y - pt.y;
	d2.z = s_C[seg_idx[0]].z - pt.z;
	vb4.x = s_C[seg_idx[0]].x - pt.x;
	vb4.y = s_C[seg_idx[0]].y - pt.y;
	vb4.z = s_C[seg_idx[0]].z - pt.z;

	for (unsigned int j=seg_idx[0]; j<=seg_idx[1]; j++){

		// Step 1: n = (C[j]-p[i]) * (c[j+1]-p[i])
		d1 = d2;
		d2.x = s_C[j+1].x - pt.x;
		d2.y = s_C[j+1].y - pt.y;
		d2.z = s_C[j+1].z - pt.z;
		n.x = d1.y*d2.z - d1.z*d2.y;
		n.y = d1.z*d2.x - d1.x*d2.z;
		n.z = d1.x*d2.y - d1.y*d2.x;

		// Step 2: rhol = n[j] * M[j]
		rhol1.x = n.y*s_M[j].z - n.z*s_M[j].y;
		rhol1.y = n.z*s_M[j].x - n.x*s_M[j].z;
		rhol1.z = n.x*s_M[j].y - n.y*s_M[j].x;
		rhol2.x = n.y*s_M[j+1].z - n.z*s_M[j+1].y;
		rhol2.y = n.z*s_M[j+1].x - n.x*s_M[j+1].z;
		rhol2.z = n.x*s_M[j+1].y - n.y*s_M[j+1].x;

		// Step 3: v2 = C[j]+t[j].normal_roh1; v3 = C[j+1]+t[j+1].normal_roh2
		// Find theta
		if (max_m[j] == 1){
			rhol_a = rhol1.y;
			rhol_b = rhol1.z;
		}
		else if (max_m[j] == 2){
			rhol_a = rhol1.x;
			rhol_b = rhol1.z;
		}
		else{
			rhol_a = rhol1.x;
			rhol_b = rhol1.y;
		}
		theta = atan2(rhol_b, rhol_a);

		// Linear search
		idx_1 = 0;
		idx_2 = 0;
		for (unsigned int i=0; i<no_deg; i++){
			unsigned int tmp = i+1;
			if (tmp==no_deg) tmp = 0;
			if (((phi[j][i]<=theta) && (phi[j][tmp]>=theta)) || ((phi[j][i]>=0) && (phi[j][tmp]<=0) && ((theta>=phi[j][i]) || (theta<=phi[j][tmp])))){
				idx_1 = i;
				idx_2 = tmp;
			}
		}
		// Calculate t[j]
		wa.x = s_C[j].x - s_W[j][idx_1].x;
		wa.y = s_C[j].y - s_W[j][idx_1].y;
		wa.z = s_C[j].z - s_W[j][idx_1].z;
		wb.x = s_W[j][idx_2].x - s_W[j][idx_1].x;
		wb.y = s_W[j][idx_2].y - s_W[j][idx_1].y;
		wb.z = s_W[j][idx_2].z - s_W[j][idx_1].z;
		pa = wa.x * wb.x + wa.y * wb.y + wa.z * wb.z;
		pb = wb.x * rhol1.x + wb.y * rhol1.y + wb.z * rhol1.z;
		pc = wa.x * rhol1.x + wa.y * rhol1.y + wa.z * rhol1.z;
		pd = wb.x * wb.x + wb.y * wb.y + wb.z * wb.z;
		t1 = pa * pb - pc * pd;
		t2 = (rhol1.x * rhol1.x + rhol1.y * rhol1.y + rhol1.z * rhol1.z) * pd - pb * pb;
		t = t1 / t2;
		// Calculate v2
		v2.x = s_C[j].x + t * rhol1.x;
		v2.y = s_C[j].y + t * rhol1.y;
		v2.z = s_C[j].z + t * rhol1.z;

		if (max_m[j+1] == 1){
			rhol_a = rhol2.y;
			rhol_b = rhol2.z;
		}
		else if (max_m[j+1] == 2){
			rhol_a = rhol2.x;
			rhol_b = rhol2.z;
		}
		else{
			rhol_a = rhol2.x;
			rhol_b = rhol2.y;
		}
		theta = atan2(rhol_b, rhol_a);
		for (unsigned int i=0; i<no_deg; i++){
			unsigned int tmp = i+1;
			if (tmp==no_deg) tmp = 0;
			if (((phi[j+1][i]<=theta) && (phi[j+1][tmp]>=theta)) || ((phi[j+1][i]>=0) && (phi[j+1][tmp]<=0) && ((theta>=phi[j+1][i]) || (theta<=phi[j+1][tmp])))){
				idx_1 = i;
				idx_2 = tmp;
			}
		}
		wa.x = s_C[j+1].x - s_W[j+1][idx_1].x;
		wa.y = s_C[j+1].y - s_W[j+1][idx_1].y;
		wa.z = s_C[j+1].z - s_W[j+1][idx_1].z;
		wb.x = s_W[j+1][idx_2].x - s_W[j+1][idx_1].x;
		wb.y = s_W[j+1][idx_2].y - s_W[j+1][idx_1].y;
		wb.z = s_W[j+1][idx_2].z - s_W[j+1][idx_1].z;
		pa = wa.x * wb.x + wa.y * wb.y + wa.z * wb.z;
		pb = wb.x * rhol2.x + wb.y * rhol2.y + wb.z * rhol2.z;
		pc = wa.x * rhol2.x + wa.y * rhol2.y + wa.z * rhol2.z;
		pd = wb.x * wb.x + wb.y * wb.y + wb.z * wb.z;
		t1 = pa * pb - pc * pd;
		t2 = (rhol2.x * rhol2.x + rhol2.y * rhol2.y + rhol2.z * rhol2.z) * pd - pb * pb;
		t = t1 / t2;
		// Calculate v3
		v3.x = s_C[j+1].x + t * rhol2.x;
		v3.y = s_C[j+1].y + t * rhol2.y;
		v3.z = s_C[j+1].z + t * rhol2.z;

		// Step 4: find lamda (old version: less adders and multipliers)
		// vd = v3 -v1 
		vd.x = v3.x - s_C[j].x;
		vd.y = v3.y - s_C[j].y;
		vd.z = v3.z - s_C[j].z;

		// vb1=v1-p[i]; vb2=v2-p[i]; vb3=v3-p[i]; vb4=v4-p[i]
		vb1 = vb4;
		vb2.x = v2.x - pt.x;
		vb2.y = v2.y - pt.y;
		vb2.z = v2.z - pt.z;
		vb3.x = v3.x - pt.x;
		vb3.y = v3.y - pt.y;
		vb3.z = v3.z - pt.z;
		vb4.x = s_C[j+1].x - pt.x;
		vb4.y = s_C[j+1].y - pt.y;
		vb4.z = s_C[j+1].z - pt.z;
		// lamda
		if ((vd.z < vd.x) && (vd.z < vd.y)) {
			lamda1 = vb2.x*vb1.y - vb1.x*vb2.y;
			lamda2 = vb3.x*vb2.y - vb2.x*vb3.y;
			lamda3 = vb4.x*vb3.y - vb3.x*vb4.y;
			lamda4 = vb1.x*vb4.y - vb4.x*vb1.y;
		} else if ((vd.y < vd.x) && (vd.y < vd.z)) {
			lamda1 = vb2.z*vb1.x - vb1.z*vb2.x;
			lamda2 = vb3.z*vb2.x - vb2.z*vb3.x;
			lamda3 = vb4.z*vb3.x - vb3.z*vb4.x;
			lamda4 = vb1.z*vb4.x - vb4.z*vb1.x;
		} else {
			lamda1 = vb2.y*vb1.z - vb1.y*vb2.z;
			lamda2 = vb3.y*vb2.z - vb2.y*vb3.z;
			lamda3 = vb4.y*vb3.z - vb3.y*vb4.z;
			lamda4 = vb1.y*vb4.z - vb4.y*vb1.z;
		}

		// Step 5: Calculate delta
		if ( ((lamda1 > 0) && (lamda2 > 0) && (lamda3 > 0) && (lamda4 > 0)) || ((lamda1 < 0) && (lamda2 < 0) && (lamda3 < 0) && (lamda4 < 0)) ){
			// if the point is inside the contour
			delta[j] = 0;
			px[j] = 0;
			py[j] = 0;
			pz[j] = 0;
		}else {
			// If the point is outside the contour
			// u = -(v2-p).(v3-v2)/(||v3-v2||^2)
			v32.x = v3.x - v2.x;
			v32.y = v3.y - v2.y;
			v32.z = v3.z - v2.z;
			u = 0 - (vb2.x*v32.x + vb2.y*v32.y + vb2.z*v32.z) / (v32.x*v32.x + v32.y*v32.y + v32.z*v32.z);
			// delta
			if (u>1){
				px[j] = v3.x;
				py[j] = v3.y;
				pz[j] = v3.z;
				w = vb3;
			}else if (u<0){
				px[j] = v2.x;
				py[j] = v2.y;
				pz[j] = v2.z;
				w = vb2;
			}else {
				px[j] = (1-u)*v2.x + u*v3.x;
				py[j] = (1-u)*v2.y + u*v3.y;
				pz[j] = (1-u)*v2.z + u*v3.z;
				w.x = pt.x-px[j];
				w.y = pt.y-py[j];
				w.z = pt.z-pz[j];
			}
			delta[j] = sqrt(w.x*w.x + w.y*w.y + w.z*w.z);
		}

	}

	// Find the penetration of the point, i.e. distance between the point and the closest link
	for (unsigned int j=seg_idx[0]; j<=seg_idx[1]; j++){
		if ( (j==seg_idx[0]) || (delta[j] < s_min_dist[pt_idx]) ){
			s_min_dist[pt_idx] = delta[j];
			//s_out_pt[pt_idx].x = px[j];
			//s_out_pt[pt_idx].y = py[j];
			//s_out_pt[pt_idx].z = pz[j];
			s_out_pt_idx[pt_idx] = j;
		}
	}
	s_out_pt[pt_idx].x = px[s_out_pt_idx[pt_idx]];
	s_out_pt[pt_idx].y = py[s_out_pt_idx[pt_idx]];
	s_out_pt[pt_idx].z = pz[s_out_pt_idx[pt_idx]];

	//std::cout << s_out_pt[pt_idx].x << std::endl;

}


