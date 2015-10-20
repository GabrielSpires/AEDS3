#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    ofstream txt;
    int numListas = 1;
    int numPalavras = 1, numPalavrasAux = 1;
    int tamPalavra = 1;
    string palavra;
    ostringstream input1, input2, input3;
    char letra;
    int dollynho, dispersao;
    dispersao = 10;

    string nomeTxt = ".txt";

    cout << "Listas a gerar: ";
    cin >> numListas;

    cout << "Qtd de palavras por lista: ";
    cin >> numPalavras;

    cout << "Tamanho das palavras: ";
    cin >> tamPalavra;

    numPalavrasAux = numPalavras;

    input1 << numListas;
    input2 << numPalavras;
    input3 << tamPalavra;

    nomeTxt = /*input1.str() + "_" + */input2.str()/* + "_" + input3.str() + "c" */+ nomeTxt;

    cout << nomeTxt << endl;

    txt.open(nomeTxt.c_str());
    txt << numListas << endl;
    
    while(numListas--){
        while(numPalavrasAux > 0){
            dollynho = (int)(numPalavras/(1+rand()%100));
            // tamPalavra = rand()%20 + 1;
            for(int i=0; i< tamPalavra; i++){
                 letra = 'a' + rand()%26;
                 palavra += letra;
            }

            txt << palavra;
            numPalavrasAux--;
            if(numPalavrasAux){
                txt << " ";
            }

            //dollynho = rand()%dollynho;
            //if((dollynho % 5 == 0) && numPalavrasAux > 0){
                
                // for (int i = 0; i < dollynho; i += rand()%10){
                //     if(numPalavrasAux <= 0) break;
                //     next_permutation(palavra.begin(),palavra.end());

                //     txt << palavra;
                //     numPalavrasAux--;
                //     if(numPalavrasAux){
                //         txt << " ";
                //     }
                // }
            // }
            palavra = "";
        }
        numPalavrasAux = numPalavras;
        txt << '\n';
    }
    txt << endl;
    return 0;
}