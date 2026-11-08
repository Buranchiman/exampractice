#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	full_parenthesis(char *s)
{
	int	i;
	i = 0;
	while (s[i])
	{
		if (s[i] != '(' && s[i] != ')')
			return (0);
		i++;
	}
	return (1);
}

void recurse(const char *input, int pos, int open, int output_pos, char *output) {
    if (input[pos] == '\0') {
        if (open == 0) {
            output[output_pos] = '\0';
            printf("%s\n", output);
        }
        return;
    }

    char c = input[pos];

    if (c == '(') {
        // Option 1: skip it
        recurse(input, pos + 1, open, output_pos, output);

        // Option 2: keep it
        output[output_pos] = '(';
        recurse(input, pos + 1, open + 1, output_pos + 1, output);
    }
    else if (c == ')') {
        // Option 1: skip it
        recurse(input, pos + 1, open, output_pos, output);

        // Option 2: keep it, only if we can match a '('
        if (open > 0) {
            output[output_pos] = ')';
            recurse(input, pos + 1, open - 1, output_pos + 1, output);
        }
    }
    else {
        // Always keep non-parenthesis characters
        output[output_pos] = c;
        recurse(input, pos + 1, open, output_pos + 1, output);
    }
}

int	main(int arc, char **arv)
{
	if (arc != 2 || !full_parenthesis(arv[1]))
		return (1);
	char	buffer[strlen(arv[1]) + 1];
	recurse(arv[1], 0, 0, 0, buffer);
	return (0);
}
