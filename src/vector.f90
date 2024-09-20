module vector
  use, intrinsic :: iso_c_binding
  use :: fortran_vector_bindings
  implicit none


  private


  public :: vec


  type :: vec
    private
    type(c_ptr) :: data
  end type vec

contains

  function new_vec() result(v)
    implicit none

    type(vec) :: v

    
  end function new_vec



end module vector
