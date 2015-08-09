10 rem	match game
20 rem	There are 26 matches.
30 rem	You are playing against the 8051, and the object is not
40 rem	to take the last match.
50 rem	You may only take 1 to 4 matches at a time.

60 title	MATCH GAME
70 matches = 26
80 title number of matches remaining: ;
90 value = matches
100 gosub 1000
110 title enter 1-4: ;
120 gosub 900
130 choice = value
140 if (choice > 4) then 110
150 if (choice < 1) then 110
160 matches = matches - choice
170 if (matches = 0) then 230
175 if (matches < 0) then 230
180 title I'll take: ;
190 value = 5 - choice
200 matches = matches - value
210 gosub 1000
220 goto 80
230 title Sorry you lose
240 goto 60

900 Rem		input value conversion routine
905 value = 0
910 read char
912 print char;
920 if (char = 13) then 950
930 value  = value*10 + (char - 48)
940 goto 910
945 rem force cr/lf
950 title
960 return

1000 Rem	output value conversion routine
1005 rem	build ASCII string in memory
1010 for i = 0 to 2
1020 mem[2:i] = value mod 10 + 48
1030 value = value / 10
1040 next i
1045 rem	output ASCII string
1050 for i = 0 to 2
1060 print mem[2:2-i];
1070 next i
1075 title
1080 return
2000 end


