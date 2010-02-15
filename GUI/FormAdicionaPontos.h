//---------------------------------------------------------------------------

#ifndef FormAdicionaPontosH
#define FormAdicionaPontosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormAddPontos : public TForm
{
__published:	// IDE-managed Components
   TStringGrid *StringGrid1;
   TButton *BtOK;
private:	// User declarations
public:		// User declarations
   __fastcall TFormAddPontos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAddPontos *FormAddPontos;
//---------------------------------------------------------------------------
#endif
