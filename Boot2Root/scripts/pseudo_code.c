// ssh laurie@192.168.56.101
// Pass : 330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4

void read_six_numbers(char *s, int *i[]) {
	if (sscanf(s, "%d %d %d %d %d %d", *i[0], *i[1], *i[2], *i[3], *i[4], *i[5]) > 5)
		return ;
	explode_bomb();
}

// Solution : "Public speaking is very easy."
void phase_1(char *s) {
	if (!strings_not_equal(s, "Public speaking is very easy."))
		return ;
	explode_bomb();
}

// k => ebx
// l => eax
// 2 * 1 => 2
// 3 * 2 => 6
// 4 * 6 => 24
// 5 * 24 => 120
// 6 * 120 => 720
// Solution : "1 2 6 24 120 720"
void phase_2(char *s) {
	int i[6] = {0};
	read_six_numbers(s, &i);
	if (i[0] == 1) {
		for (int k = 1; k <= 5; k ++) {
			int l = (k + 1) * i[k - 1];
			if ((i[k]) != l)
				explode_bomb();
		}
	}
	explode_bomb();
}

// 8 Payloads possible (Voir switch case de 0 a 7)
// Solution : "1 b 214"
void phase_3(char *s) {
	int a;
	char b;
	int c;
	if (sscanf(s, "%d %c %d", c, b, a) > 2) {
		if (c > 7)
			explode_bomb();
		char bl;
		switch (c) {
			case 0:
				bl = 113; // q
				if (a != 777)
					explode_bomb();
				break;
			case 1:
				bl = 98; // b
				if (a != 214)
					explode_bomb();
				break;
			case 2:
				bl = 98; // b
				if (a != 755)
					explode_bomb();
				break;
			case 3:
				bl = 107; // k
				if (a != 251)
					explode_bomb();
				break;
			case 4:
				bl = 111; // o
				if (a != 160)
					explode_bomb();
				break;
			case 5:
				bl = 116; // t
				if (a != 458)
					explode_bomb();
				break;
			case 6:
				bl = 118; // v
				if (a != 780)
					explode_bomb();
				break;
			case 7:
				bl = 98; // b
				if (a != 524)
					explode_bomb();
				break;
		}
		if (bl == b)
			return ;
	}
	explode_bomb();
}

// a = 1 : b = 1
// a = 2 : b = 1 + 1 => 2
// a = 3 : b = 2 + 1 => 3
// a = 4 : b = 3 + 2 => 5
// a = 5 : b = 5 + 3 => 8
// a = 6 : b = 8 + 5 => 13
// a = 7 : b = 13 + 8 => 21
// a = 8 : b = 21 + 13 => 34
// a = 9 : b = 34 + 21 => 55 <=
// Solution : "9"
int func4(int a) {
	int b;
	if (a > 1)
		b = func4(a - 1) + func4(a - 2);
	else
		b = 1;
	return (b);
}

void phase_4(char *s) {
	int a;
	if (sscanf(s, "%d", a) > 1 || a <= 0 || func4(a) != 55)
		explode_bomb();
}

// g : f => o (0x6f)
// i : 0 => p (0x70)
// a : 5 => e (0x65)
// n : b => k (0x6b)
// t : d => m (0x6d)
// s : 1 => a (0x61)
// Solution : "opekma"
void phase_5(char *s) {
	char *data = "isrveawhobpnutfg";
	char buf[6] = {0};

	if (string_length(s) != 6)
		explode_bomb();
	for (int i = 0; i <= 5; i++) {
		char al = *(s + i) & 0xf; // Takes only the smallest hex digit from the string
		int eax = (int)al;
		al = *(data + eax); // Smallest hex digit is used as an offset in the given string
		buf[i] = al;
	}
	if (strings_not_equal(buf, "giants"))
		explode_bomb();
}

// Decompiled using ghidra
// Le readme donne le premier nombre a choisir
// Apres la première boucle, le nombre de permutations possible est de 5! = 120, je les teste donc une par une à la main et les trouve en environ 5 min.
// Solution : "4 2 6 3 1 5"
void phase_6(char *s) {
    int *pt1;
    int l;
    int *pt2;
    int *i2[6];
    int i[6];
    
    int *j = 0x804b26c; // 253
    read_six_numbers(s,i);
    int k = 0;
    do {
        if (6 < i[k]) {
            explode_bomb();
        }
        l = k + 1;
        if (l < 6) {
            do {
                if (i[k] == i[l]) {
                    explode_bomb();
                }
                l = l + 1;
            } while (l < 6);
        }
        k = k + 1;
    } while (k < 6); // Each number is unique and below 7, each number is also over 0 since the checks use an unsigned jump arg

    k = 0;
    do {
        l = 1;
        pt2 = (int *)j;
        if (1 < i[k]) {
            do {
                pt2 = (int *)pt2[2];
                l = l + 1;
            } while (l < i[k]);
        }
        i2[k] = pt2;
        k = k + 1;
    } while (k < 6);

    k = 1;
    pt2 = i2[0];
    do {
        pt1 = i2[k];
        *(int **)(pt2 + 2) = pt1;
        k = k + 1;
        pt2 = pt1;
    } while (k < 6);

    pt1[2] = 0;
    k = 0;
    do {
        if (*i2[0] < *(int *)i2[0][2]) {
            explode_bomb();
        }
        i2[0] = (int *)i2[0][2];
        k = k + 1;
    } while (k < 5);
}

// L'indice dans le README implique les solutions (si plusieurs) à choisir
// Le README nous demande d'utiliser les solutions de la bombe sans espace afin de se connecter au compte thor
// D'après le slack de 42, un poste précedement sur le forum 42 expliquait la necessité d'inverser les deux derniers nombres dans le mot de passe (probablement du a une coquille : https://app.slack.com/client/T039P7U66/C3QG85SG6/thread/C3QG85SG6-1581366878.418000)
// Ma première tentative utilisant "opekma" comme partie 5 ne connectant pas, je tente la seconde possibilité : "opekmq" (même offset)
// Mot de passe de thor : "Publicspeakingisveryeasy.126241207201b2149opekmq426135"

void main() {
	char *s;
	scanf("%s", &s);
	phase_1(s);
	scanf("%s", &s);
	phase_2(s);
	scanf("%s", &s);
	phase_3(s);
	scanf("%s", &s);
	phase_4(s);
	scanf("%s", &s);
	phase_5(s);
	scanf("%s", &s);
	phase_6(s);
}