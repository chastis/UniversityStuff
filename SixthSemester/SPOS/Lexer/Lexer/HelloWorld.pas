{$IOException true   }
Program MyProgram;
var 
	a : integer;
	b : real;
begin
	a := 0; // one line
	b := 1.; /* multi
	line
	*/
	writeLn(b, ' ', b:8:4);
	if (b >= 42) then
		b >> 1;
	else
		b = a|b;
	while (true and not false)
		writeln ('Hello, world!');
end.

{ end of program