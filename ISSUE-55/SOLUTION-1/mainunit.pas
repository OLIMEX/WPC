unit mainunit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls;

const
  npt = 82;
type
  ptArray = array [0..npt, 0..npt] of integer;

  { TMainForm }

  TMainForm = class(TForm)
    Button1: TButton;
    Image1: TImage;
    Image2: TImage;
    Shape1: TShape;
    Shape2: TShape;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { private declarations }
    procedure Average(var pts: ptArray);
    procedure Filter(var pts: ptArray);
    procedure Go;
    procedure NearestNeighbour(const pts: ptArray);
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

type pt = record
  x: integer;
  y: integer;
end;

procedure TMainForm.Average(var pts: ptArray);
var
  val: integer;
  p: TColor;
  x,y,i,j: integer;
begin
  Image2.Picture.Clear;
   y := 0;
   while y < Image1.Height do
     begin
        x := 0;
        while x < Image1.Width do
         begin
           val := 0;
           for i := 0 to 2 do
             for j := 0 to 2 do
               begin
                 p := Image1.Canvas.Pixels[x+i,y+j];
                 val := val + ((p and $000000FF) div 3)
                            + (((p and $0000FF00) shr 8) div 3)
                            + (((p and $00FF0000) shr 16) div 3);
               end;
           val := val div 9;
           for i := 0 to 2 do
             for j := 0 to 2 do
               begin
                 if (val > 220) then
                  val := 255
                 else if (val > 175) then
                  val := 200
                 else if (val > 125) then
                  val := 150
                 else if (val > 75) then
                  val := 100
                 else val := 50;
                 pts[x div 3,y div 3] := val;
                 p := val shl 16 + val shl 8 + val;
                 Image2.Canvas.Pixels[x+i,y+j] := p;
               end;
           x := x + 3;
         end;
        y := y + 3;
     end;
end;

procedure TMainForm.Filter(var pts: ptArray);
var
  x,y,l1,l2,l3,l4,l5: integer;
begin
  l1:=0; l2:=0; l3:=0; l4:=0; l5:=0;
   for x:=0 to npt do
     for y:=0 to npt do
       begin
         if pts[x, y] = 255 then
          begin
            inc(l1);
            if l1 = 32 then
             begin
              pts[x, y] := 255;
              l1 := 0;
             end
            else
              pts[x, y] := 0;
          end
         else if pts[x, y] = 200 then
          begin
            inc(l2);
            if l2 = 8 then
             begin
              pts[x, y] := 200;
              l2 := 0;
             end
            else
              pts[x, y] := 0;
          end
         else if pts[x, y] = 150 then
          begin
            inc(l3);
            if l3 = 3 then
             begin
              pts[x, y] := 150;
              l3 := 0;
             end
            else
              pts[x, y] := 0;
          end
         else if pts[x, y] = 100 then
          begin
            inc(l4);
            if l4 = 2 then
             begin
              pts[x, y] := 100;
              l4 := 0;
             end
            else
              pts[x, y] := 0;
          end;
       end;
end;

procedure TMainForm.Go;
var
  pts: ptArray;
begin
  Average(pts);
  Filter(pts);
  NearestNeighbour(pts);
end;

procedure TMainForm.NearestNeighbour(const pts: ptArray);
var
  p, p1, p2, pp: ^pt;
  d, dn: int64;
  s, i, j, x ,y, cnt: integer;
  l: TList;
begin
  cnt := 0;
   l := TList.Create;
   for x:= 0 to npt do
     for y:= 0 to npt do
       begin
         if pts[x, y] > 0 then
            begin
              Shape1.Canvas.Pixels[x*3, y*3] := clBlack;
              new(p);
              p^.x:=x*3;
              p^.y:=y*3;
              l.Add(p);
              inc(cnt);
            end;
       end;
   //
   for i:=0 to l.Count-2 do
     begin
       d := 999999;
       s := i+1;
       p1 := l.Items[i];
       for j:=i+1 to l.Count-1 do
         begin
          p2 := l.Items[j];
          dn := sqr(p2^.x-p1^.x) + sqr(p2^.y-p1^.y);
          if dn < d then
            begin
              d := dn;
              s := j;
            end;
         end;
       pp := l.Items[i+1];
       l.Items[i+1] := l.Items[s];
       l.Items[s] := pp;
       p2 := l.Items[i+1];
       Shape2.Canvas.Line(p1^.x, p1^.y, p2^.x, p2^.y);
       l.Move(s, i+1);
     end;
   //
   while l.Count > 0 do
     begin
      pp := l.First;
      Dispose(pp);
      l.Delete(0);
     end;
end;

procedure TMainForm.Button1Click(Sender: TObject);
begin
  Go;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
    Image1.Picture.LoadFromFile('test.jpg');
    Image2.Picture.LoadFromFile('test.jpg');
end;

end.

