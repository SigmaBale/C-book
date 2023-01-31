static void swap(int list[], int i_dx, int i_dy)
{
    int temp = list[i_dx];
    list[i_dx] = list[i_dy];
    list[i_dy] = temp;
    return;
}

static int partition(int list[], int s_id, int e_id)
{
    int pivot, i;
    swap(list, s_id, (s_id + e_id)>>1);
    pivot = s_id;
    for(i = pivot+1; i <= e_id; i++)
        if (list[i] <= list[s_id])
            swap(list, ++pivot, i);
    swap(list, s_id, pivot);
    return pivot;
}

void quicksort(int list[], int s_id, int e_id)
{
    if (s_id < e_id)
    {
        int p_id = partition(list, s_id, e_id);
        quicksort(list, s_id, p_id-1);
        quicksort(list, p_id+1, e_id);
    }
    return;
}