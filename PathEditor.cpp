//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Source\PathEditorFrame.cpp", fmPathEditor); /* TFrame: File Type */
USEFORM("Source\PathEditorMainForm.cpp", frmPathEditorMainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
  try
  {
     Application->Initialize();
     Application->MainFormOnTaskBar = true;
     Application->Title = "Path Editor 1.0";
     Application->CreateForm(__classid(TfrmPathEditorMainForm), &frmPathEditorMainForm);
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
