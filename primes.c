#include <stdio.h>
int main()
{
	int i, j, aantal, nummer, ispriem;
	aantal = 100;
	nummer = 2;
	for(i=1; i<=aantal; nummer++)
	{
		ispriem = 1;
		for(j=2; j<nummer; j++)
		{
			if(nummer%j==0)
			{
				ispriem = 0;
				break;
			}
		}
		if(ispriem==1)
		{
			printf("%d\n", nummer);
			i++;
		}
	}
	getchar();
	return 0;
}