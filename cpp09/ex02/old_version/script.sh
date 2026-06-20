make re &&
make clean &&
clear &&
 ./PmergeMe `shuf -i 1-100 -n 33 | tr "\n" " "`
