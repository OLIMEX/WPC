(*
  Olimex WPC # 44 - ECG heart beat detection
  Not to be used for medical purposes.
*)

unit DataUnit;

{$mode objfpc}{$H+}

interface

uses Classes, SysUtils, ContNrs;

type Peak = class(TObject)
  public
    time: integer;
    value: double;
    constructor Create(atime: integer; avalue: double);
end;

var RawData: Array of word;
    LowData: Array of word;
    BandData: Array of double;
    RectData: Array of double;
    AvgData:  Array of double;
    DetectData: Array of double;
    Peaks: TFPObjectList;
    PeakData: Array of word;

procedure LoadData;
procedure LowPass;
procedure BandPass;
procedure Rectify;
procedure Average;
procedure Detect;
procedure PeakDetect;
procedure CalcBPM;

implementation

uses StrUtils, MainUnit;

type

DataPoint = record
  index: integer;
  case ba: boolean of
    true:  (bytes: packed array[1..17] of byte);
    false: (sync0: byte;
            sync1: byte;
            version: byte;
            count: byte;
            data: array[1..6] of word;
            switches: byte;
            );
end;

// Read ECG data from file
procedure LoadData;
var f:file of char;
    c1:char;
    c2:char;
    b: byte;
    cnt: byte;
    r: Datapoint;
    npoints: integer;
begin
  assignfile(f, 'ECGSAMPLE.txt');
  reset(f);
  npoints := 1;
  SetLength(RawData,100);
  while not eof(f) do
  begin
    r.index := npoints;
    // Read 17 bytes
    for cnt := 1 to 17 do
     begin
      if not eof(f) then
        begin
          // Read first hex char
          read(f,c1);
          if not eof(f) then
            begin
              // Read second hex char
              read(f,c2);
              // Glue together and convert to byte
              b := Hex2Dec(c1+c2);
              // Store byte in DataPoint record
              r.bytes[cnt] := b;
            end;
        end;
     end;
    // Change the words from big endian to little endian (if needed)
    for cnt := 1 to 6 do
     r.data[cnt] := BEtoN(r.data[cnt]);
    if r.data[1] < 1024 then
      begin
        if npoints > Length(RawData) then
          SetLength(RawData, Length(RawData) + 100);
        RawData[npoints-1] := r.data[1];
        inc(npoints);
      end;
  end;
  SetLength(RawData, npoints-1);
  closefile(f);
end;

(* Not used - 40 Hz first order Butterworth low pass filter *)
procedure LowPass;
var gain: double;
    x0, x1, y0, y1: double;
    i: integer;
begin
  gain := 2.870868412;
  x0 := 0;
  x1 := 0;
  y0 := 0;
  y1 := 0;
  SetLength(LowData, Length(RawData));
  for i := 0 to Length(RawData)-1 do
     begin
       x0 := x1;
       x1 := RawData[i] / gain;
       y0 := y1;
       y1 := x0 + x1 + (0.3033466836 * y0);
       LowData[i] := Trunc(y1);
     end;
end;

(* Second order Butterworth 5 - 15 Hz bandpass filter *)
procedure BandPass;
var i: integer;
    gain: double;
    x: array[0..4] of double;
    y: array[0..4] of double;
begin
  gain := 78.06121597;
  for i:=0 to 4 do
   begin
     x[i] := 0;
     y[i] := 0;
   end;
  SetLength(BandData, Length(RawData));
  for i := 0 to Length(RawData)-1 do
     begin
       x[0] := x[1]; x[1] := x[2]; x[2] := x[3]; x[3] := x[4];
       x[4] := RawData[i] / gain;
       y[0] := y[1]; y[1] := y[2]; y[2] := y[3]; y[3] := y[4];
       y[4] :=  (x[0] + x[4]) - 2 * x[2]
            + (-0.7067570632 * y[0]) + (2.9997032491 * y[1])
            + (-4.8675901033 * y[2]) + (3.5729237611 * y[3]);
       BandData[i] := y[4];
     end;
end;

(* Rectify the signal *)
procedure Rectify;
var i: integer;
begin
 SetLength(RectData, Length(BandData));
 for i:=0 to Length(BandData)-1 do
    RectData[i] := Abs(BandData[i]);
end;

(* Average the signal over an 80 ms interval *)
procedure Average;
var i,j: integer;
    sum: double;
begin
 SetLength(AvgData, Length(RectData));
 for i := 10 to Length(RectData)-11 do
    begin
      sum := 0;
      for j := -10 to 10 do
         begin
           sum := sum + RectData[i+j];
         end;
      AvgData[i] := sum / 21;
    end;
end;

constructor Peak.Create(atime: integer; avalue: double);
begin
 time := atime;
 value := avalue;
end;

(* Detect candidate peaks by detecting a drop below max/2 *)
procedure Detect;
var i: integer;
    max: double;
    maxpos: integer;
begin
 SetLength(DetectData, Length(AvgData));
 if Peaks <> nil then Peaks.Free;
 Peaks := TFPObjectList.Create(true);
 max := 0;
 maxpos := 0;
 for i := 0 to Length(AvgData)-1 do
    begin
      if AvgData[i] > max then
         begin
          max := AvgData[i];
          maxpos := i;
         end
      else
        begin
          if AvgData[i] < max/2 then
            begin
              Peaks.Add(Peak.Create(maxpos, max));
              max := AvgData[i];
              maxpos := i;
            end;
        end;
      DetectData[i] := max;
    end;
end;

(* Peak detection *)
procedure PeakDetect;
var i: integer;
    max: double;
    apeak : Peak;
    maxpeak: Peak;
    treshold: double;
    removed: integer;
begin
 max := 0 ;
 // Determine treshold
 for i:=0 to Peaks.Count-1 do
    begin
     apeak := Peak(Peaks.Items[i]);
     if apeak.value > max then
       begin
         max := apeak.value;
       end;
    end;
  treshold := max+1;
  //
  repeat
    // Detect biggest peak below treshold
    max := 0;
    removed := 0;
    for i:=0 to Peaks.Count-1 do
       begin
        apeak := Peak(Peaks.Items[i]);
        if (apeak.value > max) and (apeak.value < treshold) then
          begin
            max := apeak.value;
            maxpeak := apeak;
          end;
       end;
     // Remove peaks in 0.5 second interval around biggest peak
     // This limits max rate to 120 bpm
     i := 0;
     while i < Peaks.Count do
       begin
         apeak := Peak(Peaks.Items[i]);
         if (abs(apeak.time - maxpeak.time) < 128) and (apeak.time <> maxpeak.time) then
           begin
             Peaks.Remove(apeak);
             inc(removed);
             Peaks.Pack;
           end
         else
          inc(i);
       end;
     treshold := max;
  until removed = 0;
  // Visual representation of peaks
  SetLength(PeakData, Length(RawData));
  for i:=0 to Peaks.Count-1 do
     begin
       apeak := Peak(Peaks.Items[i]);
       PeakData[apeak.time] := 500;
     end;
end;

(* Calculate and display beats per minute *)
procedure CalcBPM;
var i, sum, cnt: integer;
    avg, avgms, bpm: double;
begin
  sum := 0;
  cnt := 0;
  for i:=0 to Peaks.Count-2 do
    begin
      sum := sum + Peak(Peaks.Items[i+1]).time - Peak(Peaks.Items[i]).time;
      inc(cnt);
    end;
  avg := sum / cnt;
  avgms := avg / 256;
  bpm := Round(100 * 60 / avgms) / 100;
  MainForm.BPMLabel.Caption := FloatToStr(bpm);
end;

end.

