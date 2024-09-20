module fortran_vector
  implicit none

  interface

    subroutine new_vector(t) bind(c, name = "new_vector")
      use, intrinsic :: iso_c_binding
      implicit none

      type(c_ptr), intent(in), value :: t
    end subroutine new_vector


  end interface

end module fortran_vector
