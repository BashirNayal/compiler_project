int main()
{
    // Create an auxiliary stack
    int arr_size = 8;
    int arr[arr_size] = { 4, 3, 5, 2, 1, 3, 2, 3 };


    int ii = 0;
    // printf("unsorted array: ");
    // while (ii < arr_size) {
    //     printf("%d ", arr[ii]);
    //     ii = ii + 1;
    // }
    // printf("\n");
    int h = 0;
    int l = arr_size - 1;
    int stack[8];
    int start_time = get_time();
    // initialize top of stack
    int top = 0;
    top = top - 1;
    // push initial values of l and h to stack
    top = top + 1;
    stack[top] = l;
    top = top + 1;
    stack[top] = h;
  
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top];
        top = top - 1;
        l = stack[top];
        top = top - 1;
  
        // Set pivot element at its correct position
        // in sorted array
        

        int x = arr[h];
        int i = l - 1;
        int j = l;
        int kk = h - 1;
        while (j <= kk) {
            if (arr[j] <= x) {
                i = i + 1;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j = j + 1;
        }
        int temp1 = arr[i+1];
        arr[i+1] = arr[h];
        arr[h] = temp1;

        int p = i + 1;


  
        // If there are elements on left side of pivot,
        // then push left side to stack
        int p1 = p - 1;
        if (p1 > l) {
            top = top + 1;
            stack[top] = l;
            top = top + 1;
            stack[top] = p - 1;
        }
  
        // If there are elements on right side of pivot,
        // then push right side to stack
        int p2 = p + 1;
        if (p2 < h) {
            top = top + 1;
            stack[top] = p + 1;
            top = top + 1;
            stack[top] = h;
        }
    }

    int end_time = get_time();

    int ii = 0;
    // printf("sorted array: ");
    // while (ii < arr_size) {
    //     printf("%d ", arr[ii]);
    //     ii = ii + 1;
    // }
    // printf("\ntook %d useconds to sort the array\n", end_time - start_time);
    printf("%d\n" , end_time - start_time);
    return 0;
    
}