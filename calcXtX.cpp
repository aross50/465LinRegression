//Attempt at a direct implementation; watch out though this is currently using ints.
// TODO: Currently running at 40 cycles
//		 --Can try using different sizes for inputs and outputs for saving some space/Make room for division alternative? Probably more important for space than runtime
// TODO: Find a way to Approximate division for S (it is highest latency by far). Time for good ol friend approx. comp?

#include <ap_fixed.h>


//Play around with different rounding/overflow values, see if that speeds some things up (such as the division?)
typedef ap_fixed<32, 16, AP_TRN, AP_WRAP> fix;

void calcXTX(fix x[8], fix y[8], fix& pred1, fix& pred2, fix& pred3, fix& pred4, fix& pred5, fix& pred6, fix& pred7, fix& pred8){
//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS interface s_axilite port=return
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
#pragma HLS INTERFACE s_axilite port=pred1
#pragma HLS INTERFACE s_axilite port=pred2
#pragma HLS INTERFACE s_axilite port=pred3
#pragma HLS INTERFACE s_axilite port=pred4
#pragma HLS INTERFACE s_axilite port=pred5
#pragma HLS INTERFACE s_axilite port=pred6
#pragma HLS INTERFACE s_axilite port=pred7
#pragma HLS INTERFACE s_axilite port=pred8
//#pragma HLS INTERFACE s_axilite port=theta1
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


	fix nb = n    * b[0];
	fix a2 = a[0] * a[0];

	fix D = nb-a2;


	//Trying to cast one to fix to see if this resolves division problem that was previously occuring
	//fix s = (fix(1))/D;


	fix s = 1;
	int shift_count = 0;
	const int total_width = 32;
	const int int_width = 16;

	while (s <= D) {
		s <<= 1;
		shift_count++;
	}

	// Now, calculate the number of fractional bits
	int frac_width = total_width - int_width;


	fix initial_guess = 0;
	unsigned int bitmask = 1 << (frac_width - shift_count);

	initial_guess = reinterpret_cast<fix&>(bitmask);

	s = initial_guess;

	s = s * (fix(2) - D * s);
	s = s * (fix(2) - D * s);
	s = s * (fix(2) - D * s);


	fix c =  b[0] * s;
	fix d = -a[0] * s;
	fix e =  n    * s;


	//Initializing to other than zero for testing purposes
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

	th0[0] += th0[4];


	//Theta1
	th1[6] += th1[7];
	th1[4] += th1[5];
	th1[2] += th1[3];
	th1[0] += th1[1];

	th1[4] += th1[6];
	th1[0] += th1[2];

	th1[0] += th1[4];


	//Current aim is simply to have all predictions as outputs for easy retrieval/confirmation
	pred1 = (th1[0] * x[0]) + th0[0];
	pred2 = (th1[0] * x[1]) + th0[0];
	pred3 = (th1[0] * x[2]) + th0[0];
	pred4 = (th1[0] * x[3]) + th0[0];
	pred5 = (th1[0] * x[4]) + th0[0];
	pred6 = (th1[0] * x[5]) + th0[0];
	pred7 = (th1[0] * x[6]) + th0[0];
	pred8 = (th1[0] * x[7]) + th0[0];


}
