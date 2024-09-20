module fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  interface

    ! todo: make these internal.

    function new_vector(element_size) result(vec_pointer) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      integer(c_size_t), intent(in), value :: element_size
      type(c_ptr) :: vec_pointer
    end function new_vector


    subroutine push_back(vec_pointer, new_element_pointer, element_size) bind(c, name = "vector_push_back")
      use, intrinsic :: iso_c_binding
      implicit none


      type(c_ptr), intent(in), value :: vec_pointer, new_element_pointer
      integer(c_size_t), intent(in), value :: element_size
    end subroutine push_back


  end interface

contains



end module fortran_vector
