/* Sample code to read in test cases:
#include <stdio.h>
int main(int argc, const char * argv[]) {
FILE *file = fopen(argv[1], "r");
char line[1024];
while (fgets(line, 1024, file)) {
// Do something with the line
}
return 0;
} */

#include <stdio.h>

#define MY_MAX_DATA			100

void my_swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

int my_apart(int data[], int start, int end)
{
	int index = start++;

	while (start <= end)
	{
		if (data[start] <= data[index])
		{
			my_swap(&(data[start]), &(data[index]));
			start++;
			index++;
		}
		else
		{
			my_swap(&(data[start]), &(data[end]));
			end--;
		}
	}
	return index;
}

int my_get_median(int data[], int num)
{
	int left = 0, right = num - 1, mid = (num - 1) >> 1, index = -1;

	while (index != mid)
	{
		index = my_apart(data, left, right);

		if (index < mid)
			left = index + 1;
		if (index > mid)
			right = index - 1;
	}
	return index;
}

int my_Minimum_Distance(int my_data[], int num)
{
	int index, i, end, sum = 0;

	index = my_get_median(my_data, num);

	end = num >> 1;
	for (i = 0; i<end; i++)
		sum += my_data[num - 1 - i] - my_data[i];

	return sum;
}

int main(int argc, char *argv[])
//int my_main( )
{
	int	my_data[MY_MAX_DATA], num, i, *dsp;

	//file = fopen (argv[1], "r");
	FILE *file = fopen(argv[1], "r");

	while (!feof(file))	//read the input line by line 
	{
		fscanf(file, "%d", &num);
		dsp = my_data;
		for (i = 0; i<num; i++)
		{
			fscanf(file, "%d", dsp++);
		}

		printf("%d\n", my_Minimum_Distance(my_data, num));
	}

	fclose(file);
	return 0;
}
