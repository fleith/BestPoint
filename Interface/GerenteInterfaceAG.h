#ifndef GERENTE_INTERFACE_AG_H
#define GERENTE_INTERFACE_AG_H


enum TipoCross {SEQUENCIAL= 0,ALEATORIO= 1};
enum TipoSelecao {ELITISMO= 0,ROLETA =1,CLASSIFICACAO= 2,ESTACIONARIA= 3,ALVAROS= 4};

class GI
{
public:
   //Chart
   static void AdicionaFitnessMelhorPiorEMediaIndividuo(double melhor,double pior,double media);
   static void LimpaGraficoMelhorPiorIndividuo();
   //Image
   static void LimpaTelaPontos();
   static void AdicionaPontoBase(double x,double y);
   static void AdicionaPontoIndividuo(double x,double y);

   static void AdicionaPontoMelhorIndividuo(double x,double y);
   static void AdicionaPontoPiorIndividuo(double x,double y);
   //Metodo seleção

   //Taxa Crossover
   static int PercentualCrossover();
   //Taxa Mutacao
   static int PercentualMutacao();
   //Tamanho populacao
   static int TamanhoPopulacao();
   //Número máximo de gerações
   static int NumeroMaximoDeGeracoes();

   static int ValorMaximoEixoX();
	static int ValorMaximoEixoY();
	static int ValorMinimoEixoX();
	static int ValorMinimoEixoY();

   static int NumeroDePontosBase();

   static double FatorDistribuicao();
   static double FatorDistancia();

   static int AlturaJanelaDesenho();
   static int LarguraJanelaDesenho();

   static void AtualizaInformacoesJanela();

   static TipoCross TipoDeCruzamento();
   static TipoSelecao TipoDeSelecao();

   //
   static void InicializaAplicacao();

   static void GeraPopulacaoAutomatica();
   static void GeraPopulacaoManual();

   static void ExecutaMaisUmaGeracao();
   static void ExecutaMaisDezGeracoes();
   static void ExecutaMaisCemGeracoes();
   static void ExecutaAteUltimaGeracao();

   static void GeraPontosBase();


private:
   GI();
};

#endif //GERENTE_INTERFACE_AG_H
 