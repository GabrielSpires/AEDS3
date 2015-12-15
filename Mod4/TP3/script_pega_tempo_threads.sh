for i in {2..20..2}
do
  time echo "$i" | ./tp -t "$i" < "testes/10_20.txt" > "tempo_lixo.txt"
done
