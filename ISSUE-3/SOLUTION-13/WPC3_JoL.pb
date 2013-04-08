;  ATTENTION! 
;
;  don't forget to switch to "CONSOLE" at: 
; | Compiler | Compiler Options |  Executable Format | 
;
; open question are:
; ?? how to handle duplicate identical strings
; -> inform user and ignore them
; ?? how to handle duplicate strings if they had different case (hello <-> Hello)
; -> inform user, change doOnlyLCaseTest to #False for case sensitive testing
; -> can be switched off again with !s
;

Global verbose = #False
Global doOnlyLCaseTest = #True

; Structure for the linkedList 
Structure SList
  S$  ; input string
  U$  ; this is his 'unique' string
EndStructure

NewList StringList.SList()


Procedure.s SubStrSearch(t$, List Parameter.SList())
  ; search substrings of t$ in each element of LinkedList: Parameter()
  ;
  ; Return:
  ; unique substring, if exist OR
  ; t$, if no unique substring exist
  ; 
  ; doOnlyLCaseTest =TRUE
  ; --> searching for unique substring is case insensitive (as shown in blog)
  ; doOnlyLCaseTest =FALSE
  ; --> searching for unique substring is case sensitive to get a unique substring with (hello,Hello -> h,H)
  
  i=1
  l=1           ; length of searchstring
  s$=""         ; substring of t$ with length l
  ls = Len(t$)  ; length of string which t$
  
  unique$ = ""	; return the 'unique' string
  
  ; save last position pointer, because we start searching from 1. element 
  PushListPosition(Parameter())
  
  Repeat
    
    ; Ergebnis$ = Mid(String$, StartPosition , Länge)
    s$ = Mid(t$, i, l)
    
    If verbose : Print (s$+"|") : EndIf
    
    counter = 0
    ForEach Parameter()
      
      p$=Parameter()\S$
      If doOnlyLCaseTest
        counter = counter + CountString(LCase(p$),LCase(s$))
      Else
        counter = counter + CountString(p$,s$)
      EndIf
      
    Next
    
    If counter = 1    ; h=1 if s$ only found in string which is tested himself
      unique$ = s$
    Else
      i=i+1     ; test, starting with next position in string
      
      If ((i+l-1)>ls)   ; i behind last char, 
        i=1     ; so start from 1.char 
        l=l+1   ; but inc length of searchstring 
        If verbose : PrintN("") : EndIf
        
      EndIf  
    EndIf
    
  Until ((unique$<>"") Or (l>ls))
  
  If verbose : Print (" found:"+unique$) : EndIf
  
  If unique$ = ""
    unique$ = t$
  EndIf
  If doOnlyLCaseTest
    unique$ = LCase(unique$)
  EndIf
  
  If verbose 
    PrintN(" Return:"+unique$)
    PrintN("")
  EndIf
  
  PopListPosition(Parameter())
  
  ;a$=Input()
  
  ProcedureReturn unique$
  
EndProcedure

Procedure.b IsDupSearch(t$, List Parameter.SList())
  ; search t$ in Parameter()
  ; Return:
  ; 0 if not found
  ; 1 if found and equal in case
  ; 2 if found and different in case
  found = 0
  
  ; save last position pointer, because we start searching from 1. element 
  PushListPosition(Parameter())
  
  If FirstElement(Parameter()) = 0  ; if FirstElemen() returns 0 -> empty list
    found = 0
  Else
    Repeat
      If (LCase(t$) = LCase(Parameter()\S$))
        found = 2
        If (t$ = Parameter()\S$)
          found = 1
        EndIf
      EndIf
      
    Until ( (found>0) Or (NextElement(Parameter()) = 0) )  ; if NextElemen() returns 0 -> end of list reached
  EndIf
  PopListPosition(Parameter())
  
  ProcedureReturn found
  
EndProcedure

; #####################################################################

If OpenConsole()
  
  ; add the four teststrings, can be deleted with !c
  AddElement(StringList())
  StringList()\S$ = "A13-OLinuXino"
  StringList()\U$ = ""
  AddElement(StringList())
  StringList()\S$ = "iMX233-OLinuXino"
  StringList()\U$ = ""
  AddElement(StringList())
  StringList()\S$ = "MOD-PULSE"
  StringList()\U$ = ""
  AddElement(StringList())
  StringList()\S$ = "MOD-IO"
  StringList()\U$ = ""
  
  
  PrintN("Olimex - WPC#3 - Solution in PureBasic by Joh.Lummel.")
  PrintN("to get a free test-version (Win/MacOS X/Linux/AmigOS)")
  PrintN("go to: http://www.purebasic.com/")
  PrintN("")
  PrintN("The four 'Example Strings' are always pre-stored!")
  PrintN("!c to clear them.")
  PrintN("")
  PrintN("[RETURN] or '<end>' to start searching the unique string's.")
  PrintN("'!l' to list all stored strings.")
  PrintN("'!c' to clear all strings.")
  PrintN("'!v' to toggle 'verbose'.")
  PrintN("'!s' to toggle 'case senitive'.")
  
  ; Lese alle Strings ein / get all strings
  Repeat
    Print (": ");
    a$= Input()
    
    ; ------ menue-handling... -----------------------------------------
    If a$="!c"
      ; delete every element in StringList()
      ClearList(StringList())
      PrintN("all strings deleted, start again...")
      PrintN("case sensitive testing is FALSE again.")
      
    ElseIf a$="!l" 
      ; List every element in StringList()
      ForEach StringList()
        PrintN(StringList()\S$+" -> "+StringList()\U$)
      Next
      If verbose
        PrintN("verbose is TRUE")
      Else
        PrintN("verbose is FALSE")
      EndIf
      If doOnlyLCaseTest
        PrintN("case sensitive testing is FALSE")
      Else
        PrintN("case sensitive testing is TRUE")
      EndIf
      
    ElseIf a$="!v"
      ; toggle 'verbose' output...
      If verbose
        verbose = #False
        PrintN("verbose is now FALSE")
      Else
        verbose = #True
        PrintN("verbose is now TRUE")
      EndIf
      
    ElseIf a$="!s"
      ; toggle 'doOnlyLCaseTesting' 
      If doOnlyLCaseTest
        doOnlyLCaseTest = #False
        PrintN("case sensitive testing is now TRUE")
      Else
        doOnlyLCaseTest = #True
        PrintN("case sensitive testing is now FALSE")
      EndIf
      
    ElseIf (a$<>"" And a$<>"<end>")
      ; add the new element to StringList()
      Select IsDupSearch(a$, StringList())
        Case 0 ; not found in list
          AddElement(StringList())
          StringList()\S$ = a$
        Case 1 ; equal string found in list
          PrintN("equal string always in list -> input ignored!")
        Case 2
          PrintN("same string with different case always in list.")
          PrintN("case sensitive testing is now TRUE")
          doOnlyLCaseTest = #False
          AddElement(StringList())
          StringList()\S$ = a$
      EndSelect
      
    Else
      If ListSize(StringList()) = 0
        Print ("Empty list! Sure to exit? (y/N) ")
        If LCase(Input()) <> "y"
          a$ = "."
        EndIf
      EndIf
      
    EndIf
    
  Until (a$="" Or a$="<end>")
  PrintN("")
  
  
  ; -------------------------------------------------------------------------------
  
  
  ; do it only if at least one string in list 
  If ListSize(StringList()) > 0
    
    Print ("Searching the 'unique' strings")
    If verbose
      PrintN("")
    EndIf
    
    ; Suche das Vorkommen aller möglichen SubStrings in allen Strings der Liste / 
    ; search all possible subStrings in all strings of the stored list to find 
    ; a 'unique' string
    ForEach StringList()
      If verbose
        PrintN("testing: "+StringList()\S$)
      Else 
        Print(".")
      EndIf
      StringList()\U$ = SubStrSearch(StringList()\S$, StringList())
      
    Next
    PrintN("")
    
    
    ; -------------------------------------------------------------------------------
    
    
    ; print the 'unique string' of each string
    PrintN("Ok, all done.")
    PrintN("Here are the 'unique' substring of each string:")
    
    ForEach StringList()
      Print (StringList()\S$+" -> ")
      PrintN(StringList()\U$)
    Next
    PrintN("")
    
    ; -------------------------------------------------------------------------------
    
  EndIf
  
  PrintN("That's all, folks...")
  Print ("[Return] to quit")
  a$=Input()
  
  CloseConsole()
EndIf

End
; IDE Options = PureBasic 5.11 (Windows - x86)
; ExecutableFormat = Console
; CursorPosition = 16
; FirstLine = 10
; Folding = 9
; EnableOnError
; Executable = WPC3_JoL
; DisableDebugger