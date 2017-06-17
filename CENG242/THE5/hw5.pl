:- module(hw5, [filled_area/2, filling_list/4]).
:- [tiles].

% DO NOT MODIFTILE_WIDTH THE UPPER CONTENT, WRITE TILE_WIDTHOUR CODE AFTER THIS LINE


areaofTile(TILE_NAME, AREA) :- tile(TILE_NAME,X,Y,Z), AREA is X*Y.

filled_area([],0).
filled_area([TILE_NAME | T], A) :- filled_area(T, A2), areaofTile(TILE_NAME, A3), A is A2 + A3.


percentage(WIDTH, HEIGHT, [TILE_NAME | T], PERCENTAGE) :- filled_area([TILE_NAME | T], TOTAL_AREA), PERCENTAGE is TOTAL_AREA/(WIDTH*HEIGHT).  

totalWidth([],0).
totalWidth([TILE_NAME | T], WIDTH) :- totalWidth(T, WIDTH2), tile(TILE_NAME,X,Y,Z), WIDTH is X + WIDTH2.



insert(X,R,[X|R]).

addtoList(WIDTH, LIST, NEW) :- tile(TILE_NAME, X, Y, Z), totalWidth(LIST, W), X + W =:= WIDTH, not(member(TILE_NAME, LIST)), insert(TILE_NAME, LIST, NEW). 
addtoList(WIDTH, LIST, RESULT) :- tile(TILE_NAME, X, Y, Z), totalWidth(LIST, W), X+W < WIDTH, not(member(TILE_NAME, LIST)), insert(TILE_NAME, LIST, NEW), addtoList(WIDTH, NEW, RESULT).




height(HEIGHT, [], []).
height(HEIGHT, [TILE_NAME | T], [TILE_NAME | T]) :- tile(TILE_NAME, T_WIDTH, T_HEIGHT, COLOR), T_HEIGHT =< HEIGHT, height(HEIGHT, T, T). 


filling_list(0,0,0,[]).
filling_list(WIDTH, HEIGHT, PERCENTAGE, LIST) :- addtoList(WIDTH, [], LIST), height(HEIGHT, LIST, LIST), percentage(WIDTH, HEIGHT, LIST, PERC), PERC =< 1.0, PERC >= PERCENTAGE.  











