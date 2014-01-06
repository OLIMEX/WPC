unit uGrav;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  ComCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Image: TImage;
    TrackBarY: TTrackBar;
    TrackBarX: TTrackBar;
    procedure FormCreate(Sender: TObject);
    procedure ImageMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ImageMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer
      );
    procedure ImageMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    FDrawing: Boolean;
    procedure NewImage;
    procedure WPC38;
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
begin
  NewImage;
  WPC38;
end;

procedure TForm1.ImageMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  FDrawing := True;
end;

procedure TForm1.ImageMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
const
  R = 3;
begin
  if FDrawing then
  begin
    X := X div 2;
    Y := Y div 2;
    Image.Picture.Bitmap.Canvas.Brush.Color := clBlack;
    Image.Picture.Bitmap.Canvas.Rectangle(X-R, Y-R, X+R, Y+R);
    WPC38;
  end;
end;

procedure TForm1.ImageMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  FDrawing := False;
end;

procedure TForm1.NewImage;
const
  P = 13;
  DP = 2*P;
var
  W, H: Integer;
begin
  W := Image.Picture.Width;
  H := Image.Picture.Height;

  Image.Width := 2 * W;
  Image.Height := 2 * H;

  TrackBarX.Left := Image.Left - P;
  TrackBarX.Width := Image.Width + DP;
  TrackBarX.Max := W - 1;

  TrackBarY.Top := Image.Top - P;
  TrackBarY.Height := Image.Height + DP;
  TrackBarY.Max := H - 1;

  Self.Width := Image.Left + Image.Width + P;
  Self.Height := Image.Top + Image.Height + P;
end;

type
  TRGB = packed record
    case Integer of
      0: (V: Integer);
      1: (R, G, B, A: Byte);
  end;


procedure TForm1.WPC38;
var
  V: TRGB;
  L, P: Integer;
  D, X, Y, T: Double;
begin
  X := 0.0;
  Y := 0.0;
  T := 0.0;
  for L := 0 to Image.Picture.Height - 1 do
    for P := 0 to Image.Picture.Width - 1 do
    begin
      V := TRGB(Image.Picture.Bitmap.Canvas.Pixels[P,L]);
      D := (255 * 3 - V.R - V.G - V.B)/(255.0 * 3);
      X := X + D * P;
      Y := Y + D * L;
      T := T + D;
    end;
  X := X / T;
  Y := Y / T;
  TrackBarX.Position := Trunc(X);
  TrackBarY.Position := Trunc(Y);
end;

end.

