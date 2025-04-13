/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:33:32 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:28:57 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handel_formats(char format, va_list args)
{
	int	ctrchar;

	ctrchar = 0;
	if (format == 'c')
		ctrchar += handel_c_and_prsnt_format((char)va_arg(args, int));
	else if (format == 's')
		ctrchar += handel_s_format(va_arg(args, char *));
	else if (format == 'p')
		ctrchar += handel_p_format((unsigned long)va_arg(args, void *));
	else if (format == 'd')
		ctrchar += handel_d_and_i_format(va_arg(args, int));
	else if (format == 'i')
		ctrchar += handel_d_and_i_format(va_arg(args, int));
	else if (format == 'u')
		ctrchar += handel_u_format((unsigned int)va_arg(args, int));
	else if (format == 'x')
		ctrchar += handel_x_format((unsigned long)va_arg(args, void *));
	else if (format == 'X')
		ctrchar += handel_x_upper_format((unsigned long)va_arg(args, void *));
	else if (format == '%')
		ctrchar += handel_c_and_prsnt_format('%');
	return (ctrchar);
}

int	process_format(const char *format, va_list args)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (-1);
			i++;
			n += handel_formats(format[i], args);
		}
		else
		{
			write(1, &format[i], 1);
			n++;
		}
		i++;
	}
	return (n);
}

int	ft_printf(const char *format, ...)
{
	int		n;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	n = process_format(format, args);
	va_end(args);
	return (n);
}
