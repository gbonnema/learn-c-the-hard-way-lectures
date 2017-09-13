make clean; make
echo Start test 1 ------------------
echo ./ex26 bada badb badc -o xx xy xz
./ex26 bada badb badc -o xx xy xz
echo End test 1 --------------------
echo Start test 2 ------------------
echo ./ex26 bada badb badc xx xy xz
./ex26 bada badb badc xx xy xz
echo End test 2 --------------------
