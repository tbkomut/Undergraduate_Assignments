% "Room, course ve student icin ek olarak bir ıd fact'i gereklidir."
% "Bunlarda ekleme olayı olduğundan dolayı eklenecek item'ın varlığı check edilir."
% "Bir course sadece tek bir roomda verildiğini varsaydım."
% "Verilmis olan excel sablonundan bu cıkarımımı yaptım.(Room denilmiş)"
% "Ornek: cse341 dersi yalnızca z23 yada z06, bunlardan birinde verilir gibi,Tek bir sınıf."
% "Factlerin isimlendirilmesi parametrelerin sırasına göre yani; course_instructor(course,ınstructor) seklindedir."

%---------ROOM---------%

room_ıd(z06).
room_ıd(z11).

% "Burası önemlidir."	%
% "Querylerde input girildiginde handicapped,projector,smartboard olması halinde t, olmaması halinde ise f şeklinde input girilmeli."%
room_hcapped(z06,t).
room_hcapped(z11,t).

room_projector(z06,t).
room_projector(z11,t).

room_smartboard(z06,f).
room_smartboard(z11,t).

room_capacity(z06,10).
room_capacity(z11,10).

%--------COURSE-------%

course_ıd(cse341).
course_ıd(cse343).
course_ıd(cse331).
course_ıd(cse321).

course_class(cse341,z06).
course_class(cse343,z11).
course_class(cse331,z06).
course_class(cse321,z11).

course_instructor(cse341,genc).
course_instructor(cse343,turker).
course_instructor(cse331,bayrakci).
course_instructor(cse321,gozupek).

course_hours(cse341,4).
course_hours(cse343,3).
course_hours(cse331,3).
course_hours(cse321,4).

course_capacity(cse341,10).
course_capacity(cse343,6).
course_capacity(cse331,5).
course_capacity(cse321,10).

%-------OCCUPANCY------%

% "course_class ile course_hour arasında bağlantı vardır."

course_hour(cse341,8).
course_hour(cse341,9).
course_hour(cse341,10).
course_hour(cse341,11).

course_hour(cse331,13).
course_hour(cse331,14).
course_hour(cse331,15).

course_hour(cse343,8).
course_hour(cse343,9).
course_hour(cse343,10).
course_hour(cse343,11).

course_hour(cse321,14).
course_hour(cse321,15).
course_hour(cse321,16).

%------INSTRUCTOR------%

instructor_course(cse341,genc).
instructor_course(cse343,turker).
instructor_course(cse331,bayrakci).
instructor_course(cse321,gozupek).

instructor_projector(genc,t).
instructor_projector(turker,f).
instructor_projector(gozupek,f).
instructor_projector(bayrakci,f).

instructor_smartboard(genc,f).
instructor_smartboard(turker,t).
instructor_smartboard(gozupek,t).
instructor_smartboard(bayrakci,f).

%--------STUDENT-------%

student_id(1).
student_id(2).
student_id(3).
student_id(4).
student_id(5).
student_id(6).
student_id(7).
student_id(8).
student_id(9).
student_id(10).
student_id(11).
student_id(12).
student_id(13).
student_id(14).
student_id(15).

student_handicapped(1,f).
student_handicapped(2,f).
student_handicapped(3,f).
student_handicapped(4,f).
student_handicapped(5,f).
student_handicapped(6,t).
student_handicapped(7,f).
student_handicapped(8,t).
student_handicapped(9,f).
student_handicapped(10,f).
student_handicapped(11,f).
student_handicapped(12,f).
student_handicapped(13,f).
student_handicapped(14,f).
student_handicapped(15,t).

% "Student courselar bir listedir."
student_course(1,[cse341,cse343,cse331]).
student_course(2,[cse341,cse343]).
student_course(3,[cse341,cse331]).
student_course(4,[cse341]).
student_course(5,[cse343,cse331]).
student_course(6,[cse341,cse343,cse331]).
student_course(7,[cse341,cse343]).
student_course(8,[cse341,cse331]).
student_course(9,[cse341]).
student_course(10,[cse341,cse321]).
student_course(11,[cse341,cse321]).
student_course(12,[cse343,cse321]).
student_course(13,[cse343,cse321]).
student_course(14,[cse343,cse321]).
student_course(15,[cse343,cse321]).

% "Sistemimize yeni bir room,course veya student girilmesi için; add_room,add_course,add_student calları kullanılmalı."
%-------ADDITION-------%

%---Addition Rules----%

%	"Herhangi bir ön koşul olmaz.Room birileri tarafından tercih edilir."
%	"Example input format-> add_room(16,20,t,t,t).  gibi"
add_room(ID,Capacity,Smartboard,Projector,Handicapped):-	not(room_ıd(ID))->
															assert(room_ıd(ID)),
															assert(room_capacity(ID,Capacity)),
															assert(room_smartboard(ID,Smartboard)),
															assert(room_projector(ID,Projector)),
															assert(room_hcapped(ID,Handicapped)).

%	"Kurs eklerken kurs ekleneceği room ile ilgili kursun ınstructor'ın istediği room koşullarının uyuşması lazım."
%	"Aynı zamanda kurs size, room sizedan küçük eşit olmalıdır."
%	"Example input format-> add_course(cse346,z11,turker,4,10).  gibi"
add_course(Course,Room,Instructor,Hour,Capacity):-not(course_ıd(Course)),
							room_instructor(Room,Instructor),
							room_capacity(Room,X),Capacity=<X,
							(Hour>0,Hour=<9),
							adding_course(Course,Room,Instructor,Hour,Capacity).						

%	"Engelli bir öğrenci alacağı dersler, engellilere uygun odaya sahip dersler şeklinde kayıtlı olabilir."
%	"L ders listesidir; [cse341,cse343] gibi..."
%	"Example input format-> add_student(116,[cse341,cse343],f).  gibi"
add_student(ID,L,Handicapped):-(not(student_id(ID))->(Handicapped==t->courses_checking(L);true),adding_student(ID,L,Handicapped);false).

%-Helper functions-%

room_instructor(Room,Instructor):-	room_projector(Room,X),instructor_projector(Instructor,W),
									room_smartboard(Room,Y),instructor_smartboard(Instructor,Z),
									(Z==t->Y==t;true),
									(W==t->X==t;true).
adding_course(Course,R,I,H,C):-	assert(course_ıd(Course)),
								assert(course_class(Course,R)),
								assert(course_instructor(Course,I)),
								assert(course_hour(Course,H)),
								assert(course_capacity(Course,C)).
courses_checking(L):-L==[].
courses_checking([C|L]):-course_class(C,R),room_hcapped(R,H),H==t,courses_checking(L).
adding_student(ID,L,H):-assert(student_id(ID)),
						assert(student_course(ID,L)),
						assert(student_handicapped(ID,H)).


%---------RULES--------%

% "Aynı saat aynı sınıftaki farklı dersleri gösterir.Saat başı çakışmaları gösterir."
conflicts(CourseID1,CourseID2):-conflicts_room(CourseID1,CourseID2),conflicts_hours(CourseID1,CourseID2),CourseID1\==CourseID2.

% "Bir dersi bir rooma atarken ders özelliklerine kapasitesine bakmalıyız."
assign(RoomID,CourseID):-equipment_room(RoomID,CourseID),capacity_room(RoomID,CourseID).

%	"Assign da ek olarak room'a atanacak ders için başka dersle çakışma durumunada bakmak gereklidir."
%	"Fakat ben bunu tam olarak istediğim şekilde yapamadığım için yorum satırınada olsa almak istedim.Altdaki rule"
%	assign(RoomID,CourseID):-equipment_room(RoomID,CourseID),capacity_room(RoomID,CourseID),course_class(Y,RoomID),Y\==CourseID,not(conflicts(CourseID,Y)).

%	"Bunun için gerekli olan şey öğrencinin sağlık durumuna uygun bir roomda mı ders işlenecek?"
enroll(StudentID,CourseID):-student_handicapped(StudentID,X),room_ıd(Y),(X==t -> room_hcapped(Y,t);room_ıd(Y)),course_class(CourseID,Y).


% "Helper Funtions for rules"

conflicts_room(CourseID1,CourseID2):-course_class(CourseID1,X),course_class(CourseID2,Y),X==Y.
conflicts_hours(CourseID1,CourseID2):-course_hour(CourseID1,X),course_hour(CourseID2,Y),X==Y.

% "Hoca diyelim bir özellik istemiyor fakat özellikli bir sınıf seçemeyecek mi?,Seçebilir..."
equipment_room(RoomID,CourseID):-course_instructor(CourseID,X),instructor_smartboard(X,Y),instructor_projector(X,Z),(
									(Y==t,Z==f)->room_smartboard(RoomID,t);
									(Y==f,Z==t)->room_projector(RoomID,t);
									(Y==f,Z==f)->room_ıd(RoomID);
									(Y==t,Z==f)->room_smartboard(RoomID,Y),room_projector(RoomID,Z)).

capacity_room(RoomID,CourseID):-course_capacity(CourseID,X),room_capacity(RoomID,Y),(X=<Y).
