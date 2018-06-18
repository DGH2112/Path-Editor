#include <vcl.h>
#include <dialogs.hpp>
#include <windows.hpp>
#include <IniFiles.hpp>
#include <Registry.hpp>
#include <DGHLibrary.hpp>
#pragma hdrstop

#include "PathEditorMainForm.h"
#include "PathEditorFrame.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

/** This is a C++ Builder maintained global variable for the main form. **/
TfrmPathEditorMainForm *frmPathEditorMainForm;

/**

  This is the forms constructor. This method is not used.

  @precon  None.
  @postcon None.

  @param   Owner as a TComponent

**/
__fastcall TfrmPathEditorMainForm::TfrmPathEditorMainForm(TComponent* Owner) : TForm(Owner) {
}

/**

  This is an on click event handler for the Close button.

  @precon  None.
  @postcon The form is closed.

  @param   Sender as a TObject

**/
void __fastcall TfrmPathEditorMainForm::btnCloseClick(TObject *Sender) {
  Close();
}

/**

  This is a form on create event handler for the main form.

  @precon  None.
  @postcon The form is initialised by create the path frames and loading settings.

  @param   Sender as a TObject

**/
void __fastcall TfrmPathEditorMainForm::FormCreate(TObject *Sender) {
  // Initialise Frames
  FSystemReadOnly = true;
  FUserReadOnly = true;
  SystemPathEditor->InitialisePath("", "", true, false, NULL, NULL);
  UserPathEditor->InitialisePath("", "", true, false, NULL, NULL);
  LoadSettings();
  // Update caption with app name and version info
  int iMajor, iMinor, iBugFix, iBuild;
  String strBugFix = " abcdefghijklmnopqrstuvwxyz";
  GetBuildNumber(ParamStr(0), iMajor, iMinor, iBugFix, iBuild);
  Caption = Format("Path Editor %d.%d%s (Build %d.%d.%d.%d)", ARRAYOFCONST((
    iMajor, iMinor, strBugFix[iBugFix + 1], iMajor, iMinor, iBugFix, iBuild)));
  PopulateUserProfiles();
}

/**

  This method loads the applications settings from an INI file.

  @precon  None.
  @postcon The applications settings are loaded from the INI file.

**/
void __fastcall TfrmPathEditorMainForm::LoadSettings() {
  String strINIFileName = ChangeFileExt(ParamStr(0), ".ini");
  TMemIniFile *iniFile = new TMemIniFile(strINIFileName);
  try {
    this->Top = iniFile->ReadInteger("Setup", "Top", 100);
    this->Left = iniFile->ReadInteger("Setup", "Left", 100);
    this->Width = iniFile->ReadInteger("Setup", "Width", this->Width);
    this->Height = iniFile->ReadInteger("Setup", "Height", this->Height);
  }
  __finally {
    delete iniFile;
  };
}

/**

  This method saves the applications settings to an INI file.

  @precon  None.
  @postcon The applications settings are saved to the INI file.

**/
void __fastcall TfrmPathEditorMainForm::SaveSettings() {
  String strINIFileName = ChangeFileExt(ParamStr(0), ".ini");
  TMemIniFile *iniFile = new TMemIniFile(strINIFileName);
  try {
    iniFile->WriteInteger("Setup", "Top", this->Top);
    iniFile->WriteInteger("Setup", "Left", this->Left);
    iniFile->WriteInteger("Setup", "Width", this->Width);
    iniFile->WriteInteger("Setup", "Height", this->Height);
    iniFile->UpdateFile();
  }
  __finally {
    delete iniFile;
  };
}

/**

  This is an on destroy event handler for the main form.

  @precon  None.
  @postcon Saves the applications settings.

  @param   Sender as a TObject

**/
void __fastcall TfrmPathEditorMainForm::FormDestroy(TObject *Sender) {
  SaveSettings();
}

/**

  This method returns the system path string.

  @precon  None.
  @postcon The system path string is returned.

  @param   boolReadOnly as a bool
  @return  a String

**/
String __fastcall TfrmPathEditorMainForm::GetSystemPath(bool &boolReadOnly) {
  const String strSysPath = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\";
  String strPath = "";
  // Find out if the key is read only.
  boolReadOnly = true;
  TRegistry *reg = new TRegistry(KEY_WRITE);
  try {
    reg->RootKey = HKEY_LOCAL_MACHINE;
    if (reg->OpenKey(strSysPath, false)) {
      reg->CloseKey();
      boolReadOnly = false;
    }
  } __finally {
    delete reg;
  }
  // Get the path value
  reg = new TRegistry(KEY_READ);
  try {
    reg->RootKey = HKEY_LOCAL_MACHINE;
    if (reg->KeyExists(strSysPath)) {
      if (reg->OpenKey(strSysPath, false)) {
        strPath = reg->ReadString("Path");
        reg->CloseKey();
      }
    }
  } __finally {
    delete reg;
  }
  return strPath;
}

/**

  This method returns the user path string for the geiven profile.

  @precon  None.
  @postcon The user path string is returned for the given profile.

  @param   strUserProfile as a String
  @param   boolReadOnly   as a bool
  @return  a String

**/
String __fastcall TfrmPathEditorMainForm::GetUserPath(String strUserProfile,
  bool &boolReadOnly) {
  const String strUserPath = "Environment\\";
  String strPath = "";
  // Find out if the key is read only
  boolReadOnly = true;
  TRegistry *reg = new TRegistry(KEY_WRITE);
  try {
    reg->RootKey = HKEY_USERS;
    if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
      reg->CloseKey();
      boolReadOnly = false;
    }
  } __finally {
    delete reg;
  }
  // Get the path value
  reg = new TRegistry(KEY_READ);
  try {
    reg->RootKey = HKEY_USERS;
    if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
      strPath = reg->ReadString("Path");
      reg->CloseKey();
    }
  } __finally {
    delete reg;
  }
  return strPath;
}

/**

  This method saves the new system path to the system.

  @precon  None.
  @postcon The system path is updated if it can be opened for writing else an error
           message is displayed.

  @param   strPath as a String

**/
void __fastcall TfrmPathEditorMainForm::SetSystemPath(String strPath) {
  const String strSysPath = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\";
  TRegistry *reg = new TRegistry(KEY_WRITE);
  try {
    reg->RootKey = HKEY_LOCAL_MACHINE;
    if (reg->KeyExists(strSysPath)) {
      if (reg->OpenKey(strSysPath, false)) {
        reg->WriteString("Path", strPath);
        reg->CloseKey();
      } else
        MessageDlg("Cannot open the system path for writing!", mtError,
          TMsgDlgButtons() << mbOK, 0);
    }
  }
  __finally {
    delete reg;
  }
}

/**

  This method updates the path for the given user.

  @precon  None.
  @postcon The user path is updated for the given user.

  @param   struserProfile as a String
  @param   strPath        as a String

**/
void __fastcall TfrmPathEditorMainForm::SetUserPath(String strUserProfile,
  String strPath) {
  const String strUserPath = "Environment\\";
  TRegistry *reg = new TRegistry(KEY_WRITE);
  try {
    reg->RootKey = HKEY_USERS;
    if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
      reg->WriteString("Path", strPath);
      reg->CloseKey();
    } else
      MessageDlg("Cannot open the user path for writing!", mtError,
        TMsgDlgButtons() << mbOK, 0);
  }
  __finally {
    delete reg;
  }
}

/**

  This method is an on update path event handle for the user Frame.

  @precon  None.
  @postcon The user path is set to the passed path string.

  @param   Sender        as a TObject
  @param   strSystemPath as a String

**/
void __fastcall TfrmPathEditorMainForm::UpdateUserPath(TObject *Sender,
  String strUserPath) {
  SetUserPath(GetUserProfileName(), strUserPath);
}

/**

  This method is an on update path event handle for the system Frame.

  @precon  None.
  @postcon The system path is set to the passed path string.

  @param   Sender        as a TObject
  @param   strSystemPath as a String

**/
void __fastcall TfrmPathEditorMainForm::UpdateSystemPath(TObject *Sender,
  String strSystemPath) {
  SetSystemPath(strSystemPath);
}

/**

  This is an on move path event handler for the System path.

  @precon  None.
  @postcon The given system path is moved (added) to the user path.

  @param   Sender        as a TObject
  @param   strSystemPath as a String

**/
void __fastcall TfrmPathEditorMainForm::MoveSystemPath(TObject *Sender,
  String strSystemPath) {
  UserPathEditor->AddPath(strSystemPath);
}

/**

  This is an on move path event handler for the User path.

  @precon  None.
  @postcon The given user path is moved (added) to the system path.

  @param   Sender      as a TObject
  @param   strUserPath as a String

**/
void __fastcall TfrmPathEditorMainForm::MoveUserPath(TObject *Sender,
  String strUserPath) {
  SystemPathEditor->AddPath(strUserPath);
}

/**

  This is an on form close query event handler for the form.

  @precon  None.
  @postcon If any of the paths have been modified a prompt is displayed asking whether
           the user wants to discard the changes.

  @param   Sender   as a TObject
  @param   CanClose as a bool as a reference

**/
void __fastcall TfrmPathEditorMainForm::FormCloseQuery(TObject *Sender, bool &CanClose) {
  if (UserPathEditor->Modified || SystemPathEditor->Modified) {
    CanClose = false;
    if (MessageDlg("Paths have been modified. Are you sure you want to close?",
      mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0) == mrYes) {
      CanClose = true;
    }
  }
}

/**

  This method searches through the registry user profiles for usernames in the Volatile
  Environment key and if found adds them to the user profiles combo box as available
  user profiles to edit.

  @precon  None.
  @postcon The combo box is filled with available user profiles.

**/
void __fastcall TfrmPathEditorMainForm::PopulateUserProfiles() {
  TRegistry *reg = new TRegistry(KEY_READ);
  try {
    reg->RootKey = HKEY_USERS;
    if (reg->OpenKey("", false)) {
      TStringList *sl = new TStringList();
      try {
        reg->GetKeyNames(sl);
        for (int i = 0; i < sl->Count; i++) {
          if (reg->OpenKey(sl->Strings[i] + "\\Volatile Environment", false)) {
            String strUserName = reg->ReadString("USERNAME");
            cbxUserProfiles->Items->Add(strUserName + ": " + sl->Strings[i]);
            reg->CloseKey();
          }
        }
      } __finally {
        delete sl;
      }
    }
    reg->RootKey = HKEY_CURRENT_USER;
    if (reg->OpenKey("Volatile Environment", false)) {
      for (int i = 0; i < cbxUserProfiles->Items->Count; i++) {
        String strUserName = reg->ReadString("USERNAME");
        if (CompareText(strUserName, cbxUserProfiles->Items->Strings[i].SubString(1,
          strUserName.Length())) == 0) {
          cbxUserProfiles->ItemIndex = i;
          cbxUserProfilesSelect(NULL);
          break;
        }
      }
    }
  }
  __finally {
    delete reg;
  }
}

/**

  This is an on select event handler for the user profiles combo box.

  @precon  None.
  @postcon Updates the system and user profile tabs based on the selected user.

  @param   Sender as a TObject

**/
void __fastcall TfrmPathEditorMainForm::cbxUserProfilesSelect(TObject *Sender) {
  if (UserPathEditor->Modified || SystemPathEditor->Modified) {
    if (MessageDlg("Some of the paths have been modified. Are you sure you want to "
      "change user?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,
      0) != mrYes) {
      Abort();
    }
  }
  String strPath = GetSystemPath(FSystemReadOnly);
  SystemPathEditor->InitialisePath("System Path", strPath, FSystemReadOnly,
    !FSystemReadOnly && !FUserReadOnly, UpdateSystemPath, MoveSystemPath);
  strPath = GetUserPath(GetUserProfileName(), FUserReadOnly);
  UserPathEditor->InitialisePath("User Path: " + cbxUserProfiles->Text, strPath,
    FUserReadOnly, !FSystemReadOnly && !FUserReadOnly, UpdateUserPath, MoveUserPath);
}

/**

  This method extracts the user profile security ID from the selected user profiles combo
  box item.

  @precon  None.
  @postcon Returns the user profile security ID.

  @return  a String

**/
String __fastcall TfrmPathEditorMainForm::GetUserProfileName() {
  String strUserProfile = cbxUserProfiles->Text;
  int iPos = strUserProfile.Pos(":");
  if (iPos > 0) {
    strUserProfile.Delete(1, iPos);
    strUserProfile = strUserProfile.Trim();
  }
  return strUserProfile;
}