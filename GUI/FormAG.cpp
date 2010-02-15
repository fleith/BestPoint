//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormAG.h"

#include "./Interface/GerenteInterfaceAG.h"
#include "./GUI/FormAdicionaPontos.h"
#include "./GUI/About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TTelaPrincipal *TelaPrincipal;
//---------------------------------------------------------------------------
__fastcall TTelaPrincipal::TTelaPrincipal(TComponent* Owner)
   : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TTelaPrincipal::Sair1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void TTelaPrincipal::InserePontoMelhorIndividuo(double fitness)
{
   Series1->Add(fitness,"", clTeeColor );
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::InserePontoPiorIndividuo(double fitness)
{
   Series2->Add(fitness,"",clTeeColor);
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::InserePontoMediaIndividuo(double fitness)
{
   Series3->Add(fitness,"",clTeeColor);
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::DesenhaRetangulo(int x,int y) {
   TColor corAnterior= Image1->Canvas->Brush->Color;
   Image1->Canvas->Brush->Color= clRed;
   TPoint points[3];
   points[0] = Point(x+3,y+3);
   points[1] = Point(x,y-3);
   points[2] = Point(x-3,y+3);
   Image1->Canvas->Polygon(points,2);
   //Image1->Canvas->Rectangle(x-3,y-3,x+3,y+3);
   Image1->Canvas->Brush->Color= corAnterior;
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::DesenhaCirculo(int x,int y) {
   TColor corAnterior= Image1->Canvas->Brush->Color;
   Image1->Canvas->Brush->Color= clBlue;
   Image1->Canvas->Ellipse(x-3,y-3,x+3,y+3);
   Image1->Canvas->Brush->Color= corAnterior;
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::DesenhaCirculoMelhorIndividuo(int x,int y)
{
   TColor corAnterior= Image1->Canvas->Brush->Color;
   Image1->Canvas->Brush->Color= clLime;
   Image1->Canvas->Ellipse(x-4,y-4,x+4,y+4);
   Image1->Canvas->Brush->Color= corAnterior;
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::DesenhaCirculoPiorIndividuo(int x,int y)
{
   TColor corAnterior= Image1->Canvas->Brush->Color;
   Image1->Canvas->Brush->Color= clGray;
   Image1->Canvas->Ellipse(x-4,y-4,x+4,y+4);
   Image1->Canvas->Brush->Color= corAnterior;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::AlturaJanelaDesenho()
{
   return Image1->Height;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::LarguraJanelaDesenho()
{
   return Image1->Width;
}

////////////////////////////////////////////////////////////////////////////////

void TTelaPrincipal::LimpaTelaDesenho() {
   Image1->Canvas->Rectangle(-1,-1,Image1->Width+1,Image1->Height+1);
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::PercentualCrossover()
{
   int txCross= StrToInt(EdtTxCrossover->Text);

   return txCross;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::PercentualMutacao()
{
   int txMutacao= StrToInt(EdtTxMutacao->Text);

   return txMutacao;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::NumeroIndividuosInicial()
{
   int numPopulacao= StrToInt(EdtNumeroPopulacao->Text);

   return numPopulacao;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::NumeroMaximoDeGeracoes()
{
   int numGeracoes= StrToInt(EdtNumeroGeracoes->Text);

   return numGeracoes;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::NumeroPontosBase()
{
   int numPontosBase= StrToInt(EdtNumeroPontosBase->Text);

   return numPontosBase;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::MaxX()
{
   int maxX= StrToInt(EdtMaximoX->Text);
   return maxX;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::MinX()
{
   int minX= StrToInt(EdtMinimoX->Text);
   return minX;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::MaxY()
{
   int maxY= StrToInt(EdtMaximoY->Text);
   return maxY;
}

////////////////////////////////////////////////////////////////////////////////

int TTelaPrincipal::MinY()
{
   int minY= StrToInt(EdtMinimoY->Text);
   return minY;
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TTelaPrincipal::BtGeraPopAutomaticaClick(TObject *Sender)
{
   GI::GeraPopulacaoAutomatica();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtGeraPopManualClick(TObject *Sender)
{
   GI::GeraPopulacaoManual();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtTodasGeracoesClick(TObject *Sender)
{
   GI::ExecutaAteUltimaGeracao();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtUmaGeracaoClick(TObject *Sender)
{
   GI::ExecutaMaisUmaGeracao();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtDezGeracoesClick(TObject *Sender)
{
   GI::ExecutaMaisDezGeracoes();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtCemGeracoesClick(TObject *Sender)
{
   GI::ExecutaMaisCemGeracoes();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtGerarPontosBaseManualClick(
      TObject *Sender)
{
   FormAddPontos->Show();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtInicializaValoresAppClick(
      TObject *Sender)
{
   GI::InicializaAplicacao();   
}
//---------------------------------------------------------------------------

void __fastcall TTelaPrincipal::BtGerarPontosBaseAleatorioClick(
      TObject *Sender)
{
   GI::GeraPontosBase();
}
//---------------------------------------------------------------------------

double TTelaPrincipal::FatorDistribuicao()
{
   double fator= StrToFloat(EdtFatorDistribuicao->Text);

   return fator;
}

////////////////////////////////////////////////////////////////////////////////

double TTelaPrincipal::FatorDistancia()
{
   double fator= StrToFloat(EdtFatorDistancia->Text);

   return fator;
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TTelaPrincipal::Sobre2Click(TObject *Sender)
{
   AboutBox->ShowModal();   
}
//---------------------------------------------------------------------------

