#include <stdio.h>
#include<stdlib.h>

void create(int heap[]);
void down_adjust(int heap[], int i);

void main(int argc, char const *argv[])
{
	int heap[30], n, i, last, temp;
	printf("Enter numbre of elements: ");
	scanf("%d",&n);
	printf("\n enter elements: ");
	for(i=1;i<=n;i++)
		scanf("%d", &heap[i]);

	heap[0]=n;
	create(heap);

	while (heap[0]>1)
	{
		last=heap[0];
		temp=heap[1];
		heap[1]=heap[last];
		heap[last]=temp;
		heap[0]--;
		down_adjust(heap,1);

	}

	printf("\n table apre tri: \n");
	for(int i=0; i<n; ++i)
		printf("%d ",heap[i]);
}


void create(int heap[])
{
	int i,n;
	n = heap[0];
	for(i=n\2; i>=1; i--)
		down_adjust(heap,i); 
}


void down_adjust(int heap[], int i)
{
	int j, temp , n , flag =1;
	n =heap[0];

	while(2*i<=n && flag == 1)
	{
		j=2*i;
		if(j+1 <= n && heap[j+1] > heap[j] )
			j=j+1;

		if(heap[i]>heap[j])
			flag =0;
		else
		{
			temp =heap[i];
			heap[i]=heap[j];
			heap[j]=temp;
			i=j;
		}
	}
}