object frmPathEditorMainForm: TfrmPathEditorMainForm
  Left = 0
  Top = 0
  Caption = 'Path Editor'
  ClientHeight = 315
  ClientWidth = 524
  Color = clBtnFace
  Constraints.MinHeight = 350
  Constraints.MinWidth = 540
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    524
    315)
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 304
    Top = 232
    Width = 37
    Height = 16
    Caption = 'Label1'
  end
  object lblUserProfile: TLabel
    Left = 8
    Top = 282
    Width = 71
    Height = 16
    Anchors = [akLeft, akBottom]
    Caption = 'User Profile:'
  end
  object btnClose: TBitBtn
    Left = 441
    Top = 279
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Close'
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
      F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
      000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
      338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
      45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
      3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
      F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
      000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
      338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
      4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
      8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
      333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
      0000}
    NumGlyphs = 2
    TabOrder = 2
    OnClick = btnCloseClick
  end
  object pagPaths: TPageControl
    Left = 8
    Top = 8
    Width = 508
    Height = 265
    ActivePage = tabSystemPaths
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object tabSystemPaths: TTabSheet
      Caption = '&System Paths'
      inline SystemPathEditor: TfmPathEditor
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 494
        Height = 228
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        inherited lblPath: TLabel
          Width = 488
        end
        inherited lblLength: TLabel
          Left = 416
        end
        inherited lbxPaths: TListBox
          Width = 407
          Height = 145
        end
        inherited edtPath: TButtonedEdit
          Top = 173
          Width = 407
        end
        inherited btnReplace: TBitBtn
          Left = 173
          Top = 200
        end
        inherited btnAdd: TBitBtn
          Left = 254
          Top = 200
        end
        inherited btnDelete: TBitBtn
          Left = 335
          Top = 200
        end
        inherited btnBrowse: TBitBtn
          Left = 416
          Top = 171
        end
        inherited btnUpdate: TBitBtn
          Top = 200
        end
        inherited btnUp: TBitBtn
          Left = 416
          Top = 111
        end
        inherited btnDown: TBitBtn
          Left = 416
          Top = 142
        end
        inherited btnMove: TBitBtn
          Left = 92
          Top = 200
        end
      end
    end
    object tabUserPaths: TTabSheet
      Caption = '&User Paths'
      ImageIndex = 1
      inline UserPathEditor: TfmPathEditor
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 494
        Height = 228
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        inherited lblPath: TLabel
          Width = 488
        end
        inherited lblLength: TLabel
          Left = 416
        end
        inherited lbxPaths: TListBox
          Width = 407
          Height = 145
        end
        inherited edtPath: TButtonedEdit
          Top = 173
          Width = 407
        end
        inherited btnReplace: TBitBtn
          Left = 173
          Top = 200
        end
        inherited btnAdd: TBitBtn
          Left = 254
          Top = 200
        end
        inherited btnDelete: TBitBtn
          Left = 335
          Top = 200
        end
        inherited btnBrowse: TBitBtn
          Left = 416
          Top = 171
        end
        inherited btnUpdate: TBitBtn
          Top = 200
        end
        inherited btnUp: TBitBtn
          Left = 416
          Top = 111
        end
        inherited btnDown: TBitBtn
          Left = 416
          Top = 142
        end
        inherited btnMove: TBitBtn
          Left = 92
          Top = 200
        end
      end
    end
  end
  object cbxUserProfiles: TComboBox
    Left = 96
    Top = 279
    Width = 339
    Height = 24
    Style = csDropDownList
    Anchors = [akLeft, akRight, akBottom]
    TabOrder = 1
    OnSelect = cbxUserProfilesSelect
  end
end
