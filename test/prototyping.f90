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
  integer(c_int) :: i

  v = new_vec(sizeof(10), int(10, c_size_t))

  dat%x = 10

  print*,v%size()

  i = 1


  do i = 1,10

    ! print*,i

    ! i = i + 1

    call v%push_back(i)

    print*,"new size: ",v%size()

    !! Deadlock into spin.
    call c_f_pointer(v%at(int(i - 1, c_size_t)), output)

    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(1_8), output)
    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(2_8), output)
    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(3_8), output)
    ! print*,"fortan output", output
  end do




  print*,"hi from fortran"


end program prototyping
