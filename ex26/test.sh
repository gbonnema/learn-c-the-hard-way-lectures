make clean; make
if [ $? -ne 0 ] ; then
	exit 1
fi
echo =============================================
echo Start test 1 ------------------
echo
echo Executing ./ex26 proxy cpu -o memory
echo
./ex26 Proxy Started -o memory
echo End test 1 --------------------
echo =============================================
echo Start test 2 ------------------
echo
echo Executing ./ex26 proxy cpu memory
echo
./ex26 Proxy Started
echo End test 2 --------------------
echo
