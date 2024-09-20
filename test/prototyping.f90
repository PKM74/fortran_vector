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
  type(c_ptr) :: vec_pointer

  test = 1

  ! call new_vector(c_loc(test))

  dat%x = 2147483647

  vec_pointer = new_vector(int(10, c_size_t), sizeof(bloof()), c_null_funptr)

  call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  call push_back(vec_pointer, c_loc(dat), sizeof(dat))

  print*,get_size(vec_pointer)




end program prototyping
