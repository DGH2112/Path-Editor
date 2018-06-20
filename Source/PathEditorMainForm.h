#ifndef PathEditorMainFormH
#define PathEditorMainFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <PathEditorFrame.h>

/** A class to represent the main form for the application. **/
class TfrmPathEditorMainForm : public TForm
{
__published:	// IDE-managed Components
  TBitBtn *btnClose;
  TPageControl *pagPaths;
  TTabSheet *tabSystemPaths;
  TTabSheet *tabUserPaths;
  TfmPathEditor *SystemPathEditor;
  TfmPathEditor *UserPathEditor;
  TLabel *Label1;
  TLabel *lblUserProfile;
  TComboBox *cbxUserProfiles;
  void __fastcall btnCloseClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall cbxUserProfilesSelect(TObject *Sender);
private: // User declarations
  bool  FSystemReadOnly;
  bool  FUserReadOnly;
  void   __fastcall LoadSettings();
  void   __fastcall SaveSettings();
  String __fastcall GetSystemPath(bool &boolReadOnly);
  String __fastcall GetUserPath(String strUserProfile, bool &boolReadOnly);
  void   __fastcall SetUserPath(String strUserProfile, String strPath);
  void   __fastcall SetSystemPath(String strPath);
  void   __fastcall UpdateUserPath(TObject *Sender, String strUserPath);
  void   __fastcall UpdateSystemPath(TObject *Sender, String strSystemPath);
  void   __fastcall MoveSystemPath(TObject *Sender, String strSystemPath);
  void   __fastcall MoveUserPath(TObject *Sender, String strUserPath);
  void   __fastcall PopulateUserProfiles();
  String __fastcall GetUserProfileName();
  void __fastcall TfrmPathEditorMainForm::BuildInfo(const String strFileName, int &iMajor,
    int &iMinor, int &iBugFix, int &iBuild);
public:  // User declarations
  __fastcall TfrmPathEditorMainForm(TComponent* Owner);
};

extern PACKAGE TfrmPathEditorMainForm *frmPathEditorMainForm;
#endif
