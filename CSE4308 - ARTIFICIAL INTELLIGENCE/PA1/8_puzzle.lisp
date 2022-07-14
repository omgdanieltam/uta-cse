; Daniel Tam
; 1001724986

; structure for the states
(defstruct state
	current_node
	g
	h
	f
	parent_node
)

; calculate h-score by determining the misplaced tiles
(defun calculate_h (node)
    (if (eq NIL node)
        (return-from calculate_h 10000)
    )

    (setf misplaced_tiles 0)
    (dotimes (i (length node))
        (if (eq (nth i node) (nth i goal))
            (incf misplaced_tiles 1)
        )
    )

    (return-from calculate_h (- (length node) misplaced_tiles))
)

; initialize a new state
(defun initialize_state (node)
    (setf state (make-state 
        :current_node node
        :g 0
        :h (setf h (calculate_h node))
        :f 10000
        :parent_node NIL
    ))
    (return-from initialize_state state)
)

; check if the puzzle is solvable
(defun is_solvable (node)
    (setf inversion 0)
    (loop for a from 0 to (length node)
        do (loop for b from (+ a 1) to (- (length node) 1)
            do (if (> (nth a node) (nth b node))
                (if (not (eq (nth a node) 0))
                    (if (not (eq (nth b node) 0))
                        (incf inversion 1)
                    )                
                )
            )
        )
    )
    
    (if (eq (mod inversion 2) 0)
        (return-from is_solvable T)
        (return-from is_solvable NIL)
    ) 
)

; find the next move
(defun find_next (node g_score)
    ; setup
    (setf new_possible_moves NIL)
    (setf empty_pos (find_empty (state-current_node node)))

    ; find available positions to move and create the states
    (if (eq empty_pos 0)
        (progn
            (setf new_state (swap_tiles node 0 1 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 0 3 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 1)
        (progn
            (setf new_state (swap_tiles node 1 0 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 1 2 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 1 4 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 2)
        (progn
            (setf new_state (swap_tiles node 2 1 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 2 5 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 3)
        (progn
            (setf new_state (swap_tiles node 3 0 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 3 4 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 3 6 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 4)
        (progn
            (setf new_state (swap_tiles node 4 1 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 4 3 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 4 5 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 4 7 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 5)
        (progn
            (setf new_state (swap_tiles node 5 2 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 5 4 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 5 8 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 6)
        (progn
            (setf new_state (swap_tiles node 6 3 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 6 7 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 7)
        (progn
            (setf new_state (swap_tiles node 7 6 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 7 4 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 7 8 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
    (if (eq empty_pos 8)
        (progn
            (setf new_state (swap_tiles node 8 5 g_score))
            (push new_state new_possible_moves)
            (setf new_state (swap_tiles node 8 7 g_score))
            (push new_state new_possible_moves)
            (return-from find_next new_possible_moves)
        )
    )
)

; swap tiles around and make a state
(defun swap_tiles (node_parent pos1 pos2 g_score)
    (setf new (copy-list (state-current_node node_parent)))
    (rotatef (nth pos1 new) (nth pos2 new))
    (setf new_state (initialize_state new))
    (setf (state-g new_state) g_score)
    (setf (state-f new_state) (+ (state-g new_state) (state-h new_state)))
    (setf (state-parent_node new_state) node_parent)
    (return-from swap_tiles new_state)
)

; find the empty tile in a list
(defun find_empty (node)
    (loop for a from 0 to (length node)
        do (if (eq (nth a node) 0)
            (return-from find_empty a)
        )
    )
)

; check if two lists are equal
(defun check_list(one two)
    (loop for a from 0 to (length one)
        do (if (not (eq (nth a one) (nth a two)))
            (return-from check_list NIL)
        )
    )
    (return-from check_list T)
)

; find the best next move by f-score
(defun best_next (possible)
    (setf best_f 10000)
    (setf best_pos 10000)

    ; find position of lowest f-score
    (dotimes (a (length possible))
        (setf possible_f (state-f (nth a possible)))
        (if (<= possible_f best_f)
            (if (check_closed (state-current_node (nth a possible)))
                (progn
                    (setf best_f possible_f)
                    (setf best_pos a)
                )
            )
        )
    )

    (return-from best_next best_pos)
)

; check againist our closed list
(defun check_closed (node)
    (dotimes (a (length closed_list))
        (if (check_list node (state-current_node (nth a closed_list)))
            (return-from check_closed NIL)      
        )
    )
    (return-from check_closed T)
)

; a* search
(defun a_star(start)
    ; setup
    (setf start_state (initialize_state start))
    (setf count 0)
    (setf open_list (list start_state))
    (setf closed_list NIL)
    
    ; begin our search
    (block search_loop
        ; set our initial starting point
        (setf current (nth count open_list))

        ; move our current into the closed list
        (push (pop open_list) closed_list)

        (loop
            ; grab the latest current node
            (setf current (nth count closed_list))

            ; check if we hit the goal
            (if (check_list (state-current_node current) goal)
                (return-from search_loop NIL)
            )

            ; find the next move
            (setf possible_moves (find_next current (+ count 1)))

            ; select the best next and move to closed list
            (setf best (best_next possible_moves))

            ;; push best option into closed list
            (push (nth best possible_moves) (cdr (last closed_list)))
            
            ; move all other possible into our open list
            (dotimes (i (length possible_moves))
                (if (not (eq i best))
                    (push (nth i possible_moves) open_list)
                )
            )

            ; increase our counter
            (incf count 1)
        )
    )
)

; solve the problem
(defun solve(start)
    ; test lists
    ;   (list '0 '1 '3 '4 '2 '5 '7 '8 '6)
    ;   (list '1 '8 '2 '0 '4 '3 '7 '6 '5)
    ;   (list '8 '1 '2 '0 '4 '3 '7 '6 '5)
    ;   (list '0 '1 '3 '4 '2 '5 '7 '8 '6)

    ; check if solvable first
    (if (not (is_solvable start))
        (progn
            (print "This puzzle is infeasible!")
            (return-from solve)
        )
    )

    ; set our goal and start
    (setf goal (list '1 '2 '3 '4 '5 '6 '7 '8 '0))
    (a_star start)

    ; print out
    (format t "Start ~T~T Goal~%")
    (format t "~D ~D ~D ~T~T ~D ~D ~D~%" (first start) (second start) (third start) (first goal) (second goal) (third goal))
    (format t "~D ~D ~D ~T~T ~D ~D ~D~%" (fourth start) (fifth start) (sixth start) (fourth goal) (fifth goal) (sixth goal))
    (format t "~D ~D ~D ~T~T ~D ~D ~D~%" (seventh start) (eighth start) (ninth start) (seventh goal) (eighth goal) (ninth goal))
    (format t "------~%")

    (dotimes (i (length closed_list))
        (setf current (nth i closed_list))
        (format t "~D ~D ~D ~%" (first (state-current_node current)) (second (state-current_node current)) (third (state-current_node current)))
        (format t "~D ~D ~D ~%" (fourth (state-current_node current)) (fifth (state-current_node current)) (sixth (state-current_node current)))
        (format t "~D ~D ~D ~%" (seventh (state-current_node current)) (eighth (state-current_node current)) (ninth (state-current_node current)))
        (format t "------~%")
    )

    ; print final expansion count
    (format t "Total nodes expaned: ~D" count)
)