#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "PathEditorFrame.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

/**

  This is the TfmPathEditor class constructor.

  @precon  None.
  @postcon Not used.

  @param   Owner as a TComponent

**/
__fastcall TfmPathEditor::TfmPathEditor(TComponent* Owner) : TFrame(Owner) {
}

/**

  This method initialises the frame controls with information.

  @precon  None.
  @postcon

  @param   strTitle       as a String
  @param   strPath        as a String as a Reference
  @param   boolReadOnly   as a bool
  @param   boolCanMove    as a bool
  @param   UpdatePathProc as a TUpdatePathProc
  @param   MovePathProc   as a TMovePathProc

**/
void __fastcall TfmPathEditor::InitialisePath(String strTitle, const String strPath,
  bool boolReadOnly, bool boolCanMove, TUpdatePathProc UpdatePathProc,
  TMovePathProc MovePathProc) {
  FHasBeenSaved = false;
  FHasBeenModified = false;
  FReadOnly = boolReadOnly;
  FCanMove = boolCanMove;
  lblPath->Caption = strTitle;
  lbxPaths->Items->Text = StringReplace(strPath, ";", "\n",
    TReplaceFlags() << rfReplaceAll);
  FUpdatePathProc = UpdatePathProc;
  FMovePathProc = MovePathProc;
  lbxPathsClick(NULL);
}

/**

  This is an on double click event handler for the path list box.

  @precon  None.
  @postcon Copies the selected path from the list box into the edit control.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::lbxPathsDblClick(TObject *Sender) {
  if (lbxPaths->ItemIndex > -1) {
    edtPath->Text = lbxPaths->Items->Strings[lbxPaths->ItemIndex];
  }
}

/**

  This is an on click event handler for the paths list box.

  @precon  None.
  @postcon Updates the enabled property of the buttons on the frame.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::lbxPathsClick(TObject *Sender) {
  btnUpdate->Enabled  = !FReadOnly && FHasBeenModified && !FHasBeenSaved && (FUpdatePathProc != NULL);
  btnMove->Enabled    = !FReadOnly && FCanMove && (lbxPaths->ItemIndex > -1) && (FMovePathProc != NULL);
  btnAdd->Enabled     = !FReadOnly && (edtPath->Text != "");
  btnReplace->Enabled = !FReadOnly && (edtPath->Text != "") && (lbxPaths->ItemIndex > -1);
  btnDelete->Enabled  = !FReadOnly && (lbxPaths->ItemIndex > -1);
  btnBrowse->Enabled  = !FReadOnly;
  btnUp->Enabled      = !FReadOnly && (lbxPaths->ItemIndex > 0);
  btnDown->Enabled    = !FReadOnly && (lbxPaths->ItemIndex > -1) &&
    (lbxPaths->ItemIndex < lbxPaths->Items->Count - 1);
  lblLength->Caption = "Length: " + StringReplace(
    IntToStr(lbxPaths->Items->Text.Length()), "\r\n", ";",
    TReplaceFlags() << rfReplaceAll);
}

/**

  This is an on click event handler for the Replace button.

  @precon  None.
  @postcon Replaces the selected item in the list box with the path in the edit control.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnReplaceClick(TObject *Sender) {
  if ((lbxPaths->ItemIndex > -1) && (edtPath->Text != "")) {
    lbxPaths->Items->Strings[lbxPaths->ItemIndex] = edtPath->Text;
    FHasBeenModified = true;
    lbxPathsClick(Sender);
  }
}

/**

  This is an on click event handler for the Add button.

  @precon  None.
  @postcon Adds the path in the edit control to the bottom of the list box.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnAddClick(TObject *Sender) {
  if (edtPath->Text != "") {
    if (lbxPaths->Items->IndexOf(edtPath->Text) == -1) {
      lbxPaths->Items->Add(edtPath->Text);
      FHasBeenModified = true;
      lbxPathsClick(Sender);
    } else {
      MessageDlg("Path \"" + edtPath->Text + "\" already exists.", mtError,
        TMsgDlgButtons() << mbOK, 0);
    }
  }
}

/**

  This is an on click event handler for the Delete button.

  @precon  None.
  @postcon The selected item in the list box is deleted.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnDeleteClick(TObject *Sender)
{
  int iIndex = lbxPaths->ItemIndex;
  if (iIndex > -1) {
    lbxPaths->Items->Delete(iIndex);
    FHasBeenModified = true;
  }
  if (iIndex > lbxPaths->Items->Count - 1) {
    iIndex--;
  }
  lbxPaths->ItemIndex = iIndex;
  lbxPathsClick(Sender);
}

/**

  This is an on click event hander for the Up button.

  @precon  None.
  @postcon Moves the selected item up the list one place.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnUpClick(TObject *Sender) {
  int iIndex = lbxPaths->ItemIndex;
  if (iIndex > 0) {
    lbxPaths->Items->Exchange(iIndex, iIndex - 1);
    FHasBeenModified = true;
    lbxPathsClick(Sender);
  }
}

/**

  This is an on click event handler for the Down button.

  @precon  None.
  @postcon Moves the selected item down the list by one place.

  @param   Sender as a TObject.

**/
void __fastcall TfmPathEditor::btnDownClick(TObject *Sender) {
  int iIndex = lbxPaths->ItemIndex;
  if (iIndex < lbxPaths->Items->Count - 1) {
    lbxPaths->Items->Exchange(iIndex, iIndex + 1);
    FHasBeenModified = true;
    lbxPathsClick(Sender);
  }
}

/**

  This is an on click event handler for the Browse button.

  @precon  None.
  @postcon Displays a folder browse dialogue and if the user selects a folder and confirms
           the dialogue the folder path is added to the edit control.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnBrowseClick(TObject *Sender) {
  ;
  String strPath = GetCurrentDir();
  if (SelectDirectory(strPath, TSelectDirOpts(), 0)) {
    edtPath->Text = strPath;
  };
}

/**

  This is an on click event handler for the Update button.

  @precon  None.
  @postcon If the update procedure is assigned the current built path is passed to the
           update procedure.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnUpdateClick(TObject *Sender) {
  if (FUpdatePathProc != NULL) {
    String strPath = StringReplace(lbxPaths->Items->Text, "\r\n", ";",
      TReplaceFlags() << rfReplaceAll);
    if (strPath.Length() > 0 && strPath[strPath.Length()] == ';') {
      strPath.Delete(strPath.Length(), 1);
    }
    FUpdatePathProc(Sender, strPath);
    FHasBeenSaved = true;
    lbxPathsClick(Sender);
  }
}
/**

  This is an on draw item event handler for the path list box.

  @precon  None.
  @postcon The items in the list box are drawn with invalid paths greyed out.

  @param   Control as a TWinControl
  @param   Index   as a int
  @param   Rect    as a TRect
  @param   State   as a TOwnerDrawState

**/
void __fastcall TfmPathEditor::lbxPathsDrawItem(TWinControl *Control, int Index,
  TRect &Rect, TOwnerDrawState State) {
  // Draw Background
  TCanvas *C = lbxPaths->Canvas;
  C->FillRect(Rect);
  String strPath = lbxPaths->Items->Strings[Index];
  // Colour invalid paths gray
  int iSize = MAX_PATH;
  WideChar strExpandedPath[MAX_PATH];
  ExpandEnvironmentStrings(strPath.w_str(), strExpandedPath, iSize);
  if (DirectoryExists(StrPas(strExpandedPath))) {
    C->Font->Color = clWindowText;
  } else {
    C->Font->Color = clGrayText;
  }
  // Draw Text
  C->TextRect(Rect, strPath, TTextFormat() << tfLeft << tfVerticalCenter);
}

/**

  This is an on click event handler for the Move button.

  @precon  None.
  @postcon Passes the selected path to the MovePathProc and then deletes that path from
           the list.

  @param   Sender as a TObject

**/
void __fastcall TfmPathEditor::btnMoveClick(TObject *Sender)
{
  if (FMovePathProc != NULL) {
    FMovePathProc(Sender, lbxPaths->Items->Strings[lbxPaths->ItemIndex]);
    lbxPaths->Items->Delete(lbxPaths->ItemIndex);
    FHasBeenModified = true;
    lbxPathsClick(NULL);
  }
}

/**

  This method adds a path to the bottom of the list of paths.

  @precon  None.
  @postcon The path is added to the bottom of the list.

  @param   strPath as a String

**/
void __fastcall TfmPathEditor::AddPath(String strPath) {
  if (strPath.Length() > 0) {
    lbxPaths->Items->Add(strPath);
    FHasBeenModified = true;
    lbxPathsClick(NULL);
  }
}
