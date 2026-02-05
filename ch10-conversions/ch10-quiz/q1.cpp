int main()
{
    int a { 5 }; // 1a - no conversion
    int b { 'a' }; // 1b - numeric promotion
    // int c { 5.4 }; // 1c - won't compile due to narrowing conversion
    int d { true }; // 1d - numeric promotion
    int e { static_cast<int>(5.4) }; // 1e - numeric conversion

    double f { 5.0f }; // 1f - numeric promotion
    double g { 5 }; // 1g - numeric conversion

    // Extra credit section
    long h { 5 }; // 1h - numeric conversion

    // float i { f }; // 1i (uses previously defined variable f) - won't compile due to narrowing conversion
    float j { 5.0 }; // 1j - numeric conversion

}