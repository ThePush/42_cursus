/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:02:25 by jsemel            #+#    #+#             */
/*   Updated: 2021/12/09 15:54:43 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

static int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[count] != '\0')
	{
		write(1, &str[count], 1);
		count++;
	}
	return (count);
}

static int	ft_putnbr(long long nb)
{
	unsigned long long	n;
	int					count;

	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		n = -nb;
		count++;
	}
	else
		n = nb;
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
	}
	n = n % 10 + 48;
	count += write(1, &n, 1);
	return (count);
}

static int	ft_puthex(unsigned long nb, int uplow, int p)
{
	char	*base;
	int		count;

	count = 0;
	if (p)
		count += write(1, "0x", 2);
	if (uplow)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nb > 15)
		count += ft_puthex(nb / 16, uplow, 0);
	count += write(1, &base[nb % 16], 1);
	return (count);
}

static int	analyse_and_print(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == '%')
		count += write(1, "%", 1);
	else if (c == 'c')
	{
		c = va_arg(args, int);
		count += write(1, &c, 1);
	}
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		count += ft_puthex(va_arg(args, unsigned long), 0, 1);
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_putnbr(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0, 0);
	else if (c == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1, 0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!format)
		return (0);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			count += analyse_and_print(format[i + 1], args);
			i++;
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
