/* asave - Saves a 2d array to a file

	INPUTS
		int n			Height of the array to save to file
		int m			Length of the array to save to file
		double A[]		Array to save to file
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
asave(int n, int m, double A[n][m], char fileName[])
{	
	//Open file
	FILE * pFile = fopen (fileName,"w");
	if ( pFile == NULL )
	{
		printf("COULD NOT SAVE DATA TO FILE %s", fileName);
		return;
	}
	
	//Write array to file
	int i, j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			fprintf(pFile, "%f\t", A[i][j]);
		}
		fprintf(pFile, "\n");
	}

	//Close file
	fclose(pFile);
}
