module fortran_vector
  implicit none
  private

  public :: say_hello
contains
  subroutine say_hello
    print *, "Hello, fortran_vector!"
  end subroutine say_hello
end module fortran_vector
