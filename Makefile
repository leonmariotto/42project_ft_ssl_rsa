# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Updated: 2021/03/03 08:08:46 by lmariott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ssl
CC ?= clang
CFLAGS ?= -Wall -Wextra -Werror -g3

SRC := src/main.c \
        src/exec_cmd.c \
        src/md5/build_msg.c \
        src/md5/md5.c \
        src/md5/get_md5.c \
        src/md5/md5_by_fd.c \
        src/md5/run_md5.c \
        src/md5/run_s_loop.c \
        src/md5/run_files_loop.c \
        src/md5/exit.c \
        src/sha256/run_sha256.c \
        src/sha256/sha256.c \
        src/sha256/get_sha256.c \
        src/sha256/sha256_by_fd.c \
        src/sha256/run_s_loop.c \
        src/sha256/run_files_loop.c \
        src/sha256/exit.c \
        src/base64/base64.c \
        src/base64/run_base64.c \
        src/base64/get_base64.c \
        src/base64/exit_base64.c \
        src/des-cbc/des-cbc.c \
        src/des-cbc/run_des-cbc.c \
        src/des-ecb/des-ecb.c \
        src/des-ecb/run_des-ecb.c \
        src/des-common/print_opt.c \
        src/des-common/pbkdf2.c \
        src/des-common/ask_paswd.c \
        src/des-common/gen_salt.c \
        src/des-common/get_des.c \
        src/des-common/des_getopt.c \
        src/des-common/ossl_pbkdf.c \
        src/des-common/des_blockey.c \
        src/des-common/tkey.c \
        src/des3-ecb/des3-ecb.c \
        src/des3-ecb/run_des3-ecb.c \
        src/des3-cbc/des3-cbc.c \
        src/des3-cbc/run_des3-cbc.c \
	src/genrsa/run_genrsa.c \
	src/rsa/run_rsa.c \
	src/rsa/getopt.c \
	src/rsa-common/get_random.c \
	src/rsa-common/gen_prime.c \
	src/rsa-common/euclide.c \
	src/rsa-common/gen_enckey.c \
	src/rsa-common/print_utils.c \
	src/rsa-common/rsa_printout.c \
	src/rsa-common/rsa_keyextract.c \
	src/rsa-common/pem.c \
	src/rsautl/run_rsautl.c \
	src/asn1/asn.c


HDR := libft/libft.h	

HDRDIR := inc/
LIBDIR := libft/

OBJ := $(SRC:.c=.o)
LIBFT := libft/libft.a
LIBS := $(LIBFT)

all: $(NAME) 

$(LIBFT):
	make -j 8 -C libft/

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS) -I$(HDRDIR) -I$(LIBDIR)

%.o: %.c $(HDR) Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -I$(HDRDIR) -I$(LIBDIR)

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
