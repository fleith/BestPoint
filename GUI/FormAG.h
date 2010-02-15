//---------------------------------------------------------------------------

#ifndef FormAGH
#define FormAGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Buttons.hpp>
#include <Series.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TTelaPrincipal : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TChart *Chart1;
   TLineSeries *Series1;
   TLineSeries *Series2;
   TLineSeries *Series3;
   TMainMenu *MainMenu1;
   TMenuItem *Arquivo1;
   TMenuItem *Sair1;
   TMenuItem *Sobre1;
   TMenuItem *Sobre2;
   TPanel *Panel2;
   TImage *Image1;
   TPanel *Panel4;
   TButton *BtTodasGeracoes;
   TButton *BtUmaGeracao;
   TButton *BtDezGeracoes;
   TButton *BtCemGeracoes;
   TLabel *Label5;
   TPanel *Panel5;
   TLabel *Label6;
   TButton *BtGeraPopAutomatica;
   TButton *BtGeraPopManual;
   TPanel *Panel7;
   TLabel *Label12;
   TEdit *EdtNumeroPontosBase;
   TButton *BtGerarPontosBaseAleatorio;
   TButton *BtGerarPontosBaseManual;
   TGroupBox *GroupBox1;
   TPanel *Panel3;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TEdit *EdtTxCrossover;
   TEdit *EdtTxMutacao;
   TEdit *EdtNumeroPopulacao;
   TEdit *EdtNumeroGeracoes;
   TPanel *Panel6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TEdit *EdtMaximoX;
   TEdit *EdtMinimoX;
   TEdit *EdtMaximoY;
   TEdit *EdtMinimoY;
   TPanel *Panel8;
   TLabel *Label13;
   TLabel *Label14;
   TEdit *EdtFatorDistribuicao;
   TEdit *EdtFatorDistancia;
   TRadioGroup *RGTipoCrossover;
   TRadioGroup *RGTipoSelecao;
   TRadioGroup *RGFitness;
   TButton *BtInicializaValoresApp;
   //void __fastcall BitBtn1Click(TObject *Sender);
   //void __fastcall Button1Click(TObject *Sender);
   //void __fastcall Button2Click(TObject *Sender);
   void __fastcall Sair1Click(TObject *Sender);
   void __fastcall BtGeraPopAutomaticaClick(TObject *Sender);
   void __fastcall BtGeraPopManualClick(TObject *Sender);
   void __fastcall BtTodasGeracoesClick(TObject *Sender);
   void __fastcall BtUmaGeracaoClick(TObject *Sender);
   void __fastcall BtDezGeracoesClick(TObject *Sender);
   void __fastcall BtCemGeracoesClick(TObject *Sender);
   void __fastcall BtGerarPontosBaseManualClick(TObject *Sender);
   void __fastcall BtInicializaValoresAppClick(TObject *Sender);
   void __fastcall BtGerarPontosBaseAleatorioClick(TObject *Sender);
   void __fastcall Sobre2Click(TObject *Sender);
private:	// User declarations

public:
   void DesenhaRetangulo(int x,int y);
   void DesenhaCirculo(int x,int y);
   void DesenhaCirculoMelhorIndividuo(int x,int y);
   void DesenhaCirculoPiorIndividuo(int x,int y);

   void LimpaTelaDesenho();
   void InserePontoMelhorIndividuo(double fitness);
   void InserePontoPiorIndividuo(double fitness);
   void InserePontoMediaIndividuo(double fitness);

   int PercentualCrossover();
   int PercentualMutacao();

   int NumeroIndividuosInicial();
   int NumeroMaximoDeGeracoes();

   int NumeroPontosBase();

   double FatorDistribuicao();
   double FatorDistancia();

   int AlturaJanelaDesenho();
   int LarguraJanelaDesenho();

   int MaxX();
   int MinX();
   int MaxY();
   int MinY();

public:		// User declarations
   __fastcall TTelaPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTelaPrincipal *TelaPrincipal;
//---------------------------------------------------------------------------
#endif
