#include <stdio.h>
#include <string.h>

#define MY_MAX_LEN			11

int main(int argc, char *argv[])
{
	FILE	*fp;
	char	s_number[MY_MAX_LEN], s_pattern0[MY_MAX_LEN + 1], s_pattern1[MY_MAX_LEN + 1];
	int		len0, sum;

	fp = fopen(argv[1], "r");
	//fp = fopen("E:\\test\\split_number\\data.txt", "r");
	if (fp == NULL)
	{
		printf("Can not open the file.\n");
		return -1;
	}

	while (!feof(fp))	//read the input line by line 
	{
		if (fscanf(fp, "%s %[a-z]%s", s_number, s_pattern0, s_pattern1) == 3)
		{
			len0 = strlen(s_pattern0);
			sum = atoi(&(s_number[len0]));
			s_number[len0] = '\0';
			if (s_pattern1[0] == '+')
				sum = atoi(s_number) + sum;
			else
				sum = atoi(s_number) - sum;

			printf("%d\n", sum);
		}
	}

	fclose(fp);
	return 0;
}
