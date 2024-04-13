//Attempt at a direct implementation; watch out though this is currently using ints.
// TODO: Currently running at 40 cycles
//		 --Can try using different sizes for inputs and outputs for saving some space/Make room for division alternative? Probably more important for space than runtime
// TODO: Find a way to Approximate division for S (it is highest latency by far). Time for good ol friend approx. comp?

#include <ap_fixed.h>

//Play around with different rounding/overflow values, see if that speeds some things up (such as the division?)
typedef ap_fixed<32, 16, AP_TRN, AP_WRAP> fix;

void calcXTX(fix x[8], fix y[8], fix& theta0, fix& theta1){
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
#pragma HLS INTERFACE s_axilite port=theta0
#pragma HLS INTERFACE s_axilite port=theta1
#pragma HLS ARRAY_PARTITION variable=x
#pragma HLS ARRAY_PARTITION variable=y

	fix n = 0;
	fix a[8];
	fix b[8];

	for(int i = 0; i<8; i++){
		#pragma HLS UNROLL
		n +=  1;
		a[i] =  x[i];
		b[i] = (x[i] * x[i]);
	}

	//A
	a[6] += a[7];
	a[4] += a[5];
	a[2] += a[3];
	a[0] += a[1];

	a[4] += a[6];
	a[0] += a[2];

	a[0] += a[4];


	//B
	b[6] += b[7];
	b[4] += b[5];
	b[2] += b[3];
	b[0] += b[1];

	b[4] += b[6];
	b[0] += b[2];

	b[0] += b[4];


	// should check if putting in one line is faster for whatever reason
	fix nb = n    * b[0];
	fix a2 = a[0] * a[0];
	fix s  = 1/(nb-a2);


	fix c =  b[0] * s;
	fix d = -a[0] * s;
	fix e =  n    * s;

	fix th0[8];
	fix th1[8];
	for(int i = 0; i < 8; i++){
		#pragma HLS UNROLL
		th0[i] += (c + (d*x[i]))*y[i];
		th1[i] += (d + (e*x[i]))*y[i];
	}
	//Theta0
	th0[6] += th0[7];
	th0[4] += th0[5];
	th0[2] += th0[3];
	th0[0] += th0[1];

	th0[4] += th0[6];
	th0[0] += th0[2];

	theta0 = th0[0] + th0[4];


	//Theta1
	th1[6] += th1[7];
	th1[4] += th1[5];
	th1[2] += th1[3];
	th1[0] += th1[1];

	th1[4] += th1[6];
	th1[0] += th1[2];

	theta1 = th1[0] + th1[4];


}
