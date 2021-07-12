#pragma once
//Abrindo arquivo
std::ifstream myfile;
myfile.open(nameFile);

//Recebendo as variáveis do arquivo
std::string line;
std::stringstream ss;
std::string delimiter = " ";
size_t pos = 0;
if (myfile.is_open())
{
  for (int i = 0; i < 3; i++)
  {
    if (i == 0)
    {
      // getline(myfile, line);
      // ss << line;
      // ss >> creditoInicial;
      // ss.clear();
      myfile >> creditoInicial;
    }
    else if (i == 1)
    {
      // getline(myfile, line);
      // ss << line;
      // ss >> nRodadas;
      // ss.clear();
      myfile >> nRodadas;
    }
    else if (i == 2)
    {
      int a;
      while (!myfile.eof())
      {
        if (myfile >> a)
        {
          for (int k = 0; k < spots.size(); k++)
          {

            if (a == spots[k])
            {
              std::cout << "Erro: Numero repetido" << std::endl;
              return 0;
            }
          }
          spots.push_back(a);
          indexSpots++;
        }
        else
        {
          std::cout << "Erro: Tipo não aceito" << std::endl;
          return 0;
        }
      }
    }
  }
  //Exceção números repetidos
  if (indexSpots > 15)
  {
    std::cout << "Erro: Quantidade de numeros de apostas superior a 15" << std::endl;
    return 0;
  }
  myfile.close();
}
//Exceção Arquivo não encontrado
else
{
  std::cout << "Erro: Arquivo nao encontrado" << std::endl;
  return 0;
}