unit FormOlimex48;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    pnl1: TPanel;
    pnl2: TPanel;
    lbPuntoA: TLabel;
    lbPuntoB: TLabel;
    lbPuntoC: TLabel;
    lbResult: TLabel;
    pbPuntoA: TPaintBox;
    pbPuntoB: TPaintBox;
    pbPuntoC: TPaintBox;
    procedure pbPuntoAPaint(Sender: TObject);
    procedure pbPuntoAMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure pbPuntoAMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
    posx, posy: Integer;
  public
    { Public declarations }
    procedure Recalculate;
  end;

var
  Form1: TForm1;

implementation

uses Math;

{$R *.dfm}

procedure TForm1.pbPuntoAPaint(Sender: TObject);
var
    cadena: string;
begin
	with (Sender as TPaintBox), (Sender as TPaintBox).Canvas do begin
		case (Sender as TPaintBox).Tag of
        	1: Brush.Color:=clRed;
        	2: Brush.Color:=clLime;
        	3: Brush.Color:=clAqua;
        end;
        Ellipse(0, 0, width, height);
		case (Sender as TPaintBox).Tag of
        	1: cadena:='A';
        	2: cadena:='B';
        	3: cadena:='C';
        end;

        TextOut((width-textwidth(cadena)) div 2, (Height-TextHeight(cadena)) div 2, cadena);
    end;
end;

procedure TForm1.pbPuntoAMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
    posx:=x;
    posy:=y;
end;

procedure TForm1.pbPuntoAMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
	if ssleft in Shift then begin
    	with (sender as TPaintBox) do begin
            Left:=Left + x-posx;
            Top:=top+y-posy;
    	end;
        Recalculate;
    end;
end;

procedure TForm1.Recalculate;
var
    ptA, ptB, ptC: TPoint;
    pendAB, pendBC: Single;
    pend: Single;
function angulo(org, dst: TPoint): Single;
begin
	Result:=ArcTan2((dst.Y - org.Y), (dst.X - org.X));
    Result:=RadToDeg(Result);
end;
function igualdad(op1, op2: Single): Boolean;
begin
    Result:=False;
	if Abs(op1-op2)<1 then
    	Result:=True;
end;
begin
	ptA.X:=pbPuntoA.Left + pbPuntoA.Width div 2;
    ptA.Y:=pbPuntoA.Top + pbPuntoA.Height div 2;
	ptB.X:=pbPuntoB.Left + pbPuntoB.Width div 2;
    ptB.Y:=pbPuntoB.Top + pbPuntoB.Height div 2;
	ptC.X:=pbPuntoC.Left + pbPuntoC.Width div 2;
    ptC.Y:=pbPuntoC.Top + pbPuntoC.Height div 2;

    lbPuntoA.Caption:='A: '+IntToStr(ptA.X)+'x - ' + IntToStr(ptA.Y)+'y';
    lbPuntoB.Caption:='B: '+IntToStr(ptB.X)+'x - ' + IntToStr(ptB.Y)+'y';
    lbPuntoC.Caption:='C: '+IntToStr(ptC.X)+'x - ' + IntToStr(ptC.Y)+'y';

    pendAB:=angulo(ptA, ptB);
    pendBC:=angulo(ptB, ptC);

    pend:=pendBC-pendAB;
    if pend>180 then pend:=pend-360;
    if pend<-180 then pend:=pend+360;

    if igualdad(pend, 0) or igualdad(pend, 180) or igualdad(pend, -180) then
    	lbResult.Caption:='En línea'
    else begin
        if pend<0 then
    		lbResult.Caption:='Counterclockwise'
        else
    		lbResult.Caption:='Clockwise';
    end;

//    if pendAB=pendBC then
//    	lbResult.Caption:='En línea'
//    else begin
//        pend:=pendBC-pendAB;
//        if pend>180 then pend:=pend-360;
//        if pend<-180 then pend:=pend+360;
//        if pend<0 then
//    		lbResult.Caption:='Counterclockwise'
//        else
//    		lbResult.Caption:='Clockwise';
//    end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
	Recalculate;
end;

end.
