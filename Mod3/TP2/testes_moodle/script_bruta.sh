rm -f ../tempo/input/*
rm -f ../input/*
gcc -std=c99 generator.c -o gen
for i in {2..40..1}
do
  echo "$i" | ./gen > "bruta/$i"
done
