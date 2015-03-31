#include <iostream>
using namespace std;

#define	PRIME_COUNT				1000
#define MAX_POS					4096
#define MAX_BUFF				128

int main()
{
	bool			to_lookfor = true;
	int				i, j, pos, step;
	unsigned int	no_prime[MAX_BUFF] = { 0 }, mark;
	int				my_sum = 2, count = 1;

	for (i = 0; i < MAX_POS; i++)
	{
		pos = i >> 5;
		mark = 1 << (i & 0x1f);
		if (no_prime[pos] & mark)
			continue;
		else
		{
			step = 3 + (i << 1);
			my_sum += step;
			count++;
			if (count == PRIME_COUNT)
				break;

			if (to_lookfor)
			{
				j = (step*step - 3) >> 1;
				if (j >= MAX_POS)
					to_lookfor = false;
				else
				{
					while (j < MAX_POS)
					{
						pos = j >> 5;
						mark = 1 << (j & 0x1f);
						no_prime[pos] |= mark;
						j += step;
					}
				}
			}
		}
	}

	printf("%d\n", my_sum);

	return 0;
}