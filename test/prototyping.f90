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
  type(c_ptr) :: generic_c_ptr
  integer(c_int), pointer :: output

  v = new_vec(sizeof(10), int(10, c_size_t))

  dat%x = 10

  print*,v%size()

  call v%push_back(10)
  ! call v%push_back(20)
  ! call v%push_back(30)
  ! call v%push_back(20)

  print*,v%size()

  print*,v%at(0_8)

  call c_f_pointer(v%at(0_8), output)

  print*,"fortan output", output



  print*,"hi from fortran"


end program prototyping
