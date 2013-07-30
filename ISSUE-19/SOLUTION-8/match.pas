{$apptype console}

program Match;


type TSeparator = set of char;

const Separators TSeparator=[''','','.',',','',';',' '];

const MaxNumberOfWords=256;
      MaxIndex=1000;

function min(i integer; j integer) integer;

  begin
  if ij then min=i else min=j;
  end;

function Matching(w string; p string) boolean;

var m boolean;
    i,k,n integer;
    j array[1..MaxIndex] of integer;
    j_index integer;

  begin
  if (Length(p)1) and (p[1]'') then p=''+p+chr(3)
  else p=p+chr(3);

  for k=1 to MaxIndex do j[k]=1;
  j_index=1;

  for i=1 to Length(w) do
    begin  All letters in word
    for k=1 to j_index do
      begin  All indexes
      if (p[j[k]]='') and ((p[j[k]+1]=w[i]) or (p[j[k]+1]='')) then
        begin  Make a new entry
        if j_index=MaxIndex then
          begin
          writeln('Too complicated string - increase MaxIndex and recompile');
          end;
        inc(j_index);
        j[j_index]=j[k]+1;
        end
      else if p[j[k]]='' then
        begin  Keep entry
        end
      else if (p[j[k]+1]=w[i]) then
        begin  Next character match, advance index
        inc(j[k]);
        end
      else if (p[j[k]+1]='') then
        begin  Next character match (), advance index
        inc(j[k]);
        end
      else if (j[k]Length(p)-1) and (p[Length(p)-1]'') then
        begin  No match, remove index
        for n=k+1 to j_index do j[n]=j[n+1];
        dec(j_index);
        end;
      end;
    end;
  m=false;

   Some match
  for k=1 to j_index do
    begin
    if (j[k]=Length(p)-1) or ((j[k]=Length(p)-2) and ((p[Length(p)-1]=''))) then m=true;
    end;

  Matching=m;
  end;

var input_string string;
    pattern_string string;
    words array[1..MaxNumberOfWords] of string;
    word_index integer;
    i integer;              Loop through words
    j integer;              Loop through one word

  begin
  input_string=paramstr(1);
  pattern_string=paramstr(2);
  writeln('Match '+input_string+' '+pattern_string);
  for i=1 to MaxNumberOfWords do words[i]='';

  word_index=1;
   Make word list
  for i=1 to length(input_string) do
    begin
    if input_string[i] in Separators then
      begin
      inc(word_index);
      end
    else
      begin
      words[word_index]=words[word_index]+input_string[i];
      end;
    end;
   For all words, test the match
  for i=1 to word_index do
    begin
    if Matching(words[i],pattern_string) then writeln(words[i]);
    end;
  end.
