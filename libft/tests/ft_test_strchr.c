#include "test.h"

int	ft_test_strchr2(char const *s, int c)
{
	int		res;
	char	*res2;
	char	*res3;

	res = 0;
	res2 = ft_strchr(s, c);
	res3 = strchr(s, c);
	if (res2 != res3)
		++res;
	printf("Test : \"%s\" { %p - %p }", s, res2, res3);
	ft_print_status(res);
	return (res);
}

int	ft_test_strchr(void)
{
	int		res;
	char	*str = "Hello world !";

	res = 0;
	ft_print_begin("ft_strchr");
	res += ft_test_strchr2(str, '!');
	res += ft_test_strchr2(str, 0);
	res += ft_test_strchr2(str, 'H');
	res += ft_test_strchr2(str, 'z');
	return (ft_print_end(res));
}