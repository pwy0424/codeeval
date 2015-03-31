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

#define MY_MAX_BRIDGES			30

typedef struct my_point
{
	double	x, y;
}MY_POINT;

typedef struct my_bridge
{
	int	id;
	MY_POINT	p1, p2;
}MY_BRIDGE;

int my_getMax(int cross_num[], int bridge_num)
{
	int i, max = 0, index = -1;

	for (i = 0; i<bridge_num; i++)
	{
		if (cross_num[i] > max)
		{
			max = cross_num[i];
			index = i;
		}
	}
	return index;
}

double my_min(double a, double b)
{
	return a<b ? a : b;
}
double my_max(double a, double b)
{
	return a>b ? a : b;
}
int is_OnSegment(MY_POINT p, MY_POINT p1, MY_POINT p2)
{
	if (my_min(p1.x, p2.x) <= p.x && p.x <= my_max(p1.x, p2.x))
	{
		if (my_min(p1.y, p2.y) <= p.y && p.y <= my_max(p1.y, p2.y))
		{
			return 1;
		}
	}
	return 0;
}

int my_judge_across(MY_BRIDGE b1, MY_BRIDGE b2)
{
	double	delt1, delt2, delt3, delt4;

	delt1 = (b2.p1.x - b1.p1.x)*(b2.p2.y - b1.p1.y) - (b2.p1.y - b1.p1.y)*(b2.p2.x - b1.p1.x);
	delt2 = (b2.p1.x - b1.p2.x)*(b2.p2.y - b1.p2.y) - (b2.p1.y - b1.p2.y)*(b2.p2.x - b1.p2.x);
	if ((delt1<0 && delt2<0) || (delt1>0 && delt2>0))
		return 0;
	if (delt1 == 0)
	if (is_OnSegment(b1.p1, b2.p1, b2.p2))
		return 1;
	if (delt2 == 0)
	if (is_OnSegment(b1.p2, b2.p1, b2.p2))
		return 1;
	if ((delt1 == 0) && (delt2 == 0))
	{
		if (is_OnSegment(b2.p1, b1.p1, b1.p2) || is_OnSegment(b2.p2, b1.p1, b1.p2))
			return 1;
		else return 0;
	}

	delt3 = (b1.p1.x - b2.p1.x)*(b1.p2.y - b2.p1.y) - (b1.p1.y - b2.p1.y)*(b1.p2.x - b2.p1.x);
	delt4 = (b1.p1.x - b2.p2.x)*(b1.p2.y - b2.p2.y) - (b1.p1.y - b2.p2.y)*(b1.p2.x - b2.p2.x);
	if ((delt3<0 && delt4<0) || (delt3>0 && delt4>0))
		return 0;
	if (delt3 == 0)
	if (is_OnSegment(b1.p1, b2.p1, b2.p2) == 0)
		return 0;
	if (delt4 == 0)
	if (is_OnSegment(b1.p2, b2.p1, b2.p2) == 0)
		return 0;

	return 1;
}

void my_by_bridge(MY_BRIDGE bridge[], int bridge_num)
{
	char	matrix_buff[MY_MAX_BRIDGES*MY_MAX_BRIDGES] = { 0 };
	char	*cross_matrix[MY_MAX_BRIDGES];
	int		cross_num[MY_MAX_BRIDGES] = { 0 };
	int		i, j;

	for (i = 0; i<bridge_num; i++)
		cross_matrix[i] = matrix_buff + i * bridge_num;

	for (i = 0; i<bridge_num - 1; i++)
	{
		for (j = i + 1; j<bridge_num; j++)
		{
			if (my_judge_across(bridge[i], bridge[j]))
			{
				cross_matrix[i][j] = 1;
				cross_matrix[j][i] = 1;
				cross_num[i] ++;
				cross_num[j] ++;
			}
		}
	}

	/*for (i=0; i<bridge_num; i++)
	{
	printf("%d,\t%d:", bridge[i].id, cross_num[i]);
	for(j=0; j<bridge_num; j++)
	printf("\t%d", cross_matrix[i][j]);
	printf("\n");
	}
	printf("\n");*/
	while ((i = my_getMax(cross_num, bridge_num)) >= 0)
	{
		bridge[i].id *= -1;
		cross_num[i] *= -1;
		for (j = 0; j<bridge_num; j++)
		{
			if (bridge[j].id < 0)
				continue;
			if (cross_matrix[i][j])
				cross_num[j] --;
		}
	}
	/*for (i=0; i<bridge_num; i++)
	{
	printf("%d,\t%d:", bridge[i].id, cross_num[i]);
	for(j=0; j<bridge_num; j++)
	printf("\t%d", cross_matrix[i][j]);
	printf("\n");
	}
	printf("\n");*/
}

int main(int argc, char *argv[])
//int my_main( )
{
	FILE *file = fopen(argv[1], "r");
	MY_BRIDGE	bridge[MY_MAX_BRIDGES], *dsp;
	int			bridge_num = 0, i;
	char		s[40];

	//file = fopen (argv[1], "r");
	if (file == NULL)
	{
		printf("Can not open the file.\n");
		return -1;
	}

	dsp = bridge;
	while (!feof(file))	//read the input line by line 
	{
		i = fscanf(file, "%d%[^'[']%*c%lf,%lf%[^'[']%*c%lf,%lf", &(dsp->id), s,
			&(dsp->p1.x), &(dsp->p1.y), s, &(dsp->p2.x), &(dsp->p2.y));
		if (i == 7)
		{
			dsp++;
			bridge_num++;
			fscanf(file, "%s\n", s);
		}
	}

	fclose(file);

	my_by_bridge(bridge, bridge_num);

	for (i = 0; i<bridge_num; i++)
	{
		if (bridge[i].id > 0)
			printf("%d\n", bridge[i].id);
	}

	return 0;
}
