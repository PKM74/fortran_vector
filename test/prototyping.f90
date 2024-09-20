module cool
  use, intrinsic :: iso_c_binding
  implicit none

  type :: bloof
    integer(c_int) :: x
  end type bloof

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

  call new_vector(c_loc(dat), sizeof(dat))


end program prototyping
