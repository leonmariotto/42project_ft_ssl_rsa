/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:23:32 by lmariott          #+#    #+#             */
/*   Updated: 2021/10/20 18:17:10 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "consts_base64.h"
#include <stdio.h>

int b64_isvalidchar(char c)
{
	if ((c >= '0' && c <= '9')
        || (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || c == '+' || c == '/' || c == '='
        || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int                 b64_parse_len(const char *input, int len)
{
    int i;
    int c;

    i = 0;
    c = 0;
    while (i < len)
    {
        if (!b64_isvalidchar(input[i]))
            return (0);
        if (input[i] != ' ' && input[i] != '\n')
            c++;
        ++i;
    }
    return (c);
}

int                 b64_parse_input(const char *oinput, char **input, int *len)
{
    int     plen;
    char    *new;
    int     i;
    int     j;

    if (!(plen = b64_parse_len(oinput, *len)))
        return (0);
    if (plen % 4 != 0)
        return (0);
    if (!(new = malloc(plen)))
        return (0);
    i = 0;
    j = 0;
    while (i < *len)
    {
        if (oinput[i] != ' ' && oinput[i] != '\n')
            new[j++] = oinput[i];
        i++;
    }
    *len = plen;
    *input = new;
    return (1);
}

int                 base64_decrypt(void **ptr, const u_int8_t *oinput,
                            int *len)
{
    char        *res;
    u_int32_t       cast;
    int         i;
    int         j;
    u_int8_t        *input;


    input = NULL;
    if (!(b64_parse_input((char*)oinput, (char **)&input, len)))
        return (0);
    if (!(res = (char *)malloc((((*len / 4) * 3) / 4 + 1) * 4)))
        return (0);
    i = 0;
    j = 0;
    while (i < *len)
    {
        cast = b64invs[input[i] - 43];
        cast = cast << 6 | b64invs[input[i + 1] - 43];
        cast = input[i + 2] == '=' ? cast << 6 : (cast << 6) |
                            b64invs[input[i + 2] - 43];
        cast = input[i + 3] == '=' ? cast << 6 : (cast << 6) |
                            b64invs[input[i + 3] - 43];
        res[j++] = (cast >> 16) & 0xFF;
        if (input[i + 2] != '=')
	{
		//fprintf(stderr, "j = %d\n", j);
            res[j++] = (cast >> 8) & 0xFF;
	}
        if (input[i + 3] != '=')
            res[j++] = cast & 0xFF;
        i += 4;
    }
    //fprintf(stderr, "j = %d\n", j);
    free(input);
    *ptr = res;
//    *len = (((*len / 4) * 3) / 4) * 4;
    *len = j;
    //fprintf(stderr, "len = %d\n", *len);
    return (1);
}

int                 base64_encrypt(void **ptr, const unsigned char *input, int *len)
{
    char        *res;
    unsigned char        buf[4];
    int         i;
    int         j;
    u_int32_t   cast;

    if (!(res = (char *)malloc(((*len / 3) + 1) * 4)))
        return (0);
    i = 0;
    j = 0;
    while (i < *len)
    {
        ft_bzero(buf, 4);
        ft_memcpy(buf, input + i, (*len - i > 3 ? 3 : *len - i));
        cast = (u_int32_t)buf[0];
        cast = cast << 8 | buf[1];
        cast = cast << 8 | buf[2];
        res[j++] = b64chars[cast >> 18 & 0x3F];
        res[j++] = b64chars[cast >> 12 & 0x3F];
        if (*len - i < 2)
            res[j++] = '=';
        else
            res[j++] = b64chars[cast >> 6 & 0x3F];
        if (*len - i < 3)
        {
            res[j++] = '=';
            *ptr = res;
            *len = j;
            return (1);
        }
        else
            res[j++] = b64chars[cast & 0x3F];
        i += 3;
    }
    *ptr = res;
    *len = j;
    return (1);
}

int                 base64(void **ptr, const unsigned char *input, int *len, char mod)
{
    int     r;

    if (!mod)
        r = base64_encrypt(ptr, input, len);
    else
        r = base64_decrypt(ptr, input, len);
    return (r);
}
