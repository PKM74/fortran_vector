module cool
  use, intrinsic :: iso_c_binding
  implicit none

  type :: bloof
    integer(c_int) :: x
  end type bloof

  interface bloof
    module procedure :: new_bloof
  end interface bloof

contains

  function new_bloof() result(b)
    implicit none

    type(bloof) :: b
  end function new_bloof

end module cool

program prototyping
  use :: cool
  use :: fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  integer(c_int), target :: test
  type(bloof), target :: dat

  test = 1

  ! call new_vector(c_loc(test))

  dat%x = 2147483647

  call new_vector(sizeof(bloof()))


end program prototyping
