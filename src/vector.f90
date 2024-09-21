module vector
  use, intrinsic :: iso_c_binding
  use :: fortran_vector_bindings
  implicit none


  private


  public :: vec
  public :: new_vec


  type :: vec
    private
    type(c_ptr) :: data = c_null_ptr
    integer(c_size_t) :: size_of_type = 0
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
    procedure :: pop_back => vector_pop_back
    procedure :: reserve => vector_reserve
    procedure :: resize => vector_resize
    procedure :: swap => vector_swap
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

    v%data = internal_new_vector(initial_size, size_of_type)

    v%size_of_type = size_of_type
  end function new_vec


  !* Destroy all components of the vector. Elements and underlying C memory.
  subroutine vector_destroy(this)
    implicit none

    class(vec), intent(inout) :: this

    !! todo: run the GC function here!

    call internal_destroy_vector(this%data)

    this%data = c_null_ptr
    this%size_of_type = 0
  end subroutine vector_destroy


  !* Get an element at an index in the vector.
  function vector_at(this, index) result(raw_c_pointer)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: index
    type(c_ptr) :: raw_c_pointer

    if (index < 1 .or. index > this%size()) then
      error stop "[Vector] Error: Went out of bounds."
    end if

    raw_c_pointer = internal_vector_at(this%data, index)
  end function vector_at


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
    type(c_ptr) :: black_magic

    black_magic = transfer(loc(generic), black_magic)

    call internal_vector_insert(this%data, index, black_magic, this%size_of_type)
  end subroutine vector_insert


  !* Erase an element from the vector at an index.
  subroutine vector_erase(this, index)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: index

    if (index < 1 .or. index > this%size()) then
      error stop "[Vector] Error: Went out of bounds."
    end if

    !! todo: needs to run the GC function here!

    call internal_vector_erase(this%data, index)
  end subroutine vector_erase


  !* Uses memcpy under the hood.
  !* Push an element to the back of the vector.
  subroutine vector_push_back(this, generic)
    implicit none

    class(vec), intent(inout) :: this
    class(*), intent(in), target :: generic
    type(c_ptr) :: black_magic

    black_magic = transfer(loc(generic), black_magic)

    call internal_vector_push_back(this%data, black_magic, this%size_of_type)
  end subroutine vector_push_back


  !* Remove the last element of the vector.
  subroutine vector_pop_back(this)
    implicit none

    class(vec), intent(inout) :: this

    !? If it's empty, popping can corrupt the memory.
    if (this%is_empty()) then
      return
    end if

    call internal_vector_pop_back(this%data)
  end subroutine vector_pop_back


  !* Reserve an internal capacity of the vector.
  subroutine vector_reserve(this, new_capacity)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: new_capacity

    call internal_vector_reserve(this%data, new_capacity)
  end subroutine vector_reserve


  !* Resize a vector to a new size.
  !* Requires a new default element.
  subroutine vector_resize(this, new_size, default_element)
    implicit none

    class(vec), intent(inout) :: this
    integer(c_size_t), intent(in), value :: new_size
    class(*), intent(in), target :: default_element
    type(c_ptr) :: black_magic

    black_magic = transfer(loc(default_element), black_magic)

    call internal_vector_resize(this%data, new_size, black_magic, this%size_of_type)
  end subroutine vector_resize


  !* Swap one vector's contents with another.
  !* If they are not of the same type, this will throw a C exception.
  subroutine vector_swap(this, other)
    implicit none

    class(vec), intent(inout) :: this
    type(vec), intent(inout) :: other

    call internal_vector_swap(this%data, other%data, this%size_of_type)
  end subroutine vector_swap


end module vector
