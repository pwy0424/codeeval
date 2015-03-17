#include <stdio.h>
#include <string.h>

#define my_MAX_LEN			80
#define MAXMATRIXN			20
#define MAXARRAY			400	//MAXARRAY = MAXMATRIXN * MAXMATRIXN

typedef struct customer_data
{
	int	letters;
	int	vowels;
}MY_CDATA;

typedef struct myHungaryTrans
{
	int n;				//Order of the matrix
	int	**matrix;		//The transformation matrix.
	int	in_zeroNum;		//The number of independent 0 elements.
	int	*in_zero;		//The independent 0 elements. (in_zero[row]=column)
	int	**zeroNum;		//The number of 0 elements in row or column. (zeroNum[0][row], zeroNum[1][column])
	int	**line;			//The Hungary's line. (line[0][row], line[1][column])
}HUNGARY_NODE;

void	mySubMiniElement(HUNGARY_NODE *myNode, int subtractor)
{
	int row, column, matrixN;

	matrixN = myNode->n;
	for (row = 0; row<matrixN; row++)
	{
		if (myNode->line[0][row])
			continue;

		for (column = 0; column<matrixN; column++)
		{
			if (myNode->line[1][column])
				continue;

			if ((myNode->matrix[row][column] -= subtractor) == 0)
			{
				myNode->zeroNum[0][row] ++;
				myNode->zeroNum[1][column] ++;
			}
		}
	}
}

int	myFindMiniElement(HUNGARY_NODE *myNode)
{
	int	row, column, matrixN;
	int	mini, first = 1;

	matrixN = myNode->n;
	for (row = 0; row<matrixN; row++)
	{
		if (myNode->line[0][row])
			continue;

		for (column = 0; column<matrixN; column++)
		{
			if (myNode->line[1][column])
				continue;

			if ((mini > myNode->matrix[row][column]) || first)
			{
				mini = myNode->matrix[row][column];
				first = 0;
			}
		}
	}
	return mini;
}

int	myFindLeastZero(HUNGARY_NODE *myNode, int *ind, int *flag)
{
	int	i, j, least, matrixN;

	matrixN = myNode->n;
	least = matrixN + 1;
	*flag = -1;
	for (i = 0; i<2; i++)
	{
		for (j = 0; j<matrixN; j++)
		{
			if ((myNode->line[i][j]) || (myNode->zeroNum[i][j] == 0))
				continue;

			if (least > myNode->zeroNum[i][j])
			{
				*flag = i;
				*ind = j;
				least = myNode->zeroNum[i][j];
			}
		}
	}

	if (*flag == -1)
		least = 0;

	return least;
}

void	myMarkedIndependentZero(int row, int column, HUNGARY_NODE *myNode)
{
	int	i, matrixN;

	matrixN = myNode->n;
	myNode->in_zero[row] = column;
	myNode->in_zeroNum++;
	myNode->line[0][row] = 1;
	myNode->line[1][column] = 1;
	myNode->zeroNum[0][row] = 0;
	myNode->zeroNum[1][column] = 0;

	for (i = 0; i<matrixN; i++)
	{
		if ((myNode->line[0][i] == 0) && (myNode->matrix[i][column] == 0))
			myNode->zeroNum[0][i] --;

		if ((myNode->line[1][i] == 0) && (myNode->matrix[row][i] == 0))
			myNode->zeroNum[1][i] --;
	}
}

void	myFindAllIndependentZero(HUNGARY_NODE *myNode, int *InZeroR, int *InZeroC)
{
	int	matrixN, least, ind, flag;
	int rowTemp[MAXMATRIXN], columnTemp[MAXMATRIXN];
	int	row, column, i, num, temp;

	matrixN = myNode->n;
	memcpy(rowTemp, myNode->zeroNum[0], matrixN*sizeof(int));
	memcpy(columnTemp, myNode->zeroNum[1], matrixN*sizeof(int));
	memset(myNode->line[0], 0, matrixN*sizeof(int));
	memset(myNode->line[1], 0, matrixN*sizeof(int));
	myNode->in_zeroNum = 0;
	for (row = 0; row<matrixN; row++)
		myNode->in_zero[row] = -1;

	*InZeroR = -1;
	while (least = myFindLeastZero(myNode, &ind, &flag))
	{
		temp = least;
		if (flag)
		{
			column = ind;
			num = matrixN + 1;
			for (i = 0; (i<matrixN) && least; i++)
			{
				if ((myNode->line[0][i] == 0) && (myNode->matrix[i][column] == 0))
				{
					if (myNode->zeroNum[0][i] < num)
					{
						row = i;
						num = myNode->zeroNum[0][i];
						least--;
					}
				}
			}
		}
		else
		{
			row = ind;
			num = matrixN + 1;
			for (i = 0; (i<matrixN) && least; i++)
			{
				if ((myNode->line[1][i] == 0) && (myNode->matrix[row][i] == 0))
				{
					if (myNode->zeroNum[1][i] < num)
					{
						column = i;
						num = myNode->zeroNum[1][i];
						least--;
					}
				}
			}
		}

		myMarkedIndependentZero(row, column, myNode);

		if (temp > 1)
		{
			*InZeroR = row;
			*InZeroC = column;
		}
	}

	memcpy(myNode->zeroNum[0], rowTemp, matrixN*sizeof(int));
	memcpy(myNode->zeroNum[1], columnTemp, matrixN*sizeof(int));
}

void	myTransformMatrix(HUNGARY_NODE *myNode)
{
	int i, j, matrixN;
	int	mini_ele;

	matrixN = myNode->n;
	if (myNode->in_zeroNum == 0)	// first to transform the matrix.
	{
		for (i = 0; i<2; i++)
		{//0: - sub the minimum element in row; 1: - sub the minimum element in column.
			for (j = 0; j<matrixN; j++)
			{
				myNode->line[i ^ 1][j] = 0;
				myNode->line[i][j] = 1;
			}

			for (j = 0; j<matrixN; j++)
			{
				if (myNode->zeroNum[i][j])
					continue;

				myNode->line[i][j] = 0;
				mini_ele = myFindMiniElement(myNode);
				mySubMiniElement(myNode, mini_ele);
				myNode->line[i][j] = 1;
			}
		}
	}
	else
	{
		mini_ele = myFindMiniElement(myNode);
		mySubMiniElement(myNode, mini_ele);
	}
}

void	myDrawLine(HUNGARY_NODE *myNode)
{
	int	row, column, unfinish, matrixN;

	matrixN = myNode->n;
	for (row = 0; row<matrixN; row++)
	{
		myNode->line[1][row] = 0;
		if (myNode->in_zero[row] == -1)
			myNode->line[0][row] = 1;
		else
			myNode->line[0][row] = 0;
	}

	do
	{
		unfinish = 0;
		for (row = 0; row<matrixN; row++)
		{
			if (myNode->line[0][row] != 1)
				continue;

			myNode->line[0][row] ++;
			for (column = 0; column<matrixN; column++)
			{
				if (myNode->line[1][column])
					continue;

				if (myNode->matrix[row][column] == 0)
					myNode->line[1][column] = 1;
			}
		}

		for (column = 0; column<matrixN; column++)
		{
			if (myNode->line[1][column] != 1)
				continue;

			myNode->line[1][column] ++;
			for (row = 0; row<matrixN; row++)
			{
				if (myNode->line[0][row])
					continue;

				if (myNode->in_zero[row] == column)
				{
					myNode->line[0][row] = 1;
					unfinish = 1;
				}
			}
		}
	} while (unfinish);

	for (row = 0; row<matrixN; row++)
	{
		if (myNode->line[0][row])
			myNode->line[0][row] = 0;
		else
			myNode->line[0][row] = 1;
	}
}

int	myHungary(int matrixN, int *RawData)
{
	int		transArray[MAXARRAY];
	int		*transMatrix[MAXMATRIXN];
	int		tempData[MAXMATRIXN * 5] = { 0 };
	int		*zeroNum[2];	//0: row, 1: column;
	int		*zeroLine[2];	//0: row, 1: column;
	int		i, row, column, *str;
	int		miniSum = 0, sum;
	HUNGARY_NODE	myNode;

	//Initialize matrix data address.
	zeroNum[0] = tempData;
	zeroNum[1] = tempData + MAXMATRIXN;
	zeroLine[0] = zeroNum[1] + MAXMATRIXN;
	zeroLine[1] = zeroLine[0] + MAXMATRIXN;

	memcpy(transArray, RawData, matrixN*matrixN*sizeof(int));
	str = transArray;
	for (row = 0; row < matrixN; row++)
	{
		transMatrix[row] = str;
		str += matrixN;
	}

	myNode.n = matrixN;
	myNode.matrix = transMatrix;
	myNode.in_zeroNum = 0;
	myNode.in_zero = zeroLine[1] + MAXMATRIXN;
	myNode.zeroNum = zeroNum;
	myNode.line = zeroLine;
	//////////////////////////////////////////

	while (myNode.in_zeroNum < matrixN)
	{
		myTransformMatrix(&myNode);

		myFindAllIndependentZero(&myNode, &row, &column);

		if (myNode.in_zeroNum < matrixN)
			myDrawLine(&myNode);
	}

	do
	{
		sum = 0;
		for (i = 0; i<matrixN; i++)
			sum += RawData[i*matrixN + myNode.in_zero[i]];
		if (sum < miniSum || miniSum == 0)
			miniSum = sum;

		if (row != -1)
		{
			myNode.matrix[row][column] = 1;
			myNode.zeroNum[0][row] --;
			myNode.zeroNum[1][column] --;

			myFindAllIndependentZero(&myNode, &row, &column);
		}
		else	break;
	} while (myNode.in_zeroNum == matrixN);

	return	miniSum;
}

int	isCoprime(int a, int b)
{// return 1: is coprime; another: is nocoprime
	int	t;

	if (a == 0 || a == 1 || b == 0 || b == 1)
		return 0;

	while (b != 0)
	{
		t = b;
		b = a%b;
		a = t;
	}
	return a;
}

int	myCaculateSS(MY_CDATA c_data, int p_data)
{
	int	s;

	if (p_data % 2)
		s = (c_data.letters - c_data.vowels) << 1;
	else
		s = c_data.vowels * 3;

	if (isCoprime(c_data.letters, p_data) != 1)
		s *= 3;
	else
		s <<= 1;

	return s;
}

int	myLookforSS(int c_num, MY_CDATA *c_data, int p_num, int *p_data)
{
	int		SSarray[MAXARRAY] = { 0 }, *str;
	int		SSmatrixN, maxSS, maxEle = 0;
	int		row, column;

	if (c_num == 0 || p_num == 0)
		return 0;

	SSmatrixN = p_num > c_num ? p_num : c_num;

	for (row = 0; row < c_num; row++)
	{
		str = &(SSarray[row*SSmatrixN]);
		for (column = 0; column < p_num; column++)
		{
			if (maxEle < (*str = myCaculateSS(c_data[row], p_data[column])))
				maxEle = *str;
			str++;
		}
	}

	for (row = 0; row < c_num; row++)
	{
		str = &(SSarray[row*SSmatrixN]);
		for (column = 0; column < p_num; column++)
		{
			*str = maxEle - *str;
			str++;
		}
	}

	maxSS = myHungary(SSmatrixN, SSarray);
	maxSS = c_num > p_num ? p_num*maxEle - maxSS : c_num*maxEle - maxSS;

	return maxSS;
}

void	myNameToData(int flag, char *line_data, MY_CDATA *c_data, int *p_data)
{
	int		i, len;
	char	ch;

	len = strlen(line_data);
	if (flag)	// is customer
	{
		c_data->letters = 0;
		c_data->vowels = 0;
		for (i = 0; i < len; i++)
		{
			ch = *line_data++;
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				c_data->letters++;
				if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y' ||
					ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'Y')
					c_data->vowels++;
			}
		}
	}
	else		// is product
	{
		*p_data = 0;
		for (i = 0; i < len; i++)
		{
			ch = *line_data++;
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				(*p_data)++;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE		*fp;
	char		line_data[my_MAX_LEN];
	MY_CDATA	c_data[MAXMATRIXN];
	int			p_data[MAXMATRIXN];
	int			c_num = 0, p_num = 0, count = 0;
	int			ch, customer;

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Can not open the file.\n");
		return -1;
	}

	while (!feof(fp))
	{
		customer = 1;
		c_num = 0;
		p_num = 0;
		ch = 0;
		while (ch != '\n')	//read the input line by line
		{
			if (fscanf(fp, "%[^,^;^\n]", line_data) == 1)
			{
				if (c_num <= MAXMATRIXN && p_num <= MAXMATRIXN)
				{
					myNameToData(customer, line_data, &(c_data[c_num]), &(p_data[p_num]));
					if (customer)
						c_num++;
					else
						p_num++;
				}
			}

			ch = fgetc(fp);
			if (feof(fp))
				break;
			if (ch == ';')
				customer = 0;
		}
		if (!feof(fp))
			printf("%.2f\n", (float)myLookforSS(c_num, c_data, p_num, p_data) / 4.0);
	}

	fclose(fp);
	return 0;
}
