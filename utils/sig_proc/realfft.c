/* realfft - Compute the discrete fourier transform of a vector of real values
	
	Replaces a vector of real values, data[], with the positive frequency half
	of its discrete fourier transfom using bit reversal and the 
	Danielson-Lanczos formula.  Runs in NlogN time.  Shamelessly copied from 
	Numerical Recipies in C, 2nd Edition by Press, Teukolsky, Vetterling, 
	and Flannery.
	
	Arguments
		unsigned long n		Length of complex array - MUST be a power of 2!
		double data[]		Data
		int isign			1: replaces data w/ DFT, -1: replace w/ inverse DFT
	
	Arguments
		unsigned long nn	Length of complex array - MUST be a power of 2!
		double data[]		Data
		int isign			1: replaces data w/ DFT, -1: replace w/ inverse DFT

        
    Copyright 1992 Numerical Recipies Software
    
*/

void
realfft(unsigned long n, double data[], int isign)
{
	unsigned long i, i1, i2, i3, i4, np3;
	double c1=0.5, c2, h1r, h1i, h2r, h2i, wr, wi, wpr, wpi, wtemp, theta;
	
	theta = M_PI/(double) (n>>1);
	if ( isign == 1 ) {
		c2 = -0.5;
		complexfft(n>>1, data, 1);
	} else {
		c2 = 0.5;
		theta = -theta;
	}

	wtemp = sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi = sin(theta);
	wr = 1.0 + wpr;
	wi = wpi;
	np3 = n + 3;
	for (i=2; i<=(n>>2); i++){
		i4 = 1+(i3=np3-(i2=1+(i1=i+i-1)));
		
		//Separate two separate transforms out of data
		h1r = c1*(data[i1]+data[i3]);
		h1i = c1*(data[i2]-data[i4]);
		h2r = -c2*(data[i2]+data[i4]);
		h2i = c2*(data[i1]-data[i3]);
		
		//Re-combine to form true transform of original data
		data[i1] = h1r+wr*h2r-wi*h2i;
		data[i2] = h1i+wr*h2i+wi*h2r;
		data[i3] = h1r-wr*h2r+wi*h2i;
		data[i4] = -h1i+wr*h2i+wi*h2r;
		
		//The recurrence
		wr = (wtemp=wr)*wpr-wi*wpi+wr;
		wi = wi*wpr+wtemp*wpi+wi;
	}
	if ( isign == 1 ){  //Squeeze 1st and last data together
		data[1] = (h1r=data[1])+data[2];
		data[2] = h1r-data[2];
	} else {  //Do inverse transform
		data[1] = c1*((h1r=data[1])+data[2]);
		data[2] = c1*(h1r-data[2]);
		complexfft(n>>1, data, -1);
	}
}
