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

void complexfft(unsigned long nn, double data[], int isign);
