/*
	segment_threads.c

	Finds thread divisions for a loop from a to b, puts divider index
	values in divs.
*/


void
segment_threads(int n, int a, int b, int divs[])
{
	int i;
	for (i=1; i<=n; i++){
		divs[i]=a+i/n*(b-a);
	}

}
