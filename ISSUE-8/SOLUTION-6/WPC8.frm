VERSION 5.00
Begin VB.Form WPC8 
   AutoRedraw      =   -1  'True
   Caption         =   "WPC8"
   ClientHeight    =   6285
   ClientLeft      =   4350
   ClientTop       =   2565
   ClientWidth     =   9885
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   6285
   ScaleWidth      =   9885
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   495
      Left            =   1440
      TabIndex        =   7
      Top             =   5040
      Width           =   1575
   End
   Begin VB.CommandButton Exit 
      Caption         =   "Exit"
      Height          =   495
      Left            =   6840
      TabIndex        =   6
      Top             =   5040
      Width           =   1695
   End
   Begin VB.TextBox Misses_Text 
      Height          =   600
      Left            =   5000
      MaxLength       =   28
      TabIndex        =   5
      Top             =   3840
      Width           =   3000
   End
   Begin VB.TextBox Guess_Text 
      Height          =   600
      Left            =   5000
      MaxLength       =   1
      TabIndex        =   1
      Top             =   3045
      Width           =   3000
   End
   Begin VB.TextBox Word_Text 
      Height          =   600
      Left            =   5000
      MaxLength       =   20
      TabIndex        =   4
      Top             =   2235
      Width           =   3000
   End
   Begin VB.Label Misses_Label 
      AutoSize        =   -1  'True
      Caption         =   "Misses"
      Height          =   240
      Left            =   3840
      TabIndex        =   3
      Top             =   3960
      Width           =   615
   End
   Begin VB.Label Guess_Lable 
      AutoSize        =   -1  'True
      Caption         =   "Guess"
      Height          =   240
      Left            =   3840
      TabIndex        =   2
      Top             =   3240
      Width           =   570
   End
   Begin VB.Label Word_Lable 
      AutoSize        =   -1  'True
      Caption         =   "Word"
      Height          =   240
      Left            =   3840
      TabIndex        =   0
      Top             =   2400
      Width           =   510
   End
End
Attribute VB_Name = "WPC8"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit     'Variant declaration is a must.

Public TotalWords As Long     'Public TotalWords is callable during the whole process.
Private Word As String     'Each Sub is able to change and use the random word.

Private Sub Exit_Click()     'Click Exit button to end the program.
    End
End Sub

Private Sub Form_Load()   'While program starts, load the form.

    Me.Show     'Display form.
   
    'Set Maxlength of Textbox.
    Word_Text.MaxLength = 20
    Guess_Text.MaxLength = 1
    Misses_Text.MaxLength = 20
    
     'All three Textbox is unable to input when form is loaded.
    Word_Text.Enabled = False
    Guess_Text.Enabled = False
    Misses_Text.Enabled = False
    
    Start.SetFocus   'Start button get focus.
    
    'Print brief introduction of the game.
    Print "Welcome to play HANGMAN Game!"
    Print "The player will have N times to guess random generated word from dictionary D:\A-Z Words.txt."
    Print "N depends on the number of letters in the random word."
    Print "Each time the player can input one letter only to guess in the middle textbox."
    Print "After N times attempts if the player still can not guess the right word then the game is over."
    Print "Remember that each random word includes 2~10 letters"
    Print "Misses letters will be displayed in the bottom textbox."
    Print "Enjoy the game :-)"
    
    'Open the dictionary from file (Path:"D:\A-Z Words.txt") and caculate total words in the dictionary.
    TotalWords = 0
    Open "D:\A-Z Words.txt" For Input As #1
        While Not EOF(1)
            Line Input #1, Word
            If Len(Word) >= 2 Then     'Every word in the dictionary >=2.
                TotalWords = TotalWords + 1
            End If
        Wend
    Close #1

End Sub

Private Sub Start_Click()

    Dim i As Long      'Mark i=i+1 when i=Count the random word is created.
    Dim Count As Long  'Count is used to locate line number of the random word in the dictionary: A-Z Words.txt
    
    Cls     'Clear Form printing
         
    Misses_Text.Text = ""
    Start.Enabled = False   'Make user the player is unable to make any change of Guess-Text Textbox before clicking Start button.
    Guess_Text.Enabled = True
    
    Randomize    'Make sure every time running the program with different random seed.
    Open "D:\A-Z Words.txt" For Input As #1     'Open the dictionary for input
        Count = Int(Rnd * TotalWords + 1)     'Locate line number of random word.
        Do While Not EOF(1)     'Read the file until line number is found.
            Line Input #1, Word
            i = i + 1
            If i = Count Then
                Exit Do
            End If
        Loop
    Close #1
    
    For i = 1 To Len(Word)
        Word_Text.Text = Word_Text.Text + "_" + " "    'Notify player how many letters exist in the random word.
    Next i
    
    Guess_Text.SetFocus
    
End Sub

Private Sub Guess_Text_Change()   'Once the player inputs a letter into Guess_Text Textbox, then do below process.

    Dim LetterCheck, Str As String     'LetterCheck: store one letter of random word, Str: get one word from dictionary.
    Dim i, j, WordLength As Integer     'i, j as loop variant, WordLength to store random word length.
    Static ChangeCount As Integer      'ChangeCount as Static type to record total letters the player input.
    Dim GuessLetterCorrect, Flag As Boolean     'While player guess one letter correct, set GuessLetterCorrect=True.

    WordLength = Len(Word)     'Get length of the random word.
    
    If Guess_Text.Text <> "" Then     'Avoid the case when backspace key is pressed Textbox will be empty.
        LetterCheck = Guess_Text.Text
    End If

    'The guess letter is between "a~z" and "A~Z". Record guessed letters to ChangeCount and display the missed letter.
    If (LetterCheck >= "a" And LetterCheck <= "z") Or (LetterCheck >= "A" And LetterCheck <= "Z") Then
        ChangeCount = ChangeCount + 1
        Misses_Text.Text = LCase(Misses_Text.Text + " " + LetterCheck)   'Change all letters to lower case.
    End If
    
    'Check each guess letter whether it is in the random word or not
    For i = 1 To WordLength
        If LetterCheck = Mid(Word, i, 1) Then
            GuessLetterCorrect = True
            Exit For
        Else
            GuessLetterCorrect = False
        End If
    Next i

    'In case the guess letter is in the random word then get the headmost new word from the dictionary
    'which with the same word length but exclusive the correctly guessed letter to cheat the player. :)
    
    If GuessLetterCorrect = True Then
        Open "D:\A-Z Words.txt" For Input As #1
            Do While Not EOF(1)
                Line Input #1, Str
                    Flag = False     'Set flag to judge whether it is the suitable new word.
                    If Len(Str) = WordLength Then
                        Flag = True
                        For i = 1 To Len(Str)
                            If Mid(Str, i, 1) = LetterCheck Then
                                Flag = False
                            End If
                        Next i
                    End If
                    
                    If Flag = True Then    'If it is, replace the previous word.
                        Word = Str
                        Exit Do
                        Close #1
                    End If
            Loop
        Close #1
    End If
    
    'Once player tried Len(Word) times (N times) ChangeCount=Len(Word)
    'it means player didn't guess the word correctly.
    If ChangeCount = Len(Word) Then
        ChangeCount = 0
        Cls
        Word_Text.Text = ""     'Empty Textbox
        Guess_Text.Text = ""
        Guess_Text.Enabled = False     'Unable to guess
        Print "Failed. Game is over!"
        Print "Click Start to guess other random words, click Exit to end."
        Start.Enabled = True     'The player can choose another word to guess.
        Start.SetFocus
    End If

End Sub

