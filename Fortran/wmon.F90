module wmon
use iso_c_binding

USE iso_c_binding,       ONLY :  &
  C_PTR, C_NULL_PTR, C_ASSOCIATED, C_NULL_CHAR, C_LOC, &
  C_INT, C_FLOAT, C_DOUBLE, c_size_t

implicit none

  interface
integer(kind=c_size_t) function timestamp() bind(c)
  use iso_c_binding
end function

type(c_ptr) function wmon_init() bind(c)
  use iso_c_binding
end function

subroutine wmon_push_metric(wm, meas, fieldvalpair, timestamp) bind(c)
    use iso_c_binding
    type(c_ptr), value :: wm
    integer(kind=c_signed_char) :: meas(*)
    integer(kind=c_signed_char) :: fieldvalpair(*)
    integer(kind=c_size_t), value :: timestamp
end subroutine

subroutine wmon_push_metric_tag(wm, meas, fieldvalpair, timestamp, tag) bind(c)
    use iso_c_binding
    type(c_ptr), value :: wm
    integer(kind=c_signed_char) :: meas(*)
    integer(kind=c_signed_char) :: fieldvalpair(*)
    integer(kind=c_size_t), value :: timestamp
    integer(kind=c_signed_char) :: tag(*)
end subroutine

subroutine wmon_destroy(wm) bind(c)
    use iso_c_binding
    type(c_ptr), value :: wm
end subroutine
end interface

contains

FUNCTION C_Value_string(v)
  USE iso_c_binding, only : c_signed_char
  CHARACTER(*), INTENT(IN) :: v
  INTEGER(c_signed_char), DIMENSION(LEN_TRIM(v)+1) :: C_Value_string
  INTEGER :: i
  DO i = 1, LEN_TRIM(v)
      C_Value_string(i) = ICHAR(v(i:i), KIND=c_signed_char)
  END DO
  C_Value_string(LEN_TRIM(v)+1) = 0
END FUNCTION


end module
