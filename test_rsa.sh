echo "coucou" > data
echo ./ft_ssl genrsa -o k
./ft_ssl genrsa -o k
echo ./ft_ssl rsa -in k -des-cbc -out k.des
./ft_ssl rsa -in k -des-ecb -out k.des
echo ./ft_ssl rsautl -in data -inkey k.des -out data.enc
./ft_ssl rsautl -in data -inkey k.des -out data.enc
echo ./ft_ssl rsautl -in data.enc -inkey k.des -out data.dec
./ft_ssl rsautl -in data.enc -inkey k.des -out data.dec -d
echo diff data.enc data.dec
diff data data.dec
rm data.enc data.dec data k k.des



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
