module vector
  use, intrinsic :: iso_c_binding
  use :: fortran_vector_bindings
  implicit none


  private


  public :: vec


  type :: vec
    private
    type(c_ptr) :: data
    integer(c_size_t) :: size_of_type
  end type vec


contains


  !* Create a new vector.
  function new_vec(size_of_type, initial_size) result(v)
    implicit none

    ! size_of_type allows you to simply get the size of your type before and hard code it into your program. 8)
    integer(c_size_t), intent(in), value :: size_of_type, initial_size
    type(vec) :: v

    ! todo: needs a GC func thing.

    v%data = internal_new_vector(initial_size, size_of_type, c_null_funptr)
    v%size_of_type = size_of_type
  end function new_vec



end module vector
