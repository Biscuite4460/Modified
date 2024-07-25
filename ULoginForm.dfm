object LoginForm: TLoginForm
  Left = 0
  Top = 0
  Caption = 'LoginForm'
  ClientHeight = 199
  ClientWidth = 287
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 40
    Width = 92
    Height = 25
    Caption = 'username:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Sylfaen'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 88
    Width = 92
    Height = 25
    Caption = 'password:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Sylfaen'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object EditUsername: TEdit
    Left = 122
    Top = 40
    Width = 121
    Height = 25
    TabOrder = 0
  end
  object EditPassword: TEdit
    Left = 122
    Top = 88
    Width = 121
    Height = 25
    TabOrder = 1
  end
  object ButtonOK: TButton
    Left = 41
    Top = 144
    Width = 75
    Height = 25
    Caption = 'Continue'
    TabOrder = 2
    OnClick = ButtonOKClick
  end
  object ButtonCancel: TButton
    Left = 168
    Top = 144
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = ButtonCancelClick
  end
end
