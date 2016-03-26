#include "test.h"

int	ft_test_lstnew(void)
{
	t_list	*elem;
	int		res;
	char	str[] = "Welcome";

	res = 0;
	ft_print_begin("ft_lstnew");
	elem = ft_lstnew((void const *)str, strlen(str));
	if (!elem)
		++res;
	else if (elem->content != (void *)str ||
			 elem->content_size != strlen(str) ||
			 elem->next != 0)
		++res;
	printf("Test");
	ft_print_status(res);
	return (ft_print_end(res));
}