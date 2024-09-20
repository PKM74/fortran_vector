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
    procedure :: at => vector_at
    procedure :: is_empty => vector_is_empty
    procedure :: size => vector_size
    procedure :: capacity => vector_capacity
    procedure :: shrink_to_fit => vector_shrink_to_fit
    procedure :: clear => vector_clear
    procedure :: insert => vector_insert
    procedure :: erase => vector_erase
    procedure :: push_back => vector_push_back

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


  !* Get an element at an index in the vector.
  subroutine vector_at(this, index, generic_pointer)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: index
    class(*), intent(inout), pointer :: generic_pointer
    type(c_ptr) :: raw_pointer
    integer(1), dimension(:), pointer :: black_magic

    !! If this works, I will be impressed.
    raw_pointer = internal_vector_at(this%data, index)

    call c_f_pointer(raw_pointer, black_magic, [this%size_of_type])

    generic_pointer => black_magic(1)
  end subroutine vector_at


  !* Check if the vector is empty.
  function vector_is_empty(this) result(empty)
    implicit none

    class(vec), intent(inout) :: this
    logical(c_bool) :: empty

    empty = internal_vector_is_empty(this%data)
  end function vector_is_empty


  !* Get the number of elements in the vector.
  function vector_size(this) result(size)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t) :: size

    size = internal_vector_size(this%data)
  end function vector_size


  !* Get the total allocated size (in elements) of the vector.
  !* You can think of this as: "slots available before a resize occurs"
  function vector_capacity(this) result(cap)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t) :: cap

    cap = internal_vector_capacity(this%data)
  end function vector_capacity


  !* Shrink the capacity of the vector to it's size.
  !* (container size is trimmed to the current number of elements)
  subroutine vector_shrink_to_fit(this)
    implicit none

    class(vec), intent(inout) :: this

    call internal_vector_shrink_to_fit(this%data)
  end subroutine vector_shrink_to_fit


  !* Clear all the elements from the vector.
  !* The GC function will run on each element.
  subroutine vector_clear(this)
    implicit none

    class(vec), intent(inout) :: this

    !! todo: needs to run the GC function here!

    call internal_vector_clear(this%data)
  end subroutine vector_clear


  !* Insert an element into an index of the array.
  subroutine vector_insert(this, index, generic)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: index
    class(*), intent(in), target :: generic
    integer(1), dimension(:), pointer :: black_magic

    !! Just WAT.

    black_magic = transfer(generic, 1_1, size = this%size_of_type)

    call internal_vector_insert(this%data, index, c_loc(black_magic), this%size_of_type)
  end subroutine vector_insert


  !* Erase an element from the vector at an index.
  subroutine vector_erase(this, index)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: index

    !! todo: needs to run the GC function here!

    call internal_vector_erase(this%data, index)
  end subroutine vector_erase


  !* Uses memcpy under the hood.
  !* Push an element to the back of the vector.
  subroutine vector_push_back(this, generic)
    implicit none

    class(vec), intent(inout) :: this
    class(*), intent(in), target :: generic
    integer(1), dimension(:), pointer :: black_magic

    black_magic = transfer(generic, 1_1, size = this%size_of_type)

    call internal_vector_push_back(this%data, c_loc(black_magic), this%size_of_type)
  end subroutine vector_push_back





end module vector
