void fsaludo()
{
}

int fdup(int a)
{
    return a * 2;
}

float fprom(float x, float y)
{
    return (x + y) / 2.0;
}

int ffact(int n)
{
    if(n <= 1)
        return 1;
    return n * ffact(n - 1);
}

void fcopia(int v[], int &out)
{
    out = v[0];
}

int fcond(int val)
{
    while(val > 0)
    {
        val = val - 1;
    }
    return val;
}

void main()
{
    int a, b, res;
    float p;
    int arr[10];

    a = 5;
    b = 10;
    arr[0] = 42;

    fsaludo();

    res = fdup(a);
    res = fdup(fdup(b));
    res = ffact(a);

    p = fprom(12.5, 7.5);

    fcopia(arr, res);

    if(fdup(a) > 5)
    {
        cout << ffact(3);
    }

    res = fcond(res);
}
