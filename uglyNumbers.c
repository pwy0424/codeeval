#include <stdio.h>

#define MY_MAX_LEN			14

int is_ugly(int number)//very simple function to determain an interger is an ugly number or not
{
	if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 || number % 7 == 0)
		return 1;
	else
		return 0;
}

int myMakeNum(int *deli_num, int deli_len, int last_num, int gc, int bit_change)
{
	int		mark = 1;
	int	sum = 0;

	if (gc)
	{
		deli_num++;
		while (!(bit_change & mark))
		{
			deli_num++;
			mark <<= 1;
		}

		if (gc & mark)
			sum = last_num - ((*deli_num) << 1);
		else
			sum = last_num + ((*deli_num) << 1);
	}
	else
	{
		while (deli_len--)
		{
			sum += *deli_num;
			deli_num++;
		}
	}

	return sum;
}

int	myDeliNum(int *my_input, int input_len, int *deli_num, int my_delimiter)
{
	int num = 1, mark = 1;

	*deli_num = *my_input;
	while (--input_len)
	{
		my_input++;
		if (my_delimiter & mark)
		{
			deli_num++;
			num++;
			*deli_num = *my_input;
		}
		else
			*deli_num = (*deli_num * 10 + *my_input) % 210;

		mark <<= 1;
	}

	return num;
}

int myFunction(char *input)//the main processing function
/**
* @input: the input numbers
* @return: the number of ugly numbers
*/
{
	int		count = 0;	//result to count the number of ugly numbers
	int		input_len, my_input[MY_MAX_LEN - 1];
	int		deli_len;
	int	    deli_num[MY_MAX_LEN - 1];
	int		deli_ind, deli_max, oper_ind, oper_max;
	int		oper_gc, last_oper_gc;
	int  	num, last_num;

	//data Initialization
	input_len = 0;
	while ((*input != '\0') && (*input != '\n'))
	{
		my_input[input_len] = *input - '0';
		input++;
		input_len++;
	}

	if (!input_len)
		return -1;

	deli_max = 1 << (input_len - 1);
	for (deli_ind = 0; deli_ind < deli_max; deli_ind++)
	{
		deli_len = myDeliNum(my_input, input_len, deli_num, deli_ind);

		oper_max = 1 << (deli_len - 1);
		for (oper_ind = 0; oper_ind < oper_max; oper_ind++)
		{
			oper_gc = oper_ind ^ (oper_ind >> 1);
			num = myMakeNum(deli_num, deli_len, last_num, oper_gc, last_oper_gc^oper_gc);

			if (is_ugly(num))
				count++;

			last_num = num;
			last_oper_gc = oper_gc;
		}
	}

	return count;
}

int main(int argc, char *argv[])
//int my_main( )
{
	FILE	*file;
	char	lineBuffer[MY_MAX_LEN];
	int		ugly_count;

	file = fopen(argv[1], "r");
	//file = fopen("E:\\test\\my_ugly1\\data.txt", "r");
	if (file == NULL)
	{
		printf("Can not open the file.\n");
		return -1;
	}

	while (!feof(file))	//read the input line by line 
	{
		if (fgets(lineBuffer, MY_MAX_LEN, file))
		{
			ugly_count = myFunction(lineBuffer);
			if (ugly_count >= 0)
				printf("%d\n", ugly_count);	//print the results line by line
		}
	}

	fclose(file);
	return 0;
}
