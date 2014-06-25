program seconds;

(*
 *
 * Olimex WPC 58
 * Convert Gregorian date to seconds elapsed since ...
 *
 * Environment:
 * - Linux Mint 17
 * - Lazarus 1.0.10
 *
 *)

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Interfaces, // this includes the LCL widgetset
  Forms, runtimetypeinfocontrols, MainUnit
  { you can add units after this };

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.

