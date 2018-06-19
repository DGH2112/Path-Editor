//---------------------------------------------------------------------------

#ifndef PathEditorBroadcastFormH
#define PathEditorBroadcastFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmBroadcastChanges : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnlMessage;
private:	// User declarations
public:		// User declarations
  __fastcall TfrmBroadcastChanges(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBroadcastChanges *frmBroadcastChanges;
//---------------------------------------------------------------------------
#endif
