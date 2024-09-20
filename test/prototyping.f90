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
  use :: vector
  use, intrinsic :: iso_c_binding
  implicit none

  type(bloof), target :: dat
  type(vec) :: v

  ! test = 1

  v = new_vec(sizeof(dat), int(10, c_size_t))

  dat%x = 2147483647


  ! call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  ! call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  ! call push_back(vec_pointer, c_loc(dat), sizeof(dat))
  ! call push_back(vec_pointer, c_loc(dat), sizeof(dat))

  ! print*,get_size(vec_pointer)




end program prototyping
