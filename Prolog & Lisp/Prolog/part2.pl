% "direclty path for facts"
flight(edirne,erzurum,5).
flight(erzurum,edirne,5).
flight(erzurum,antalya,2).
flight(antalya,erzurum,2).
flight(antalya,izmir,1).
flight(izmir,antalya,1).
flight(antalya,diyarbakir,5).
flight(diyarbakir,antalya,5).
flight(izmir,istanbul,3).
flight(istanbul,izmir,3).
flight(istanbul,ankara,2).
flight(ankara,istanbul,2).
flight(izmir,ankara,6).
flight(ankara,izmir,6).
flight(istanbul,trabzon,3).
flight(trabzon,istanbul,3).
flight(ankara,trabzon,6).
flight(trabzon,ankara,6).
flight(ankara,kars,3).
flight(kars,ankara,3).
flight(ankara,diyarbakir,8).
flight(diyarbakir,ankara,8).
flight(kars,gaziantep,3).
flight(gaziantep,kars,3).

member(X,[X|_]).
member(X,[_|Tail]):-member(X,Tail).

% "Bir liste tut gidilen pathleri tutsun ki birdaha geri dönme olmasın."
route(X,Y,C):-undirected_path(X,Y,[X],C).

undirected_path(X,Y,[X|_],C):-flight(X,Y,C).
undirected_path(X,Y,L,C):-flight(X,Z,W),Z\==Y,not(member(Z,L)),undirected_path(Z,Y,[Z|L],D),(C is W+D),X\==Y.


%	Istanbul-Gaziantep yolu...
%	flight(istanbul,ankara,2).
%	flight(ankara,kars,3).
%	flight(kars,gaziantep,3).