unit mainunit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls, LCLIntf;

  { TMainForm }

type
  TMainForm = class(TForm)
    Button1: TButton;
    Image1: TImage;
    Image2: TImage;
    Label1: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { private declarations }
    procedure Lightness;
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

uses Math;

procedure TMainForm.Lightness;
var
  p: TColor;
  x, y: Integer;
  r,g,b: Byte;
  t: Double;
  l: Byte;
begin
  Image2.Picture.Clear;
   y := 0;
   while y < Image1.Height do
     begin
        x := 0;
        while x < Image1.Width do
          begin
            p := Image1.Canvas.Pixels[x,y];
            r := GetRValue(p);
            g := GetGValue(p);
            b := GetBValue(p);
            t := (0.2126 * r + 0.7152 * g + 0.0722 * b)/255;
            if t > Power(6/29, 3)
               then t := Power(t, 1/3)
               else t := (1/3 * 29/6 * 29/6 * t) +  (4/29);
            l := Byte(Trunc(2.55 * (116 * t - 16)));
            Image2.Canvas.Pixels[x,y] :=  RGBToColor(l, l, l);
            Inc(x);
          end;
        Inc(y);
     end;
end;

procedure TMainForm.Button1Click(Sender: TObject);
begin
  Lightness;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
    Image1.Picture.LoadFromFile(Application.Location + '/test.jpg');
end;

end.

