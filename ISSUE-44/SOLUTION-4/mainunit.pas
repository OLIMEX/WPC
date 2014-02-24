(*
  Olimex WPC # 44 - ECG heart beat detection
  Not to be used for medical purposes.
*)

unit MainUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  TAGraph, TASeries;

type

  { TMainForm }

  TMainForm = class(TForm)
    Button1: TButton;
    Chart: TChart;
    BandSeries: TLineSeries;
    AvgSeries: TLineSeries;
    BPMLabel: TLabel;
    Label1: TLabel;
    PeakSeries: TLineSeries;
    DetectSeries: TLineSeries;
    RectSeries: TLineSeries;
    RawSeries: TLineSeries;
    procedure Button1Click(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

uses DataUnit;

procedure TMainForm.Button1Click(Sender: TObject);
var npt: integer;
begin
  DataUnit.LoadData;
  DataUnit.LowPass;
  DataUnit.BandPass;
  DataUnit.Rectify;
  DataUnit.Average;
  DataUnit.Detect;
  DataUnit.PeakDetect;
  DataUnit.CalcBPM;

  RawSeries.Clear;
  BandSeries.Clear;
  RectSeries.Clear;
  AvgSeries.Clear;
  DetectSeries.Clear;

  for npt := 0 to Length(DataUnit.RawData)-1 do
    RawSeries.AddXY(npt/256,DataUnit.RawData[npt]);
  for npt := 0 to Length(DataUnit.BandData)-1 do
    BandSeries.AddXY(npt/256,DataUnit.BandData[npt]);
  for npt := 0 to Length(DataUnit.RectData)-1 do
    RectSeries.AddXY(npt/256,DataUnit.RectData[npt]);
  for npt := 0 to Length(DataUnit.AvgData)-1 do
    AvgSeries.AddXY(npt/256,DataUnit.AvgData[npt]);
  for npt := 0 to Length(DataUnit.DetectData)-1 do
    DetectSeries.AddXY(npt/256,DataUnit.DetectData[npt]);
  for npt := 0 to Length(DataUnit.PeakData)-1 do
    PeakSeries.AddXY(npt/256,DataUnit.PeakData[npt]);

  Chart.Extent.XMax := RawSeries.GetXMax;
  Chart.Extent.YMax := RawSeries.GetYMax;
end;

end.

