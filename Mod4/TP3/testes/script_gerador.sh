for i in {4..50..2}
do
  echo "$i" | ./a.out 10 "$i" > "10_$i.txt"
done
