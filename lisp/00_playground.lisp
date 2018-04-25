;;; # is a so-called dispatching macro character

;;; Style Guide -> https://google.github.io/styleguide/lispguide.xml

;;; Interesting links
;;; https://stackoverflow.com/questions/24418838/how-to-stop-evaluating-lisp-form-when-passed-as-function-parameter
;;; https://stackoverflow.com/questions/4906255/whats-the-difference-between-and-in-lisp
;;;   '  -> evaluates to the symbol FOO
;;;   #' -> evaluates to the function bound to the name FOO
;;; https://stackoverflow.com/questions/869529/difference-between-set-setq-and-setf-in-common-lisp
;;;   setq -> set quoted -> (set (quote *foo*) 42)
;;;   setf -> set field  -> x.car := 42 == (setf (car x) 42)
;;;   NOTE: in modern lisp setf should be used
