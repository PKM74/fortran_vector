module fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  interface


    !* Create the new C vector memory.
    function internal_new_vector(initial_size, element_size, gc_func) result(vec_pointer) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      integer(c_size_t), intent(in), value :: initial_size, element_size
      type(c_funptr), intent(in), optional :: gc_func
      type(c_ptr) :: vec_pointer
    end function internal_new_vector


    !* Destroy C vector memory.
    subroutine internal_destroy_vector(vec_pointer) bind(c, name = "destroy_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_destroy_vector


    !* Get the pointer of an index into the vector.
    function internal_vector_at(vec_pointer, index) result(void_pointer) bind(c, name = "vector_at")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t), intent(in), value :: index
      type(c_ptr) :: void_pointer
    end function internal_vector_at


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


    



    !* Uses memcpy under the hood.
    !* Push an element back.
    subroutine internal_push_back(vec_pointer, new_element_pointer, element_size) bind(c, name = "vector_push_back")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer, new_element_pointer
      integer(c_size_t), intent(in), value :: element_size
    end subroutine internal_push_back


    !* Get the size of a vector.
    function internal_get_size(vec_pointer) result(vec_size) bind(c, name = "vector_size")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
      integer(c_size_t) :: vec_size
    end function internal_get_size


  end interface


contains



end module fortran_vector
