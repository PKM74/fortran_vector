module fortran_vector
  use, intrinsic :: iso_c_binding
  implicit none

  interface

    subroutine new_vector(t, element_size) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: t
      integer(c_size_t), intent(in), value :: element_size
    end subroutine new_vector


  end interface

contains



end module fortran_vector
