#include <iostream>
#include <cmath>
#include <fstream>
#include <deque>

struct Ponto{
  bool was_visited;
  float x;
  float y;
};

float distanciaEntrePontos(const Ponto& ponto_a, const Ponto& ponto_b){
  float eixo_x = ponto_a.x - ponto_b.x;
  float eixo_y = ponto_a.y - ponto_b.y;
  return sqrt(eixo_x*eixo_x + eixo_y*eixo_y);
}

float acharMenorDistanciaELocalDeAdicao(const float& distancia_ao_primeiro_ponto, const float& distancia_ao_ultimo_ponto, char& local_de_adicao_do_ponto){
  if(distancia_ao_primeiro_ponto < distancia_ao_ultimo_ponto){
    local_de_adicao_do_ponto = 'i';
    return distancia_ao_primeiro_ponto;
  }
  local_de_adicao_do_ponto = 'f';
  return distancia_ao_ultimo_ponto;
}

int main(){
  std::ofstream arquivo("saida.txt");

  int numero_de_pontos;
  std::cin >> numero_de_pontos;
  
  Ponto pontos[numero_de_pontos];  // Criado uma lista das coordenadas de cada ponto
  std::deque<Ponto> sequencia_percorrida_pelos_pontos;

  for(int i=0;i<numero_de_pontos;i++){   // Leitura das coordenadas de cada ponto
    std::cin >> pontos[i].x;
    std::cin >> pontos[i].y;
    pontos[i].was_visited = false;
  }

  int ponto_inicial = 0;   //Numero aleatorio que representa o primeiro ponto que vai se partir o caixeiro
  float distancia_percorrida = 0;
  pontos[ponto_inicial].was_visited = true;   // Seta primeiro ponto como visitado
  sequencia_percorrida_pelos_pontos.push_back(pontos[ponto_inicial]);   // Comeca a ordenar os pontos na sequencia
  
  int primeiro_ponto_da_sequencia = ponto_inicial;   // Variavel auxiliar para guardar o ponto atual em que vai se verificar a menor distancia para o proximo ponto
  int ultimo_ponto_da_sequencia;    // Segunda variavel auxiliar que vai verificar a menor distancia porem analisando o ponto que esta no inicio da rota

  // Acha-se a primeira distancia entre dois pontos e seta o segundo numero da sequencia, que sera o ultimo_ponto_da_sequencia no comeco do programa
  for(int i=0;i<numero_de_pontos;i++){
    int menor_distancia = 100000;

    if(pontos[i].was_visited == true)
      continue;

    float distancia_entre_pontos = distanciaEntrePontos(pontos[ponto_inicial], pontos[i]);

    if(distancia_entre_pontos < menor_distancia){
      menor_distancia = distancia_entre_pontos;
      ultimo_ponto_da_sequencia = i;
    }
  }

  sequencia_percorrida_pelos_pontos.push_back(pontos[ultimo_ponto_da_sequencia]); // Seta o segundo ponto da sequencia de forma ordenada
  
  // Calcula a distancia entre o primeiro_ponto_da_sequencia e os demais e o ultimo_ponto_da_sequencia e os demais simultaneamente, achando a menor entre elas
  int auxiliar = numero_de_pontos-2;  // Menos 2 pois 2 pontos ja foram encontrados, o primeiro e o ultimo da sequencia
  while(auxiliar != 0){
    float menor_distancia = 100000;
    int index_do_ponto_mais_proximo;
    char local_de_adicao_do_ponto;  // Se for i = inicio, se for f = fim

    for(int i=0;i<numero_de_pontos;i++){
      if(pontos[i].was_visited == true)   //Ignora pontos que ja se passou por eles
        continue;

      // Calcula distancias para o primeiro e para o ultimo ponto da sequencia
      float distancia_ao_primeiro_ponto = distanciaEntrePontos(pontos[primeiro_ponto_da_sequencia], pontos[i]);
      float distancia_ao_ultimo_ponto = distanciaEntrePontos(pontos[ultimo_ponto_da_sequencia],pontos[i]);

      // Verifica se uma das duas distancia eh menor que a menor_distancia atual
      if(distancia_ao_primeiro_ponto < menor_distancia || distancia_ao_ultimo_ponto < menor_distancia){
        // Acha a menor distancia entre os dois pontos e define o local onde sera adicionada
        menor_distancia = acharMenorDistanciaELocalDeAdicao(distancia_ao_primeiro_ponto,distancia_ao_ultimo_ponto, local_de_adicao_do_ponto);
        index_do_ponto_mais_proximo = i;
      }
    }

    pontos[index_do_ponto_mais_proximo].was_visited = true;   // Seta o ponto de menor distancia como visitado
    distancia_percorrida += menor_distancia;    // Contabiliza a distancia percorrida ate esse ponto

    // Atualiza o novo ponto para a proxima iteracao do loop
    if(local_de_adicao_do_ponto == 'i'){
      sequencia_percorrida_pelos_pontos.push_front(pontos[index_do_ponto_mais_proximo]);
      primeiro_ponto_da_sequencia = index_do_ponto_mais_proximo;
    }
    else if(local_de_adicao_do_ponto == 'f'){
      ultimo_ponto_da_sequencia = index_do_ponto_mais_proximo;
      sequencia_percorrida_pelos_pontos.push_back(pontos[index_do_ponto_mais_proximo]);
    }

    auxiliar--;
  }

  // Escreve-se no arquivo a sequencia ordenada de pontos
  arquivo << '(' << sequencia_percorrida_pelos_pontos[0].x << ", " << sequencia_percorrida_pelos_pontos[0].y << ")";
  for(int i=1;i<sequencia_percorrida_pelos_pontos.size();i++){
    arquivo << ", (" << sequencia_percorrida_pelos_pontos[i].x << ", " << sequencia_percorrida_pelos_pontos[i].y << ")";
  }

  arquivo << std::endl;
  arquivo << "distancia: " << distancia_percorrida;
  arquivo.close();

  return 0;
}