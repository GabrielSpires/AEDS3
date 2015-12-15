for i in {4..20..1}
do
  time echo "$i" | ./tp -t 300 < "testes/10_$i.txt" > "tempo_lixo.txt"
done
