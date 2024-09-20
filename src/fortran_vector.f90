module fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  interface



    function internal_new_vector(initial_size, element_size, gc_func) result(vec_pointer) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      integer(c_size_t), intent(in), value :: initial_size, element_size
      type(c_funptr), intent(in), optional :: gc_func
      type(c_ptr) :: vec_pointer
    end function internal_new_vector

    subroutine internal_destroy_vector(vec_pointer) bind(c, name = "destroy_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: vec_pointer
    end subroutine internal_destroy_vector




    !* Uses memcpy under the hood.
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
