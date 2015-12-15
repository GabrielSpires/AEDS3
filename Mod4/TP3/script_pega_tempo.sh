for i in {4..20..2}
do
  time echo "$i" | ./tp -t 300 < "testes/10_$i.txt" > "tempo_lixo.txt"
done
