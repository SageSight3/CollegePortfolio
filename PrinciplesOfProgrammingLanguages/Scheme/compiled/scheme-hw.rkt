#lang racket

(define (pick index a-list)
 (cond
   ((< index 1) '())
   ((null? a-list) '())
   ((= index 1) (car a-list))
   (else (pick (- index 1) (cdr a-list)))))

(define (frontier a-list)
    (if (not (pair? a-list))
        (list a-list)
        (append (frontier (car a-list)) (frontier (cdr a-list)))))

(define (my-reverse a-list)
  (if (null? a-list)
      '()
      (append (my-reverse (cdr a-list)) (list (car a-list)))))

(define (deep-reverse a-list)
  (if (pair? a-list)
      (map deep-reverse (my-reverse a-list))
      a-list))

(define (reduce a-list)
  a-list)

(provide pick frontier my-reverse deep-reverse reduce)