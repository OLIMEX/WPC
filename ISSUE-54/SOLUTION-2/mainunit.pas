unit mainunit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  TAGraph, TASources, TASeries, TATools, TATransformations, sndfile, ucomplex,
  math;

const bufsize = 1024;
      points = 65536;

type

  { TMainForm }

  TMainForm = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Label2: TLabel;
    LogAxisTransformations: TChartAxisTransformations;
    ChartAxisTransformations1LogarithmAxisTransform1: TLogarithmAxisTransform;
    FFTChart: TChart;
    FFTChartLineSeries1: TLineSeries;
    FFTChartSource: TListChartSource;
    Label1: TLabel;
    FilenameLabel: TLabel;
    FileOpenDialog: TOpenDialog;
    SndChart: TChart;
    SndChartLineSeries1: TLineSeries;
    SndChartSource: TListChartSource;
    procedure FileButtonClick(Sender: TObject);
    procedure TestButtonClick(Sender: TObject);
  private
    { private declarations }
    data: array[0..points-1] of double;
    fftbuf: array[0..points-1] of complex;
    rate: integer;
    procedure SineTest;
    procedure LoadSndFile(filename: String);
    procedure FFT;
    procedure DisplayFFT;
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

procedure TMainForm.LoadSndFile(filename: String);
var
  buffer: array[0..bufsize-1] of double;
  sfile: psndfile;
  sinfo: TSF_INFO;
  cnt: longint;
  i: longint;
  x: longint;
begin
  SndChartSource.Clear;
  for i := 0 to points - 1 do
    begin
      data[i] := 0;
      fftbuf[i].re := 0;
      fftbuf[i].im := 0;
    end;
  sfile := sf_open(PChar(filename), SFM_READ, @sinfo);
  rate := sinfo.samplerate;
  cnt := sf_read_double(sfile, @buffer, bufsize);
  x := 0;
  while (cnt <> 0) and (x < points-1) do
    begin
      for i:=0 to bufsize-1 do
        begin
          SndChartSource.Add(x,buffer[i]);
          if (x < points-1) then
             data[x] := buffer[i];
          inc(x);
        end;
      cnt := sf_read_double(sfile, @buffer, bufsize);
    end;
  sf_close(sfile) ;
end;

procedure TMainForm.SineTest;
var i: longint;

begin
  SndChartSource.Clear;
  rate := 44100;
  for i := 0 to points - 1 do
    begin
      data[i] := 10 * sin(i * 2 * pi *  1000 / rate) +
                  5 * sin(i * 2 * pi *  5000 / rate) +
                  1 * sin(i * 2 * pi * 10000 / rate);
      SndChartSource.Add(i,data[i]);
      fftbuf[i].re := 0;
      fftbuf[i].im := 0;
    end;
end;

procedure TMainForm.FFT;
var sqrpoints: double;
    logpoints: integer;
    p: integer;
    u, t: complex;
    w: array of array of complex;
    i, j, l, l2, r, h, m, s, lev, incr: integer;
    rev: array[0..points-1] of integer;
begin
  sqrpoints := sqrt(points);
  p := points;
  logpoints := 0;
  dec(p);
  while (p <> 0) do
   begin
        p := p shr 1;
        inc(logpoints);
   end;
   setlength(w, logpoints+1);
   l2 := 2;
   for l := 1 to logpoints do
     begin
       setlength(w[l], points);
       for i := 0 to points-1 do
         begin
           w[l][i].re:=  cos(2 * pi * i / l2);
           w[l][i].im:= -sin(2 * pi * i / l2);
         end;
       l2 := l2 * 2;
     end;
    r := 0;
    h := points div 2;
    for i := 0 to points - 2 do
      begin
        rev[i] := r;
        m := h;
        while (r >= m) do
          begin
            r := r - m;
            m := m shr 1;
          end;
        r := r + m;
      end;
     rev[points-1] := points - 1;
    //
    for i := 0 to points-1 do
      begin
        fftbuf[rev[i]].re := data[i];
      end;
    //
    s := 1;
    for lev := 1 to logpoints do
      begin
        incr := s * 2;
        for j := 0 to s -1 do
          begin
            u := w[lev][j];
            i := j;
            while (i < points) do
              begin
                t := u;
                t := t * fftbuf[i+s];
                fftbuf[i+s] := fftbuf[i];
                fftbuf[i+s] := fftbuf[i+s] - t;
                fftbuf[i] := fftbuf[i] + t;
                i := i + incr;
              end;
          end;
        s := s * 2;
      end;
end;

procedure TMainForm.DisplayFFT;
var i: integer;
begin
  FFTChartSource.Clear;
  for i := 0 to  (points div 2) - 1 do
    FFTChartSource.Add(i * rate / points, sqrt(sqr(fftbuf[i].re)+sqr(fftbuf[i].im)));
end;

procedure TMainForm.FileButtonClick(Sender: TObject);
begin
  if FileOpenDialog.Execute then
     begin
       FilenameLabel.Caption := SysUtils.ExtractFileName(FileOpenDialog.FileName);
       LoadSndFile(FileOpenDialog.FileName);
       FFT;
       DisplayFFT;
     end;
end;

procedure TMainForm.TestButtonClick(Sender: TObject);
begin
  FilenameLabel.Caption := '1 kHz + 5 kHz + 10 kHz sine waves';
  SineTest;
  FFT;
  DisplayFFT;
end;


end.

