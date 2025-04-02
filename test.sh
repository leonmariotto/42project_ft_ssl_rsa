echo "\n\nDo simple test for des encryption\n\n"

echo "coucou" > data
echo ./ft_ssl genrsa -o k
./ft_ssl genrsa -o k
echo ./ft_ssl rsa -in k -des-ecb -out k.ecb
./ft_ssl rsa -in k -des-ecb -out k.ecb
echo ./ft_ssl rsa -in k -des-cbc -out k.cbc
./ft_ssl rsa -in k -des-cbc -out k.cbc

echo ./ft_ssl rsa -in k -passin "coucou" -des-cbc -out k.cbc.pass
./ft_ssl rsa -in k -passout "c" -des-cbc -out k.cbc.pass
echo ./ft_ssl rsautl -in data -inkey k.cbc.pass -out data.enc3
./ft_ssl rsautl -in data -inkey k.cbc.pass -out data.enc3

echo ./ft_ssl rsautl -in data -inkey k.des -out data.enc
./ft_ssl rsautl -in data -inkey k.ecb -out data.enc
echo ./ft_ssl rsautl -in data.enc -inkey k.des -out data.dec
./ft_ssl rsautl -in data.enc -inkey k.ecb -out data.dec -d
echo ./ft_ssl rsautl -in data -inkey k -out data.enc2
./ft_ssl rsautl -in data -inkey k -out data.enc2
echo diff data.enc data.dec
diff data data.dec
echo diff data.enc data.enc2
diff data.enc data.enc2
echo diff data.enc data.enc3
diff data.enc data.enc3

echo ./ft_ssl rsa -in k.cbc -passin coucou -noout -text
./ft_ssl rsa -in k.cbc -passin c -noout -text
echo ./ft_ssl rsautl -in data -inkey k.des -out data.enc
./ft_ssl rsautl -in data -inkey k.cbc -out data.enc
echo ./ft_ssl rsautl -in data.enc -inkey k.des -out data.dec
./ft_ssl rsautl -in data.enc -inkey k.cbc -out data.dec -d
echo ./ft_ssl rsautl -in data -inkey k -out data.enc2
./ft_ssl rsautl -in data -inkey k -out data.enc2
echo diff data.enc data.dec
diff data data.dec
echo diff data.enc data.enc2
diff data.enc data.enc2

rm data.enc data.enc3 data.enc2 data.dec data k k.des


echo "\n\nDo simple test for genrsa\n\n"
echo ./ft_ssl genrsa -i Makefile -o k
./ft_ssl genrsa -i Makefile -o k
echo ./ft_ssl genrsa -i Makefile -o kk
./ft_ssl genrsa -i Makefile -o kk
echo ./ft_ssl genrsa -o ok
./ft_ssl genrsa -o ok
echo openssl rsa -in ok -text
openssl rsa -in ok -text
echo diff k kk
diff k kk
rm k kk ok

echo "\n\nDo simple test for rsa\n\n"
./ft_ssl genrsa -o k
echo TOCHECK: ./ft_ssl rsa -in k -noout
./ft_ssl rsa -in k -noout
echo TOCKECK: ./ft_ssl rsa -in k -noout -text
./ft_ssl rsa -in k -noout -text
echo TOCKECK: ./ft_ssl rsa -in k -noout -modulus
./ft_ssl rsa -in k -noout -modulus
echo ./ft_ssl rsa -in k -noout -check
./ft_ssl rsa -in k -noout -check
rm k


echo "\n\nDo test for pub key\n\n"
./ft_ssl genrsa -o k
echo coucou > data
echo ./ft_ssl rsa -in k -pubout -out k.pub
./ft_ssl rsa -in k -pubout -out k.pub
echo openssl asn1parse -in k.pub
openssl asn1parse -in k.pub
echo ./ft_ssl rsautl -in data -inkey k.pub -pubin -out data.enc
./ft_ssl rsautl -in data -inkey k.pub -pubin -out data.enc
echo ./ft_ssl rsautl -in data -inkey k -decrypt -out data.dec -hexdump
./ft_ssl rsautl -in data.enc -inkey k -decrypt -out data.dec -hexdump
echo diff data data.dec
diff data data.dec
echo ./ft_ssl rsa -in k.pub -pubin -text -noout
./ft_ssl rsa -in k.pub -pubin -text -noout
echo ./ft_ssl rsa -in k.pub -pubin -text
./ft_ssl rsa -in k.pub -pubin -text


rm k k.pub data data.dec data.enc





##export VALGRIND="valgrind --leak-check=full "
#export VALGRIND="valgrind "
##export VALGRIND=" "
##
#echo "\n\nGENERATE SOME KEY, ENCRYPT IT, DECRYPT IT\n\n"
#
#
#echo $VALGRIND ./ft_ssl genrsa -o key
#$VALGRIND ./ft_ssl genrsa -o key
#echo $VALGRIND ./ft_ssl rsa -in key -des-ecb -passout coucou -out key.ecb
#$VALGRIND ./ft_ssl rsa -in key -des-ecb -passout coucou -out key.ecb
#echo $VALGRIND ./ft_ssl rsa -in key -out -passout coucou -out key.cbc
#$VALGRIND ./ft_ssl rsa -in key -des-cbc -passout coucou -out key.cbc
##./ft_ssl rsa -in key -text -noout
##./ft_ssl rsa -in key.ecb -text -out key.ecb.dec
##./ft_ssl rsa -in key.cbc -text -out key.cbc.dec
#echo $VALGRIND ./ft_ssl rsa -in key -text -noout
#$VALGRIND ./ft_ssl rsa -in key -text -noout
#echo $VALGRIND ./ft_ssl rsa -in key.ecb -passin coucou -text -out key.ecb.dec
#$VALGRIND ./ft_ssl rsa -in key.ecb -passin coucou -text -out key.ecb.dec
#echo $VALGRIND ./ft_ssl rsa -in key.cbc -passin coucou -text -out key.cbc.dec
#$VALGRIND ./ft_ssl rsa -in key.cbc -passin coucou -text -out key.cbc.dec
#diff key key.ecb.dec
#diff key key.cbc.dec
##rm key.ecb.dec
##rm key.cbc.dec
#
#
#echo "\n\n Encrypt some stuff \n\n"
#
#echo -n "test" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#echo -n "coucou" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#echo -n "merde" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#echo -n "cafe?" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#echo -n "orange" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#
#echo -n "lol" > p
#$VALGRIND ./ft_ssl rsautl -inkey key.ecb -pass coucou -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey key.ecb -pass coucou -in c -out d -decrypt
#diff d p
#
#echo -n "ahaha" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsa -in k -text -pubout -out k.pub
#$VALGRIND ./ft_ssl rsautl -inkey k.pub -pubin -in p -out c -hexdump
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt -hexdump
#diff d p
#
#echo -n "cafeeeeeeeeeeeeeeeeeeeeee?" > p
#$VALGRIND ./ft_ssl genrsa -o k #-i ft_ssl
#$VALGRIND ./ft_ssl rsautl -inkey k -in p -out c
#$VALGRIND ./ft_ssl rsautl -inkey k -in c -out d -decrypt
#diff d p
#
#rm d p k c
#rm k*
