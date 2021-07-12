#pragma once

#include <vector>

class KenoBet
{

public:
  //! Creates an empty Keno bet.
  KenoBet() : m_wage(0){/* empty */};

  /*
  Adiciona um número às apostas, somente se o número não estiver lá.
  @param spot_ O número que deseja incluir na aposta
  @return T se o número escolhido for inserido; F senão
  */
  bool add_number(int spot_)
  {
    m_spots.push_back(spot_);
    return true;
  };

  /*
  Retorna o número da aposta do jogador a partir de um index
  */

  int get_number(int index)
  {
    return m_spots[index];
  }

  /* 
  Seta o crédito que o jogador está apostando.
  @param wage_ é o crédito
  @return T se tem crédito acima de zero; F se não
  */
  bool set_betting_wage(float wage_)
  {
    m_wage = wage_;
    if (m_wage > 0)
      return true;
    else
      return false;
  };

  bool set_total_wage(float wage_)
  {
    t_wage = wage_;
    if (t_wage > 0)
      return true;
    else
      return false;
  }

  void add_total_wage(float wage_)
  {
    t_wage = t_wage + wage_;
  }

  void subtract_total_wage(float wage_)
  {
    t_wage = t_wage - wage_;
  }

  //Reseta a aposta para estado vazio
  void reset(void);

  /*
  Recupera a carteira do jogador na aposta
  @return o valor da carteira
  */
  float get_total_wage(void) const
  {
    return t_wage;
  }

  float get_betting_wage(void) const
  {
    return m_wage;
  }
  /*
  Retorna o número de apostas do jogador
  @return número de apostas presente na aposta
  */
  size_t size(void) const
  {
    return m_spots.size();
  }

  /*
  Determina quantas apostas combina com os hits passados por argumento
  @param hits_ lista os hits escolhidos randomicamente
  @return um vetor com a lista de hits 
  */
  std::vector<int>
  get_hits(const std::vector<int> &hits_) const;

  /*
  Retorna um vector<spot_type> com os spots que o jogador escolheu
  @return p vector<spot_type> com os spots do player
  */
  std::vector<int> get_spots(void) const
  {
    return m_spots;
  }

private:
  std::vector<int> m_spots; //Apostas do jogador
  float m_wage;             //Créditos do jogador
  float t_wage;             //Crédito total do jogador
};