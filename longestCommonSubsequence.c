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

#define MY_MAX_LEN			50

typedef struct my_index
{
	int	num;
	int	*ind;
	int	curr;
}MY_INDEX;

int my_find_longest_list(int *index, int len, int result[])
{
	int	lis_temp[MY_MAX_LEN], pre_temp[MY_MAX_LEN];
	int i, j, max_pos = 0, max = 1;

	for (i = 0; i<len; i++)
	{
		lis_temp[i] = 1;
		pre_temp[i] = i;
	}

	for (i = 1; i<len; i++)
	{
		for (j = 0; j<i; ++j)
		{
			if (index[j]<index[i] && lis_temp[j] + 1>lis_temp[i])
			{
				lis_temp[i] = lis_temp[j] + 1;
				pre_temp[i] = j;

				if (max < lis_temp[i])
				{
					max = lis_temp[i];
					max_pos = i;
				}
			}
		}
	}

	i = max - 1;
	while (pre_temp[max_pos] != max_pos)
	{
		result[i--] = index[max_pos];
		max_pos = pre_temp[max_pos];
	}
	result[i] = index[max_pos];

	return max;
}

int	my_GetNextIndexChain(MY_INDEX *index, int index_len)
{
	int i, ret = 0;

	for (i = index_len - 1; i >= 0; i--)
	{
		if (++index[i].curr < index[i].num)
		{
			ret = 1;
			break;
		}
		else
			index[i].curr = 0;
	}
	return ret;
}

int my_indexdataIni(int *index_Buff, MY_INDEX *index, char *s1, int len1, char *s2, int len2)
{
	int	i, j, len = 0;

	for (i = 0; i<len1; i++)
	{
		index->curr = 0;
		index->num = 0;
		index->ind = index_Buff;
		for (j = 0; j<len2; j++)
		{
			if (s1[i] == s2[j])
			{
				*index_Buff++ = j;
				index->num++;
			}
		}
		if (index->num > 0)
		{
			index++;
			len++;
		}
	}
	return len;
}

int main(int argc, char *argv[])
{
	FILE *file = fopen(argv[1], "r");
	int			index_Buff[MY_MAX_LEN*MY_MAX_LEN];
	MY_INDEX	index[MY_MAX_LEN];
	int			index_data[MY_MAX_LEN], index_len;
	int			res1[MY_MAX_LEN], res2[MY_MAX_LEN];
	int			max, *result, tmp_max, *tmp_result, *pt;
	char		s1[MY_MAX_LEN + 1], s2[MY_MAX_LEN + 1], line[(MY_MAX_LEN + 1) * 2];
	int			i, len1, len2;

	//file = fopen (argv[1], "r");

	if (file == NULL)
	{
		printf("Can not open the file.\n");
		return -1;
	}

	while (fgets(line, (MY_MAX_LEN + 1) * 2, file) != NULL)	//read the input line by line 
	{
		if (sscanf(line, "%[^;]%*c%[^\n]%*c", s1, s2) == 2)
		{
			len1 = strlen(s1);
			len2 = strlen(s2);
			//printf("%s,\t%d\n%s,\t%d\n", s1, len1, s2, len2);

			index_len = my_indexdataIni(index_Buff, index, s2, len2, s1, len1);
			max = 0;
			tmp_result = res1;
			result = res2;
			do
			{
				for (i = 0; i<index_len; i++)
					index_data[i] = index[i].ind[index[i].curr];

				tmp_max = my_find_longest_list(index_data, index_len, tmp_result);

				if (tmp_max > max)
				{
					max = tmp_max;
					pt = result;
					result = tmp_result;
					tmp_result = pt;
				}
			} while (my_GetNextIndexChain(index, index_len));

			for (i = 0; i<max; i++)
				printf("%c", s1[result[i]]);
			printf("\n");
		}
	}

	fclose(file);

	return 0;
}


