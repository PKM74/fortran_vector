module fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  interface

    function new_vector(element_size) result(vec_pointer) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      integer(c_size_t), intent(in), value :: element_size
      type(c_ptr) :: vec_pointer
    end function new_vector


  end interface

contains



end module fortran_vector
