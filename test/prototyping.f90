module cool
  use, intrinsic :: iso_c_binding
  implicit none

  type :: bloof
    integer(c_int) :: x
    character(64) :: d
    character(len = :, kind = c_char), pointer :: f
  end type bloof

  interface bloof
    module procedure :: new_bloof
  end interface bloof

contains

  function new_bloof() result(b)
    implicit none
    type(bloof) :: b
  end function new_bloof

  subroutine test_gc_func(raw_c_pointer)
    implicit none

    type(c_ptr), intent(in), value :: raw_c_pointer
    type(bloof), pointer :: dat

    call c_f_pointer(raw_c_pointer, dat)

    deallocate(dat%f)

  end subroutine test_gc_func

end module cool

program prototyping
  use :: cool
  use :: vector
  use, intrinsic :: iso_c_binding
  implicit none

  type(bloof) :: dat
  type(vec) :: v
  type(c_ptr) :: generic_c_ptr
  integer(c_int) :: i, y
  type(bloof), pointer :: output
  logical(c_bool) :: t

  t = .true.

  do y = 1,10
    if (t) then
      print*,"tick"
    else
      print*,"tock"
    end if
    t = .not. t

    v = new_vec(sizeof(dat), int(10000000, c_size_t), test_gc_func)

    do i = 1,10000000
      dat%x = i
      dat%d = "hello"
      allocate(character(22) :: dat%f)
      dat%f = "foop"
      call v%push_back(dat)
    end do


    do i = 1,10000000
      generic_c_ptr = v%at(int(i, c_size_t))
      call c_f_pointer(generic_c_ptr, output)
      ! print*,output%x, output%d, output%f
    end do

    call v%destroy()

  end do

end program prototyping
