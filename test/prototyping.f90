module my_cool_module
  use, intrinsic :: iso_c_binding
  implicit none

  type :: some_data
    integer(c_int) :: a_number
    character(64) :: a_fixed_length_string
    character(len = :, kind = c_char), pointer :: a_pointer_string
  end type some_data

  interface some_data
    module procedure :: new_some_data
  end interface some_data

contains

  function new_some_data() result(output)
    implicit none
    type(some_data) :: output
  end function new_some_data

  subroutine example_gc_func(raw_c_pointer)
    implicit none

    type(c_ptr), intent(in), value :: raw_c_pointer
    type(some_data), pointer :: dat

    call c_f_pointer(raw_c_pointer, dat)

    deallocate(dat%a_pointer_string)

  end subroutine example_gc_func

end module my_cool_module

program example
  use :: my_cool_module
  use :: vector
  use, intrinsic :: iso_c_binding
  implicit none

  type(some_data) :: dat
  type(vec) :: v
  type(c_ptr) :: generic_c_ptr
  integer(c_int) :: i, y
  type(some_data), pointer :: output
  logical(c_bool) :: t

  t = .true.

  do y = 1,10
    if (t) then
      print*,"tick"
    else
      print*,"tock"
    end if
    t = .not. t

    v = new_vec(sizeof(dat), int(10000000, c_size_t), example_gc_func)

    do i = 1,10000000
      dat%a_number = i
      dat%a_fixed_length_string = "I'm memcpy'd straight into the vector!"
      allocate(character(35) :: dat%a_pointer_string)
      t = .not. t
      if (t) then
        dat%a_pointer_string = "check it, I'm a fortran pointer 8)"
      else
        dat%a_pointer_string = "also I'm a fortran pointer! :D"
      end if
      call v%push_back(dat)
    end do

    do i = 1,10000000
      generic_c_ptr = v%at(int(i, c_size_t))
      call c_f_pointer(generic_c_ptr, output)
      print*,output%a_number, output%a_fixed_length_string, output%a_pointer_string
    end do

    call v%destroy()

  end do

end program example
