(defun make-cd (title artist rating ripped)
  ;; plist
  (list :title title :artist artist :rating rating :ripped ripped))

;; *x* -> *_* is code convention for a global var
(defvar *db* nil)

(defun add-record (cd) (push cd *db*))

(defun print-db ()
  *db*)

(defun dump-db ()
  (dolist (cd *db*)
    ;; ~{ ~} -> print list
    ;; ~a -> print in a human readable format
    ;; ~10t -> 10 spaces
    (format t "~{~a:~10t~a~%~}~%" cd)))

(defun dump-db-oneline ()
  (format t "~{~{~a:~10t~a~%~}~%~}" *db*))

(defun prompt-read (prompt)
  (format *query-io* "~a: " prompt)
  ;; some list impls require force-output
  (force-output *query-io*)
  (read-line *query-io*))

(defun prompt-for-cd ()
  (make-cd
    (prompt-read "Title")
    (prompt-read "Artist")
    (or (parse-integer (prompt-read "Rating") :junk-allowed t) 0)
    (y-or-n-p "Ripped [y/n]: ")))

(defun add-cds ()
  (loop (add-record (prompt-for-cd))
    (if (not (y-or-n-p "Another? [y/n]: ")) (return))))

(defun save-db (filename)
  (with-open-file (out filename
                   :direction :output
                   :if-exists :supersede)
    (with-standard-io-syntax
      (print *db* out))))

(defun load-db (filename)
  (with-open-file (in filename)
    (with-standard-io-syntax
      (setf *db* (read in)))))

;;; #' -> Get me a function.

(defun select-by-artist (artist)
  (remove-if-not #'(lambda (cd) (equal (getf cd :artist) artist)) *db*))

(defun select (selector-fn)
  (remove-if-not selector-fn *db*))

(defun artist-selector (artist)
  #'(lambda (cd) (equal (getf cd :artist) artist)))

;;; (select (artist-selector "XYZ"))

;;; &key -> keyword paramaters
;;; supplied-p parameter (info whether a parameter is nil by default
;;;     or a caller explicitly set nil value
;;; a parameter example -> (name default-value supplied-p-var)

(defun where (&key title artist rating (ripped nil ripped-p))
  #'(lambda (cd)
      (and
        (if title (equal (getf cd :title) title) t)
        (if artist (equal (getf cd :artist) artist) t)
        (if rating (equal (getf cd :rating) rating) t)
        (if ripped-p (equal (getf cd :ripped) ripped) t))))

(defun update (selector-fn &key title artist rating (ripped nil ripped-p))
  (setf *db*
      (mapcar
        #'(lambda (row)
            (when (funcall selector-fn row)
              (if title (setf (getf row :title) title))
              (if artist (setf (getf row :artist) artist))
              (if rating (setf (getf row :rating) rating))
              (if ripped-p (setf (getf row :ripped) ripped)))
            row) *db*)))

(defun delete-rows (selector-fn)
  (setf *db* (remove-if selector-fn *db*)))

(defmacro backwards (expr) (reverse expr))

;;; (backwards ("hello world" t format)) --> (format t "hello world")

;;; WHERE MACRO
;;; (defun make-comparison-expr (field value)
;;;  (list 'equal (list 'getf 'cd field) value))
;;; In a back-quoted expression, any subexpression that’s preceded
;;; by a comma is evaluated.
(defun make-comparison-expr (field value)
  `(equal (getf cd ,field) ,value))

(defun make-comparisons-list (fields)
  (loop while fields
     collecting (make-comparison-expr (pop fields) (pop fields))))

;;; With &rest in its parameter list, a function or macro can
;;; take an arbitrary number of arguments, which are collected
;;; into a single list that becomes the value of the variable
;;; whose name follows the &rest

;;; ,@ "splices" the value of the following expression—which must
;;; evaluate to a list

;;; (macroexpand-1 '(macro ...)) -> macro expansion

(defmacro where (&rest clauses)
  `#'(lambda (cd) (and ,@(make-comparisons-list clauses))))
;;; WHERE MACRO

;;; UPDATE MACRO
(defun make-update (field value)
  `(setf (getf row ,field) ,value))

(defun make-updates-list (fields)
  (loop while fields
     collecting (make-update (pop fields) (pop fields))))

(defmacro update (selector-fn &rest updates)
  `(setf *db*
      (mapcar
        #'(lambda (row)
            (when (funcall ,selector-fn row)
              ,@(make-updates-list updates))
            row) *db*)))
;;; UPDATE MACRO
