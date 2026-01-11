int least_rotation(string& s) {
    int n = s.length();
    vi f(2 * n, -1);
    int k = 0;
    for (int j = 1; j < 2 * n; j++) {
        int i = f[j - k - 1];
        while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) k = j - i - 1;
            i = f[i];
        }
        if (i == -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) k = j;
            f[j - k] = -1;
        }
        else {
            f[j - k] = i + 1;
        }
    }
    return k;
}
