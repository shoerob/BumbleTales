object Form1: TForm1
  Left = 480
  Top = 173
  Width = 1015
  Height = 749
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = onClose
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 580
    Width = 999
    Height = 9
    Cursor = crVSplit
    Align = alBottom
    Beveled = True
    Constraints.MaxHeight = 200
  end
  object Splitter2: TSplitter
    Left = 65
    Top = 0
    Width = 10
    Height = 580
    Cursor = crHSplit
    Beveled = True
  end
  object TabSheet: TPageControl
    Left = 75
    Top = 0
    Width = 924
    Height = 580
    ActivePage = HFF
    Align = alClient
    ParentShowHint = False
    ShowHint = True
    Style = tsFlatButtons
    TabOrder = 0
    Visible = False
    object HGF: TTabSheet
      Caption = 'HGF'
      object Label1: TLabel
        Left = 704
        Top = 8
        Width = 76
        Height = 20
        Caption = 'HGF Files:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Frame_Rate: TLabel
        Left = 128
        Top = 280
        Width = 71
        Height = 16
        Caption = 'Frame Rate'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 120
        Top = 248
        Width = 76
        Height = 16
        Caption = 'Frames / Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object FrameSets: TLabel
        Left = 128
        Top = 216
        Width = 69
        Height = 16
        Caption = 'Frame Sets'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object textHeight: TLabel
        Left = 112
        Top = 168
        Width = 81
        Height = 16
        Caption = 'Frame Height'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object textWidth: TLabel
        Left = 120
        Top = 144
        Width = 76
        Height = 16
        Caption = 'Frame Width'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 120
        Top = 88
        Width = 73
        Height = 13
        Caption = 'Image Location'
      end
      object Label4: TLabel
        Left = 136
        Top = 56
        Width = 53
        Height = 13
        Caption = 'Description'
      end
      object R: TLabel
        Left = 336
        Top = 144
        Width = 10
        Height = 16
        Caption = 'R'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object G: TLabel
        Left = 336
        Top = 168
        Width = 10
        Height = 16
        Caption = 'G'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object B: TLabel
        Left = 336
        Top = 192
        Width = 9
        Height = 16
        Caption = 'B'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 360
        Top = 128
        Width = 110
        Height = 16
        Hint = 'Color Key Transparency in RGB value'
        Caption = 'Transparency Key'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object Label6: TLabel
        Left = 328
        Top = 256
        Width = 161
        Height = 13
        Caption = 'example: (frames  in set 1, 2,3,4,5)'
      end
      object Label7: TLabel
        Left = 232
        Top = 528
        Width = 158
        Height = 20
        Caption = 'HGF Location / Name:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object framerate: TEdit
        Left = 200
        Top = 280
        Width = 121
        Height = 24
        Hint = 'Frame Rate'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 13
      end
      object HGFImages: TComboBox
        Left = 336
        Top = 0
        Width = 313
        Height = 21
        Hint = 'Images belonging to the current HGF'
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        Text = 'Current Images'
        OnChange = HGFImagesChange
      end
      object DescriptionEdit: TEdit
        Left = 200
        Top = 56
        Width = 281
        Height = 24
        Hint = 'Description of Image -- shows up in the image drop down box'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
      end
      object ImageLocEdit: TEdit
        Left = 200
        Top = 88
        Width = 361
        Height = 24
        Hint = 'Full path location of the image'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
      end
      object imagelocbut: TButton
        Left = 568
        Top = 88
        Width = 73
        Height = 25
        Caption = 'Browse'
        TabOrder = 8
        OnClick = imagelocbutClick
      end
      object red: TEdit
        Left = 352
        Top = 144
        Width = 121
        Height = 24
        TabOrder = 15
      end
      object green: TEdit
        Left = 352
        Top = 168
        Width = 121
        Height = 24
        TabOrder = 16
      end
      object blue: TEdit
        Left = 352
        Top = 192
        Width = 121
        Height = 24
        TabOrder = 17
      end
      object frameset: TEdit
        Left = 200
        Top = 216
        Width = 121
        Height = 24
        Hint = '# of frame sets'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 11
      end
      object framesperset: TEdit
        Left = 200
        Top = 248
        Width = 121
        Height = 24
        Hint = 'Frames in EACH frame set -- seperated by commas'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 12
      end
      object autoanimate: TCheckBox
        Left = 200
        Top = 304
        Width = 121
        Height = 25
        Caption = 'Auto Animate'
        TabOrder = 14
      end
      object applysettingsbut: TButton
        Left = 296
        Top = 344
        Width = 97
        Height = 25
        Hint = 'Apply above settings to the current image'
        Caption = 'Apply Settings'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 18
        OnClick = applysettingsbutClick
      end
      object height: TEdit
        Left = 200
        Top = 168
        Width = 121
        Height = 24
        Hint = 'Height of a single frame'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 10
      end
      object width: TEdit
        Left = 200
        Top = 144
        Width = 121
        Height = 24
        Hint = 'Width of a single frame'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 9
      end
      object addimagebut: TButton
        Left = 0
        Top = 0
        Width = 97
        Height = 25
        Hint = 'Add Image to Current HGF'
        Caption = 'Add Image'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = addimagebutClick
      end
      object removeimagebut: TButton
        Left = 0
        Top = 24
        Width = 97
        Height = 25
        Hint = 'Remove Image From Current HGF'
        Caption = 'Remove Image'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = removeimagebutClick
      end
      object hgflocname: TEdit
        Left = 392
        Top = 528
        Width = 361
        Height = 24
        Hint = 'Location and name of the current HGF file'
        ReadOnly = True
        TabOrder = 4
      end
      object hgflocbut: TButton
        Left = 760
        Top = 528
        Width = 73
        Height = 25
        Caption = 'Browse'
        TabOrder = 5
        OnClick = hgflocbutClick
      end
      object HGFFiles: TListBox
        Left = 696
        Top = 32
        Width = 137
        Height = 305
        Hint = 'HGF files in current game project'
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = HGFFilesClick
      end
      object palletentry: TEdit
        Left = 296
        Top = 0
        Width = 33
        Height = 24
        Hint = 'Pallet entry of the current image'
        ParentShowHint = False
        ReadOnly = True
        ShowHint = True
        TabOrder = 19
      end
    end
    object HLFHTF: TTabSheet
      Caption = 'HLF / HTF'
      ImageIndex = 1
      object Levels: TLabel
        Left = 680
        Top = -2
        Width = 49
        Height = 20
        Caption = 'Levels:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label20: TLabel
        Left = 112
        Top = 40
        Width = 47
        Height = 13
        Caption = 'Map Data'
      end
      object Label23: TLabel
        Left = 135
        Top = 348
        Width = 26
        Height = 13
        Caption = 'Level'
      end
      object LevelsList: TListBox
        Left = 664
        Top = 19
        Width = 153
        Height = 318
        ItemHeight = 13
        TabOrder = 0
        OnClick = LevelsListClick
      end
      object GroupBox1: TGroupBox
        Left = 64
        Top = 64
        Width = 599
        Height = 129
        Caption = 'Front Layer'
        TabOrder = 1
        object Label11: TLabel
          Left = 40
          Top = 35
          Width = 56
          Height = 13
          Caption = 'Tile'#39's Image'
        end
        object Label12: TLabel
          Left = 52
          Top = 66
          Width = 43
          Height = 13
          Alignment = taRightJustify
          Caption = 'Tile Data'
        end
        object Label21: TLabel
          Left = 24
          Top = 100
          Width = 74
          Height = 13
          Caption = 'Number of Tiles'
        end
        object fronttileimageedit: TEdit
          Left = 104
          Top = 32
          Width = 401
          Height = 24
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object fronttiledataedit: TEdit
          Left = 104
          Top = 64
          Width = 401
          Height = 24
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object fronttibut: TButton
          Left = 512
          Top = 30
          Width = 75
          Height = 25
          Caption = 'Browse'
          Enabled = False
          TabOrder = 2
          OnClick = fronttibutClick
        end
        object fronttdbut: TButton
          Left = 512
          Top = 62
          Width = 75
          Height = 25
          Caption = 'Browse'
          Enabled = False
          TabOrder = 3
          OnClick = fronttdbutClick
        end
        object frontlayernumbertiles: TEdit
          Left = 104
          Top = 96
          Width = 97
          Height = 24
          Enabled = False
          TabOrder = 4
        end
      end
      object GroupBox2: TGroupBox
        Left = 64
        Top = 200
        Width = 599
        Height = 137
        Caption = 'Scrolling Background'
        TabOrder = 2
        object Label16: TLabel
          Left = 52
          Top = 65
          Width = 43
          Height = 13
          Alignment = taRightJustify
          Caption = 'Tile Data'
        end
        object Label19: TLabel
          Left = 40
          Top = 34
          Width = 56
          Height = 13
          Caption = 'Tile'#39's Image'
        end
        object Label22: TLabel
          Left = 24
          Top = 100
          Width = 74
          Height = 13
          Caption = 'Number of Tiles'
        end
        object backtileimageedit: TEdit
          Left = 104
          Top = 32
          Width = 401
          Height = 24
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object backtiledataedit: TEdit
          Left = 104
          Top = 64
          Width = 401
          Height = 24
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object backtdbut: TButton
          Left = 512
          Top = 62
          Width = 75
          Height = 25
          Caption = 'Browse'
          Enabled = False
          TabOrder = 2
          OnClick = backtdbutClick
        end
        object backtibut: TButton
          Left = 512
          Top = 30
          Width = 75
          Height = 25
          Caption = 'Browse'
          Enabled = False
          TabOrder = 3
          OnClick = backtibutClick
        end
        object scrollinglayernumbertiles: TEdit
          Left = 104
          Top = 96
          Width = 97
          Height = 24
          Enabled = False
          TabOrder = 4
        end
      end
      object mapdataedit: TEdit
        Left = 168
        Top = 40
        Width = 401
        Height = 24
        Enabled = False
        ReadOnly = True
        TabOrder = 3
      end
      object mapdatabut: TButton
        Left = 576
        Top = 38
        Width = 75
        Height = 25
        Caption = 'Browse'
        Enabled = False
        TabOrder = 4
        OnClick = mapdatabutClick
      end
      object leveloutputedit: TEdit
        Left = 168
        Top = 344
        Width = 401
        Height = 24
        Enabled = False
        ReadOnly = True
        TabOrder = 5
      end
      object leveloutputbut: TButton
        Left = 576
        Top = 342
        Width = 75
        Height = 25
        Caption = 'Browse'
        Enabled = False
        TabOrder = 6
      end
    end
    object HSF: TTabSheet
      Caption = 'HSF'
      ImageIndex = 2
      object SoundFiles: TLabel
        Left = 704
        Top = 8
        Width = 74
        Height = 20
        Caption = 'HSF Files:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 120
        Top = 88
        Width = 75
        Height = 13
        Caption = 'Sound Location'
      end
      object Label9: TLabel
        Left = 136
        Top = 56
        Width = 53
        Height = 13
        Caption = 'Description'
      end
      object Label10: TLabel
        Left = 232
        Top = 528
        Width = 156
        Height = 20
        Caption = 'HSF Location / Name:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object HSFFiles: TListBox
        Left = 696
        Top = 32
        Width = 137
        Height = 305
        ItemHeight = 13
        TabOrder = 0
        OnClick = HSFFilesClick
      end
      object HSFSounds: TComboBox
        Left = 240
        Top = 0
        Width = 241
        Height = 21
        Hint = 'Sounds in current HSF'
        ItemHeight = 13
        TabOrder = 1
        Text = 'HSFSounds'
        OnChange = HSFSoundsChange
      end
      object SDescriptionEdit: TEdit
        Left = 200
        Top = 56
        Width = 281
        Height = 21
        Hint = 'Description / Name of the current sound'
        TabOrder = 2
      end
      object spalletnumber: TEdit
        Left = 200
        Top = 0
        Width = 33
        Height = 21
        Hint = 'Pallet entry of current sound'
        ReadOnly = True
        TabOrder = 3
      end
      object SoundLocEdit: TEdit
        Left = 200
        Top = 88
        Width = 361
        Height = 21
        Hint = 'Location of current sound'
        TabOrder = 4
      end
      object hsflocname: TEdit
        Left = 392
        Top = 528
        Width = 361
        Height = 21
        Hint = 'Location of current HSF file'
        ReadOnly = True
        TabOrder = 5
      end
      object addsoundbut: TButton
        Left = 0
        Top = 8
        Width = 97
        Height = 25
        Hint = 'Add sound to current HSF'
        Caption = 'Add Sound'
        TabOrder = 6
        OnClick = addsoundbutClick
      end
      object removesoundbut: TButton
        Left = 0
        Top = 32
        Width = 97
        Height = 25
        Hint = 'Remove sound from current HSF'
        Caption = 'Remove Sound'
        TabOrder = 7
        OnClick = removesoundbutClick
      end
      object sapplysettingbut: TButton
        Left = 200
        Top = 176
        Width = 105
        Height = 25
        Hint = 'Apply setting to current sound'
        Caption = 'Apply Settings'
        TabOrder = 8
        OnClick = sapplysettingbutClick
      end
      object hsflocbut: TButton
        Left = 760
        Top = 528
        Width = 73
        Height = 25
        Caption = 'Browse'
        TabOrder = 9
        OnClick = hsflocbutClick
      end
      object soundlocbut: TButton
        Left = 576
        Top = 88
        Width = 65
        Height = 25
        Caption = 'Browse'
        TabOrder = 10
        OnClick = soundlocbutClick
      end
    end
    object HFF: TTabSheet
      Caption = 'HFF'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImageIndex = 3
      ParentFont = False
      object Label13: TLabel
        Left = 58
        Top = 120
        Width = 57
        Height = 25
        AutoSize = False
        Caption = 'RED'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label14: TLabel
        Left = 56
        Top = 152
        Width = 73
        Height = 25
        AutoSize = False
        Caption = 'GREEN'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label15: TLabel
        Left = 56
        Top = 184
        Width = 73
        Height = 25
        AutoSize = False
        Caption = 'BLUE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label17: TLabel
        Left = 704
        Top = 8
        Width = 45
        Height = 20
        Caption = 'Fonts:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label18: TLabel
        Left = 232
        Top = 528
        Width = 155
        Height = 20
        Caption = 'HFF Location / Name:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object KeyRedEdit: TEdit
        Left = 152
        Top = 128
        Width = 129
        Height = 21
        TabOrder = 1
        Text = '0'
        OnChange = KeyRedEditChange
        OnClick = coloreditClick
        OnExit = KeyRedEditExit
      end
      object KeyGreenEdit: TEdit
        Left = 152
        Top = 160
        Width = 129
        Height = 21
        TabOrder = 2
        Text = '0'
        OnChange = KeyGreenEditChange
        OnClick = coloreditClick
        OnExit = KeyGreenEditExit
      end
      object KeyBlueEdit: TEdit
        Left = 152
        Top = 192
        Width = 129
        Height = 21
        TabOrder = 3
        Text = '0'
        OnChange = KeyBlueEditChange
        OnClick = coloreditClick
        OnExit = KeyBlueEditExit
      end
      object ColorRedEdit: TEdit
        Left = 328
        Top = 128
        Width = 121
        Height = 21
        TabOrder = 4
        Text = '0'
        OnChange = ColorRedEditChange
        OnClick = coloreditClick
        OnExit = ColorRedEditExit
      end
      object ColorGreenEdit: TEdit
        Left = 328
        Top = 160
        Width = 121
        Height = 21
        TabOrder = 5
        Text = '0'
        OnChange = ColorGreenEditChange
        OnClick = coloreditClick
        OnExit = ColorGreenEditExit
      end
      object ColorBlueEdit: TEdit
        Left = 328
        Top = 192
        Width = 121
        Height = 21
        TabOrder = 6
        Text = '0'
        OnChange = ColorBlueEditChange
        OnClick = coloreditClick
        OnExit = ColorBlueEditExit
      end
      object HFFFiles: TListBox
        Left = 696
        Top = 32
        Width = 137
        Height = 305
        ItemHeight = 13
        TabOrder = 7
        OnClick = HFFFilesClick
      end
      object hfflocedit: TEdit
        Left = 392
        Top = 528
        Width = 361
        Height = 21
        Hint = 'Location of current HFF'
        ReadOnly = True
        TabOrder = 8
      end
      object choosefontbut: TButton
        Left = 0
        Top = 0
        Width = 97
        Height = 25
        Hint = 'Change font settings for current HSF'
        Caption = 'Choose Font'
        TabOrder = 9
        OnClick = choosefontbutClick
      end
      object Button2: TButton
        Left = 0
        Top = 24
        Width = 97
        Height = 25
        Hint = 'Generate the font (must be done before saving HFF)'
        Caption = 'Create HPT Font'
        TabOrder = 0
        OnClick = Button2Click
      end
      object hfflocbut: TButton
        Left = 760
        Top = 528
        Width = 73
        Height = 25
        Caption = 'Browse'
        TabOrder = 10
        OnClick = hfflocbutClick
      end
      object backgroundcolorbut: TButton
        Left = 144
        Top = 88
        Width = 145
        Height = 33
        Caption = 'Background Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 11
        OnClick = backgroundcolorbutClick
      end
      object foregroundcolorbut: TBitBtn
        Left = 312
        Top = 88
        Width = 153
        Height = 33
        Caption = 'Foreground Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 12
        OnClick = foregroundcolorbutClick
      end
      object fringingcheckbox: TCheckBox
        Left = 488
        Top = 96
        Width = 17
        Height = 17
        TabOrder = 13
        OnClick = fringcolorcheckOnClick
      end
      object fringingcolorbut: TButton
        Left = 512
        Top = 88
        Width = 113
        Height = 33
        Caption = 'Fringing Color'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 14
        OnClick = fringingcolorbutClick
      end
      object FringRedEdit: TEdit
        Left = 504
        Top = 128
        Width = 121
        Height = 21
        Enabled = False
        TabOrder = 15
        Text = '0'
      end
      object FringGreenEdit: TEdit
        Left = 504
        Top = 160
        Width = 121
        Height = 21
        Enabled = False
        TabOrder = 17
        Text = '0'
      end
      object FringBlueEdit: TEdit
        Left = 504
        Top = 192
        Width = 121
        Height = 21
        Enabled = False
        TabOrder = 16
        Text = '0'
      end
      inline fontscroll1: Tfontscroll
        Left = 8
        Top = 368
        Width = 825
        Height = 105
        TabOrder = 18
        inherited Image1: TImage
          Left = 8
          Top = 8
          Height = 96
          AutoSize = True
        end
      end
    end
  end
  object Messages: TListBox
    Left = 0
    Top = 589
    Width = 999
    Height = 104
    Align = alBottom
    ItemHeight = 13
    TabOrder = 1
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 0
    Width = 65
    Height = 580
    Align = alLeft
    Indent = 19
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 328
    Top = 448
    object MenuFile: TMenuItem
      Caption = 'File'
      object NewGame: TMenuItem
        Caption = 'New Game'
        OnClick = NewGameClick
      end
      object OpenGame: TMenuItem
        Caption = 'Open Game'
        OnClick = OpenGameClick
      end
      object SaveGame: TMenuItem
        Caption = 'Save Game'
        OnClick = SaveGameClick
      end
      object CloseGame: TMenuItem
        Caption = 'Close Game'
        OnClick = CloseGameClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object BuildProject1: TMenuItem
        Caption = 'Build Game'
        Hint = 'Creates all game files'
        OnClick = BuildProject1Click
      end
      object Options: TMenuItem
        Caption = 'Options...'
        OnClick = OptionsClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit: TMenuItem
        Caption = 'Exit'
        OnClick = ExitClick
      end
    end
    object MenuHGF: TMenuItem
      Caption = 'HGF'
      object NewHGF: TMenuItem
        Caption = 'New HGF'
        OnClick = NewHGFClick
      end
      object RemoveHGF: TMenuItem
        Caption = 'Remove HGF'
        OnClick = RemoveHGFClick
      end
      object SaveHGF: TMenuItem
        Caption = 'Save HGF'
        OnClick = SaveHGFClick
      end
      object SaveAllHGFS: TMenuItem
        Caption = 'Save All HGF'#39's'
        OnClick = SaveAllHGFSClick
      end
    end
    object MenuHLFHTF: TMenuItem
      Caption = 'H&LF / HTF'
      object CreateNewLevel: TMenuItem
        Caption = 'Create New Level'
        OnClick = CreateNewLevelClick
      end
      object RemoveLevel: TMenuItem
        Caption = 'Remove Level'
      end
      object SaveLevel: TMenuItem
        Caption = 'Save Level'
        OnClick = SaveLevelClick
      end
      object SaveAllLevels: TMenuItem
        Caption = 'Save All Level'#39's'
      end
    end
    object MenuHSF: TMenuItem
      Caption = 'HSF'
      object NewHSF: TMenuItem
        Caption = 'New HSF'
        OnClick = NewHSFClick
      end
      object RemoveHSF: TMenuItem
        Caption = 'Remove HSF'
        OnClick = RemoveHSFClick
      end
      object SaveHSF: TMenuItem
        Caption = 'Save HSF'
        OnClick = SaveHSFClick
      end
      object SaveAllHSFS: TMenuItem
        Caption = 'Save All HSF'#39's'
        OnClick = SaveAllHSFSClick
      end
    end
    object HFF1: TMenuItem
      Caption = 'HFF'
      object AddFont1: TMenuItem
        Caption = 'New HFF'
        OnClick = AddFont1Click
      end
      object RemoveHFF1: TMenuItem
        Caption = 'Remove HFF'
        OnClick = RemoveHFF1Click
      end
      object SaveHFF1: TMenuItem
        Caption = 'Save HFF'
        OnClick = SaveHFFClick
      end
      object SaveAllHFFs1: TMenuItem
        Caption = 'Save All HFF'#39's'
        OnClick = SaveAllHFFs1Click
      end
    end
  end
  object ImageLocationDialog: TOpenDialog
    Left = 256
    Top = 24
  end
  object AddImage: TOpenDialog
    Filter = 'PNG|*.PNG|BMP|*.BMP|JPG|*.JPG'
    Left = 232
    Top = 24
  end
  object DialogNewHGF: TSaveDialog
    DefaultExt = '.hgf'
    Filter = 'HGF|*.hgf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 480
    Top = 424
  end
  object DialogNewGame: TSaveDialog
    DefaultExt = '.hgp'
    Filter = 'HPT Game Project|*.hgp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 376
    Top = 440
  end
  object DialogOpenGame: TOpenDialog
    DefaultExt = '.hgp'
    Filter = 'HPT Game Project|*.hgp'
    Options = [ofHideReadOnly, ofCreatePrompt, ofEnableSizing]
    Left = 520
    Top = 416
  end
  object DialogHGFLoc: TOpenDialog
    DefaultExt = '.hgf'
    Filter = 'HGF|*.HGF'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 284
    Top = 24
  end
  object DialogSaveHSF: TSaveDialog
    DefaultExt = '.hsf'
    Filter = 'HSF|*.hsf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 552
    Top = 416
  end
  object DialogAddSound: TOpenDialog
    DefaultExt = '.wav'
    Filter = 'WAV|*.wav'
    Left = 552
  end
  object DialogHSFLoc: TOpenDialog
    DefaultExt = '.hsf'
    Filter = 'HPT Sound File|*.hsf'
    Left = 576
  end
  object DialogSoundLocation: TOpenDialog
    DefaultExt = '.wav'
    Filter = 'WAV|*.wav'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 600
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 688
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'HFF'
    Filter = '*.HFF|*.HFF'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 712
  end
  object DialogNewHFF: TSaveDialog
    DefaultExt = '*.hff'
    Filter = 'HPT Font File|*.HFF'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 584
    Top = 424
  end
  object DialogBackGroundColor: TColorDialog
    Ctl3D = True
    Options = [cdFullOpen]
    Left = 740
  end
  object DialogForegroundColor: TColorDialog
    Ctl3D = True
    Options = [cdFullOpen]
    Left = 768
  end
  object TimerAutoSave: TTimer
    Interval = 300000
    OnTimer = AutoSave
    Left = 616
    Top = 424
  end
  object DialogFringingColor: TColorDialog
    Ctl3D = True
    Options = [cdFullOpen]
    Left = 792
  end
  object DialogMapData: TOpenDialog
    DefaultExt = '.map'
    Filter = 'Map Data|*.dat'
    Left = 368
  end
  object DialogTileData: TOpenDialog
    DefaultExt = '.td'
    Filter = 'Tile Data|*.td'
    Left = 392
  end
  object NewLevelDialog: TSaveDialog
    Left = 287
    Top = 443
  end
end
