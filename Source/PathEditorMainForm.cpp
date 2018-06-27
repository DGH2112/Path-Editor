#include <vcl.h>
#include <dialogs.hpp>
#include <windows.hpp>
#include <IniFiles.hpp>
#include <Registry.hpp>
#include <memory>
#pragma hdrstop

#include "PathEditorMainForm.h"
#include "PathEditorFrame.h"
#include "PathEditorBroadcastForm.h"

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
  BuildINIFileName();
  // Initialise Frames
  FSystemReadOnly = true;
  FUserReadOnly = true;
  SystemPathEditor->InitialisePath("", "", true, false, NULL, NULL);
  UserPathEditor->InitialisePath("", "", true, false, NULL, NULL);
  LoadSettings();
  // Update caption with app name and version info
  int iMajor, iMinor, iBugFix, iBuild;
  String strBugFix = " abcdefghijklmnopqrstuvwxyz";
  BuildInfo(ParamStr(0), iMajor, iMinor, iBugFix, iBuild);
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
  std::unique_ptr<TMemIniFile> iniFile ( new TMemIniFile(FINIFileName) );
  this->Top = iniFile->ReadInteger("Setup", "Top", 100);
  this->Left = iniFile->ReadInteger("Setup", "Left", 100);
  this->Width = iniFile->ReadInteger("Setup", "Width", this->Width);
  this->Height = iniFile->ReadInteger("Setup", "Height", this->Height);
}

/**

  This method saves the applications settings to an INI file.

  @precon  None.
  @postcon The applications settings are saved to the INI file.

**/
void __fastcall TfrmPathEditorMainForm::SaveSettings() {
  std::unique_ptr<TMemIniFile> iniFile ( new TMemIniFile(FINIFileName) );
  iniFile->WriteInteger("Setup", "Top", this->Top);
  iniFile->WriteInteger("Setup", "Left", this->Left);
  iniFile->WriteInteger("Setup", "Width", this->Width);
  iniFile->WriteInteger("Setup", "Height", this->Height);
  iniFile->UpdateFile();
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
  std::unique_ptr<TRegistry> reg ( new TRegistry(KEY_WRITE) );
  reg->RootKey = HKEY_LOCAL_MACHINE;
  if (reg->OpenKey(strSysPath, false)) {
    reg->CloseKey();
    boolReadOnly = false;
  }
  // Get the path value
  reg.reset( new TRegistry(KEY_READ) );
  reg->RootKey = HKEY_LOCAL_MACHINE;
  if (reg->KeyExists(strSysPath)) {
    if (reg->OpenKey(strSysPath, false)) {
      strPath = reg->ReadString("Path");
      reg->CloseKey();
    }
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
  std::unique_ptr<TRegistry> reg ( new TRegistry(KEY_WRITE) );
  reg->RootKey = HKEY_USERS;
  if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
    reg->CloseKey();
    boolReadOnly = false;
  }
  // Get the path value
  reg.reset( new TRegistry(KEY_READ) );
  reg->RootKey = HKEY_USERS;
  if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
    strPath = reg->ReadString("Path");
    reg->CloseKey();
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
  std::unique_ptr<TRegistry> reg ( new TRegistry(KEY_WRITE) );
  reg->RootKey = HKEY_LOCAL_MACHINE;
  if (reg->KeyExists(strSysPath)) {
    if (reg->OpenKey(strSysPath, false)) {
      reg->WriteExpandString("Path", strPath);
      reg->CloseKey();
    } else
      MessageDlg("Cannot open the system path for writing!", mtError, TMsgDlgButtons() << mbOK, 0);
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
  std::unique_ptr<TRegistry> reg ( new TRegistry(KEY_WRITE) );
  reg->RootKey = HKEY_USERS;
  if (reg->OpenKey(strUserProfile + "\\" + strUserPath, false)) {
    reg->WriteExpandString("Path", strPath);
    reg->CloseKey();
  } else
    MessageDlg("Cannot open the user path for writing!", mtError, TMsgDlgButtons() << mbOK, 0);
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
  if (
    (UserPathEditor->HasBeenModified && !UserPathEditor->HasBeenSaved) ||
    (SystemPathEditor->HasBeenModified && !SystemPathEditor->HasBeenSaved)) {
    CanClose = false;
    switch (MessageDlg("Paths have been modified. Are you sure you want to close?",
      mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0)) {
      case mrYes:
        CanClose = true;
        return;
      case mrNo, mrCancel:
        return;
    }
  }
  if (CanClose && (SystemPathEditor->HasBeenSaved || UserPathEditor->HasBeenSaved)) {
    std::unique_ptr<TfrmBroadcastChanges> BroadcastForm( new TfrmBroadcastChanges(this) );
    BroadcastForm->Show();
    try {
      Application->ProcessMessages(); // Ensure form is painted
      unsigned long dwReturnValue = 0;
      SendMessageTimeout(
        HWND_BROADCAST,
        WM_SETTINGCHANGE,
        0,
        (LPARAM) L"Environment",
        SMTO_ABORTIFHUNG,
        5000,
        &dwReturnValue
      );
    } __finally {
      BroadcastForm->Hide();
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
  std::unique_ptr<TRegistry> reg ( new TRegistry(KEY_READ) );
  reg->RootKey = HKEY_USERS;
  if (reg->OpenKey("", false)) {
    std::unique_ptr<TStringList> sl ( new TStringList() );
    reg->GetKeyNames(sl.get());
    for (int i = 0; i < sl->Count; i++) {
      if (reg->OpenKey(sl->Strings[i] + "\\Volatile Environment", false)) {
        String strUserName = reg->ReadString("USERNAME");
        cbxUserProfiles->Items->Add(strUserName + ": " + sl->Strings[i]);
        reg->CloseKey();
      }
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

/**

  This is an on select event handler for the user profiles combo box.

  @precon  None.
  @postcon Updates the system and user profile tabs based on the selected user.

  @param   Sender as a TObject

**/
void __fastcall TfrmPathEditorMainForm::cbxUserProfilesSelect(TObject *Sender) {
  if (
    (UserPathEditor->HasBeenModified && !UserPathEditor->HasBeenSaved) ||
    (SystemPathEditor->HasBeenModified && !SystemPathEditor->HasBeenSaved)) {
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

/**

  This method updates the application caption to include the applications version number
  and build information.

  @precon  None.
  @postcon The applications caption is updated with version and build information.

**/
void __fastcall TfrmPathEditorMainForm::BuildInfo(const String strFileName, int &iMajor,
  int &iMinor, int &iBugFix, int &iBuild) {
  DWORD iVerHandle = NULL;
  DWORD iVerInfoSize = GetFileVersionInfoSize(strFileName.c_str(), &iVerHandle);
  if (iVerInfoSize) {
    LPSTR VerInfo = new char [iVerInfoSize];
    try {
      if (GetFileVersionInfo(strFileName.c_str(), iVerHandle, iVerInfoSize, VerInfo)) {
        unsigned int iVerValueSize = 0;
        LPBYTE lpBuffer = NULL;
        if (VerQueryValue(VerInfo, TEXT("\\"), (VOID FAR* FAR*)&lpBuffer, &iVerValueSize)) {
          if (iVerValueSize) {
            VS_FIXEDFILEINFO *VerValue = (VS_FIXEDFILEINFO *)lpBuffer;
            iMajor = VerValue->dwFileVersionMS >> 16;
            iMinor = VerValue->dwFileVersionMS & 0xFFFF;
            iBugFix = VerValue->dwFileVersionLS >> 16;
            iBuild = VerValue->dwFileVersionLS & 0xFFFF;
          }
        }
      }
    } __finally {
      delete[] VerInfo;
    }
  } else
    ShowMessage("The executable """ + strFileName + """ does not contain any version information.");
}

/**

  This method build an INI filename based in the computer name username and the users profile location.

  @precon  None.
  @postcon FINIFileName contaisn a valid INI filename in the users profile.

  @return  a String

**/
void __fastcall TfrmPathEditorMainForm::BuildINIFileName() {
  const String strINIPattern = L"%s Settings for %s on %s.INI";
  const String strSeasonsFall = L"\\Season's Fall\\";
  String strBuffer = "";
  strBuffer.SetLength(MAX_PATH);
  int iSize = GetModuleFileName(HInstance, strBuffer.c_str(), MAX_PATH);
  strBuffer.SetLength(iSize);
  FINIFileName = ChangeFileExt(strBuffer, "");
  FINIFileName = Format(strINIPattern, ARRAYOFCONST((FINIFileName, UserName(), ComputerName())));
  strBuffer.SetLength(MAX_PATH);
  if (SHGetFolderPath(0, CSIDL_APPDATA | CSIDL_FLAG_CREATE, 0, 0, strBuffer.c_str()) == S_OK) {
    iSize = strBuffer.Pos('\0');
    strBuffer.SetLength(--iSize);
    strBuffer = strBuffer + strSeasonsFall;
    if (!DirectoryExists(strBuffer))
      ForceDirectories(strBuffer);
    FINIFileName = strBuffer + ExtractFileName(FINIFileName);
  }
}

/**

  This method returns the computer name.

  @precon  None.
  @postcon The computer name is returned.

  @return  a String

**/
String __fastcall TfrmPathEditorMainForm::ComputerName() {
  unsigned long iSize = MAX_PATH;
  String strBuffer = "";
  strBuffer.SetLength(iSize);
  GetComputerName(strBuffer.c_str(), &iSize);
  strBuffer.SetLength(iSize);
  return strBuffer;
};

/**

  This method returns the user name.

  @precon  None.
  @postcon The user name is returned.

  @return  a String

**/
String __fastcall TfrmPathEditorMainForm::UserName() {
  unsigned long iSize = MAX_PATH;
  String strBuffer = "";
  strBuffer.SetLength(iSize);
  GetUserName(strBuffer.c_str(), &iSize);
  strBuffer.SetLength(--iSize);
  return strBuffer;
};

