program wmon_test
    USE iso_c_binding,       ONLY :  &
    C_PTR, C_NULL_PTR, C_ASSOCIATED, C_NULL_CHAR, C_LOC, &
    C_INT, C_FLOAT, C_DOUBLE, c_size_t
    use wmon, ONLY : wmon_init, wmon_push_metric, C_Value_string, wmon_destroy, timestamp
    
    integer(kind=c_size_t) :: tstamp
    real(kind=8) :: rr
    type(c_ptr) :: wm
    character(len=32) :: fieldname
    character(len=32) :: fieldval
    character(len=32) :: fieldpair

    fieldname = "ftime"
    
    wm = wmon_init()
    
    do while(.true.) 
        tstamp = timestamp()
        rr = rand() * 5
        write(fieldval , *) rr

        call sleep(int(rr))

        fieldpair = trim(adjustl(fieldname)) // "=" // trim(adjustl(fieldval))
        write(*,*) fieldpair
        call wmon_push_metric(wm, C_Value_string("cosmof"), C_Value_string(fieldpair), tstamp)
    enddo

end program