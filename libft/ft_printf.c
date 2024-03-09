/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:10:23 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:20:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* ************************************************************************** */
/*  ft_parse: Takes a string and a pointer to the argument list.              */
/*            Loop through the string when it encounters the % flag           */
/*            if the flag is a valid type, print the argument.                */
/*            Otherwise, print the usual character.                           */
/*            Returns the number of output characters.                        */
/* ************************************************************************** */
static int	ft_parse(char *str, va_list args);

/* ************************************************************************** */
/*  ft_print_arg: Takes the flag type and pointer to the argument list        */
/*                It calls the output fucntion based on the flag type         */
/*                through accessing current variadic function variable        */
/*                and then pointing to next one                               */
/*                Returns the number of output characters.                    */
/* ************************************************************************** */
static int	ft_print_arg(char type, va_list args);

/* ************************************************************************** */
/*  ft_printf: Takes a constant string of format and arguments,               */
/*             output a formatted string on stdout.                           */
/*             Returns the number of output characters.                       */
/* ************************************************************************** */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	char	*str;

	if (!format || *format == '\0')
		return (0);
	str = ft_strdup(format);
	if (!str || *str == '\0')
		return (0);
	count = 0;
	va_start(args, format);
	count += ft_parse(str, args);
	va_end(args);
	free(str);
	return (count);
}

static int	ft_parse(char *str, va_list args)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			if (ft_istype(str[i + 1]))
			{
				count += ft_print_arg(str[i + 1], args);
				i++;
			}
		}
		else
			count += ft_print_c(str[i]);
	}
	return (count);
}

static int	ft_print_arg(char type, va_list args)
{
	int	count;

	count = 0;
	if (type == '%')
		count += ft_print_c('%');
	else if (type == 'c')
		count += ft_print_c(va_arg(args, int));
	else if (type == 's')
		count += ft_print_str(va_arg(args, const char *));
	else if (type == 'd' || type == 'i')
		count += ft_print_digit(va_arg(args, int));
	else if (type == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), ISLOWER);
	else if (type == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), ISUPPER);
	else if (type == 'u')
		count += ft_print_unsigned_dec(va_arg(args, unsigned int));
	else if (type == 'p')
		count += ft_print_ptr((unsigned long int)va_arg(args, void *));
	return (count);
}
