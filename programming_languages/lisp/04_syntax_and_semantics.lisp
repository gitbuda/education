(defvar x t)
(write x)
(print (if x (format t "yes") (format t "no")))
;;; (quote (+ 1 2)) is the same as '(+ 1 2) -> do not evaluate just return
;;; always use EQL
