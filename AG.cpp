//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("GUI\FormAG.cpp", TelaPrincipal);
USEFORM("GUI\FormAdicionaPontos.cpp", FormAddPontos);
USEFORM("GUI\About.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       srand(time(0)); //inicializando semente para números aleátorios

       Application->Initialize();
       Application->CreateForm(__classid(TTelaPrincipal), &TelaPrincipal);
       Application->CreateForm(__classid(TFormAddPontos), &FormAddPontos);
       Application->CreateForm(__classid(TAboutBox), &AboutBox);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   catch (...)
   {
       try
       {
          throw Exception("");
       }
       catch (Exception &exception)
       {
          Application->ShowException(&exception);
       }
   }
   return 0;
}
//---------------------------------------------------------------------------
