unit MainUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    CalcButton: TButton;
    CircleButton: TButton;
    RadiusEdit: TEdit;
    XWidthEdit: TEdit;
    YHeightEdit: TEdit;
    XPosEdit: TEdit;
    YPosEdit: TEdit;
    Label1: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    AlphaLabel: TLabel;
    BetaLabel: TLabel;
    Shape: TShape;
    procedure CalcButtonClick(Sender: TObject);
    procedure CircleButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ShapePaint(Sender: TObject);
  private
    { private declarations }
    candraw: boolean;
    radius, X, Y, XWidth, YHeight, alpha, beta: double;
    procedure Calc;
    function GetParameters: Boolean;
  public
    { public declarations }
  end; 

var
  Form1: TForm1; 

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Calc;
begin
  alpha := (Y - X) / radius;
  beta := (-Y - X) / radius;
  candraw := true;
  self.Invalidate;
end;

function TForm1.GetParameters: Boolean;
begin
  result := true;
  radius := StrToFloat(RadiusEdit.Text);
  XWidth := StrToFloat(XWidthEdit.Text);
  YHeight := StrToFloat(YHeightEdit.Text);
  X := StrToFloat(XPosEdit.Text);
  Y := StrToFloat(YPosEdit.Text);
  if (abs(X) > ((XWidth / 2)  - (6 * radius))) then
    begin
      Application.MessageBox('X out of range', 'Error', 0);
      result := false;
    end;
  if (abs(Y) > ((YHeight / 2) - (6 * radius))) then
      begin
        Application.MessageBox('Y out of range', 'Error', 0);
        result := false;
      end;
end;

procedure TForm1.CalcButtonClick(Sender: TObject);
begin
  if (not GetParameters) then exit;
  Calc;
  AlphaLabel.Caption := FloatToStrF(alpha, ffFixed, 10,2);
  BetaLabel.Caption := FloatToStrF(beta, ffFixed, 10,2);
end;

procedure TForm1.CircleButtonClick(Sender: TObject);
var angle: double;
begin
  if (not GetParameters) then exit;
  angle := 0;
  while (angle <= PI*2) do
    begin
     X := 180 * cos(angle);
     Y := 180 * sin(angle);
     Calc;
     XPosEdit.Text := FloatToStr(X);
     YPosEdit.Text := FloatToStr(Y);
     AlphaLabel.Caption := FloatToStrF(alpha, ffFixed, 10,2);
     BetaLabel.Caption := FloatToStrF(beta, ffFixed, 10,2);
     self.Repaint;
     sleep(100);
     angle := angle + 0.1;
    end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  candraw := false;
end;

procedure TForm1.ShapePaint(Sender: TObject);
var scale, scalex, scaley: double;
    offx, offy: longint;
    w, h: longint;
    xw, yh: double;
    gx, gy: longint;
    gw: longint;
    tw, th: longint;
    tx, ty: longint;
    rrx, rry, lrx, lry: longint;
    sr: longint;
begin
  if (not candraw) then
    exit;

  // Drawing scale
  scalex := Shape.Width /  XWidth;
  scaley := Shape.Height / (2 * YHeight);
  if (scalex < scaley) then
      scale := scalex
  else
      scale := scaley;

  w := Shape.Width;
  h := Shape.Height;
  xw := XWidth;
  yh := YHeight;
  sr := trunc(scale*radius);

  // Drawing offset from edges
  offx := (w - trunc(scale * xw)) div 2;
  offy := (h - trunc(scale * 2 * yh)) div 2;

  // X roller positions
  rrx := offx + 0;
  rry := offy + h div 2;
  lrx := offx + trunc(scale * xw);
  lry := offy + h div 2;

  // Gantry width and position
  gw := trunc(scale*2*radius);
  gx := rrx + trunc(scale * (xw/2 + x)) ;
  gy := rry;

  // Tool width and height
  tw := gw - sr;
  th := gw div 2;

  // Tool position
  tx := rrx + trunc(scale * (xw/2 + x));
  ty := rry + trunc(scale * 2 * radius) + trunc(scale * (yh/2 - y));

  with Shape.Canvas do
    begin
         Pen.Color := clBlack;
         Pen.Width := 1;
         Pen.Style := psSolid;

         Brush.Color := clBlue;

         // Left and right rollers
         Ellipse(rrx - sr, rry - sr, rrx + sr, rry + sr);
         Ellipse(lrx - sr, lry - sr, lrx + sr, lry + sr);

         Brush.Color := clGreen;

         // Gantry
         Rectangle(gx-gw, gy-gw, gx+gw, gy+gw);

         // Gantry rollers
         Ellipse(gx-gw-sr, gy-gw-sr,gx-gw+sr,gy-gw+sr);
         Ellipse(gx+gw-sr, gy-gw-sr,gx+gw+sr,gy-gw+sr);
         Ellipse(gx-gw-sr, gy+gw-sr,gx-gw+sr,gy+gw+sr);
         Ellipse(gx+gw-sr, gy+gw-sr,gx+gw+sr,gy+gw+sr);

         Brush.Color := clRed;

         // Top Y arm roller
         Ellipse(tx-sr, ty-sr-trunc(scale*yh), tx+sr,ty+sr-trunc(scale*yh));

         // Tool
         Rectangle(tx-tw, ty-th, tx+tw, ty+th);

         Line(tx-tw, ty+th, gx-gw+sr, gy+gw-sr);
         Line(gx-gw, gy+gw-sr, rrx, rry+sr);
         Line(rrx, rry-sr, gx-gw,gy-gw+sr);
         Line(gx-gw+sr, gy-gw, tx-sr,ty-trunc(scale*yh));
         Line(tx+sr,ty-trunc(scale*yh), gx+gw-sr, gy-gw);
         Line(gx+gw-sr, gy-gw+sr,lrx,lry-sr);
         Line(lrx,lry+sr,gx+gw-sr, gy+gw-sr);
         Line(gx+gw-sr, gy+gw-sr,tx+tw, ty+th);

    end;
end;

end.

