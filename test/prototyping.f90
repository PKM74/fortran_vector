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

  type(bloof) :: dat
  type(vec) :: v
  type(c_ptr) :: generic_c_ptr
  integer(c_int) :: i
  type(bloof), pointer :: output

  v = new_vec(sizeof(dat), int(0, c_size_t))

  do i = 1,10000000
    dat%x = i
    call v%push_back(dat)
  end do


  do i = 1,10000000
    generic_c_ptr = v%at(int(i, c_size_t))
    call c_f_pointer(generic_c_ptr, output)
    print*,output%x
  end do




end program prototyping
