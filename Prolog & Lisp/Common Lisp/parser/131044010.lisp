; Bu global variable üzerinde değişiklikler yapmaktayım. Eğer programda bir loop içerisinde function call edilirse
; kodun yanlış çalışmasına sebep olabilir...
(setq result "")

(setq A '( 
("operator" "(") ("keyword" "deffun") ("identifier" "check_coord") ("operator" "(") 
("identifier" "x") ("identifier" "y") ("operator" ")")

("operator" "(") ("keyword" "if") ("operator" "(") ("keyword" "and") 
("operator" "(") ("keyword" "equal") ("identifier" "x") ("integer" "1") ("operator" ")")
("operator" "(") ("keyword" "equal") ("identifier" "y") ("integer" "2") ("operator" ")") ("operator" ")")
("integer" "1")
("integer" "0")("operator" ")")
("operator" ")")


))

(setq B '(

("keyword" "null")  

)
)


; Ilk bastan itibaren integer value gördügü kadar liste ilerlenir.
(defun value_s (listVar)
	(cond
		((null listVar) nil)
		((cond
			((equal (car (cdr (car listVar))) ")") listVar)
			((equal (car (car listVar)) "integer") 
				(cond
					((value_s (cdr listVar)))
				)
			)
			(listVar)
		))
	)
)

; İlk baştan itibaren identifier veya identifier listeyi gördüğü kadar liste ilerletir
(defun base_id_list(listVar)
	(cond
		((null listVar) nil)
		((cond
			((equal (car (cdr (car listVar))) "(")
				(setq temp (base_id_list (cdr listVar)))
				(cond
					((equal (car (cdr (car temp))) ")") (cdr temp))
					((equal  (car (car temp)) "identifier") (setq inner (base_id_list (cdr temp)))
						(cond 
							((equal (car (cdr (car inner))) ")") (cdr inner))
							(listVar) 
						)
					)					
					(listVar)
				)
			)
			((equal (car (car listVar)) "identifier") (id_list listVar))
			(listVar)
		))
	)
)

(defun id_list(listVar)
	(cond
		(
			(equal (car (car listVar)) "identifier")
			(cond 
				((equal (car(car(cdr listVar))) "identifier")(id_list (cdr listVar))) 
				((cdr listVar))
			)
		)
		(listVar)
	)
)

; Binary expression olan kısma kadar listeyi alır gerisini döndürür.
(defun base_exp_b(listVar)
	(cond
		((null listVar) nil)
		(
			(setq exp_list (base_exp_i listVar))
			(cond
				((not (equal exp_list listVar)) (base_exp_b (cdr listVar)))
				((cond
					((equal (car (cdr (car listVar))) "(")
						(setq p (exp_b (cdr listVar)))
						(cond
							((equal (car (cdr (car p))) ")") (cdr p))
							((equal (car (cdr (car p))) nil) listVar)
							(p)
						)
					)
					((equal t 	(or (equal (car (cdr (car listVar))) "true") 
									(equal (car (cdr (car listVar))) "false")
								))
						; Burası değişmeli gibi...
;						(base_exp_b (cdr listVar))
						(cdr listVar)
					)	
					(listVar)
				))
			)
		)
	)
)

(defun exp_b(listVar)
	(cond
		((equal t 	(or (equal (car (cdr (car listVar))) "and") 
					(equal (car (cdr (car listVar))) "or")))
			(setq var (base_exp_b (cdr listVar))) (base_exp_b var)
		)
		((equal (car (cdr (car listVar))) "not")
			(base_exp_b (cdr listVar))
		)
		((equal (car (cdr (car listVar))) "equal")
			(setq var (base_exp_b (cdr listVar))) (setq endof (base_exp_b var))
			(cond
				((equal t (searching endof)) endof)
				((setq expi_list (base_exp_i endof))
					(cond
						((equal expi_list endof)(cdr var))
						(expi_list)
					)
				)
			)					
		)		
		(listVar)
	)
)

; exp_list olan kısmı kadar olanı kabul edilip geri kalan listeyi döndürür.
(defun base_explist_i(listVar)
	(setq exp_il (base_exp_i listVar))
	(cond
		((equal exp_il listVar)
			(cond
				; Ilk sırada olmalıdır...
				((equal (car (cdr (car listVar))) "(")
					(setq p (explist_i (cdr listVar)))
					(cond
						((equal (car (cdr (car p))) ")") (cdr p))
						(listVar)
					)
				)
				((equal (car (cdr (car listVar))) "null") (setf result "null") (cdr listVar))
				((equal (car (cdr (car listVar))) "'(")	
					(setq k (explist_i listVar))
					(cond
						((equal (car (cdr (car k))) ")") (setf result "'( VALUES )") (cdr k) )
						(listVar)
					)
				)
				((equal (car (cdr (car listVar))) "'()")
					(setf result "'()")
					(cdr listVar)
				)		
				(listVar)
			)
		)	 
		((setf result "EXPI")  exp_il)
	)
)

;(print (base_explist_i A))

(defun explist_i(listVar)
	(cond
		((equal (car (cdr (car listVar))) "concat")
			(setq var (base_explist_i (cdr listVar))) 
			(setq res (base_explist_i var))
			(setf result "(concat EXPLISTI EXPLISTI)")
			res
		)
		((equal (car (cdr (car listVar))) "append")
			(setq var (base_exp_i (cdr listVar))) 
			(setq res (base_explist_i var))
			(setf result "(append EXPI EXPLISTI)")
			res
		)
		((equal (car (cdr (car listVar))) "'(")
			(value_s (cdr listVar))
		)	
		(listVar)
	)
)

; Helper functions

(defun searching(listVar)
	(cond
		((null listVar))
		((cond
				((equal (car listVar) (list "operator" ")") ) )
				(nil)			
			)
			(searching (cdr listVar)))
	)
)

(defun element(listVar)
	(cond
		((null listVar)nil)
		((print (base_exp_i listVar))(element (cdr listVar)))
	)
)

; exp_i olan kısmı kadar olanı kabul edilip geri kalan listeyi döndürür.
(defun base_exp_i(listVar)
	(cond
		((equal (car (cdr (car listVar))) "(")
			(setq p (exp_i (cdr listVar)))
			(cond
				((equal (car (cdr (car p))) ")") (cdr p))
				(listVar)
			)
		)
		((equal (car (car listVar)) "identifier")
			(setf result "ID")
			(cdr listVar)
;			(base_exp_i (cdr listVar))
		)
;
		((equal (car (car listVar)) "integer") (setf result "VALUES") (cdr listVar))
		(listVar)
	)
)

(defun exp_i(listVar)
	(cond
		((equal t 	(or (equal (car (cdr (car listVar))) "set") 
					(equal (car (cdr (car listVar))) "defvar")))
			(cond
				( (equal (car (car (cdr listVar))) "identifier")
					(setq var (base_exp_i (cdr(cdr listVar))))
					;
					(cond
						((equal var (cdr(cdr listVar))) listVar)
						((setf result (concatenate 'string (concatenate 'string "(" (car (cdr (car listVar)))) " ID EXPI)")) var)
					)
				)
				(listVar)
			)
		)
		((equal t	(or (equal (car (cdr (car listVar))) "+")
					(equal (car (cdr (car listVar))) "-")
					(equal (car (cdr (car listVar))) "*")
					(equal (car (cdr (car listVar))) "**")
					(equal (car (cdr (car listVar))) "/")))
					(setq var (base_exp_i (cdr listVar)))
					(cond
						((equal var (cdr listVar)) listVar)
						(
							(setq var2 (base_exp_i var))
							(cond
								((equal var2 var) listVar)
								((setf result (concatenate 'string (concatenate 'string "(" (car (cdr (car listVar)))) " EXPI EXPI)")) var2)
							)
						)
					)
		)
		((equal (car (cdr (car listVar))) "deffun")
			(setq leng_list (cdr listVar))
			(cond
				((equal (car (car leng_list)) "identifier" )
					(setq id (base_id_list (cdr leng_list)))
					(cond 
						((equal (cdr leng_list) id) listVar)
						(
							(setq expl (base_explist_i id))
							(cond
								((equal expl id) listVar)
								( (setf result "(deffun ID IDLIST EXPLISTI)") expl)
							)
						)
					)
				)
				(listVar)
			)
		)
		((equal (car (cdr (car listVar))) "if")
			(setq exp_binary (base_exp_b (cdr listVar)))
			(cond
				((equal exp_binary (cdr listVar)) listVar)
				(
					(setq exp_list (base_explist_i exp_binary))				
					(cond
						((equal exp_binary exp_list) listVar)
						(
							(setq exp_list2 (base_explist_i exp_list))					
							(cond 
								((equal exp_list exp_list2) (setf result "(if EXPB EXPLISTI)") exp_list)
								((setf result "(if EXPB EXPLISTI EXPLISTI)") exp_list2)
							)
						)
					)
				)
			)
		)
		((equal (car (cdr (car listVar))) "while")
			(setq paranthes (cdr listVar))
			(cond
				((equal (car (cdr (car paranthes))) "(")
					(setq exp_binary (base_exp_b (cdr paranthes)))
					(cond
						((equal exp_binary (cdr paranthes)) listVar)
						(
							(cond 
								((equal (car (cdr (car exp_binary))) ")") 
									(setq exp_list (base_explist_i (cdr exp_binary)))
									(cond
										((equal exp_list (cdr exp_binary)) listVar)
										((setf result "(while (EXPB) EXPLISTI)") exp_list)
									)
								)
								(listVar)
							)
						)
					)
				)
				(listVar)
			)
		)	
		((equal (car (cdr (car listVar))) "for")
			(setq paranthes (cdr listVar))
			(cond
				((equal (car (cdr (car paranthes))) "(")
					(cond
						((equal (car (car (cdr paranthes))) "identifier")
							(setq exp_i1 (base_exp_i (cdr (cdr paranthes))))
							(cond
								((equal exp_i1 (cdr (cdr paranthes))) listVar)
								(
									(setq exp_i2 (base_exp_i exp_i1))
									(cond
										((equal exp_i2 exp_i1) listVar)
										(
											(cond 
												((equal (car(cdr (car exp_i2))) ")")
													(setq exp_list (base_explist_i (cdr exp_i2)))
													(cond
														((equal exp_list (cdr exp_i2)) listVar)
														((setf result "(for (ID EXPI EXPI) EXPLISTI)") exp_list)
													)
												)
												(listVar)
											)
										)
									)
								)
							)
						)
						(listVar)
					)
				)
				(listVar)
			)
		)				
		((equal (car(car listVar)) "identifier")
			(setq res (base_explist_i (cdr listVar)))
			(cond
				((equal res (cdr listVar)) listVar)
				((setf result "(ID EXPLISTI)")res)
			)
		)
		(listVar)
	)
)

(defun writing_file(str)
	(with-open-file (stream "131044010.tree":direction :output)
		(format stream "~A~%" "; DIRECTIVE: identify")
		(format stream "~A~%" "START")
		(format stream "~A~%" "INPUT")
		(format stream "~A~%" (concatenate 'string (string "INPUT -> ") str))
		(format stream "~A~%" (concatenate 'string str (concatenate 'string "-> " result)))
	)
)

; Eğer program exp_i yada explist ile başlamazsa analizi yapmaz. Çünkü start koşulumuz...
(defun parser (listVar)
	(cond
		((null listVar) nil)
		(
			(setq start1 (list(base_exp_i listVar)))
			; start1==(NIL) olmalı değilse hatalı kod ve tüm listeyi döndürür.
			(cond
				((equal start1 (list NIL)) (writing_file "EXPI ") nil)
				(
					(setq start2 (list(base_explist_i listVar)))
					(cond
						((equal start2 (list NIL)) (writing_file "EXPLIST ") nil)
						(listVar)
					)
				)
			)
		)
	)
)

(print (parser B))