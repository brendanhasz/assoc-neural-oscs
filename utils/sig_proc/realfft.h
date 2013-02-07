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

void realfft(unsigned long n, double data[], int isign);
