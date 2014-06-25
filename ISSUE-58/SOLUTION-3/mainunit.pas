unit MainUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, EditBtn,
  StdCtrls, ExtCtrls, RTTICtrls;

type

  { TMainForm }

  TMainForm = class(TForm)
    DateEdit: TDateEdit;
    DateLabel: TLabel;
    OutputLabel: TLabel;
    RadioGroup: TRadioGroup;
    procedure DateEditEditingDone(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Recalc;
  private
    { private declarations }
    function CalcDays(Year, Month, Day: Int64): Int64;
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

procedure TMainForm.Recalc;
var FromDays, ToDays, DeltaDays, DeltaSeconds: Int64;
    Year, Month, Day: Word;
begin
  DecodeDate(DateEdit.Date, Year, Month, Day);
  ToDays := CalcDays(Year, Month, Day);
  if (RadioGroup.ItemIndex = 0)
     then FromDays := CalcDays(1,1,1)
     else FromDays := CalcDays(1582,10,15);
  DeltaDays := ToDays - FromDays;
  DeltaSeconds := DeltaDays * 24 * 60 * 60;
  OutputLabel.Caption := IntToStr(DeltaSeconds) + ' seconds';
end;

function TMainForm.CalcDays(Year, Month, Day: Int64): Int64;
var y, m, d: Int64;
begin
  d := Day;
  if (Month <= 2) then
    begin
      m := Month + 13;
      y := Year - 1;
    end
  else
    begin
      m := Month + 1;
      y := Year;
    end;
  result := y * 365 + y div 4 - y div 100 + y div 400 + m * 306001 div 10000 + d - 429;
end;

procedure TMainForm.DateEditEditingDone(Sender: TObject);
begin
  try
     StrToDate(DateEdit.Text);
     Recalc;
  except on EConvertError do
    OutputLabel.Caption := 'Invalid date';
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  FormatSettings.ShortDateFormat := 'd/m/y';
  FormatSettings.DateSeparator := '-';
end;

end.

