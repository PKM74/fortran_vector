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

  v = new_vec(sizeof(10), int(10, c_size_t))

  dat%x = 2147483647

  print*,c_loc(dat)

  call v%push_back(10)
  call v%push_back(20)
  call v%push_back(30)
  call v%push_back(40)

  print*,v%size()

  print*,v%capacity()

  ! print*,get_size(vec_pointer)




end program prototyping
