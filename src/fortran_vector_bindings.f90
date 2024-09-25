module fortran_vector_bindings
  use, intrinsic :: iso_c_binding
  implicit none


  interface


    !* Create the new C vector memory.
    function internal_new_vector(initial_size, element_size) result(vec_pointer) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      integer(c_size_t), intent(in), value :: initial_size, element_size
      type(c_ptr) :: vec_pointer
    end function internal_new_vector


    !* Destroy C vector memory.
    subroutine internal_destroy_vector(vec_pointer) bind(c, name = "destroy_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_destroy_vector


    !* Get the pointer of an index into the vector.
    function internal_vector_get(vec_pointer, index) result(void_pointer) bind(c, name = "vector_get")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t), intent(in), value :: index
      type(c_ptr) :: void_pointer
    end function internal_vector_get


    !* Overwrite of an index into the vector.
    function internal_vector_set(vec_pointer, index, fortran_data) result(void_pointer) bind(c, name = "vector_set")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t), intent(in), value :: index
      type(c_ptr), intent(in), value :: fortran_data
      type(c_ptr) :: void_pointer
    end function internal_vector_set


    !* Check if a vector is empty.
    function internal_vector_is_empty(vec_pointer) result(vec_is_empty) bind(c, name = "vector_is_empty")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      logical(c_bool) :: vec_is_empty
    end function internal_vector_is_empty


    !* Get the number of elements in the vector.
    function internal_vector_size(vec_pointer) result(vec_size) bind(c, name = "vector_size")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t) :: vec_size
    end function internal_vector_size


    !* Get the total allocated size (in elements) of the vector.
    !* You can think of this as: "slots available before a resize occurs"
    function internal_vector_capacity(vec_pointer) result(vec_cap) bind(c, name = "vector_capacity")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t) :: vec_cap
    end function internal_vector_capacity


    !* Shrink the capacity of the vector to it's size.
    !* (container size is trimmed to the current number of elements)
    subroutine internal_vector_shrink_to_fit(vec_pointer) bind(c, name = "vector_shrink_to_fit")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_vector_shrink_to_fit


    !* Clear all the elements from the vector.
    subroutine internal_vector_clear(vec_pointer) bind(c, name = "vector_clear")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_vector_clear


    !* Insert an element into an index of the array.
    subroutine internal_vector_insert(vec_pointer, index, new_element, element_size) bind(c, name = "vector_insert")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(inout) :: vec_pointer
      type(c_ptr), intent(in), value :: new_element
      integer(c_size_t), intent(in), value :: index, element_size
    end subroutine internal_vector_insert


    !* Remove an element from the vector at an index.
    !* This will shift the entire vector back after the index.
    subroutine internal_vector_remove(vec_pointer_pointer, index) bind(c, name = "vector_remove")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer_pointer
      integer(c_size_t), intent(in), value :: index
    end subroutine internal_vector_remove


    !* Uses memcpy under the hood.
    !* Push an element to the back of the vector.
    subroutine internal_vector_push_back(vec_pointer, new_element_pointer, element_size) bind(c, name = "vector_push_back")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(inout) :: vec_pointer
      type(c_ptr), intent(in), value :: new_element_pointer
      integer(c_size_t), intent(in), value :: element_size
    end subroutine internal_vector_push_back


    !* Removes the last element from the vector.
    subroutine internal_vector_pop_back(vec_pointer) bind(c, name = "vector_pop_back")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_vector_pop_back


    !* Request a vector to reallocate to the new capacity.
    subroutine internal_vector_reserve(vec_pointer, new_capacity) bind(c, name = "vector_reserve")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(inout) :: vec_pointer
      integer(c_size_t), intent(in), value :: new_capacity
    end subroutine internal_vector_reserve


    !* Resize a vector to a new size.
    !* Requires a new default element.
    subroutine internal_vector_resize(vec_pointer, new_size, default_element_pointer, element_size) bind(c, name = "vector_resize")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(inout) :: vec_pointer
      type(c_ptr), intent(in), value :: default_element_pointer
      integer(c_size_t), intent(in), value :: new_size, element_size
    end subroutine internal_vector_resize


    !* Swap one vector's contents with another.
    !* If they are not of the same type, this will throw a C exception.
    subroutine internal_vector_swap(vec_pointer, other_vec_pointer, element_size) bind(c, name = "vector_swap")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer, other_vec_pointer
      integer(c_size_t), intent(in), value :: element_size
    end subroutine internal_vector_swap


!? BEGIN FUNCTION BLUEPRINTS ==================================================


    !* If your type uses pointers, I suggest you give your vector a GC.
    !*
    !* The raw_c_pointer is the element in the array. You'll be getting it
    !* right before it's freed from C memory.
    subroutine vec_gc_blueprint(raw_c_pointer)
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: raw_c_pointer
    end subroutine vec_gc_blueprint


  end interface


end module fortran_vector_bindings
