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

  v = new_vec(sizeof(10), int(0, c_size_t))

  dat%x = 10

  ! print*,v%size()

  call v%reserve(3_8)

  ! do

  !   call v%push_back(1)
  !   call v%push_back(2)
  !   call v%push_back(3)
  !   call v%push_back(4)

  !   call v%erase(2_8)

  !   call c_f_pointer(v%at(1_8), output)
  !   print*,"output:", output

  !   call c_f_pointer(v%at(2_8), output)
  !   print*,"output:", output

  !   call c_f_pointer(v%at(3_8), output)
  !   print*,"output:", output

  !   print*,"begin insertion"

  !   call v%insert(2_8, 2)

  !   call c_f_pointer(v%at(1_8), output)
  !   print*,"output:", output

  !   call c_f_pointer(v%at(2_8), output)
  !   print*,"output:", output

  !   call c_f_pointer(v%at(3_8), output)
  !   print*,"output:", output

  !   call v%pop_back()
  !   call v%pop_back()
  !   call v%pop_back()
  !   call v%pop_back()
  !   call v%pop_back()

  ! end do



  do i = 1,10000000

    ! print*,i

    ! i = i + 1

    call v%push_back(i)

    if (mod(v%size(), 1000000) == 0) then
      print*,"new size: ",v%size()
    end if

    !? Insurance
    call c_f_pointer(v%at(int(i, c_size_t)), output)
    if (output /= i) then
      error stop
    end if

    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(1_8), output)
    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(2_8), output)
    ! print*,"fortan output", output
    ! call c_f_pointer(v%at(3_8), output)
    ! print*,"fortan output", output
  end do


  print*,"hi from fortran"

  ! call sleep(10)


end program prototyping
