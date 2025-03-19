#include <iostream>
#include <cmath>
#include <fstream>

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

int main(){
  std::ofstream arquivo("saida.txt");

  int numero_de_pontos;
  std::cin >> numero_de_pontos;

  Ponto pontos[numero_de_pontos];   // Criado uma lista das coordenadas de cada ponto

  for(int i=0;i<numero_de_pontos;i++){   // Leitura das coordenadas de cada ponto
    std::cin >> pontos[i].x;
    std::cin >> pontos[i].y;
    pontos[i].was_visited = false;
  }

  int ponto_inicial = 39;   //Numero aleatorio que representa o primeiro ponto que vai se partir o caixeiro
  int ponto_atual = ponto_inicial;   // Variavel auxiliar para guardar o ponto atual em que vai se verificar a menor distancia para o proximo ponto
  float distancia_percorrida = 0;
  std::string rota_percorrida = "x";  // Comeca pelo ponto_atual
  pontos[ponto_atual].was_visited = true;

  arquivo << '(' << pontos[ponto_atual].x << ", " << pontos[ponto_atual].y << ")," << std::endl;
  
  int auxiliar = numero_de_pontos-1;
  while(auxiliar != 0){   // Calcula-se a distancia de todo percurso
    float menor_distancia_atual = 100000;
    int ponto_da_menor_distancia_atual;

    for(int i=0;i<numero_de_pontos;i++){
      if(pontos[i].was_visited == true)   //Ignora pontos que ja se passou por eles
        continue;

      float distancia_atual = distanciaEntrePontos(pontos[ponto_atual], pontos[i]);  // Calcula distancia entre dois pontos

      if(distancia_atual < menor_distancia_atual){   // Atualiza valor de menor_distancia e ponto_da_menor_distancia_atual
        menor_distancia_atual = distancia_atual;
        ponto_da_menor_distancia_atual = i;
      }
    }

    pontos[ponto_da_menor_distancia_atual].was_visited = true;
    ponto_atual = ponto_da_menor_distancia_atual;
    distancia_percorrida += menor_distancia_atual;
    arquivo << '(' << pontos[ponto_atual].x << ", " << pontos[ponto_atual].y << ")," << std::endl;    // Escreve no arquivo o ponto escolhido da menor distancia
    rota_percorrida += ", " + std::to_string(ponto_atual);
    auxiliar--;
  }

  // Fechamento do ciclo com a volta para o ponto_inicial
  distancia_percorrida += distanciaEntrePontos(pontos[ponto_atual], pontos[ponto_inicial]);
  arquivo << '(' << pontos[ponto_inicial].x << ", " << pontos[ponto_inicial].y << ")" << std::endl;    // Escreve no arquivo o ponto inicial novamente para fechar o ciclo
  rota_percorrida += ", " + std::to_string(ponto_inicial);

  arquivo << std::endl;
  arquivo << "rota: " << rota_percorrida << std::endl << std::endl;
  arquivo << "distancia: " << distancia_percorrida;
  arquivo.close();

  return 0;
}