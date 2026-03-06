object TelaPrincipal: TTelaPrincipal
  Left = 62
  Top = 110
  Width = 987
  Height = 822
  Caption = 'Algoritmo Gen'#233'tico'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 16
    Top = 400
    Width = 745
    Height = 321
    BevelOuter = bvSpace
    BevelWidth = 5
    TabOrder = 0
    object Chart1: TChart
      Left = 5
      Top = 5
      Width = 735
      Height = 311
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      BackWall.Color = 4227327
      Foot.Font.Charset = DEFAULT_CHARSET
      Foot.Font.Color = clBlack
      Foot.Font.Height = -13
      Foot.Font.Name = 'Arial'
      Foot.Font.Style = []
      Foot.Text.Strings = (
        'Gera'#231#245'es')
      PrintProportional = False
      Title.Text.Strings = (
        'Melhor, pior indiv'#237'duo e a m'#233'dia (Fitness X Gera'#231#227'o)')
      BackColor = 4227327
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.ExactDateTime = False
      LeftAxis.Grid.Style = psDashDotDot
      LeftAxis.Grid.SmallDots = True
      LeftAxis.StartPosition = 10
      LeftAxis.Title.Caption = 'Fitness (Maior '#233' mais adaptado)'
      Legend.Visible = False
      View3D = False
      Align = alClient
      BevelOuter = bvLowered
      Color = clWhite
      TabOrder = 0
      object Series1: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clGreen
        Title = 'SeriesMelhor'
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series2: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        Title = 'SeriesPior'
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series3: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clYellow
        Title = 'SeriesMedia'
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
  end
  object Panel2: TPanel
    Left = 448
    Top = 8
    Width = 457
    Height = 329
    BevelOuter = bvSpace
    BevelWidth = 5
    TabOrder = 1
    object Image1: TImage
      Left = 5
      Top = 5
      Width = 447
      Height = 319
      Align = alClient
    end
  end
  object Panel4: TPanel
    Left = 768
    Top = 528
    Width = 137
    Height = 193
    TabOrder = 2
    object Label5: TLabel
      Left = 8
      Top = 8
      Width = 119
      Height = 16
      Caption = 'Executar  gera'#231#245'es:'
    end
    object BtTodasGeracoes: TButton
      Left = 24
      Top = 39
      Width = 75
      Height = 25
      Caption = 'Todas'
      TabOrder = 0
      OnClick = BtTodasGeracoesClick
    end
    object BtUmaGeracao: TButton
      Left = 24
      Top = 71
      Width = 75
      Height = 25
      Caption = 'Uma'
      TabOrder = 1
      OnClick = BtUmaGeracaoClick
    end
    object BtDezGeracoes: TButton
      Left = 24
      Top = 104
      Width = 75
      Height = 25
      Caption = 'Dez'
      TabOrder = 2
      OnClick = BtDezGeracoesClick
    end
    object BtCemGeracoes: TButton
      Left = 24
      Top = 136
      Width = 75
      Height = 25
      Caption = 'Cem'
      TabOrder = 3
      OnClick = BtCemGeracoesClick
    end
  end
  object Panel5: TPanel
    Left = 776
    Top = 400
    Width = 129
    Height = 121
    TabOrder = 3
    object Label6: TLabel
      Left = 16
      Top = 8
      Width = 105
      Height = 16
      Caption = 'Gerar popula'#231#227'o:'
    end
    object BtGeraPopAutomatica: TButton
      Left = 24
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Automatica'
      TabOrder = 0
      OnClick = BtGeraPopAutomaticaClick
    end
    object BtGeraPopManual: TButton
      Left = 24
      Top = 72
      Width = 75
      Height = 25
      Caption = 'Manual'
      Enabled = False
      TabOrder = 1
      OnClick = BtGeraPopManualClick
    end
  end
  object Panel7: TPanel
    Left = 448
    Top = 344
    Width = 457
    Height = 49
    TabOrder = 4
    object Label12: TLabel
      Left = 8
      Top = 16
      Width = 96
      Height = 16
      Caption = 'N'#186' pontos base:'
    end
    object EdtNumeroPontosBase: TEdit
      Left = 112
      Top = 12
      Width = 49
      Height = 24
      TabOrder = 0
      Text = '2'
    end
    object BtGerarPontosBaseAleatorio: TButton
      Left = 176
      Top = 12
      Width = 113
      Height = 25
      Caption = 'Gerar aleat'#243'rio'
      TabOrder = 1
      OnClick = BtGerarPontosBaseAleatorioClick
    end
    object BtGerarPontosBaseManual: TButton
      Left = 312
      Top = 12
      Width = 113
      Height = 25
      Caption = 'Gerar manual'
      Enabled = False
      TabOrder = 2
      OnClick = BtGerarPontosBaseManualClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 8
    Width = 425
    Height = 385
    Caption = 'Dados AG'
    TabOrder = 5
    object Panel3: TPanel
      Left = 16
      Top = 24
      Width = 236
      Height = 131
      TabOrder = 0
      object Label1: TLabel
        Left = 18
        Top = 8
        Width = 82
        Height = 16
        Caption = 'Crossover(%)'
      end
      object Label2: TLabel
        Left = 28
        Top = 40
        Width = 72
        Height = 16
        Caption = 'Muta'#231#227'o(%)'
      end
      object Label3: TLabel
        Left = 2
        Top = 72
        Width = 98
        Height = 16
        Caption = 'N'#186' de individuos'
      end
      object Label4: TLabel
        Left = 5
        Top = 104
        Width = 95
        Height = 16
        Caption = 'N'#186' de gera'#231#245'es'
      end
      object EdtTxCrossover: TEdit
        Left = 106
        Top = 4
        Width = 121
        Height = 24
        TabOrder = 0
        Text = '60'
      end
      object EdtTxMutacao: TEdit
        Left = 106
        Top = 36
        Width = 121
        Height = 24
        TabOrder = 1
        Text = '3'
      end
      object EdtNumeroPopulacao: TEdit
        Left = 106
        Top = 68
        Width = 121
        Height = 24
        TabOrder = 2
        Text = '20'
      end
      object EdtNumeroGeracoes: TEdit
        Left = 106
        Top = 100
        Width = 121
        Height = 24
        TabOrder = 3
        Text = '50'
      end
    end
    object Panel6: TPanel
      Left = 264
      Top = 24
      Width = 148
      Height = 132
      TabOrder = 1
      object Label7: TLabel
        Left = 34
        Top = -1
        Width = 84
        Height = 16
        Caption = 'Faixa eixo X,Y'
      end
      object Label8: TLabel
        Left = 2
        Top = 22
        Width = 50
        Height = 16
        Caption = 'Max. (X):'
      end
      object Label9: TLabel
        Left = 2
        Top = 49
        Width = 46
        Height = 16
        Caption = 'Min. (X):'
      end
      object Label10: TLabel
        Left = 2
        Top = 108
        Width = 47
        Height = 16
        Caption = 'Min. (Y):'
      end
      object Label11: TLabel
        Left = 2
        Top = 82
        Width = 51
        Height = 16
        Caption = 'Max. (Y):'
      end
      object EdtMaximoX: TEdit
        Left = 58
        Top = 18
        Width = 81
        Height = 24
        TabOrder = 0
        Text = '110'
      end
      object EdtMinimoX: TEdit
        Left = 58
        Top = 45
        Width = 81
        Height = 24
        TabOrder = 1
        Text = '-30'
      end
      object EdtMaximoY: TEdit
        Left = 58
        Top = 78
        Width = 81
        Height = 24
        TabOrder = 2
        Text = '50'
      end
      object EdtMinimoY: TEdit
        Left = 58
        Top = 104
        Width = 81
        Height = 24
        TabOrder = 3
        Text = '0'
      end
    end
    object Panel8: TPanel
      Left = 16
      Top = 160
      Width = 396
      Height = 37
      TabOrder = 2
      object Label13: TLabel
        Left = 3
        Top = 8
        Width = 103
        Height = 16
        Caption = 'Fator distribui'#231#227'o'
      end
      object Label14: TLabel
        Left = 201
        Top = 8
        Width = 88
        Height = 16
        Caption = 'Fator dist'#226'ncia'
      end
      object EdtFatorDistribuicao: TEdit
        Left = 115
        Top = 4
        Width = 65
        Height = 24
        TabOrder = 0
        Text = '1'
      end
      object EdtFatorDistancia: TEdit
        Left = 313
        Top = 4
        Width = 66
        Height = 24
        TabOrder = 1
        Text = '1'
      end
    end
    object RGTipoCrossover: TRadioGroup
      Left = 292
      Top = 205
      Width = 113
      Height = 73
      Caption = 'Tipo crossover'
      ItemIndex = 1
      Items.Strings = (
        'Sequencial'
        'Aleat'#243'rio')
      TabOrder = 3
    end
    object RGTipoSelecao: TRadioGroup
      Left = 165
      Top = 205
      Width = 121
      Height = 121
      Caption = 'Tipo sele'#231#227'o'
      ItemIndex = 4
      Items.Strings = (
        'Elitismo'
        'Roleta'
        'Classifica'#231#227'o'
        'Estacion'#225'ria'
        'Alvaro'#39's')
      TabOrder = 4
    end
    object RGFitness: TRadioGroup
      Left = 20
      Top = 205
      Width = 137
      Height = 73
      Caption = 'Tipo fitness'
      ItemIndex = 0
      Items.Strings = (
        'Menor distancia'
        'Maior distancia')
      TabOrder = 5
      Visible = False
    end
    object BtInicializaValoresApp: TButton
      Left = 8
      Top = 336
      Width = 409
      Height = 41
      Caption = 'Carrega informa'#231#245'es'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = BtInicializaValoresAppClick
    end
  end
  object MainMenu1: TMainMenu
    object Arquivo1: TMenuItem
      Caption = '&Arquivo'
      object Sair1: TMenuItem
        Caption = '&Sair'
        OnClick = Sair1Click
      end
    end
    object Sobre1: TMenuItem
      Caption = 'A&juda'
      object Sobre2: TMenuItem
        Caption = '&Sobre'
        OnClick = Sobre2Click
      end
    end
  end
end
