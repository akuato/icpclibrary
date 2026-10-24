for f in cf naive gen;do g++ $f.cpp -O2 -o $f||exit;done
for((i=1;;i++));do ./gen>in;./cf<in>o1||break;./naive<in>o2||break;cmp -s o1 o2||break;done
echo case $i;cat in o1 o2