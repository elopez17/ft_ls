/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 00:06:40 by eLopez            #+#    #+#             */
/*   Updated: 2017/08/01 14:08:54 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>

typedef struct	s_flags
{
	int				width;
	int				precision_num;
	unsigned int	precision : 1;
	unsigned int	alter : 1;
	unsigned int	zero : 1;
	unsigned int	left_adj : 1;
	unsigned int	sign : 1;
	unsigned int	space : 1;
	unsigned int	h : 1;
	unsigned int	hh : 1;
	unsigned int	l : 1;
	unsigned int	ll : 1;
	unsigned int	j : 1;
	unsigned int	z : 1;
}				t_flags;

typedef union	u_spec
{
	int					dval;
	long				lval;
	long long			llval;
	intmax_t			imax;
	uintmax_t			uimax;
	unsigned long long	ullval;
	unsigned char		cval;
	wint_t				c_val;
	char				*sval;
	wchar_t				*s_val;
	void				*pval;
	double				lfval;
}				t_spec;

int				ft_printf(const char *format, ...);
t_flags			pf_conv_flags(const char **format);
void			pf_conv_width(const char **format, t_flags *flag, va_list *ap);
void			pf_conv_precision(const char **format, t_flags *flag, \
		va_list *ap);
void			pf_conv_length(const char **format, t_flags *flag);
int				pf_conv_specifier(const char **format, t_flags *flag, \
		va_list *ap);
int				pf_conv_specif_2(const char **format, t_flags *flag, \
		va_list *ap);
int				pf_invalid_spec(va_list *ap);
int				pf_invalid_flag(va_list *ap);
int				pf_invalid_prec(va_list *ap);
int				pf_spec_di(t_flags *flag, va_list *ap);
int				pf_spec_cs(t_flags *flag, va_list *ap, char c);
int				pf_spec_ouxz(t_flags *flag, va_list *ap, char c);
char			*pf_o_conv(t_flags *flag, unsigned long long dec);
char			*pf_x_conv(t_flags *flag, unsigned long long dec, char c);
char			*pf_o_uintmax(t_flags *flag, uintmax_t dec);
char			*pf_x_uintmax(t_flags *flag, uintmax_t dec, char c);
int				pf_int(t_flags *flag, va_list *ap);
int				pf_long(t_flags *flag, va_list *ap);
int				pf_long_long(t_flags *flag, va_list *ap);
int				pf_ulong_long(t_flags *flag, va_list *ap, char c);
int				pf_intmax_t(t_flags *flag, va_list *ap);
int				pf_uintmax_t(t_flags *flag, va_list *ap, char c);
int				pf_wint_t(t_flags *flag, va_list *ap);
int				pf_wchar_t(t_flags *flag, va_list *ap);
int				pf_char(t_flags *flag, va_list *ap);
int				pf_str(t_flags *flag, va_list *ap);
int				pf_color(const char **format, va_list *ap);
int				pf_at_fd(va_list *ap);
int				pf_itobi(t_flags *flag, va_list *ap);
int				pf_atom(va_list *ap);
int				pf_float(t_flags *flag, va_list *ap);
int				pf_iso_8601(va_list *ap);

#endif
