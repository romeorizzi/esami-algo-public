{ constraints }
const
    MAXN = 1000;

{ input data }
var
    Nm, Nf, i : longint;
    M, F      : array[0..MAXN-1] of longint;

begin
{
    uncomment the following lines if you want to read/write from files
    assign(input,  'input.txt');  reset(input);
    assign(output, 'output.txt'); rewrite(output);
}

    readln(Nm, Nf);
    for i:=0 to Nm-1 do
        read(M[i]);
    readln();
    for i:=0 to Nf-1 do
        read(F[i]);
    readln();

    { insert your code here }

    writeln(42); { change 42 with actual answer }
end.
