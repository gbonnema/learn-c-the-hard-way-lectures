make clean; make
if [ $? -ne 0 ] ; then
	exit 1
fi
echo =============================================
echo Start test 1 ------------------
echo
echo Executing ./ex26 bada badb badc -o xx xy xz
echo
./ex26 bada badb badc -o xx xy xz
echo End test 1 --------------------
echo =============================================
echo Start test 2 ------------------
echo
echo Executing ./ex26 bada badb badc xx xy xz
echo
./ex26 bada badb badc xx xy xz
echo End test 2 --------------------
echo
