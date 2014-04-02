object Form1: TForm1
  Left = 226
  Top = 141
  Width = 706
  Height = 621
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 698
    Height = 520
    Align = alClient
    TabOrder = 0
    object pbPuntoA: TPaintBox
      Tag = 1
      Left = 104
      Top = 256
      Width = 30
      Height = 30
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = pbPuntoAMouseDown
      OnMouseMove = pbPuntoAMouseMove
      OnPaint = pbPuntoAPaint
    end
    object pbPuntoB: TPaintBox
      Tag = 2
      Left = 304
      Top = 256
      Width = 30
      Height = 30
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = pbPuntoAMouseDown
      OnMouseMove = pbPuntoAMouseMove
      OnPaint = pbPuntoAPaint
    end
    object pbPuntoC: TPaintBox
      Tag = 3
      Left = 504
      Top = 256
      Width = 30
      Height = 30
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = pbPuntoAMouseDown
      OnMouseMove = pbPuntoAMouseMove
      OnPaint = pbPuntoAPaint
    end
  end
  object pnl2: TPanel
    Left = 0
    Top = 520
    Width = 698
    Height = 67
    Align = alBottom
    TabOrder = 1
    object lbPuntoA: TLabel
      Left = 24
      Top = 24
      Width = 68
      Height = 13
      Caption = 'A: 000x - 000y'
      Color = clRed
      ParentColor = False
    end
    object lbPuntoB: TLabel
      Left = 144
      Top = 24
      Width = 68
      Height = 13
      Caption = 'B: 000x - 000y'
      Color = clLime
      ParentColor = False
    end
    object lbPuntoC: TLabel
      Left = 264
      Top = 24
      Width = 68
      Height = 13
      Caption = 'C: 000x - 000y'
      Color = clAqua
      ParentColor = False
    end
    object lbResult: TLabel
      Left = 472
      Top = 24
      Width = 131
      Height = 13
      Caption = 'Result: xxxxxxxxxxxxxxxxxxx'
    end
  end
end
