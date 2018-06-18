#ifndef PathEditorFrameH
#define PathEditorFrameH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>

/** This ia a call back method signature for the updating of the edited paths. **/
typedef void __fastcall (__closure *TUpdatePathProc)(TObject *Sender, String strPath);

/** This is a call back method for the moving of a path from system to user or vice versa. **/
typedef void __fastcall (__closure *TMovePathProc)(TObject *Sender, String strPath);

/** This class represents the frame interface for editing a single set of paths. **/
class TfmPathEditor : public TFrame
{
__published:	// IDE-managed Components
  TLabel *lblPath;
  TListBox *lbxPaths;
  TButtonedEdit *edtPath;
  TBitBtn *btnReplace;
  TBitBtn *btnAdd;
  TBitBtn *btnDelete;
  TBitBtn *btnBrowse;
  TBitBtn *btnUpdate;
  TBitBtn *btnUp;
  TBitBtn *btnDown;
  TLabel *lblLength;
  TBitBtn *btnMove;
  void __fastcall lbxPathsDblClick(TObject *Sender);
  void __fastcall lbxPathsClick(TObject *Sender);
  void __fastcall btnReplaceClick(TObject *Sender);
  void __fastcall btnAddClick(TObject *Sender);
  void __fastcall btnDeleteClick(TObject *Sender);
  void __fastcall btnUpClick(TObject *Sender);
  void __fastcall btnDownClick(TObject *Sender);
  void __fastcall btnBrowseClick(TObject *Sender);
  void __fastcall btnUpdateClick(TObject *Sender);
  void __fastcall lbxPathsDrawItem(TWinControl *Control, int Index, TRect &Rect,
    TOwnerDrawState State);
  void __fastcall btnMoveClick(TObject *Sender);
private: // User declarations
  TUpdatePathProc FUpdatePathProc;
  TMovePathProc   FMovePathProc;
  bool            FModified;
  bool            FHasBeenModified;
  bool            FReadOnly;
  bool            FCanMove;
public:  // User declarations
       __fastcall TfmPathEditor(TComponent* Owner);
  void __fastcall InitialisePath(const String strTitle, const String strPath,
    bool boolReadOnly, bool boolCanMove, TUpdatePathProc UpdatePathProc,
    TMovePathProc MovePathProc);
  void __fastcall AddPath(String strPath);
  /**
    This is an on update event handler for the frame and must be hooked and handled in
    order for the update button to be enabled and the path updated (be the calling code).
    @precon  None.
    @postcon The hooked event handler is called with the updated path. The handler need to
             update the specified path.
    @return  TUpdatePathProc
  **/
  __property TUpdatePathProc OnUpdate = {read = FUpdatePathProc, write = FUpdatePathProc};
  /**
    This is an on move event handler for the frame and must be hooked and handled in
    order for the move button to be enabled and the path move (be the calling code).
    @precon  None.
    @postcon The hooked event handler is called with the move path. The handler need to
             move the specified path.
    @return  TUpdatePathProc
  **/
  __property TMovePathProc   OnMove   = {read = FMovePathProc  , write = FMovePathProc};
  __property bool Modified = {read = FModified};
  __property bool HasBeenModified = {read = FHasBeenModified};
};

//: @debug extern PACKAGE TfmPathEditor *fmPathEditor;
#endif
