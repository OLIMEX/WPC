(* WPC 59: Determine endianness without using C *)

program endianness;

type VariantRecord = record
		case selector: Byte of	
			0: (WordValue: Word);
			1: (ByteValue: Array[1..2] of Byte);
	 end;

procedure UsingVariantRecords;
var VRec: VariantRecord;
begin
 VRec.WordValue := 1;
 if (VRec.ByteValue[2] = 0) and (VRec.ByteValue[1] = 1) then
	Writeln('Variant record says: Little endian')
 else if (VRec.ByteValue[2] = 1) and (VRec.ByteValue[1] = 0) then
	Writeln('Variant record says: Big endian')
 else
	Writeln('Variant record says: Cannot determine endianness')
end;

procedure UsingPointers;
var AWord: Word;
	BytePointer: ^Byte;
    Byte1, Byte2: Byte;
begin
 AWord := 1;
 BytePointer := @AWord;
 Byte1 := BytePointer^;
 Inc(BytePointer);
 Byte2 := BytePointer^;
 if (Byte1 = 1) and (Byte2 = 0) then
	Writeln('Pointer says: Little endian')
 else if (Byte1 = 0) and (Byte2 = 1) then
	Writeln('Pointer says: Big endian')
 else
	Writeln('Pointer says: Cannot determine endianness');
end;

procedure UsingCompiler;
begin
{$IFDEF ENDIAN_BIG}
	Writeln('Compiler says: Big endian')
{$ELSE}
  	{$IFDEF ENDIAN_LITTLE}
		Writeln('Compiler says: Little endian')
	{$ELSE}
		Writeln('Compiler says: Cannot determine endianness')
    {$ENDIF}
{$ENDIF}
end;

begin
  UsingVariantRecords;
  UsingPointers;
  UsingCompiler;
end.
			
