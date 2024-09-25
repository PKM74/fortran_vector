module my_cool_module
  use, intrinsic :: iso_c_binding
  implicit none

  !* An example data type you can use.
  type :: some_data
    integer(c_int) :: a_number
    character(64) :: a_fixed_length_string
    character(len = :, kind = c_char), pointer :: a_pointer_string => null()
  end type some_data

  !* Allows you to call some_data() when getting the size.
  interface some_data
    module procedure :: new_some_data
  end interface some_data

contains

  !* A very explicit constructor.
  function new_some_data() result(output)
    implicit none
    type(some_data) :: output
  end function new_some_data

  !* If your type uses pointers, I suggest you give your vector a GC.
  !*
  !* The raw_c_pointer is the element in the array. You will be getting it
  !* right before it is freed from C memory.
  !*
  !* Here is an example using our some_data type.
  subroutine example_gc_func(raw_c_pointer)
    implicit none

    type(c_ptr), intent(in), value :: raw_c_pointer
    type(some_data), pointer :: dat

    call c_f_pointer(raw_c_pointer, dat)

    deallocate(dat%a_pointer_string)
  end subroutine example_gc_func

end module my_cool_module


!* Now, let us move onto the actual program.
program example
  use :: my_cool_module
  use :: vector
  use, intrinsic :: iso_c_binding
  implicit none

  type(some_data) :: dat
  type(vec) :: v
  type(c_ptr) :: generic_c_ptr
  integer(c_int) :: i, y
  integer(c_size_t) :: j
  type(some_data), pointer :: output
  integer(c_int), pointer :: int_pointer
  logical(c_bool) :: t


  v = new_vec(int(sizeof(10), c_int64_t), 0_8)

  call v%push_back(1)
  call v%push_back(2)
  call v%push_back(3)

  call v%set(1_8, 99999)

  do i = 1, int(v%size())
    call c_f_pointer(v%get(int(i, c_int64_t)), int_pointer)
    print*,int_pointer
  end do


  call sleep(100)


  t = .true.

  !* We are going to shovel through 200 million items over the course of this. 43.9 GB of data.
  do y = 1,200

    !* I thought this would be entertaining.
    if (t) then
      print*,"tick ",y
    else
      print*,"tock ",y
    end if
    t = .not. t

    !* Our vector shall start off with a capacity of 0.
    !* This creates the underlying C memory.
    !* If you know your data size and it never changes, you can use a literal number here.
    v = new_vec(sizeof(dat), int(0, c_size_t), example_gc_func)

    !* Let us push 1 million items into the vector.
    do i = 1,1000000
      dat%a_number = i
      dat%a_fixed_length_string = "I'm memcpy'd straight into the vector!"

      !! Notice I am giving the pointer a new memory address!
      !! If you do not do this, you are going to double free an address in your GC. :)
      allocate(character(35) :: dat%a_pointer_string)

      !* I thought this would also be entertaining.
      t = .not. t

      if (t) then
        dat%a_pointer_string = "check it, I'm a fortran pointer 8)"
      else
        dat%a_pointer_string = "also I'm a fortran pointer! :D"
      end if

      !* Push that thing to the end of the list.
      !* This uses memcpy under the hood, your element can just be a target as shown!
      call v%push_back(dat)
    end do

    !* Let us just pop 10k items off the stack for no reason.
    do i = 1,10000
      call v%pop_back()
    end do

    !* Now let us get the elements.
    !* You can see we can iterate based on the size of the vector.
    do j = 1,v%size()
      generic_c_ptr = v%get(int(j, c_size_t))
      call c_f_pointer(generic_c_ptr, output)

      !* Add in an extra assertion for double check in this example.
      if (output%a_number /= j) then
        error stop
      end if

      !? Printing is very slow due to terminal syncronization.
      ! print*,output%a_number, output%a_fixed_length_string, output%a_pointer_string
    end do

    !* Now let us just shove something in the middle.
    !! Notice I am giving the pointer a new memory address!
    !! If you do not do this, you are going to double free an address in your GC. :)
    !? Also, notice: Due to the sheer size of this list, this is very slow.
    allocate(character(3) :: dat%a_pointer_string)
    dat%a_pointer_string = "yep"
    call v%insert(23451_8, dat)

    !* Now let us delete the first 10 items.
    !* With a list this HUGE this is very slow!
    !* We literally have to memmove the items down, byte by byte.
    !? In the future: I hope to optimize this so you can do it in one huge chunk.
    do i = 1,10
      call v%remove(1_8)
    end do

    do i = 1,int(v%size())
      call c_f_pointer(v%get(int(i, c_int64_t)), output)
      ! print*,output%a_number
    end do

    !* This not only calls the GC on all of our elements (if you gave it one),
    !* It also destroys the underlying C memory.
    call v%destroy()

    !* Now we go again.
  end do

end program example
