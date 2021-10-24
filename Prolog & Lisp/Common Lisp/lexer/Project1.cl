; Keywordsler listesi...
(setq keywords '("and" "or"  "not" "equal" "append" "concat" "set" "deffun" "for" "while" "if" "exit"))
; Operator listesi...
(setq operator '("+" "/"))
; Boolean değerler listesi...
(setq boolean '("true" "false"))
; Parantezler listesi...
(setq paranthes '("(" ")"))

; Operator listesini gezerek her bir operator için t f listesi döner.
(defun operatorCheckingList(x)
	(map 'list #'(lambda (charVar) 
		(cond
			((equal charVar x) t)
		)
	)operator)
)

; Parantez listesini gezerek her bir parantez operatorü için t f listesi döner.
(defun paranthesCheckingList(x)
	(map 'list #'(lambda (charVar) 
		(cond
			((search charVar x) t)
		)
	)paranthes)
)

; Keywords listesini gezerek her bir keyword için t f listesi döner.
(defun keywordCheckingList(x)
	(map 'list #'(lambda (charVar) 
		(cond
			((equal charVar x) t)
		)
	)keywords)
)
; Boolean listesini gezerek her bir boolean için t f listesi döner.
(defun booleanCheckingList(x)
	(map 'list #'(lambda (charVar) 
		(cond
			((equal charVar x) t)
		)
	)boolean)
)

;Harflerin condition'ı
(defun ıdentifierCondition(x)
	(cond
		((equal 0 (length x)) t)
		((equal t (or (and (char>= (char x 0) #\A) (char<= (char x 0) #\Z)) (and (char>= (char x 0) #\a) (char<= (char x 0) #\z)))) (ıdentifierCondition (subseq x 1)))
		(nil)
	)
)

;	Tam sayıların condition'ı
;	Negatifler için - condition
(defun ıntegerCondition(x)
	(cond
		((equal 0 (length x)) t)
		((equal t (and (char>= (char x 0) #\0) (char<= (char x 0) #\9))) (ıntegerCondition (subseq x 1)))
		((equal t (equal (char x 0) #\-)) (ıntegerCondition (subseq x 1)))
		(nil)
	)
)

; Global listesindekiler içerisinde en az biri true değer var mı? Yani değer listedeki en az bir elemanlar aynı mı?
(defun valid(x)
	(cond
		((null x) nil)
		((equal t (car x)) t)
		((valid (cdr x)))
	)
)

; Identifier yada Integer valueların önünde yada arkasında parantezler olabilir onlar temizlenmelidir.
(defun clearString(str)
	(cond
		((equal (length str) 0)nil)
		(
			(setq size (length str))
			(cond
				((or (equal "(" (subseq str 0 1)) (equal ")" (subseq str 0 1)))  (clearString (subseq str 1)))
				((or (equal ")" (subseq str (- size 1) size )) (equal "(" (subseq str (- size 1) size ))) (clearString (subseq str 0 (- size 1))))
				(str)
			)
		)
	)
)

;Yalnızca identifier ınteger ve operator kontrolünün yapıldıgı fonksiyon
(defun ıdentifierChecking (str size counter)
	(cond
		((equal size 0)  nil)
		(
			(setq sub (subseq str 0 counter))
			(setq O (operatorCheckingList sub))
			(setq P (paranthesCheckingList sub))
			(cond
				; Operatorler
				((equal t (equal t (valid O)))
					(setq clear (clearString str))
					(setq s (length clear))
					(cond
						((equal size 1)(cons (list "operator" sub) (ıdentifierChecking (subseq str 1) (- size 1) 1)))
						((ıdentifierChecking (subseq str s) (- size s) 1))
					)
				)
				; *,- Operatorü özel
				((equal sub "*")
					(setq clear (clearString str))
					(setq s (length clear))
					(cond
						((equal size 1)(cons (list "operator" "*") (ıdentifierChecking (subseq str 1) (- size 1) 1)))
						((equal size 2)(cons (list "operator" "**") (ıdentifierChecking (subseq str 2) (- size 2) 1)))
						((ıdentifierChecking (subseq str s) (- size s) 1))
					)
				)
				((equal sub "-")
					(cond
						((equal size 1)(cons (list "operator" "-") (ıdentifierChecking (subseq str 1) (- size 1) 1)))
						(	
							(setq clear (clearString str))
							(setq s (length clear))
							(cond						
								((equal (ıntegerCondition clear) t) (cons (list "integer" clear)(ıdentifierChecking (subseq str s) (- size s) 1)))
								((ıdentifierChecking (subseq str s) (- size s) 1))
							)
						)
					)
				)
				;Parantezler
				((equal t (valid P)) (cons (list "operator" sub) (ıdentifierChecking (subseq str 1) (- size 1) 1)))
				; Identifier ve Literallar
				(
					(setq clear (clearString str))
					(setq s (length clear))
					(cond
						((equal (ıdentifierCondition clear) t) (cons (list "identifier" clear) (ıdentifierChecking (subseq str s) (- size s) 1)))
						((equal (ıntegerCondition clear) t) (cons (list "integer" clear) (ıdentifierChecking (subseq str s) (- size s) 1)))
						((ıdentifierChecking (subseq str s) (- size s) 1))
					)
				)
				; String üzerinden düz ilerleme
				((ıdentifierChecking str (- size 1) (+ 1 counter)))
			)
		)
	)
)

;Yalnızca Keywords boolean ve operator kontrolünün yapıldıgı fonksiyon
(defun specialWordsChecking (str size counter)
	(cond
		((equal size 0) nil)
		(
			(setq sub (subseq str 0 counter))
			(setq val (length (subseq str 0 counter)))
			(setq O (operatorCheckingList sub))
			(setq P (paranthesCheckingList sub))
			(setq K (keywordCheckingList sub))
			(setq B (booleanCheckingList sub))
			(cond
				((equal t (or (equal t (valid P)) (equal t (valid O)))) (cons (list "operator" sub)  (specialWordsChecking (subseq str val) (- size val) 1)))
				((equal t (valid K)) (cons (list "keyword" sub) (specialWordsChecking (subseq str val) (- size 1) 1)))
				((equal t (valid B)) (cons (list "boolean" sub ) (specialWordsChecking (subseq str val) (- size 1) 1)))
				((specialWordsChecking str (- size 1) (+ 1 counter)))
			)
		)
	)
)

; Recursive caller fonksiyonumuz; duruma göre ıdentifier yada keyword calllarını seçer.
(defun selectOperation(str option)
	(cond
		((equal (length str) 0)nil)
		(
			(cond
				((equal option 0) (specialWordsChecking str (length str) 1))
				((ıdentifierChecking str (length str) 1))
			)
		)
	)
)

;Identifier wordu mü yoksa keyword yada boolean değer wordu mu  duruma göre 1 0 döner.
(defun isIdentifier(str)
	(setq A (keywordCheckingList (clearString str)))
	(setq B (booleanCheckingList (clearString str)))
	(cond
		((or (equal t (valid A)) (equal t (valid B))) 0)
		(1)
	)
)

;Parametre olarak tek satırdaki kelimeler listesi alır
(defun lexicalAnalyze(variable)
	(cond
		((null variable) nil)
		(
			(setq option (isIdentifier (car variable)))
			(append (selectOperation (car variable) option)(lexicalAnalyze(cdr variable)))
		)
	)
)

; Satırı kelime kelime parse ayırır.
(defun parser(variable)
	(cond
		((equal (length variable) 0) (list nil))
		(
			(cond
				((equal (subseq variable 0 1) (string #\Space)) (parser (subseq variable 1)))
				((equal (subseq variable 0 1) (string #\tab)) (parser (subseq variable 1)))
				(   
					; Size variable'ı burada string tipindedir.
					(setq size (words variable))
					(cons size (parser (subseq variable (length size))))
				)
			)
		)
	)
)

; Stringdeki boşluğa yada taba kadar olan wordu döndürür.
(defun words(str)
	(cond
		((equal (length str) 0) nil)
		((eq t (string= (subseq str 0 1) (string #\Space))) nil)
		((eq t (string= (subseq str 0 1) (string #\tab))) nil)
		((concatenate 'string (subseq str 0 1)(words (subseq str 1))))
	)
)

; Dosya satırlarını okuyan stream fonksiyonu
(defun streamControl(stream eofchar)
	(let ((result (read-line stream nil eofchar)))
		(cond 
			((eq result eofchar) nil)
			(	 
				; Bir satırın wordslere ayrılmış şeklinin listesini döndürür.
				(setq words (parser result))
				(append (lexicalAnalyze words) (streamControl stream eofchar))
			)
		)
	)
)

;	Ana fonksiyonumuz file stream açarak dosya okunur ve analizlerime geçmemizi sağlar.
(defun lexer(filename)
	(with-open-file (stream filename)
		(let 
			((content (streamControl stream (list '$eof$))))
			content
		)
	)
)

(print (lexer "g++.txt"))

; G++ syntax pdfdeki kurallara aykırı şeyleri output listeye eklemedim. Analizi doğru olanları output listesine ekledim.