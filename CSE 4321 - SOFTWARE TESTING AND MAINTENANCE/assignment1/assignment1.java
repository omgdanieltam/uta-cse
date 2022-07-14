public class assignment1
{
	public static int findLast (int[] x, int y)
	{
		for(int i=x.length-1; i >= 0; i--)
		{
			if(x[i] == y)
			{
				return i;
			}
		}

		return -1;
	}

	public static int countPositive(int[] x)
	{
		int count = 0;
		for(int i = 0; i < x.length; i++)
		{
			if(x[i] > 0)
			{
				count++;
			}
		}
		return count;
	}

	public static void main(String[] args)
	{
		//int x[] = {2, 3, 5};
		int x[] = null;
		int y = 2;
		System.out.printf("findLast%nExpected: 0%nResult: %d%n%n", findLast(x, y));

		int z[] = {-4, 2, 0, 2};
		System.out.printf("countPositive%nExpected: 2%nResult: %d%n", countPositive(z));
	}
}
