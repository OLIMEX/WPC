unit MainUnit;

{$mode objfpc}{$H+}

(*
  Olimex WPC 50
  Find the centre of a circle with a 50 pixel diameter in a 100 x 100 window.
*)

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ComCtrls,
  Arrow, ExtCtrls, StdCtrls, Buttons;

type

  { TMainForm }

  TMainForm = class(TForm)
    DiameterRadioGroup: TRadioGroup;
    AlgoRadioGroup: TRadioGroup;
    RunBitBtn: TBitBtn;
    ExitBitBtn: TBitBtn;
    MainImage: TShape;
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    Panel5: TPanel;
    DiameterRadioGroupPanel6: TPanel;
    Panel7: TPanel;
    StatusBar: TStatusBar;
    procedure ExitBitBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure MainImagePaint(Sender: TObject);
    procedure RunBitBtnClick(Sender: TObject);
  private
    { private declarations }
    radius: Integer;
    circle_x, circle_y: Integer;
    centre_x, centre_y: Integer;
    procedure FindCentre;
    procedure SearchCentre;
  public
    { public declarations }
  end; 

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

// Find the centre by simply calculating
// the average coordinates of the blue pixels
procedure TMainForm.FindCentre;
var x,y: Integer;
    cx, cy: LongInt;
    cnt: Integer;
begin
  cnt := 0;
  cx := 0;
  cy := 0;
  for x := 0 to MainImage.Width - 1 do
   begin
    for y := 0 to MainImage.Height - 1 do
     begin
       if MainImage.Canvas.Pixels[x,y] = clBlue then
        begin
          cx := cx + x;
          cy := cy + y;
          Inc(cnt);
        end;
      end;
    end;
  centre_x := round(cx / cnt);
  centre_y := round(cy / cnt);
end;

// Find the centre by sending rays in four directions
procedure TMainForm.SearchCentre;
var tx,ty,
    lx,ly,
    bx,by,
    rx,ry: Integer;
    x,y: Integer;
    px,py: Integer;
    step: Integer;
    tf, bf, rf, lf: Boolean;
    found: Boolean;
begin
  found := false;
  centre_x := 0;
  centre_y := 0;
  // Examine the image in a grid of size "step"
  step := MainImage.Width div 2;
  while not found do
    begin
     x := 1;
     while (x < MainImage.Width) and (not found) do
       begin
         y := 1;
         while (y < MainImage.Height) and (not found) do
          begin
           // Send rays in four directions, starting from
           // the current x,y location
           // If the ray detects a transition from blue to non-blue
           // then we have found a point on the circumference of
           // the circle
           tx := -1; ty := -1; lx := -1; ly := -1;
           rx := -1; ry := -1; bx := -1; by := -1;
           tf := false; bf := false; rf := false; lf := false;
           // Probe the top
            for py := y downto 1 do
              if (MainImage.Canvas.Pixels[x,py] = clBlue) and
                 (MainImage.Canvas.Pixels[x,py-1] <> clBlue) then
              begin
                tx :=x; ty := py;
                tf := true;
              end;
            // Probe the bottom
            for py := y to MainImage.Height - 1 do
              if (MainImage.Canvas.Pixels[x,py] = clBlue) and
                 (MainImage.Canvas.Pixels[x,py+1] <> clBlue) then
              begin
                bx := x; by := py;
                bf := true;
              end;
            // Probe left
            for px := x downto 1 do
              if (MainImage.Canvas.Pixels[px,y] = clBlue) and
                 (MainImage.Canvas.Pixels[px-1,y] <> clBlue) then
              begin
                lx := px; ly := y;
                lf := true;
              end;
            // Probe right
            for px := x to MainImage.Width - 1 do
              if (MainImage.Canvas.Pixels[px,y] = clBlue) and
                 (MainImage.Canvas.Pixels[px+1,y] <> clBlue) then
              begin
                rx := px; ry := y;
                rf := true;
              end;
            // If all four rays detected an edge
            // then calculate the centre coordinate
            if tf and rf and lf and bf then
              begin
                found := true;
                centre_x := lx + (rx - lx) div 2;
                centre_y := ty + (by - ty) div 2;
                break;
              end;
            y := y+step;
          end;
         x:=x+step;
        end;
      if (step = 1) and (not found) then
        raise  Exception.Create('No centre could be found');
      step := step div 2;
    end;
end;

procedure TMainForm.RunBitBtnClick(Sender: TObject);
begin
  // Generate circle radius
  if DiameterRadioGroup.ItemIndex = 0 then
     radius := 25
  else
     radius := 5 + random(40);
  // Generate random centre
  circle_x := radius + random(MainImage.Width - 2*radius);
  circle_y := radius + random(MainImage.Height - 2*radius);
  // Repaint
  MainImage.Invalidate;
end;

procedure TMainForm.MainImagePaint(Sender: TObject);
var R: TRect;
begin
  with MainImage.Canvas do
    begin
         // Fill background
         Brush.Color := clWhite;
         R.Left:=0;
         R.Top:=0;
         R.Right:=Height-1;
         R.Bottom:=Height-1;
         FillRect(R);
         // Draw circle
         Brush.Color := clBlue;
         Ellipse(circle_x-radius,circle_y-radius,
                 circle_x+radius,circle_y+radius);
         // Calculate centre
         if AlgoRadioGroup.ItemIndex = 0 then
            FindCentre
         else
            SearchCentre;
         // Draw crosshair
         Pen.Color := clRed;
         Pen.Width := 1;
         Pen.Style := psSolid;
         Line(centre_x, 0, centre_x, Height-1);
         Line(0, centre_y, Width-1, centre_y);
    end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  Randomize;
  RunBitBtnClick(self);
end;

procedure TMainForm.ExitBitBtnClick(Sender: TObject);
begin
  Application.Terminate;
end;

end.

