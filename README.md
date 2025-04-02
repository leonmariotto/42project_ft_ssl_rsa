# ft_ssl

Openssl-like cryptographic utility from scratch.
Run make to compile.

## Usage

./ft_ssl command [command opts] [command args]

Standard commands:
rsa
genrsa:
    -i [FILE]: input file
    -o [FILE]: output file
rsautl

Message Digest commands:
md5:
sha256:
    -q: quiet mode
    -r: reverse the format of the output
    -p: echo STDIN to STDOUT and append the digest
    -s [STRING]: input string
    -s [STRING]: input string

Cipher commands:
base64:
    -d: decryption
    -e: encryption
    -i [FILE]: input file
    -o [FILE]: output file
des-ecb:
des-cbc:
des3-ecb:
des3-cbc:
    -d: decryption
    -e: encryption
    -pbkdf2: use pbkdf2 for password derivation
    -nosalt: no salt mode
    -iter [NB]: number of iteration
    -p [PASSWORD]: password string
    -iv [HEX STRING]: initialization vector in hex
    -k [HEX STRING]: key in hex
    -i [FILE]: input file
    -o [FILE]: output file

