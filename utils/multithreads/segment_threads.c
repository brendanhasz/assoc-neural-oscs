/*
	segment_threads.c

	Finds thread divisions for a loop from a to b, puts divider index
	values in divs.
*/


void
segment_threads(int n, int a, int b, int divs[])
{
	int i;
	divs[0]=a;
	for (i=1; i<=n; i++){
		divs[i]=a+((double) i)/((double) n)*(b-a);
	}

}
