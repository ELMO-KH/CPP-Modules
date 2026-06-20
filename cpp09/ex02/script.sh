#!/bin/sh

N=${1:-33}
MAX=${2:-100000}

make re >/dev/null || exit 1

VALUES=$(shuf -i 1-"$MAX" -n "$N" | tr "\n" " ")
OUTPUT=$(./PmergeMe $VALUES)
COMPARISONS=$(printf "%s\n" "$OUTPUT" | awk -F': ' '/Comparisons made with std::vector/{print $2; exit}')

LOWER_BOUND=$(awk -v n="$N" '
function ceil(x) {
	return (x <= int(x) + 0.000000001) ? int(x) : int(x) + 1
}
BEGIN {
	sum = 0
	for (i = 1; i <= n; i++)
		sum += log(i) / log(2)
	print ceil(sum)
}')

WORST_CASE=$(awk -v n="$N" '
function ceil(x) {
	return (x <= int(x) + 0.000000001) ? int(x) : int(x) + 1
}
BEGIN {
	sum = 0
	for (i = 1; i <= n; i++)
		sum += ceil(log((3 * i) / 4) / log(2))
	print sum
}')

printf "%s\n" "$OUTPUT"
printf "\nPDF comparison range for n=%s:\n" "$N"
printf "  lower bound ceil(log2(n!)) : %s\n" "$LOWER_BOUND"
printf "  Ford-Johnson worst F(n)    : %s\n" "$WORST_CASE"

if [ -z "$COMPARISONS" ]; then
	printf "  program comparisons        : not printed (already sorted or error)\n"
elif [ "$COMPARISONS" -le "$WORST_CASE" ]; then
	printf "  program comparisons        : %s OK (<= F(n))\n" "$COMPARISONS"
else
	printf "  program comparisons        : %s TOO HIGH (> F(n))\n" "$COMPARISONS"
fi

make clean >/dev/null
