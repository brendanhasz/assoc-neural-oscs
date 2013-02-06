/* complexfft - Compute the complex discrete fourier transform of a vector
	
	Computes the discrete fourier transfom of a vector using bit reversal and
	the Danielson-Lanczos formula.  Runs in NlogN time. Shamelessly copied
	from Numerical Recipies in C, 2nd Edition by Press, Teukolsky, Vetterling, 
	and Flannery.
	
	Arguments
		unsigned long nn	Length of complex array - MUST be a power of 2!
		double data[]		Data
		int isign			1: replaces data w/ DFT, -1: replace w/ inverse DFT

        
    Copyright 1992 Numerical Recipies Software
    
*/

void
complexfft(unsigned long nn, double data[], int isign)
{
	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta, temp, tempi;
	
	//Bit-reversal
	n = nn << 1;
	j = 1;
	for (i=1; i<n; i+=2){
		if ( j > i ){  //Exchange 2 complex numbers
			temp=data[j]; data[j]=data[i]; data[i]=temp;
			temp=data[j+1]; data[j+1]=data[i+1]; data[i+1]=temp;
		}
		m = n >> 1;
		while ( m>=2 && j>m ){
			j -= m;
			m >>= 1;
		}
		j +=m;
	}

	//Danielson-Lanczos recurrence
	mmax = 2;
	while ( n > mmax ){
		istep = mmax << 1;
		theta = isign*(6.28318530717959/mmax);
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m=1; m<mmax; m+=2){
			for (i=m; i<=n; i+=istep){
				j = i + mmax;
				temp = wr*data[j]-wi*data[j+1];  //Danielson-Lanczos formula
				tempi = wr*data[j+1]-wi*data[j];
				data[j] = data[i] - temp;
				data[j+1] = data[i+1] - tempi;
				data[i] += temp;
				data[i+1] += tempi;
			}
			wr = (wtemp=wr)*wpr-wi*wpi+wr;  //Trigonometric recurrence
			wi = wi*wpr+wtemp*wpi+wi;
		}
		mmax = istep;
	}
}
