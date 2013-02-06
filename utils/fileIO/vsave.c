/* vsave - Saves a vector to a file

	INPUTS
		int n			Length of the vector to save to file
		double A[]		Vector to save to file
		char fileName[]	The name of the file to save to

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void
vsave(int n, double A[], char fileName[])
{	
	//Open file
	FILE * pFile = fopen (fileName,"w");
	if ( pFile == NULL )
	{
		printf("COULD NOT SAVE DATA TO FILE %s", fileName);
		return;
	}
	
	//Write vector to file
	int i;
	for (i=0; i<n; i++)
	{
		fprintf(pFile, "%f\n", A[i]);
	}

	//Close file
	fclose(pFile);
}
