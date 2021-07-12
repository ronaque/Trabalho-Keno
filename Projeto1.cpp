#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <typeinfo>

#include <string.h>

#include "KenoBetIsaque.h"

void printVector(std::vector<int> vetor, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << vetor[i] << " ";
  }
  // std::cout << std::endl;
}

std::vector<int> bubbleSort(std::vector<int> vetor)
{
  int aux;
  for (int i = 0; i < (vetor.size()) - 1; i++)
  {
    for (int j = 0; j < (vetor.size()) - i - 1; j++)
    {
      if (vetor[j] > vetor[j + 1])
      {
        aux = vetor[j + 1];
        vetor[j + 1] = vetor[j];
        vetor[j] = aux;
      }
    }
  }
  return vetor;
}

std::vector<int> sorteio(std::vector<int> vetorSorteio)
{
  bool check;
  int n;
  // srand((unsigned)time(0));
  for (int i = 0; i < 20; i++)
  {
    do
    {
      check = true;
      n = rand() % 80 + 1;
      for (int j = 0; j < vetorSorteio.size(); j++)
      {
        if (vetorSorteio[j] == n)
        {
          check = false;
          break;
        }
      }
    } while (!check);
    vetorSorteio.push_back(n);
  }
  return vetorSorteio;
}

std::vector<int> comparador(std::vector<int> spots, std::vector<int> bets)
{
  std::vector<int> acertos;

  for (int i = 0; i < bets.size(); i++)
  {
    for (int k = 0; k < spots.size(); k++)
    {
      if (spots[k] == bets[i])
      {
        acertos.push_back(spots[k]);
      }
    }
  }

  return acertos;
}

int main(int argc, char *argv[])
{
  ///////////////////////////////////////// Variáveis /////////////////////////////////////////
  //Definição de variáveis inicais
  float creditoInicial;
  float creditoTotal;
  float apostaRodada;
  float retorno;
  float lucro;

  int nSortido;
  int nRodadas;

  std::vector<int> acertos;

  std::vector<int> spots;
  int indexSpots = 0;

  std::vector<int> sorteados;
  srand((unsigned)time(0));

  float playoffTable[15][16] = {{0, 3},
                                {0, 1, 9},
                                {0, 1, 2, 16},
                                {0, 0.5, 2, 6, 12},
                                {0, 0.5, 1, 3, 15, 50},
                                {0, 0.5, 1, 2, 3, 30, 75},
                                {0, 0.5, 0.5, 1, 6, 12, 36, 100},
                                {0, 0.5, 0.5, 1, 3, 6, 19, 90, 720},
                                {0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200},
                                {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800},
                                {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000},
                                {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000},
                                {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000},
                                {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500},
                                {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}};

  KenoBet keno;

  ///////////////////////////////////////// Leitura /////////////////////////////////////////

  //Recebendo o nome do arquivo
  char nameFile[20];
  strcpy(nameFile, argv[1]);

  std::cout << ">>> Lendo arquivo de apostas [" << nameFile << "], por favor aguarde..." << std::endl;
  std::cout << "-------------------------------------------------------------------" << std::endl;

#include "leitura.h"

  //Valor Aposta feita em cada rodada
  apostaRodada = creditoInicial / nRodadas;
  creditoTotal = creditoInicial;

  //Organização spots
  spots = bubbleSort(spots);
  // std::cout << "spots: ";
  // printVector(spots, spots.size());
  std::cout << std::endl;

  //////////////////////////////////////// Começo do jogo ////////////////////////////////////////
  std::cout << ">>> Aposta lida com sucesso!" << std::endl;
  std::cout << "  Você apostará um total de $" << creditoInicial << " Créditos." << std::endl;
  std::cout << "  Jogará um total de " << nRodadas << " rodadas, apostando $" << apostaRodada << " créditos por rodada" << std::endl;

  std::cout << std::endl;
  std::cout << "  Sua aposta tem " << spots.size() << " números, eles são: [ ";
  printVector(spots, spots.size());
  std::cout << "]" << std::endl;
  std::cout << "    ----------|---------" << std::endl;
  std::cout << "    Hits      | Retorno " << std::endl;
  for (int j = 0; j <= spots.size(); j++)
  {
    std::cout << "    " << j << "         | " << playoffTable[spots.size() - 1][j] << "        " << std::endl;
  }
  std::cout << "-------------------------------------------------------------------" << std::endl;

  ///////////////////////////////////////// Jogos /////////////////////////////////////////

  for (int k = 1; k <= spots.size(); k++)
  {
    ///Setar o jogador keno

    //Crédito do jogador
    keno.set_total_wage(creditoTotal);

    // std::cout << "Total wage: " << keno.get_total_wage() << std::endl;

    //Setar valor da aposta
    keno.set_betting_wage(apostaRodada);
    // std::cout << "Betting wage: " << keno.get_betting_wage() << std::endl;

    //Diminuir o valor da rodada da carteira do keno
    keno.subtract_total_wage(apostaRodada);

    //Spots do jogador
    for (int l; l < spots.size(); l++)
    {
      keno.add_number(spots[l]);
    }

    // std::cout << "Keno array: [ ";
    // for (int i = 0; i < keno.size(); i++)
    // {
    //   std::cout << keno.get_number(i);
    // }
    // std::cout << "]" << std::endl;

    ///Print inicial
    std::cout << "  Esta é a rodada #" << k << " de " << nRodadas << ", sua aposta é $" << apostaRodada << ". Boa sorte!" << std::endl;

    sorteados = sorteio(sorteados);
    sorteados = bubbleSort(sorteados);

    std::cout << "  Os números sorteados são: [ ";
    printVector(sorteados, sorteados.size());
    std::cout << "]" << std::endl;
    std::cout << std::endl;

    //Jogo
    acertos = comparador(spots, sorteados);

    std::cout << "  Você acertou os números [ ";
    printVector(acertos, acertos.size());
    std::cout << "], um total de " << acertos.size() << " hits de " << spots.size() << std::endl;

    retorno = apostaRodada * playoffTable[spots.size()][acertos.size()];

    std::cout << "  Sua taxa de retorno é " << playoffTable[spots.size()][acertos.size()] << ", assim você sai com: $" << retorno << std::endl;

    keno.add_total_wage(retorno);

    std::cout << "  Você possui um total de: $" << keno.get_total_wage() << std::endl;

    // std::cout << "Clear: [ ";
    // printVector(sorteados, sorteados.size());
    // std::cout << "]" << std::endl;
    sorteados.clear();
    creditoTotal = keno.get_total_wage();
    if (k < spots.size())
    {
      std::cout << "  -------------------------------------------------------------------" << std::endl;
    }
  }

  //Fim
  if ((keno.get_total_wage() - creditoInicial) < 0)
  {
    lucro = 0;
  }
  else
  {
    lucro = (keno.get_total_wage() - creditoInicial);
  }

  std::cout << ">>> Fim das rodadas!" << std::endl;
  std::cout << "-------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << "======= Sumário =======" << std::endl;
  std::cout << ">>> Você gastou um total de $" << creditoInicial << " créditos" << std::endl;
  std::cout << ">>> Hooray! você ganhou $" << lucro << " créditos!" << std::endl;
  std::cout << ">>> Você está saindo do jogo com um total de $" << keno.get_total_wage() << " créditos" << std::endl;
  return 0;
}