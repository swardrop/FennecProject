
int mod (int a, int b)
{
    int ret = a % b;
    if(ret < 0)
    {
        ret+=b;
    }
    return ret;
}

long square (int a)
{
    long ret = a * a;
    return ret;
}

int absval(int val)
{
    if (val < 0)
        return -val;
    else return val;
}