//by @AntoineLemarchand

int	ft_printf(const char * format, ...);

#include<stdio.h>
#define KNRM  "\x1B[0m"
#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"
#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"
#define KMAG  "\x1B[35m"

int	main(void)
{
	unsigned int	max_uint;
	int				max_int;
	int				min_int;
	unsigned long	max_ulong_int;
	unsigned long	min_ulong_int;
	int				ret1;
	int				ret2;

	max_uint = 4294967295;
	max_int = 2147483647;
	min_int = -2147483648;
	max_ulong_int = 4294967295;
	min_ulong_int = 0;

	// percent
	printf(KMAG "\nDISPLAY PERCENT :\n" KNRM);
	ret1 = printf(KYEL "42%%\n" KNRM);
	ret2 = ft_printf(KCYN "42%%\n" KNRM);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);


	// char
	printf(KMAG "DISPLAY ONE CHAR :\n" KNRM);
	ret1 = printf(KYEL "--%c--\n" KNRM, 'c', 'c');
	ret2 = ft_printf(KCYN "--%c--\n" KNRM, 'c', 'c');
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	// str
	printf(KMAG "DISPLAY STRING :\n" KNRM);
	ret1 = printf(KYEL "%s\n" KNRM, "Hello world !");
	ret2 = ft_printf(KCYN "%s\n" KNRM, "Hello world !");
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "%s\n" KNRM, NULL);
	ret2 = ft_printf(KCYN "%s\n" KNRM, NULL);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	// int
	printf(KMAG "DISPLAY INT :\n" KNRM);
	ret1 = printf(KYEL "%i %d\n" KNRM, 42, -42);
	ret2 = ft_printf(KCYN "%i %d\n" KNRM, 42, -42);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "int max: %i\n" KNRM, max_int);
	ret2 = ft_printf(KCYN "int max: %i\n" KNRM, max_int);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "0 = %i\n" KNRM, 0);
	ret2 = ft_printf(KCYN "0 = %i\n" KNRM, 0);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "int min: %i\n" KNRM, min_int);
	ret2 = ft_printf(KCYN "int min: %i\n" KNRM, min_int);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	// uint
	printf(KMAG "DISPLAY UNSIGNED INT :\n" KNRM);
	ret1 = printf(KYEL "%u %u\n" KNRM, 42, -42);
	ret2 = ft_printf(KCYN "%u %u\n" KNRM, 42, -42);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "uint max: %u\n" KNRM, max_uint);
	ret2 = ft_printf(KCYN "uint max: %u\n" KNRM, max_uint);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "0 = %u\n" KNRM, 0);
	ret2 = ft_printf(KCYN "0 = %u\n" KNRM, 0);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "%u " KNRM, 10);
	printf("\n");
	ret2 = ft_printf(KCYN "%u " KNRM, 10);
	printf("\n");
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	// hex
	printf(KMAG "DISPLAY HEXADECIMAL :\n" KNRM);
	ret1 = printf(KYEL "lowercase: %x, uppercase: %X\n" KNRM, 42, 42);
	ret2 = ft_printf(KCYN "lowercase: %x, uppercase: %X\n" KNRM, 42, 42);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "lowercase: %x, uppercase: %X\n" KNRM, -42, -42);
	ret2 = ft_printf(KCYN "lowercase: %x, uppercase: %X\n" KNRM, -42, -42);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "hexadecimal int max: %x\n" KNRM, max_uint);
	ret2 = ft_printf(KCYN "hexadecimal int max: %x\n" KNRM, max_uint);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "hexadecimal 0: %x\n" KNRM, 0);
	ret2 = ft_printf(KCYN "hexadecimal 0: %x\n" KNRM, 0);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "hexadecimal int min: %x\n" KNRM, min_int);
	ret2 = ft_printf(KCYN "hexadecimal int min: %x\n" KNRM, min_int);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	// ptr
	printf(KMAG "DISPLAY POINTER :\n" KNRM);
	char *str = "home";
	ret1 = printf(KYEL "address: %p\n" KNRM, str);
	ret2 = ft_printf(KCYN "address: %p\n" KNRM, str);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);

	ret1 = printf(KYEL "null: %p\n" KNRM, NULL);
	ret2 = ft_printf(KCYN "null: %p\n" KNRM, NULL);
	if (ret1 == ret2)
		printf(KGRN "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	else
		printf(KRED "printf : %i || ft_printf : %i\n\n" KNRM, ret1, ret2);
	return (0);
}
