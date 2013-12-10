#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *table[] = {
		".,1",		// keypad 1
		"ABC2",		// keypad 2
		"DEF3",		// keypad 3
		"GHI4",		// keypad 4
		"JKL5",		// keypad 5
		"MNO6",		// keypad 6
		"PQRS7",	// keypad 7
		"TUV8",		// keypad 8
		"WXYZ9",	// keypad 9
		"*+",		// keypad *
		" ",		// keypad 0
		"#"		// keypad #
		};

char *get_keypad_configuration(int c)
{
	int i, j, t;
	char tmp[2] = { 0 };
	char tx[3] = { 0 };
	char ret[5] = { 0 };

	for (i = 0; i < (sizeof(table) / sizeof(table[0])); i++) {
		for (j = 0; j < strlen(table[i]); j++)
			if (table[i][j] == c) {
				for (t = 0; t < j + 1; t++) {
					snprintf(tx, sizeof(tx), "%d", i + 1);
					tmp[0] = tx[0];
					strcat(ret, tmp);
				}
			}
	}

	return strdup(ret);
}

char *read_string(void)
{
	int c;
	char tmp[2] = { 0 };
	char ret[750] = { 0 }; // 160 should be OK for one SMS message, ~750 characters when split to multiple parts

	while ((c = getchar()) != '\n') {
		tmp[0] = c;
		strcat(ret, tmp);
	}

	return strdup(ret);
}

int main()
{
	int c;
	char *str = NULL;
	char ret[8192] = { 0 };

	printf("Enter string to be translated in uppercase: ");
	str = read_string();
	while (c = *str++) {
		char *tmp = get_keypad_configuration(c);
		strcat(ret, tmp);
		strcat(ret, " ");
		free(tmp); tmp = NULL;
	}

	printf("String translated to sequence %s\n", ret);
	return 0;
}

