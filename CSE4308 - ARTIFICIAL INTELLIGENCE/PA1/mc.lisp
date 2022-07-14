; Daniel Tam
; 1001724986

; structure for states
(defstruct state
    current
    parent
    boat
)

; generate available search options
(defun generate_search_options (boatcount)
    (setf search_options NIL)
    (let ((i 1))
        (block outer
            (loop
                ; 0 x
                (setf temp (list i 0))
                (push temp search_options)
                ; x 0
                (setf temp (list 0 i))
                (push temp search_options)

                ; all non-zeros
                (let ((j 1))
                    (block inner
                        (loop
                            (if (<= j (- boatcount i))
                                (progn
                                    (setf temp (list i j))
                                    (push temp search_options)
                                    (incf j 1)
                                )
                                (return-from inner)
                            )
                        ) 
                    )
                )
                
                (if (< i boatcount)
                    (incf i 1)
                    (return-from outer)
                )
            )
        )
    )
    (return-from generate_search_options NIL)
)

; subtract two lists
(defun subtract_lists (list1 list2)
    (return-from subtract_lists (list (- (nth 0 list1) (nth 0 list2)) (- (nth 1 list1) (nth 1 list2))))
)

; add two lists
(defun add_lists (list1 list2)
    (return-from add_lists (list (+ (nth 0 list1) (nth 0 list2)) (+ (nth 1 list1) (nth 1 list2))))
)

; check if lists are equal
(defun is_equal (list1 list2)
    (loop for a from 0 to (length list1)
        do (if (not (eq (nth a list1) (nth a list2)))
            (return-from is_equal NIL)
        )
    )
    (return-from is_equal T)
)

; check if one list is within the second list of lists
(defun contains_list (list1 list2)
    (dotimes (i (length list2))
        (if (is_equal list1 (nth i list2))
            (return-from contains_list T)
        )
    )
    (return-from contains_list NIL)
)

; generate a list of illegal items to remove
(defun generate_removal (list1)
    (setf remove NIL)
    (dotimes (i (length list1))
        (setf temp (state-current (nth i list1)))

        ; greater than max group size
        (if (or (> (first temp) groupsize) (> (second temp) groupsize))
            (push temp remove)

            ; less than 0
            (if (or (< (first temp) 0) (< (second temp) 0))
                (push temp remove)

                ; if it's been previously visited
                (if (has_visited (nth i list1))
                    (push temp remove)
                    (progn
                        ; if missionaries are less than cannibals and not 0 (left)
                        (if (and (< (first temp) (second temp)) (> (first temp) 0))
                            (push temp remove)
                        )
                        ; if missionaries are less than cannibales and not 0 (right) and all the missionaries cannot all fit back on a boat
                        (if (and (< (- groupsize (first temp)) (- groupsize (second temp))) (> (- groupsize (first temp)) 0))
                            (push temp remove)
                        )
                    )
                )
            )
        )
    )
    (return-from generate_removal remove)
)

; check if the node has been visited before
(defun has_visited (node)
    (dotimes (i (length visited))
        (if (and (is_equal (state-current node) (state-current (nth i visited))) (eq (state-boat node) (state-boat (nth i visited))))
            (return-from has_visited T)
        )
    )
    (return-from has_visited NIL)
)

; expand the state
(defun expand (node_list)
    ; setup
    (setf available_moves NIL)
    (setf next_moves NIL)
    (setf fnext_moves NIL)
    (setf removal_list NIL)
    (incf depth 1)

    (dotimes (i (length node_list))
        (setf node (nth i node_list))
        ;(push (state-current (nth i node_list)) visited)
        (push node visited)

        ; check our current against the goal
        (if (is_equal (state-current node) end)
            (return-from expand node)
        )

        ; use our available options to add/subtract from our nodes
        (if (eq (state-boat node) 1) ; boat on left
            (progn
                ; loop through search options and subtract from our node
                (dotimes (i (length search_options))
                    (push (initialize_state (subtract_lists (state-current node) (nth i search_options)) node 0) available_moves)            
                )
            )
            (progn
                ; loop through our search options and add from our node
                (dotimes (i (length search_options))
                    (push (initialize_state (add_lists (state-current node) (nth i search_options)) node 1) available_moves)
                )
            )
        )
    )

    ; check our available moves and remove illegal moves
    (setf removal_list (generate_removal available_moves))

    (dotimes (i (length available_moves))
        (if (not (contains_list (state-current (nth i available_moves)) removal_list))
            (push (nth i available_moves) next_moves)
        )
    )
    
    ; take out duplicates (we just did two for loops)
    (setf outer 0)
    (block dup_loop_out
        (loop
            (if (>= outer (length next_moves))
                (return-from dup_loop_out)
            )
            (setf inner (+ outer 1))
            (setf dup NIL)

            (block dup_loop_in
                (loop
                    (if (>= inner (length next_moves))
                        (return-from dup_loop_in)
                    )

                    (if (is_equal (state-current (nth inner next_moves)) (state-current (nth outer next_moves)))
                        (setf dup T)
                    )
                    (incf inner 1)
                )
            )
            (if (not dup)
                (push (nth outer next_moves) fnext_moves)
            )
            (incf outer 1)
        ) 
    )

    (return-from expand (expand fnext_moves))

)

; initilize a state
(defun initialize_state (current_node parent_node boat_side)
    (setf state (make-state
        :current current_node
        :parent parent_node
        :boat boat_side
    ))
    (return-from initialize_state state)
)

; split nodes back to the parent
(defun split_to_parent (node)
    (if (not (eq (state-parent node) NIL))
        (return-from split_to_parent (state-parent node))
    )
    (push (state-current node) split)
    (return-from split_to_parent split)
)

(defun solve (groupcount boatcount)
    ; create our left side and goal
    (setf start (initialize_state (list groupcount groupcount) NIL 1))
    (setf end (list 0 0))

    ; overhead variables
    (setf visited NIL)
    (setf groupsize groupcount)
    (setf boatsize boatcount)
    (setf depth 0)

    ; generate available movement options
    (generate_search_options boatcount)

    ; begin our search
    (setf search (expand (list start)))

    ;(return-from cannibals NIL)

    ; split our nodes back up to output
    (setf split NIL)
    (setf temp (state-parent search))
    (push (state-current search) split)
    (split_to_parent search)
    (dotimes (i (- depth 1))
        (push (state-current temp) split)
        (setf temp (state-parent temp))
    )

    (dotimes (i (length split))
        (if (eq i 0)
            (progn
                (format t "~v@{~A~:*~}" 10 "=")
                (format t " ~A " "Start")
                (format t "~v@{~A~:*~}~%" 10 "=")
                (format t "~v@{~A~:*~} " (nth 0 (nth i split)) "M")
                (format t "~v@{~A~:*~} " (nth 1 (nth i split)) "C")
                (format t " ^~v@{~A~:*~}" 10 "-")
                (format t "~%~%")
            )
            (progn
                (format t "~v@{~A~:*~}" 10 "=")
                (format t " ~A ~D " "Step" i )
                (format t "~v@{~A~:*~}~%" 10 "=")
                (format t "~v@{~A~:*~} " (nth 0 (nth i split)) "M")
                (format t "~v@{~A~:*~} " (nth 1 (nth i split)) "C")
                (if (eq (mod i 2) 0)
                    (format t " ^~v@{~A~:*~} " 10 "-")
                    (format t " ~v@{~A~:*~}^ " 10 "-")
                )
                (format t "~v@{~A~:*~} " (- groupsize (nth 0 (nth i split))) "M")
                (format t "~v@{~A~:*~} " (- groupsize (nth 1 (nth i split))) "C")
                (format t "~%~%")
            )
        )
    )
    (format t "~A ~D " "Total Depth:" (- depth 1))
) 