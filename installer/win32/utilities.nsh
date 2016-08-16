;--------------------------------
; Utility functions

Function is64BitWindows

  Push $0
  Push $1
  Push $2
  ReadRegStr $0 HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PROCESSOR_ARCHITECTURE"
  ${StrStr}  $1 "$0" "x86"
  ${StrStr}  $2 "$0" "X86"
  StrCpy $0 "0"

  StrCmp $1 "" x64yes
  StrCmp $2 "" x64yes x64no

x64yes:
  StrCpy $0 "1"

x64no:

  Pop  $2
  Pop  $1
  Exch $0

FunctionEnd

Function un.is64BitWindows

  Push $0
  Push $1
  Push $2
  ReadRegStr $0 HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PROCESSOR_ARCHITECTURE"
  ${UnStrStr}  $1 "$0" "x86"
  ${UnStrStr}  $2 "$0" "X86"
  StrCpy $0 "0"

  StrCmp $1 "" x64yes
  StrCmp $2 "" x64yes x64no

x64yes:
  StrCpy $0 "1"

x64no:

  Pop  $2
  Pop  $1
  Exch $0

FunctionEnd

; Usage:
;   Push 3                 ; to get the 3rd parameter of the command line
;   Call GetONEParameter
;   Pop $R0                ; saves the result in $R0
; returns an empty string if not found

Function GetONEParameter
   Exch $R0
   Push $R1
   Push $R2
   Push $R3
   Push $R4
   Push $R5
   Push $R6

; init variables
   IntOp $R5 $R0 + 1
   StrCpy $R2 0
   StrCpy $R4 1
   StrCpy $R6 0

   loop3: ; looking for a char that's not a space
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 " " loop3
     StrCpy $R3 $R2   ; found the beginning of the current parameter


   loop:          ; scanning for the end of the current parameter

     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 " " loop2
     StrCmp $R0 "" last
     IntOp $R2 $R2 + 1
     Goto loop

   last: ; there will be no other parameter to extract
   StrCpy $R6 1

   loop2: ; found the end of the current parameter

   IntCmp $R4 $R5 0 NextParam end
   StrCpy $R6 1 ; to quit after this process

   IntOp $R1 $R2 - $R3 ;number of letter of current parameter
   StrCpy $R0 $CMDLINE $R1 $R3        ; stores the result in R0

   NextParam:
   IntCmp $R6 1 end ; leave if found or if not enough parameters

   ; process the next parameter
   IntOp $R4 $R4 + 1

   Goto loop3

   end:

   Pop $R6  ; restore R0 - R6 to their initial value
   Pop $R5
   Pop $R4
   Pop $R3
   Pop $R2
   Pop $R1

   Exch $R0    ;Puts the result on the stack

 FunctionEnd
 
 ; from http://nsis.sourceforge.net/GetTime
 !macro GetTimeWrapper un
   Function ${un}GetTime
    Exch $1
    Exch
    Exch $0
    Exch
    Push $2
    Push $3
    Push $4
    Push $5
    Push $6
    Push $7
    ClearErrors
   
    StrCmp $1 'L' gettime
    StrCmp $1 'A' getfile
    StrCmp $1 'C' getfile
    StrCmp $1 'M' getfile
    StrCmp $1 'LS' gettime
    StrCmp $1 'AS' getfile
    StrCmp $1 'CS' getfile
    StrCmp $1 'MS' getfile
    goto error
   
    getfile:
    IfFileExists $0 0 error
    System::Call /NOUNLOAD '*(i,l,l,l,i,i,i,i,&t260,&t14) i .r6'
    System::Call /NOUNLOAD 'kernel32::FindFirstFileA(t,i)i(r0,r6) .r2'
    System::Call /NOUNLOAD 'kernel32::FindClose(i)i(r2)'
   
    gettime:
    System::Call /NOUNLOAD '*(&i2,&i2,&i2,&i2,&i2,&i2,&i2,&i2) i .r7'
    StrCmp $1 'L' 0 systemtime
    System::Call /NOUNLOAD 'kernel32::GetLocalTime(i)i(r7)'
    goto convert
    systemtime:
    StrCmp $1 'LS' 0 filetime
    System::Call /NOUNLOAD 'kernel32::GetSystemTime(i)i(r7)'
    goto convert
   
    filetime:
    System::Call /NOUNLOAD '*$6(i,l,l,l,i,i,i,i,&t260,&t14)i(,.r4,.r3,.r2)'
    System::Free /NOUNLOAD $6
    StrCmp $1 'A' 0 +3
    StrCpy $2 $3
    goto tolocal
    StrCmp $1 'C' 0 +3
    StrCpy $2 $4
    goto tolocal
    StrCmp $1 'M' tolocal
   
    StrCmp $1 'AS' tosystem
    StrCmp $1 'CS' 0 +3
    StrCpy $3 $4
    goto tosystem
    StrCmp $1 'MS' 0 +3
    StrCpy $3 $2
    goto tosystem
   
    tolocal:
    System::Call /NOUNLOAD 'kernel32::FileTimeToLocalFileTime(*l,*l)i(r2,.r3)'
    tosystem:
    System::Call /NOUNLOAD 'kernel32::FileTimeToSystemTime(*l,i)i(r3,r7)'
   
    convert:
    System::Call /NOUNLOAD '*$7(&i2,&i2,&i2,&i2,&i2,&i2,&i2,&i2)i(.r5,.r6,.r4,.r0,.r3,.r2,.r1,)'
    System::Free $7
   
    IntCmp $0 9 0 0 +2
    StrCpy $0 '0$0'
    IntCmp $1 9 0 0 +2
    StrCpy $1 '0$1'
    IntCmp $2 9 0 0 +2
    StrCpy $2 '0$2'
    IntCmp $6 9 0 0 +2
    StrCpy $6 '0$6'
   
    StrCmp $4 0 0 +3
    StrCpy $4 Sunday
    goto end
    StrCmp $4 1 0 +3
    StrCpy $4 Monday
    goto end
    StrCmp $4 2 0 +3
    StrCpy $4 Tuesday
    goto end
    StrCmp $4 3 0 +3
    StrCpy $4 Wednesday
    goto end
    StrCmp $4 4 0 +3
    StrCpy $4 Thursday
    goto end
    StrCmp $4 5 0 +3
    StrCpy $4 Friday
    goto end
    StrCmp $4 6 0 error
    StrCpy $4 Saturday
    goto end
   
    error:
    SetErrors
    StrCpy $0 ''
    StrCpy $1 ''
    StrCpy $2 ''
    StrCpy $3 ''
    StrCpy $4 ''
    StrCpy $5 ''
    StrCpy $6 ''
   
    end:
    Pop $7
    Exch $6
    Exch
    Exch $5
    Exch 2
    Exch $4
    Exch 3
    Exch $3
    Exch 4
    Exch $2
    Exch 5
    Exch $1
    Exch 6
    Exch $0
  FunctionEnd
!macroend

!insertmacro GetTimeWrapper "un."
!insertmacro GetTimeWrapper ""
