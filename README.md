# ft_ssl

Openssl-like cryptographic utility from scratch. <br>
Run make to compile. <br>

## Usage

./ft_ssl command [command opts] [command args] <br>

Standard commands: <br>
rsa <br>
genrsa: <br>
    -i [FILE]: input file <br>
    -o [FILE]: output file <br>
rsautl <br>

Message Digest commands: <br>
md5: <br>
sha256: <br>
    -q: quiet mode <br>
    -r: reverse the format of the output <br>
    -p: echo STDIN to STDOUT and append the digest <br>
    -s [STRING]: input string <br>
    -s [STRING]: input string <br>

Cipher commands: <br>
base64: <br>
    -d: decryption <br>
    -e: encryption <br>
    -i [FILE]: input file <br>
    -o [FILE]: output file <br>
des-ecb: <br>
des-cbc: <br>
des3-ecb: <br>
des3-cbc: <br>
    -d: decryption <br>
    -e: encryption <br>
    -pbkdf2: use pbkdf2 for password derivation <br>
    -nosalt: no salt mode <br>
    -iter [NB]: number of iteration <br>
    -p [PASSWORD]: password string <br>
    -iv [HEX STRING]: initialization vector in hex <br>
    -k [HEX STRING]: key in hex <br>
    -i [FILE]: input file <br>
    -o [FILE]: output file <br>

