object fmPathEditor: TfmPathEditor
  AlignWithMargins = True
  Left = 0
  Top = 0
  Width = 518
  Height = 281
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  DesignSize = (
    518
    281)
  object lblPath: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 512
    Height = 13
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'lblPath'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    ExplicitWidth = 615
  end
  object lblLength: TLabel
    Left = 440
    Top = 22
    Width = 75
    Height = 16
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = 'lblLength'
    ExplicitLeft = 385
  end
  object lbxPaths: TListBox
    AlignWithMargins = True
    Left = 3
    Top = 22
    Width = 431
    Height = 198
    Style = lbOwnerDrawFixed
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    OnClick = lbxPathsClick
    OnDblClick = lbxPathsDblClick
    OnDrawItem = lbxPathsDrawItem
  end
  object edtPath: TButtonedEdit
    Left = 3
    Top = 226
    Width = 431
    Height = 24
    Anchors = [akLeft, akRight, akBottom]
    TabOrder = 1
    OnChange = lbxPathsClick
    ExplicitTop = 244
    ExplicitWidth = 451
  end
  object btnReplace: TBitBtn
    Left = 197
    Top = 253
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Replace'
    TabOrder = 2
    OnClick = btnReplaceClick
    ExplicitLeft = 217
    ExplicitTop = 271
  end
  object btnAdd: TBitBtn
    Left = 278
    Top = 253
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Add'
    TabOrder = 3
    OnClick = btnAddClick
    ExplicitLeft = 298
    ExplicitTop = 271
  end
  object btnDelete: TBitBtn
    Left = 359
    Top = 253
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Delete'
    TabOrder = 4
    OnClick = btnDeleteClick
    ExplicitLeft = 379
    ExplicitTop = 271
  end
  object btnBrowse: TBitBtn
    Left = 440
    Top = 224
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Browse'
    Glyph.Data = {
      F6000000424DF600000000000000760000002800000010000000100000000100
      0400000000008000000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
      77777777777777777777000000000007777700333333333077770B0333333333
      07770FB03333333330770BFB0333333333070FBFB000000000000BFBFBFBFB07
      77770FBFBFBFBF0777770BFB0000000777777000777777770007777777777777
      7007777777770777070777777777700077777777777777777777}
    TabOrder = 5
    OnClick = btnBrowseClick
    ExplicitLeft = 460
    ExplicitTop = 242
  end
  object btnUpdate: TBitBtn
    Left = 3
    Top = 253
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = '&Update'
    TabOrder = 6
    OnClick = btnUpdateClick
    ExplicitTop = 271
  end
  object btnUp: TBitBtn
    Left = 440
    Top = 164
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'U&p'
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000333
      3333333333777F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333FF7F7FFFF333333000090000
      3333333777737777F333333099999990333333373F3333373333333309999903
      333333337F33337F33333333099999033333333373F333733333333330999033
      3333333337F337F3333333333099903333333333373F37333333333333090333
      33333333337F7F33333333333309033333333333337373333333333333303333
      333333333337F333333333333330333333333333333733333333}
    NumGlyphs = 2
    TabOrder = 7
    OnClick = btnUpClick
    ExplicitLeft = 460
    ExplicitTop = 182
  end
  object btnDown: TBitBtn
    Left = 440
    Top = 195
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Do&wn'
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333303333
      333333333337F33333333333333033333333333333373F333333333333090333
      33333333337F7F33333333333309033333333333337373F33333333330999033
      3333333337F337F33333333330999033333333333733373F3333333309999903
      333333337F33337F33333333099999033333333373333373F333333099999990
      33333337FFFF3FF7F33333300009000033333337777F77773333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333300033333333333337773333333}
    NumGlyphs = 2
    TabOrder = 8
    OnClick = btnDownClick
    ExplicitLeft = 460
    ExplicitTop = 213
  end
  object btnMove: TBitBtn
    Left = 116
    Top = 253
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Move'
    TabOrder = 9
    OnClick = btnMoveClick
    ExplicitLeft = 136
    ExplicitTop = 271
  end
end
