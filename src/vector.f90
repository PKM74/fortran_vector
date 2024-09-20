module vector
  use, intrinsic :: iso_c_binding
  use :: fortran_vector_bindings
  implicit none


  private


  public :: vec
  public :: new_vec


  type :: vec
    private
    type(c_ptr) :: data
    integer(c_size_t) :: size_of_type
  contains
    procedure :: destroy => vector_destroy
  end type vec


contains


  !* Create a new vector.
  !* I did not create a module interface because I want you to be able to see explicitly
  !* Where you create your vector.
  function new_vec(size_of_type, initial_size) result(v)
    implicit none

    ! size_of_type allows you to simply get the size of your type before and hard code it into your program. 8)
    integer(c_size_t), intent(in), value :: size_of_type, initial_size
    type(vec) :: v

    ! todo: needs a GC func thing.

    v%data = internal_new_vector(initial_size, size_of_type, c_null_funptr)
    v%size_of_type = size_of_type
  end function new_vec


  !* Destroy all components of the vector. Elements and underlying C memory.
  subroutine vector_destroy(this)
    implicit none

    class(vec), intent(inout) :: this

    !! todo: run the GC function here!

    call internal_destroy_vector(this%data)
  end subroutine vector_destroy


end module vector
